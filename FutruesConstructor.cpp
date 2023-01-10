#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <experimental/filesystem>
#include "Modules.h"
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include "Functions.h"
using namespace std;
namespace fs = std::experimental::filesystem;


/***********INFO*******************/
//iteration should go backwards, hence back adjusting, look out for segmentation faults!
/*********************************/


// changing standard delimeter for ifstream
struct colon_is_space : std::ctype<char>
{
	colon_is_space() : std::ctype<char>(get_table()) {}
	static mask const* get_table()
	{
		static mask rc[table_size];
		rc[';'] = std::ctype_base::space;
		rc['\n'] = std::ctype_base::space;
		return &rc[0];
	}
};

//formatting date into sortable int format
int Functions::DateFormatter(string date)
{
	string Ndate = string() + date[6] + date[7] + date[8] + date[9] + date[3] + date[4] + date[0] + date[1];

	return stoi(Ndate);
}

int Functions::SymbolFormatter(string symbol)
{
	string Nsymbol;
	int endindex = symbol.size() - 1;

	switch (symbol[endindex])
	{
	case 'F':
		Nsymbol = string() + symbol[endindex - 4] + symbol[endindex - 3] + symbol[endindex - 2] + symbol[endindex - 1] + "01";
		break;

	case 'G':
		Nsymbol = string() + symbol[endindex - 4] + symbol[endindex - 3] + symbol[endindex - 2] + symbol[endindex - 1] + "02";
		break;

	case 'H':
		Nsymbol = string() + symbol[endindex - 4] + symbol[endindex - 3] + symbol[endindex - 2] + symbol[endindex - 1] + "03";
		break;

	case 'J':
		Nsymbol = string() + symbol[endindex - 4] + symbol[endindex - 3] + symbol[endindex - 2] + symbol[endindex - 1] + "04";
		break;

	case 'K':
		Nsymbol = string() + symbol[endindex - 4] + symbol[endindex - 3] + symbol[endindex - 2] + symbol[endindex - 1] + "05";
		break;

	case 'M':
		Nsymbol = string() + symbol[endindex - 4] + symbol[endindex - 3] + symbol[endindex - 2] + symbol[endindex - 1] + "06";
		break;

	case 'N':
		Nsymbol = string() + symbol[endindex - 4] + symbol[endindex - 3] + symbol[endindex - 2] + symbol[endindex - 1] + "07";
		break;

	case 'Q':
		Nsymbol = string() + symbol[endindex - 4] + symbol[endindex - 3] + symbol[endindex - 2] + symbol[endindex - 1] + "08";
		break;

	case 'U':
		Nsymbol = string() + symbol[endindex - 4] + symbol[endindex - 3] + symbol[endindex - 2] + symbol[endindex - 1] + "09";
		break;

	case 'V':
		Nsymbol = string() + symbol[endindex - 4] + symbol[endindex - 3] + symbol[endindex - 2] + symbol[endindex - 1] + "10";
		break;

	case 'X':
		Nsymbol = string() + symbol[endindex - 4] + symbol[endindex - 3] + symbol[endindex - 2] + symbol[endindex - 1] + "11";
		break;

	case 'Z':
		Nsymbol = string() + symbol[endindex - 4] + symbol[endindex - 3] + symbol[endindex - 2] + symbol[endindex - 1] + "12";
		break;

	default:
		break;
	}

	return stoi(Nsymbol);

}

bool Functions::sortcol(const vector<double>& v1,const vector<double>& v2)
{
	return v1[0] < v2[0];
}

void Modules::SubroutineFuturesConstructor()
{
	std::cout << "FUTURESCONSTRUCTOR" << endl;
	std::cout << "Please select type in Folder Destination of Futures contracts or return to main Menu with 3 \n \
			Sample: F:/Users/david/Desktop/The_Domain/Library/PremiumData/CONTRACTS/ \n \
			Target folder should only consist of one future" << endl;

	string Path = "SET HERE YOUR FILEPATH";

	

	if (Path != "3")
	{
		std::cout << "Construction starts" << endl;

		string date;
		string Open;
		string High;
		string Low;
		string close;
		string volume;
		string OI;
		string symbol;
		long counter = 0;
		ifstream theFile;

		for (const auto& entry : fs::directory_iterator(Path)) 
		{
			//start Subroutine here
			//First we need the size of the array

			string Path2 = entry.path().string();

			for (const auto& entry : fs::directory_iterator(Path2))
			{
				string filelocation = entry.path().string();
				theFile.open(filelocation);


				if (theFile.is_open())
				{
					while (theFile >> symbol >> date >> Open >> High >> Low >> close >> volume >> OI)
					{
						//counting each action of each line in Folder
						counter++;

						///std::cout << counter << endl;
					}

					theFile.close();
				}
			}

			counter = counter * 9;

			//Now we create the Array with the appropriate size 
			vector<vector<double> > Arr(counter);

			int size = (int)Arr.size() + 1;

			for (int i = 0; i < counter; i++)
			{
				// declare the i-th row to size of column, I think multiplying with N+1 because putting 2d into one (n+1 is for length of 1d)
				Arr[i] = vector<double>(8);

				for (int j = 0; j < 8; j++)
				{
					Arr[i][j] = 0;
				}

			}

			counter = 0;
			string test;

			theFile.imbue(locale(theFile.getloc(), new colon_is_space));

			//Now filling array with values 
			for (const auto& entry : fs::directory_iterator(Path2))
			{
				string filelocation = entry.path().string();
				theFile.open(filelocation);

				if (theFile.is_open())
				{
					while (theFile >> symbol >> date >> Open >> High >> Low >> close >> volume >> OI)
					{
						Arr[counter][0] = Functions::DateFormatter(date);
						Arr[counter][1] = Functions::SymbolFormatter(symbol);
						Arr[counter][2] = atof(Open.c_str());
						Arr[counter][3] = atof(High.c_str());
						Arr[counter][4] = atof(Low.c_str());
						Arr[counter][5] = atof(close.c_str());
						Arr[counter][6] = atof(volume.c_str());
						Arr[counter][7] = atof(OI.c_str());

						///Test code
						/*std::cout << Arr[counter][0] << ";" << Arr[counter][1] << ";" << Arr[counter][2] << ";" << Arr[counter][3] << ";" << Arr[counter][4] << ";" << Arr[counter][5] << ";"
							<< Arr[counter][6] << ";" << Arr[counter][7] << endl;*/


						counter++;
					}

					theFile.close();
				}
			}

			std::cout << "storage successfull" << endl;


			//sorting arry for analysis
			std::sort(Arr.rbegin(), Arr.rend(), Functions::sortcol);

			///testcode
			/**for (int i = 0; i < counter; i++)
			{
				int date = (int)Arr[i][0];
				cout << Arr[i][0] << ";		" << Arr[i][1] << ";		" << Arr[i][2] << ";		" << Arr[i][3] << ";		" << Arr[i][4] << ";		" << Arr[i][5] << ";		"
					<< Arr[i][6] << ";		" << Arr[i][7] << ";		" << date << endl;
			}**/

			Path2.erase(Path2.begin(), Path2.begin()+Path.length());

			
			for (int i = 0; i < (int)Path2.length() ; i++)
			{
				if (Path2[i] == ' ')
				{
					Path2[i] = '_';
				}
			}

			std::cout << "Path2 of M1 is : " << Path2 << endl;


			ofstream OAsciiFile;
			string Output = "/home/Dave/Desktop/Test/Merged_" + Path2 + ".txt";

			//defining criteria
			short daysVol = 3;
			short daysVolc = 0;
			double Offset = 0;
			double prevsettl;
			double currsettl;
			int currcontract = 0;

			OAsciiFile.open(Output);


			//back asjusting panama- method- nearest contract
			if (OAsciiFile.is_open())
			{
				/*checking criteria: if only next contract fullfills those criteria, then take quotes from it */
				for (int i = 1; i < counter; i++)
				{
					/*int date = (int)Arr[i][0];
					cout << Arr[i][0] << ";		" << Arr[i][1] << ";		" << Arr[i][2] << ";		" << Arr[i][3] << ";		" << Arr[i][4] << ";		" << Arr[i][5] << ";		"
						<< Arr[i][6] << ";		" << Arr[i][7] << ";		" << date << endl;*/

					if (Arr[i][0] < Arr[i - 1][0]) //in this case a new day starts
					{
						int Ncontracts = 1;
						//we need to know how much contracts there are 
						while (Arr[i][0] == Arr[i + Ncontracts][0])
						{
							Ncontracts++;
						}

						//i += Ncontracts-1;

						int maxVol = 0;

						for (int n = 0; n < Ncontracts; n++)
						{
							if (Arr[i + n][6] > maxVol)
							{
								maxVol = Arr[i + n][6];
							}
						}

						//for first time& pre-analysis
						for (int n = 0; n < Ncontracts; n++)
						{
							if (currcontract == 0 && Arr[i + n][6] == maxVol)
							{
								currcontract = Arr[i + n][1];
							}

							else if (Arr[i + n][6] == maxVol && Arr[i + n][1] < currcontract) //Finding the current contract
							{
								daysVolc++;
								if (daysVolc == daysVol)
								{
									daysVolc = 0;
									currcontract = Arr[i + n][1];
									Offset = prevsettl - Arr[i + n][5];
									///cout << "prevsettl is : " << prevsettl << " and currsettl is : " << Arr[i + n][5] << endl;
									///cout << "***************************rollover**********************************" << endl;
								}
							}
						}

						//collecting quotes from the current contract
						for (int n = 0; n < Ncontracts; n++)
						{
							if (Arr[i + n][1] == currcontract)
							{
								
								string date = to_string(Arr[i + n][0]);
								date = string() + date[6] + date[7] + date[4] + date[5] + date[0] + date[1] + date[2] + date[3];
								date.insert(date.begin() + 2, '.');
								date.insert(date.begin() + 5, '.');
								///cout << Offset << ";" << Arr[i + n][1] << endl;								

								OAsciiFile << /*Arr[i + n][1]<< ";" <<*/ Path2 + "_M1" << ";" << date << ";" << Arr[i + n][2] + Offset << ";" << Arr[i + n][3] + Offset << ";" << Arr[i + n][4] + Offset << ";" << Arr[i + n][5] + Offset << ";" << fixed << setprecision(0)<< to_string((long)Arr[i + n][6]) << ";" << to_string((long)Arr[i + n][7])<< setprecision(4) << endl;
								prevsettl = Arr[i + n][5]+ Offset;

								///cout << "presettls is : " << prevsettl << endl;
							}
						}


					}

				}
			}

			OAsciiFile.close();

			std::cout << " Do you want to merge a spread pair? 1= yes " << endl;

			int A = 1;

			///std::cin >> A;

			//**********************************************second merge*****************************************
			if (A == 1)
			{
				std::cout << "Please enter  n>0 of nearest contract: " << endl;

				int N = 1;
				///std::cin >> N;


				std::cout << "Path2 of M2 is : " << Path2 << endl;

				ofstream OAsciiFile;
				string Output = "/home/Dave/Desktop/Test/Merged2_" + Path2 + ".txt";

				//defining criteria
				short nearestConstract = 0;
				short daysVol = 3;
				short daysVolc = 0;
				double Offset = 0;
				double prevsettl;
				int change = 0;
				int currcontract = 0;

				OAsciiFile.open(Output);


				//back asjusting panama- method- nearest contract
				if (OAsciiFile.is_open())
				{
					/*checking criteria: if only next contract fullfills those criteria, then take quotes from it */
					for (int i = 1; i < counter; i++)
					{
						/*int date = (int)Arr[i][0];
						cout << Arr[i][0] << ";		" << Arr[i][1] << ";		" << Arr[i][2] << ";		" << Arr[i][3] << ";		" << Arr[i][4] << ";		" << Arr[i][5] << ";		"
							<< Arr[i][6] << ";		" << Arr[i][7] << ";		" << date << endl;*/

						if (Arr[i][0] < Arr[i - 1][0]) //in this case a new day starts
						{
							int Ncontracts = 1;
							//we need to know how much contracts there are 
							while (Arr[i][0] == Arr[i + Ncontracts][0])
							{
								Ncontracts++;
							}

							//i += Ncontracts - 2;
							int maxVol = 0;

							for (int n = 0; n < Ncontracts; n++)
							{
								if (Arr[i + n][6] > maxVol)
								{
									maxVol = Arr[i + n][6];
								}
							}

							//for first time& pre-analysis
							for (int n = 0; n < Ncontracts; n++)
							{
								if (currcontract == 0 && Arr[i + n][6] == maxVol)
								{
									currcontract = Arr[i + n][1];
								}

								else if (Arr[i + n][6] == maxVol && Arr[i + n][1] < currcontract) //Finding the current contract
								{
									daysVolc++;
									if (daysVolc == daysVol)
									{
										daysVolc = 0;
										nearestConstract = (currcontract - Arr[i + n][1]) * N;
										currcontract = Arr[i + n][1];
										change = 1;
									}
								}
							}

							//collecting quotes from the current contract
							for (int n = 0; n < Ncontracts; n++)
							{
								if (Arr[i + n][1] == currcontract + nearestConstract)
								{
									if (change == 1)
									{
										Offset = prevsettl - Arr[i + n][5];
										change = 0;
										///cout << "prevsettl is : " << prevsettl << " and currsettl is : " << Arr[i + n][5] << endl;
										///cout << "***************************rollover**********************************" << endl;
									}

									
									string date = to_string(Arr[i + n][0]);
									date = string() + date[6] + date[7] + date[4] + date[5] + date[0] + date[1] + date[2] + date[3];
									date.insert(date.begin() + 2, '.');
									date.insert(date.begin() + 5, '.');

									///cout << Offset << ";" << Arr[i + n][1] << endl;

									OAsciiFile << /*Arr[i + n][1]<<";"<<*/ Path2 + "_M2" << ";" << date << ";" << Arr[i + n][2] + Offset << ";" << Arr[i + n][3] + Offset << ";" << Arr[i + n][4] + Offset << ";" << Arr[i + n][5] + Offset << ";" << fixed << setprecision(0) << Arr[i + n][6] << ";" << Arr[i + n][7] << setprecision(4) <<endl;
									prevsettl = Arr[i + n][5]+Offset;

									///cout << "presettls is : " << prevsettl << endl;

								}
							}


						}


					}
				}

				OAsciiFile.close();


			}
		}



		//exit options
		std::cout << "Merging finished! please proceed with 0 to return to main menu" << endl;

		int A;

		std::cin >> A;

		if (A == 0) { Modules::SubroutineMainMenu();}


	}

	else
	{
		Modules::SubroutineMainMenu();
	}

}

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
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;
namespace fs = std::experimental::filesystem;

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

//***************************NOTES***************************************//
//add Module for optimized construction based on volume and expiry dates //
//be cautious to make everything in one slice (no usage of filtered sprds//



void Modules::SubroutineSpreadsConstructor()
{
	std::cout << "**********SPREADCONSTRUCTOR********"<< endl;
	std::cout << "Please select type in Folder Destination of Futures contracts or return to main Menu with 3 \n \
			Sample: F:/Users/david/Desktop/The_Domain/Library/PremiumData/CONTRACTS/ \n \
			Target folder should only consist of one future" << endl;

	string Path = "/media/Dave/Volume/Futures2020/ASCII/";
	
	//distinction between raw and optimized
	std::cout << "Select construction mode: 1= raw; 2= optimized; 3= VolSplit; 4= Floating"<< endl;
	
	int D;
	
	std::cin >>D;
	
	switch (D)
	{
		case 1:
		{
			string Dirr = "/media/usr/Volume/Futures2020/ASCII_SPREADS_Raw/";
			mkdir(Dirr.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			break;
		}
		
		case 2:
		{
			string Dirr2 = "/media/usr/Volume/Futures2020/ASCII_SPREADS_Opt/";
			mkdir(Dirr2.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			break;
		}
		
		case 3:
		{
			string Dirr3 = "/media/usr/Volume/Futures2020/ASCII_SPREADS_VolSplit/";
			mkdir(Dirr3.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			break;
		}
		
		case 4:
		{
			string Dir4 = "/media/usr/Volume/Futures2020/ASCII_SPREADS_Floating/";
			mkdir(Dir4.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			break;
		}
		
		default:
		{
			cout << "invalid input!"<< endl;
			Modules::SubroutineSpreadsConstructor();
			break;
		}			
	}

	
	//At first everything is the same for both
	if (Path != "0")
	{
		std::cout<<"Construction starts"<< endl;
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
		
		for(const auto& entry : fs::directory_iterator(Path))
		{
			string Path2 = entry.path().string();
			cout << Path2 << endl;

			
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
			
			//Now we create the vector 
			vector<vector<double>> Arr(counter);
			for(int i = 0; i < counter; i++)
			{
				Arr[i] = vector<double>(8);
				
				for(int j = 0; j < 8; j++)
				{
					Arr[i][j] = 0;
				}
			}
			
			counter = 0;
			string test;
			
			theFile.imbue(locale(theFile.getloc(), new colon_is_space));
			
			for(const auto& entry : fs::directory_iterator(Path2))
			{
				string filelocation = entry.path().string();
				theFile.open(filelocation);
				
				if(theFile.is_open())
				{
					while(theFile >> symbol >> date >> Open >> High >> Low >> close >> volume >> OI)
					{
						Arr[counter][0] = Functions::DateFormatter(date);
						Arr[counter][1] = Functions::SymbolFormatter(symbol);
						Arr[counter][2] = atof(Open.c_str());
						Arr[counter][3] = atof(High.c_str());
						Arr[counter][4] = atof(Low.c_str());
						Arr[counter][5] = atof(close.c_str());
						Arr[counter][6] = atof(volume.c_str());
						Arr[counter][7] = atof(OI.c_str());
						
						counter++;
						
					}
					
					theFile.close();
					
				}
				
			}
			
			std::cout << "storage successful" << endl;
			
			//Sorting Array first by date and then by contracts, thus creating forward curve
			std::sort(Arr.rbegin(),Arr.rend());
			std::sort(Arr[1].rbegin(),Arr[1].rend());
			//noob sort
			
			///testcode
			for (int i = 0; i < counter; i++)
			{
				int date = (double)Arr[i][0];
				cout <<std::fixed<< Arr[i][0] << ";		" << Arr[i][1] << ";		" << Arr[i][2] << ";		" << Arr[i][3] << ";		" << Arr[i][4] << ";		" << Arr[i][5] << ";		"
					<< Arr[i][6] << ";		" << Arr[i][7] << ";		" << date << endl;
			}
			
			short X;
			std::cin>>X;
			
			Path2.erase(Path2.begin(), Path2.begin()+Path.length());
			
			for (int i = 0; i < (int)Path2.length() ; i++)
			{
				if(Path2[i] == ' ')
				{
					Path2[i] = '_';
				}
			}	
			
			//Raw mode
			switch(D)
			{
				case 1:
				{
					string Dir = "/media/usr/Volume/Futures2020/ASCII_SPREADS_Raw/"+Path2;
			
					mkdir(Dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
					
					int k=0;
					//Other way aroung because of sorting order
					for(int i = counter; i>5; i--)
					{
						//When a new Day starts, analyze the forward curve
						if(Arr[i][0] > Arr[i+1][0])
						{
							k= 0;
							//subtracting n+1 from current contract and creating corresponding ASCII-file
							while (Arr[i-k][0]==Arr[i-k-1][0] && i-k-1 >= 5)
							{
								///cout <<"Breakpoint_Test"<< endl;

								string ASCII_name = Dir+'/'+Path2+to_string((int)Arr[i-k][1])+"-"+to_string((int)Arr[i-k-1][1])+".txt";
								ofstream Output;
								Output.open(ASCII_name,ios::app);
								
								if(Output.is_open())
								{							
									string date = to_string(Arr[i-k][0]);
									date = string() + date[6] + date[7] + date[4] + date[5] + date[0]+ date[1] + date[2] + date[3];
									date.insert(date.begin() + 2, '.');
									date.insert(date.begin() + 5, '.');
									
									Output << Path2+"_"+to_string((int)Arr[i-k][1])+"_"+to_string((int)Arr[i-k-1][1])<< ";"<<date <<";"<<Arr[i-k-1][2] - Arr[i-k][2]<<";"<<Arr[i-k-1][3] - Arr[i-k][3]<<";"<<
									Arr[i-k-1][4]-Arr[i-k][4]<<";"<<Arr[i-k-1][5]-Arr[i-k][5]<<";"<<Arr[i-k-1][6]+Arr[i-k][6]<<";"<<Arr[i-k-1][7]+Arr[i-k][7]<< endl;
								}
								
								Output.close();
								k++;
							}	
							
						}
					}				
					
					Arr.clear();//You should erase here
					cout<< "Arr is cleared"<< endl;
					break;
					
				}
				
				//Optimized mode with regard to expiry and volume
				case 2:
				{
					int VolMin = 200;
					//state must be concrete for each pair, so how do we achieve this?
					vector<vector<long>> states(2);								
					for(int i = 0; i < (int)states.size(); i++)
					{
						//each column gets one row
						states[i] = vector<long>(1);
						//initializing Matrix 
						for(int j = 0; j < (int)states[0].size(); j++)
						{
							Arr[i][j] = 0;
							///std::cout<<Arr[i][j]<<": i is :"<<i<<" j is "<<j<< endl;
						}
					}
					
					//NOTE: first col is spread name second col is state
					
					string Dir = "/media/Dave/Volume/Futures2020/ASCII_SPREADS_Opt/"+Path2;
			
					mkdir(Dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
					int index;
					int k=0;
					//Other way aroung because of sorting order
					for(int i = counter; i>5; i--)
					{
						//When a new Day starts, analyze the forward curve**************************************************
						if(Arr[i][0] > Arr[i+1][0])
						{
							string Compare = to_string(states[0][1]);
							Compare.erase(Compare.begin()+6,Compare.end());
							///std::cout<<"Oldest spread: "<<Compare<<endl;
							//delete items from matrix, if length is too long, the first ones should be expired (assuming array was really sorted so each spread is in future)
							///std::cout<<Arr[i][1]<<" > "<<stoi(Compare)<<"→→→→→→→→→→→→→→→→→→→→→→→→→→→→"<<endl;
							if((int)Arr[i][1] > stoi(Compare) && stoi(Compare) != 0 && (int)states[0].size() > 1)
							{
								for(int k=0;k < 2;k++)
								{
									states[k].erase(states[k].begin());
									///std::cout<<" item was deleted "<<endl;
								}
							}
							
							///std::cout<<"**********************************************************************************************New Forwardcurve*********************************************************************From Date: "<<(int)(double)Arr[i][0]<<endl;
							k= 0;
							//subtracting n+1 from current contract and creating corresponding ASCII-file, checking whether we are still in the same day
							while (Arr[i-k][0]==Arr[i-k-1][0] && i-k-1 >= 5)
							{
								///std::cout<<(long)Arr[i-k][1]<<": first leg "<<(long)Arr[i-k-1][1]<<": second leg "<<endl;
								string ASCII_name2 = to_string((int)Arr[i-k][1])+to_string((int)Arr[i-k-1][1]);
								///std::cout<<ASCII_name2<<" is ASCII_name2 "<<endl;
								
								int forsize = (int)states[0].size();
								
								//checking if current spread is in matrix if yes break if not insert
								///std::cout<<(int)states[0].size()<<" is size of states"<<endl;
								for( int n = 0; n < forsize; n++)
								{
									///std::cout<<states[0][n]<<" is Spread of n ;"<<states[1][n]<<" is state "<<endl;
									if (states[0][n] == stol(ASCII_name2))
									{
										index = n;
										///std::cout<<index<<" is index"<<endl;
										break;
									}
									
									if (n == (int)states[0].size()-1)
									{
										///std::cout<<stol(ASCII_name2)<<" this should be stored as name added"<<endl;
										states[0].push_back(stol(ASCII_name2)); //push and enter ascii name and status
										states[1].push_back(0);
										index = (int)states[0].size()-1; //because the current spread should be the last one in Matrix
										///std::cout<<states[0][(int)states[0].size()-1]<<" is Name added"<<endl;
										///std::cout<<states[1][(int)states[1].size()-1]<<" is state added"<<endl;
									}
								}					
								
								
								//defining and checking for volume and expiry conditions, technically only volume should be sufficient
								//First time conditions reached
								///std::cout<<Arr[i-k][6]<<" > "<< VolMin+300<<" && "<< Arr[i-k-1][6]<<" > "<<VolMin+300<<" && "<<states[1][index]<<" < 3 && "<<states[0][index]<<" == "<<stol(ASCII_name2)<<endl;
								if (Arr[i-k][6] > VolMin+300 && Arr[i-k-1][6] > VolMin+300 && states[1][index] < 3 && states[0][index] == stol(ASCII_name2))
								{
									states[1][index] += 1;
									if(states[1][index] == 3)
									{
										///std::cout<<"Spread is activated------------------------------------------------------------------------------------------------------------------------------"<<endl;
									}
								}
								/*
								std::cout<<Arr[i-k][6]<<" < "<< VolMin<<" || "<< Arr[i-k-1][6]<<" < "<<VolMin<<" && "<<states[1][index]<<" >= 3 && "<<states[1][index]<<" <= 6 "<<states[0][index]<<" == "<<stol(ASCII_name2)<<endl;
								//kick out
								if ((Arr[i-k][6] < VolMin || Arr[i-k-1][6] < VolMin) && states[1][index] >= 3 && states[1][index] <= 6 && states[0][index] == stol(ASCII_name2))
								{
									states[1][index] += 1;
									if(states[1][index] == 6)
									{
										std::cout<<"Spread expired///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;
									}
								}
								*/
								//Generate ASCII-files if state of the stpread is open
								///std::cout<<states[1][index]<<" states[1][index] "<<states[0][index]<<" states[0][index] "<<ASCII_name2<<" Spread name "<<Arr[i-k][1]<<": first leg"<<Arr[i-k-1][1]<<": second leg "<<endl;
								if (states[1][index] >= 3 && states[1][index] <= 6)
								{
									string ASCII_name = Dir+'/'+Path2+to_string((int)Arr[i-k][1])+"-"+to_string((int)Arr[i-k-1][1])+".txt";
									ofstream Output;
									Output.open(ASCII_name,ios::app);
									
									if(Output.is_open())
									{
										///std::cout<<"............................................printing.............................................................."<<ASCII_name<<endl;
										string date = to_string(Arr[i-k][0]);
										date = string() + date[6] + date[7] + date[4] + date[5] + date[0]+ date[1] + date[2] + date[3];
										date.insert(date.begin() + 2, '.');
										date.insert(date.begin() + 5, '.');
										
										Output << Path2+"_"+to_string((int)Arr[i-k][1])+"_"+to_string((int)Arr[i-k-1][1])<< ";"<<date <<";"<<Arr[i-k-1][2] - Arr[i-k][2]<<";"<<Arr[i-k-1][3] - Arr[i-k][3]<<";"<<
										Arr[i-k-1][4]-Arr[i-k][4]<<";"<<Arr[i-k-1][5]-Arr[i-k][5]<<";"<<(long)Arr[i-k][6]<<";"<<(long)Arr[i-k-1][6]<<";"<<(long)Arr[i-k][7]<<";"<<(long)Arr[i-k-1][7]<< endl;
									}
									
									Output.close();
								}					
								/*short A;
								cout<<"Brakepoint! type 1 to kill"<<endl;
								cin>>A;
								switch(A)
								{
									case 1:
									{
										Modules::SubroutineMainMenu();
										exit(EXIT_SUCCESS);
										break;
									}
									default:
									break;
								}*/
								k++;
							}	
							
						}
					}				
					
					Arr.clear();
					cout<< "Arr is cleared"<< endl;
					break;
				}
				//volSplit+RET
				case 3:
				{
					string Dir = "/media/usr/Volume/Futures2020/ASCII_SPREADS_VolSplit/"+Path2;
			
					mkdir(Dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
					
					int k=0;
					//Other way aroung because of sorting order
					for(int i = counter; i>5; i--)
					{
						//When a new Day starts, analyze the forward curve
						if(Arr[i][0] > Arr[i+1][0])
						{
							k= 0;
							//subtracting n+1 from current contract and creating corresponding ASCII-file
							while (Arr[i-k][0]==Arr[i-k-1][0] && i-k-1 >= 5)
							{
								///cout <<"Breakpoint_Test"<< endl;

								string ASCII_name = Dir+'/'+Path2+to_string((int)Arr[i-k][1])+"-"+to_string((int)Arr[i-k-1][1])+".txt";
								ofstream Output;
								Output.open(ASCII_name,ios::app);
								
								if(Output.is_open())
								{							
									string date = to_string(Arr[i-k][0]);
									date = string() + date[6] + date[7] + date[4] + date[5] + date[0]+ date[1] + date[2] + date[3];
									date.insert(date.begin() + 2, '.');
									date.insert(date.begin() + 5, '.');
									
									Output << Path2+"_"+to_string((int)Arr[i-k][1])+"_"+to_string((int)Arr[i-k-1][1])<< ";"<<date <<";"<<Arr[i-k-1][2] - Arr[i-k][2]<<";"<<Arr[i-k-1][3] - Arr[i-k][3]<<";"<<
									Arr[i-k-1][4]-Arr[i-k][4]<<";"<<Arr[i-k-1][5]-Arr[i-k][5]<<";"<<(long)Arr[i-k][6]<<";"<<(long)Arr[i-k-1][6]<<";"<<(long)Arr[i-k][7]<<";"<<(long)Arr[i-k-1][7]<< endl;
								}
								
								Output.close();
								k++;
							}	
							
						}
					}				
					
					Arr.clear();//You should erase here
					cout<< "Arr is cleared"<< endl;
					break;
					
				}
				//floating Spreads
				case 4:
				{
					int Ncontracts = 0;
					int maxvol = 0;
					int oldmaxvol = 0;
					double CurrContr = 0;
					int state = 0;
					int newname = 0;
					int currisin = 0;
					
					string Dir = "/media/usr/Volume/Futures2020/ASCII_SPREADS_Floating/"+Path2;
					mkdir(Dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
					
					int k=0;
					//Other way aroung because of sorting order
					for(int i = counter; i>5; i--)
					{
						//When a new Day starts, analyze the forward curve
						if(Arr[i][0] > Arr[i+1][0])
						{
							std::cout<<"----------------New Curve ahead----------------"<<Arr[i][0]<<endl;
							
							Ncontracts = 0;
							maxvol = 0;
							k= 0;
							currisin = 0;
							while(Arr[i-Ncontracts][0]==Arr[i-Ncontracts-1][0] && i-Ncontracts-1 >= 5)
							{
								std::cout<<" vol is : "<<Arr[i-Ncontracts][6]<<" and maxvol is : "<<maxvol<<endl;
								
								if(Arr[i-Ncontracts][6] > maxvol)
								{
									maxvol = Arr[i-Ncontracts][6];
									newname = Arr[i-Ncontracts][1];
									
								}
								
								if(CurrContr == Arr[i-Ncontracts][1])
								{
									currisin = 1;
								}
								
								Ncontracts++;
							}
							Ncontracts = 0;
							
							std::cout<<" state is : "<<state<<endl;
							if(state == 0 || currisin == 0)
							{
								std::cout<<" *******CurrContr is : "<<Arr[i-Ncontracts][1]<<endl;
								std::cout<<" *******oldmaxvol is : "<<maxvol<<endl;
								CurrContr = newname;
								oldmaxvol = maxvol;
								state = 3;
							}
								
							std::cout<<" oldmaxvol "<<oldmaxvol<<" < "<<" maxvol : "<<maxvol<<" maxvol/2 "<<(int)(maxvol/2)<<endl;
							if(oldmaxvol < (int)(maxvol/2))
							{
								std::cout<<" state should be -- : "<<state<<endl;
								state--;
							}
							
							
							//subtracting n+1 from current contract and creating corresponding ASCII-file
							while (Arr[i-k][0]==Arr[i-k-1][0] && i-k-1 >= 5)
							{								
								//Only outputting if contract is the currentmaxvol
								if(Arr[i-k][1] == CurrContr)
								{
									///cout <<"Breakpoint_Test"<< endl;

									string ASCII_name = Dir+'/'+Path2+to_string((int)Arr[i-k][1])+"-"+to_string((int)Arr[i-k-1][1])+".txt";
									ofstream Output;
									Output.open(ASCII_name,ios::app);
									
									if(Output.is_open())
									{							
										string date = to_string(Arr[i-k][0]);
										date = string() + date[6] + date[7] + date[4] + date[5] + date[0]+ date[1] + date[2] + date[3];
										date.insert(date.begin() + 2, '.');
										date.insert(date.begin() + 5, '.');
										
										Output << Path2+"_"+to_string((int)Arr[i-k][1])+"_"+to_string((int)Arr[i-k-1][1])<< ";"<<date <<";"<<Arr[i-k-1][2] - Arr[i-k][2]<<";"<<Arr[i-k-1][3] - Arr[i-k][3]<<";"<<
										Arr[i-k-1][4]-Arr[i-k][4]<<";"<<Arr[i-k-1][5]-Arr[i-k][5]<<";"<<(long)Arr[i-k][6]<<";"<<(long)Arr[i-k-1][6]<<";"<<(long)Arr[i-k][7]<<";"<<(long)Arr[i-k-1][7]<< endl;
									}
									Output.close();
								}						
								
								k++;
							}	
							
						}
					}				
					
					Arr.clear();//You should erase here
					cout<< "Arr is cleared"<< endl;
					break;
				}
				
				default:
				{
					Modules::SubroutineMainMenu();
					break;
				}
				
			}
			
			
		}
		
		
	}
	
	else 
	{
		Modules::SubroutineMainMenu();
	}
}

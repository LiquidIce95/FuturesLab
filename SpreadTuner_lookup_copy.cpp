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


void Modules::SubroutineSpreadTuner()
{
	std::cout<<"********SPREADTUNER*************"<<endl;
	
	
	short B;
	
	std::cin>>B;
	
	switch(B)
	{
		case 1:
		{
			if(Path != "0")
			{
				string Path = "/media/usr/Volume/Futures2020/ASCII_CalenderSpreadsSelected/";
				
				string Date;
				string Spread;
				string Open;
				string High;
				string Low;
				string Close;
				string Vol1;
				string Vol2;
				string Oi1;
				string Oi2;
				long Tradingdays = 0;
				ifstream theFile;
				ofstream output;
				string Path2;
				string Path3;
				string filelocation;
				
				theFile.imbue(locale(theFile.getloc(), new colon_is_space));
				//three iterations because of the subfolders
				for(const auto& entry : fs::directory_iterator(Path))
				{
					Path2 = entry.path().string();
					
					std::cout<<Path2<<endl;
					for(const auto& entry : fs::directory_iterator(Path2))
					{
						Path3 = entry.path().string();
						
						std::cout<<Path3<<endl;
						for(const auto& entry : fs::directory_iterator(Path3))
						{
							vector<vector<string>> Arr(10); //columns
							for(int i = 0; i < (int)Arr.size(); i++)
							{
								Arr[i] = vector<string>(10); //Rows
									
								for(int n = 0; n<(int)Arr[0].size(); n++)
								{
									Arr[i][n] = "0";
								}
							}
							
							filelocation = entry.path().string();
							theFile.open(filelocation);
							
							if(theFile.is_open())
							{						
								while(theFile >>Spread>>Date>>Open>>High>>Low>>Close>>Vol1>>Vol2>>Oi1>>Oi2)
								{
									Arr[0][Tradingdays] = Spread.c_str();
									Arr[1][Tradingdays] = Date.c_str();
									Arr[2][Tradingdays] = Open.c_str();
									Arr[3][Tradingdays] = High.c_str();
									Arr[4][Tradingdays] = Low.c_str();
									Arr[5][Tradingdays] = Vol1.c_str();
									Arr[6][Tradingdays] = Vol2.c_str();
									Arr[7][Tradingdays] = Oi1.c_str();
									Arr[8][Tradingdays] = Oi2.c_str();
									
									Tradingdays++;
									
									if(Tradingdays>=(int)Arr[0].size())
									{
										Arr[0].push_back("0");
										Arr[1].push_back("0");
										Arr[2].push_back("0");
										Arr[3].push_back("0");
										Arr[4].push_back("0");
										Arr[5].push_back("0");
										Arr[6].push_back("0");
										Arr[7].push_back("0");
										Arr[8].push_back("0");
										Arr[9].push_back("0");							
										
									}
								}
								
								for(int n = 0; n < Tradingdays; n++)
								{
									Arr[9][n] = to_string(Tradingdays-n);
								}						
								
								theFile.close();						
							}
							//Assign Path2 and 3 to seperate variables because they mess up with the loop
							std::cout<<"-------Output-------"<<endl;
							
							string filelocationCopy = filelocation;
							string Path2Copy = Path2;
							string Path3Copy = Path3;
							string Dir = "/media/usr/Volume/Futures2020/ASCII_CalendarSpreadsTuned/";
							
							filelocationCopy.erase(filelocationCopy.begin(),filelocationCopy.begin()+Path3Copy.length()+1);
							
							string OutputFile = filelocationCopy;
							
							Path3Copy.erase(Path3Copy.begin(), Path3Copy.begin()+Path2Copy.length());
							
							string Dir2 = Path3Copy; 	std::cout<<Dir2<<endl;
							
							Path2Copy.erase(Path2Copy.begin(),Path2Copy.begin()+Path.length());
							
							Dir = Dir+Path2Copy; 	std::cout<<Dir<<endl;
							
							Dir2 = Dir+Dir2; 	std::cout<<Dir2<<endl;
							
							mkdir(Dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
							mkdir(Dir2.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
							
							OutputFile = Dir2+"/"+OutputFile; std::cout<<OutputFile<<endl;
							
							output.open(OutputFile, ios::app);
							
							for(int i = 0; i < Tradingdays-12; i++)
							{						
								if(output.is_open())
								{
									output		<<Arr[0][i]<<";"
												<<Arr[1][i]<<";"
												<<Arr[2][i]<<";"
												<<Arr[3][i]<<";"
												<<Arr[4][i]<<";"
												<<Arr[5][i]<<";"
												<<Arr[6][i]<<";"
												<<Arr[7][i]<<";"
												<<Arr[8][i]<<";"
												<<Arr[9][i]<<endl;
								}
							}
							
							output.close();
							
							Arr.clear();
							Tradingdays = 0;
							
							///Breakpoint--------------
							/*std::cout<<"Breakepoint"<<endl;
							int A; 
							std::cin>>A;
							
							switch(A)
							{
								case 1:
									Modules::SubroutineMainMenu();
									break;
								case 2:
									break;
								default:
									exit(EXIT_SUCCESS);
							}*/
						}
					}
					
				}
				
			}
			
			Modules::SubroutineMainMenu();
			
		}
	
	
		case 2:
		{
			
			
			
			
		}
		
	}
	
	
	
}

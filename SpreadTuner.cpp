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

long NameRename(string name)
{
	string copname = name;
	
	name.erase(name.begin(),name.end()-6);
	string part2 = name;
	///std::cout<<part2<<endl;
	
	///std::cout<<copname<<endl;
	copname.erase(copname.begin(),copname.end()-13);
	///std::cout<<copname<<endl;
	copname.erase(copname.begin()+6,copname.end());
	///std::cout<<copname<<endl;
	string part1 = copname;
	
	
	string nname = part1+part2;
	
	///std::cout<<nname<<endl;
	
	long newname = stol(nname);
	
	return newname;
	
}

void Modules::SubroutineSpreadTuner()
{
	std::cout<<"********SPREADTUNER*************"<<endl;
	
	std::cout<<"Enter 1 for cutting and 2 for merging: "<<endl;
	
	short B;
	
	std::cin>>B;
	
	switch(B)
	{
		case 1:
		{
			string Path = "/media/Dave/Volume/Futures2020/ASCII_CalenderSpreadsSelected/";
			
			if(Path != "0")
			{				
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
							vector<vector<string>> Arr(12); //columns
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
									Arr[5][Tradingdays] = Close.c_str();
									Arr[6][Tradingdays] = Vol1.c_str();
									Arr[7][Tradingdays] = Vol2.c_str();
									Arr[8][Tradingdays] = Oi1.c_str();
									Arr[9][Tradingdays] = Oi2.c_str();
									
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
										Arr[10].push_back("0");							
										
									}
								}
								
								for(int n = 0; n < Tradingdays; n++)
								{
									Arr[10][n] = to_string(Tradingdays-n);
								}						
								
								theFile.close();						
							}
							//Assign Path2 and 3 to seperate variables because they mess up with the loop
							std::cout<<"-------Output-------"<<endl;
							
							string filelocationCopy = filelocation;
							string Path2Copy = Path2;
							string Path3Copy = Path3;
							string Dir = "/media/Dave/Volume/Futures2020/ASCII_CalendarSpreadsTuned/";
							
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
												<<Arr[9][i]<<";"
												<<Arr[10][i]<<endl;
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
			string Path = "/media/Dave/Volume/Futures2020/ASCII_CalendarSpreadsTuned_OPT";
			
			///Reading values
			long Row=0;
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
			string RET;
			/// filesystem variables
			ifstream theFile;
			ofstream output1;
			ofstream output2;
			string Path2;
			string Path3;
			string filelocation;
			
			long fakeYear = 1;
			short fakeday = 1;
			short fakemonth = 1;
			long fakeDate;
			
			theFile.imbue(locale(theFile.getloc(),new colon_is_space));
			for(const auto&entry : fs::directory_iterator(Path))	///All markets
			{
				Path2 = entry.path().string();
				
				for(const auto&entry : fs::directory_iterator(Path2))	///All Substringsfolder
				{
					Path3 = entry.path().string();
					
					vector<vector<double>> Arr(12); ///columns
					for(int i = 0; i < (int)Arr.size();i++)
					{
						Arr[i] = vector<double>(10); ///Rows
						for(int n = 0; n<(int)Arr[0].size(); n++)
						{
						
							Arr[i][n] = 0;
						
						}
					
					}
					
					fakeday = 1;
					fakemonth = 1;
					fakeYear = 1;
					Row = 0;
					
					for(const auto&entry : fs::directory_iterator(Path3))	///All Substringfiles
					{					
						
						filelocation = entry.path().string();
						theFile.open(filelocation);
						
						if(theFile.is_open())
						{
							while(theFile >>Spread>>Date>>Open>>High>>Low>>Close>>Vol1>>Vol2>>Oi1>>Oi2>>RET)
							{
								if(fakeday>27)
								{
									fakeday = 1;
									fakemonth++;
								}
								if(fakemonth>12)
								{
									fakeYear+= 1;
									fakemonth = 1;
								}
								
								fakeDate = fakeday+100*fakemonth+10000*fakeYear+19100000;
								fakeday++;
								
								Arr[0][Row] = NameRename(Spread);
								Arr[1][Row] = fakeDate;
								Arr[2][Row] = atof(Open.c_str());
								Arr[3][Row] = atof(High.c_str());
								Arr[4][Row] = atof(Low.c_str());
								Arr[5][Row] = atof(Close.c_str());
								Arr[6][Row] = atof(Vol1.c_str());
								Arr[7][Row] = atof(Vol2.c_str());
								Arr[8][Row] = atof(Oi1.c_str());
								Arr[9][Row] = atof(Oi2.c_str());
								Arr[10][Row] = atof(RET.c_str());
								Arr[11][Row] = Functions::DateFormatter(Date); //Real Date
								
								Row++;
								
								if(Row>=(int)Arr[0].size())
								{
									Arr[0].push_back(0);
									Arr[1].push_back(0);
									Arr[2].push_back(0);
									Arr[3].push_back(0);
									Arr[4].push_back(0);
									Arr[5].push_back(0);
									Arr[6].push_back(0);
									Arr[7].push_back(0);
									Arr[8].push_back(0);
									Arr[9].push_back(0);
									Arr[10].push_back(0);
									Arr[11].push_back(0);
								}
							}
							
							theFile.close();
							
						}
					}
					
					std::cout << "storage successful" << endl;
					//We do now want them to be sorted, order is already given
					///std::sort(Arr[1].begin(),Arr[1].end());
					
					///testcode
					/*for (int i = 0; i < Row; i++)
					{
						int date = (double)Arr[0][i];
						
						cout	<<(long)Arr[0][i]<<";		"
								<<(long)Arr[1][i]<<";		"
								<<Arr[2][i]<<";		"
								<<Arr[3][i]<<";		"
								<<Arr[4][i]<<";		"
								<<Arr[5][i]<<";		"
								<<Arr[6][i]<<";		"
								<<Arr[7][i]<<";		"
								<<Arr[8][i]<<";		"
								<<Arr[9][i]<<";		"
								<<(long)Arr[10][i]<<endl;
					}*/
					
					//Creating necessary folders
					string Outputpath1 = "/media/Dave/Volume/Futures2020/ASCII_SPREADS_DB_SUB_OPT";
					string Outputpath2 = "/media/Dave/Volume/Futures2020/ASCII_SPREADS_MC_SUB_OPT";
					
					string filelocationCopy1 = filelocation;
					string filelocationCopy2 = filelocation;
					
					string Path2Copy1 = Path2;
					string Path2Copy2 = Path2;
					
					string Path3Copy1 = Path3;
					string Path3Copy2 = Path3;
					
					filelocationCopy1.erase(filelocationCopy1.begin(), filelocationCopy1.begin()+Path2Copy1.length()+1);
					filelocationCopy2.erase(filelocationCopy2.begin(), filelocationCopy2.begin()+Path2Copy2.length()+1);
					
					string Outputfile1 = filelocationCopy1;
					string Outputfile2 = filelocationCopy2;
					
					Path3Copy1.erase(Path3Copy1.begin(),Path3Copy1.begin()+Path2Copy1.length()+1);
					Path3Copy2.erase(Path3Copy2.begin(),Path3Copy2.begin()+Path2Copy2.length()+1);
					
					string Dir2 = Path3Copy1;
					string Dir2_2 = Path3Copy2;
					
					Path2Copy1.erase(Path2Copy1.begin(),Path2Copy1.begin()+Path.length());
					Path2Copy2.erase(Path2Copy2.begin(),Path2Copy2.begin()+Path.length());
					
					Outputpath1 = Outputpath1+Path2Copy1;
					Outputpath2 = Outputpath2+Path2Copy2;
					
					Dir2 = Outputpath1+"/"+Dir2;
					Dir2_2 = Outputpath2+"/"+Dir2_2;
					
					mkdir(Outputpath1.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
					mkdir(Outputpath2.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
					
					///mkdir(Dir2.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
					///mkdir(Dir2_2.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
					
					
					
					string cmonth1 = Dir2;
					
					cmonth1.erase(cmonth1.begin(),cmonth1.begin()+Outputpath1.length()+1);
					
					//Breakpoint--------------
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
					
					output1.open(Outputpath1+Path2Copy1+"_"+cmonth1+".txt",ios::app);
					output2.open(Outputpath2+Path2Copy2+"_"+cmonth1+".txt",ios::app);
					
					string rowname = Path2Copy2;
					for_each(rowname.begin(),rowname.end(), [](char & c)
					{
						c = ::toupper(c);
					});
					
					rowname.erase(rowname.begin(),rowname.begin()+1);
					
					//Breakpoint--------------
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
					}
					*/
					//Outputs
					for(int i = 0; i < (int)Arr[0].size()-1; i++)
					{	
						
						if(output1.is_open())//For Database
						{
							string date = to_string(Arr[1][i]);
							date = string() + date[6] + date[7] + date[4] + date[5] + date[0]+ date[1] + date[2] + date[3];
							date.insert(date.begin() + 2, '.');
							date.insert(date.begin() + 5, '.');
						
							output1		<<(long)Arr[0][i]<<";"
										<<date<<";"
										<<Arr[2][i]<<";"
										<<Arr[3][i]<<";"
										<<Arr[4][i]<<";"
										<<Arr[5][i]<<";"
										<<Arr[6][i]<<";"
										<<Arr[7][i]<<";"
										<<Arr[8][i]<<";"
										<<Arr[9][i]<<";"
										<<Arr[10][i]<<";"
										<<(long)Arr[11][i]<<endl;
						}
						
						if(output2.is_open())//For Multicharts
						{
							string date = to_string(Arr[1][i]);
							date = string() + date[6] + date[7] + date[4] + date[5] + date[0]+ date[1] + date[2] + date[3];
							date.insert(date.begin() + 2, '.');
							date.insert(date.begin() + 5, '.');
							
							int minvol = min(Arr[6][i],Arr[7][i]);
							int minio = min(Arr[8][i],Arr[9][i]);
							double genericLow = min(Arr[2][i],min(Arr[3][i],Arr[5][i]));
							double genericHigh = max(Arr[2][i],max(Arr[3][i],Arr[5][i]));
							
							output2		<<std::fixed
										<<std::setprecision(5)
										<<rowname+"_"+cmonth1<<";"
										<<date<<";"
										<<Arr[2][i]<<";"
										<<genericHigh<<";"
										<<genericLow<<";"
										<<Arr[5][i]<<";"
										<<minvol<<";"
										<<(long)Arr[10][i]<<endl;
							
						}
						
						
					}
					
					output1.close();
					output2.close();
					
					Arr.clear();
					std::cout<<" Arr is cleared "<<endl;
			
				}
				
				
				
			}
			
			
		}
		
	}
	
	
	
}
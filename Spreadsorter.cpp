#include <iostream>
#include <stdio.h>
#include <experimental/filesystem>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include "Modules.h"
#include "Functions.h"
using namespace std;
namespace fs = std::experimental::filesystem;

void move(char oldname[], char newname[])
{
	cout<<"Spreadsorter initiating"<<endl;
	rename( oldname, newname);
}


void Modules::SubroutineSpreadsorter()
{
	// Testing purpose
	/*
	char oldname[] = "/home/Dave/Desktop/dev/C++/Spreadsorter/oldfol/file.txt";
	char newname[] = "/home/Dave/Desktop/dev/C++/Spreadsorter/newfol/file.txt";
	
	move(oldname, newname);
	*/
	string snip;
	string newname;
	string oldname;
	string MonthA;
	string MonthB;
	string contractmonths;
	string filelocation;
	string Folder;
	string path = "/media/Dave/Volume/Futures2020/ASCII_SPREADS_Opt/";
	
	for (const auto& entry : fs::directory_iterator(path))
	{
		string path = entry.path().string();
		string lenA = path;
		cout<<path<<endl;
		for (const auto& entry : fs::directory_iterator(path))
		{
			filelocation = entry.path().string();
			
			string oldfilelocation = filelocation;
			
			filelocation.erase(filelocation.begin(),filelocation.begin()+lenA.length()+1);
			
			string filename = filelocation;
			
			cout<<filename<<endl;
			filelocation = oldfilelocation;
			cout<<filelocation<<endl;
			
			cout<<filelocation<<endl;
			
			MonthB = string()+filelocation[filelocation.size()-6]+filelocation[filelocation.size()-5];
			MonthA = string()+filelocation[filelocation.size()-13]+filelocation[filelocation.size()-12];
			contractmonths = string()+MonthA+MonthB;
			
			string len = "/media/Dave/Volume/Futures2020/ASCII_SPREADS_Opt/";
			
			filelocation.erase(filelocation.begin()+path.length(),filelocation.end());
			
			filelocation.erase(filelocation.begin(),filelocation.begin()+len.length()-1);	
		
			snip = filelocation;

			string dir = "/media/Dave/Volume/Futures2020/ASCII_SPREADS_SUB_ALL_Opt"+snip+"/";
			newname = "/media/Dave/Volume/Futures2020/ASCII_SPREADS_SUB_ALL_Opt"+snip+"/"+contractmonths+"/";
			cout<<newname<<endl;
			
			mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			mkdir(newname.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			
			newname = string()+newname+filename;
			
			///cout<<contractmonths<<endl;
			
			cout<<newname<<" newname"<<endl;
			cout<<oldfilelocation<<" odlname"<<endl;
			
			char oldname[oldfilelocation.length()+1];
			
			for(int i = 0; i< (int)oldfilelocation.length()+1; i++)
			{
				oldname[i] = oldfilelocation[i];
			}
			
			char Newname[newname.length()+1];
			for(int i = 0; i < (int)newname.length()+1; i++)
			{
				Newname[i] = newname[i];
			}
			
			move(oldname, Newname);
			
		}
	}
	
	
	Modules::SubroutineMainMenu();
	
}



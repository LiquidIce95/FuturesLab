#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <clocale>
#include <locale>
#include <vector>
#include <experimental/filesystem>
#include <sys/stat.h>
#include <sys/types.h>
#include "Modules.h"

using namespace std;
namespace fs = std::experimental::filesystem;


/*First step : get all the text file names which need to be converted
 Second step: store them in a array
 third step: loop through each array element and convert these files
 for each file storing each value of one line seperately and the outputting it in the preffered format*/



void Modules::SubroutineFormatter() 
{
	cout << "********FORMATTER***********"<< endl;
    cout << "Please make sure that all Targets are prepared, if yes type in '1' otherwise return to mainmenu with 0" << endl;

    short A;

    cin >> A;

    if (A == 1) 
    {
        cout << "Formatting has begun...please wait" << endl;

        string date;
        string Open;
        string High;
        string Low;
        string close;
        string volume;
        string OI;
        string symbol;
        string symbolCapture;
        string Year;
        //int IndexLoc;

        ifstream theFile;
        string str;

        int i = 0;

        ofstream ascfile;
        string Output;
        string test;
        string Subfolder;
        string Folder;

        //initializing char array
        char Switch[10];

        for (int i = 0; i < (int)sizeof(Switch); i++)
        {
            Switch[i] = '1';
        }

        string FolName = "";

        //Folder prozedure
        string path = "/media/Dave/Volume/Futures2020/";
        int indexlength = path.length();
        for (const auto& entry : fs::directory_iterator(path))
        {
			Folder = entry.path().string();
			
            ///std::cout << entry.path() << std::endl;
            string path = entry.path().string();
            for (const auto& entry : fs::directory_iterator(path))
            {
                ///std::cout << entry.path() << std::endl;
                string filelocation = entry.path().string();
                ///cout << filelocation << endl;

                //changing output Folder
                //IndexLoc = filelocation.find('\\');

                filelocation.insert(indexlength, "ASCII/");
				Folder.insert(indexlength, "ASCII/");
                
                filelocation.erase(filelocation.begin() + indexlength + 6, filelocation.end());

                //creating output folder
                mkdir(filelocation.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                ///cout << filelocation.c_str() << endl;

                //delte from index of '\' +1 fro subfolder
                filelocation.erase(filelocation.begin() + indexlength, filelocation.end());

                mkdir(Folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                ///cout << Folder.c_str() << endl;
            }

        }


        //String TargetArr[];
        for (const auto& entry : fs::directory_iterator(path))
        {
            ///std::cout << entry.path() << std::endl;
            string path = entry.path().string();
            for (const auto& entry : fs::directory_iterator(path))
            {
                ///cout << entry.path() << std::endl;
                string filelocation = entry.path().string();
                theFile.open(filelocation);

                //changing fileformat
                filelocation[filelocation.length() - 3] = 't';
                filelocation[filelocation.length() - 2] = 'x';
                filelocation[filelocation.length() - 1] = 't';

                filelocation.insert(indexlength, "ASCII/");
                ///cout << filelocation << endl;


                Output = filelocation;
                ascfile.open(Output);

                if (theFile.is_open())
                {
                    getline(theFile, str);

                    while (theFile >> date >> Open >> High >> Low >> close >> volume >> OI >> symbol >> symbolCapture)
                    {
                        High.erase(High.end() - 2, High.end()); Low.erase(Low.end() - 2, Low.end()); close.erase(close.end() - 2, close.end()); volume.erase(volume.end() - 2, volume.end());
                        OI.erase(OI.end() - 2, OI.end()); symbol.erase(symbol.end() - 2, symbol.end()); symbolCapture.erase(symbolCapture.end() - 1, symbolCapture.end()); Open.erase(Open.end() - 2, Open.end());

                        for (i = 0; i < (int)Open.length(); i++)
                        {
                            Switch[i] = Open[i];
                        }


                        Open = Switch[6];Open += Switch[7];Open += ".";Open += Switch[4];Open += Switch[5];Open += ".";Open += Switch[0];Open += Switch[1];Open += Switch[2];Open += Switch[3];


                        ///cout << symbolCapture << ";" << Open << ";" << High << ";" << Low << ";" << close << ";" << volume << ";" << OI << ";" << symbol << Output << endl; //IMPORANT: variable names confused because of stupid format
                        ascfile << symbolCapture << ";" << Open << ";" << High << ";" << Low << ";" << close << ";" << volume << ";" << OI << ";" << symbol << endl;

                        i++;
                    }
                }
                theFile.close();
                ascfile.close();

            }

        }
    } 

    else 
    {
        Modules::SubroutineMainMenu();
    }

}

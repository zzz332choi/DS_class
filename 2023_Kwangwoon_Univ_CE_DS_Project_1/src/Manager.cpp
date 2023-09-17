#include "Manager.h"

Manager::Manager()
{

}
Manager::~Manager()
{

}

void Manager::run(const char* command)
{
    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt");
    if (!fcmd)
    {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    // Run command
    while(!fcmd.eof()){
        char com[7] = {0};
        fcmd >> com;

        string str;
        getline(fcmd, str);


    }


    fcmd.close();
    flog.close();
    return;
}

void Manager::PrintSuccess(const char* cmd)
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;
}
void Manager::PrintErrorCode(int num)
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============" << endl << endl;
}

// LOAD
void Manager::LOAD(){
    ifstream fdata;
    fdata.open("data.txt"); 

    while(!fdata.eof()){
        string str;
        getline(fdata, str);
    }
}
// ADD

// QPOP

// SEARCH

// PRINT

// DELETE
#include "Manager.h"

Manager::Manager()
{
}
Manager::~Manager()
{
}

void Manager::run(const char *command)
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
    while (!fcmd.eof())
    {
        char com[7] = {0};
        fcmd >> com;

        if (!strcmp(com, "LOAD"))
            LOAD();
        else if (!strcmp(com, "ADD"))
        {
            string str;
            getline(fcmd, str);
            ADD(str);
        }
        else if (!strcmp(com, "QPOP"))
            QPOP();
        else if (!strcmp(com, "SEARCH"))
        {
        }
    }

    fcmd.close();
    flog.close();
    return;
}

void Manager::PrintSuccess(const char *cmd)
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl
         << endl;
}
void Manager::PrintErrorCode(int num)
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============" << endl
         << endl;
}

void Manager::print_info(string str)
{
    char *s = new char[str.length() + 1];
    s[0] = 0;
    strcpy(s, str.c_str());

    char *p = strtok(s, " ");
    flog << p << '/'; // print name

    p = strtok(NULL, " ");
    flog << p << '/'; // print age

    p = strtok(NULL, " ");
    flog << p << '/'; // print date

    p = strtok(NULL, " ");
    flog << p << endl;

    p = strtok(NULL, " ");

    delete[] s;
}

// LOAD
void Manager::LOAD()
{
    ifstream fdata;
    fdata.open("data.txt");

    if (!fdata || !queue.empty())
    {
        PrintErrorCode(100);
        return;
    }

    flog << "===== LOAD =====" << endl;

    while (!fdata.eof())
    {
        string str;
        getline(fdata, str);

        queue.push(str);
        print_info(str);
    }

    flog << "===============" << endl
         << endl;

    fdata.close();
    return;
}
// ADD
void Manager::ADD(string str)
{
    int cnt = 1;

    char *s = new char[str.length() + 1];
    s[0] = 0;
    strcpy(s, str.c_str());

    char *p = nullptr;
    if (s)
    {
        p = strtok(s, " ");

        while (p)
        {
            p = strtok(NULL, " ");
            cnt++;
        }
    }

    if (cnt == 4)
    {
        flog << "===== ADD =====" << endl;
        queue.push(str);
        print_info(str);
        flog << "===============" << endl
             << endl;
    }

    else
        PrintErrorCode(200);

    delete[] s;
}
// QPOP
void Manager::QPOP()
{
    if (!queue.empty())
    {
        while (!queue.empty())
        {
            Termsbst._insert(queue.pop());
        }
        PrintSuccess("QPOP");
    }

    else
        PrintErrorCode(300);
}
// SEARCH
void Manager::SEARCH(string str)
{
}
// PRINT

// DELETE
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
            char name[21] = { 0 };
            fcmd >> name;
            SEARCH(name);
        }
        else if (!strcmp(com, "PRINT"))
        {
            char str[6] = { 0 };
            fcmd >> str;
            PRINT(str);
        }
        else if (!strcmp(com, "DELETE")) {
            char str1[5] = { 0 }, str2[21] = { 0 };
            fcmd >> str1 >> str2;
            DELETE(str1, str2);
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

    // Error code if file is not open or data remains in data structure
    if (!fdata || !queue.empty() || namebst.getRoot())    
    {
        PrintErrorCode(100);
        return;
    }

    flog << "===== LOAD =====" << endl;

    while (!fdata.eof())
    {
        string str;
        getline(fdata, str);

        if (str[0]) {
            queue.push(str);
            print_info(str);
        }
    }

    flog << "===============" << endl
         << endl;

    fdata.close();
    return;
}
// ADD
void Manager::ADD(string str)
{
    int cnt = 0;

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
            MemberQueueNode q_node = queue.pop();
            termslist.INSERT(q_node);
            namebst.INSERT(q_node);
        }
        PrintSuccess("QPOP");
    }

    else
        PrintErrorCode(300);
}

// SEARCH
void Manager::SEARCH(char* str)
{
    NameBSTNode* ptr = namebst.SEARCH(str);

    if (ptr) {
        flog << "===== SEARCH =====" << endl;
        flog << ptr->get_name() << '/' << ptr->get_age() << '/' << ptr->get_date() <<
            '/' << ptr->get_end_date() << endl;
        flog << "===============" << endl
            << endl;
    }

    else PrintErrorCode(600);
}

// PRINT
void Manager::PRINT(char* str)
{
    if (!strcmp(str, "NAME")) { // Name_BST print
        if (namebst.getRoot()) {
            flog << "==== PRINT =====" << endl;
            flog << "Name_BST" << endl;
            namebst.FILEOPEN();
            namebst.PRINT(namebst.getRoot());
            namebst.FILECLOSE();
            flog.close();

            flog.open("log.txt", ios::app);
            flog << "===============" << endl
                << endl;
        }

        else PrintErrorCode(500);
    }

    else { // Terms_BST print
        TermsListNode* ptr = termslist.SEARCH(str[0]); 
        if (ptr) { //Find the bst of that type
            TermsBST* pptr = ptr->get_root();
            flog << "==== PRINT =====" << endl;
            flog << "Terms_BST" << ' ' << ptr->get_condition_type() << endl;
            pptr->FILEOPEN();
            pptr->PRINT(pptr->getRoot());
            pptr->FILECLOSE();
            flog.close();

            flog.open("log.txt", ios::app);
            flog << "===============" << endl
                << endl;
        }

        else PrintErrorCode(500);
    }
}

// DELETE
void Manager::DELETE(char* str1, char* str2)
{
    if (!strcmp(str1, "DATE")) {
        char name[21] = { 0 };
        strcpy(name, termslist.DELETE_(str2));
        if (strcmp(name, "END")) {  //Perform deletion operations in termslist
            while (strcmp(name, "END")) {
                namebst.DELETE_(name); // If you deleted from the previous line, namebst also performs the delete operation
                strcpy(name, termslist.DELETE_(str2));
            }
            //  {
            //    //PrintSuccess("DELETE"); // case 1. Print every time delete
            //}
            PrintSuccess("DELETE"); // case 2. Print once
        }
        else PrintErrorCode(600); // There is no name to delete
    }

    else {
        MemberQueueNode* node = namebst.DELETE(str2);
        if (node) {
            termslist.DELETE(node);
            PrintSuccess("DELETE");
        }
        else PrintErrorCode(600); // There is no name to delete
    }
}

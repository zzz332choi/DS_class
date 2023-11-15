#define _CRT_SECURE_NO_WARNINGS

#include "Manager.h"
#include <fstream>
#include <cstring>

#define endl '\n'

void Manager::run(const char* command) 
{
	fin.open(command);
	if(!fin)
	{
		flog << "File Open Error" << endl;
		return;
	}

	// allocate each datastructure
	bptree = new BpTree(&flog, bpOrder);
	stree = new SelectionTree(&flog);

	while (!fin.eof())
	{
		/* You must fill here */
		cmd = new char [11];
		cmd[0] = 0;
		fin >> cmd; // input command

		// if cmd is "LOAD"
		if(!strcmp(cmd, "LOAD")) {
			if(LOAD()) printSuccessCode("LOAD");
			else printErrorCode(100);		
		}

		// // if cmd is "ADD"
		 else if (!strcmp(cmd, "ADD")) {
		 	if(ADD()); 					// printing success code runs within a function
		 	else printErrorCode(200); 	// print error code 
		 }

		 // if cmd is "SEARCH_BP"
		 else if (!strcmp(cmd, "SEARCH_BP")) {
		 	char* str = new char [100];
		 	str[0] = 0;				 // initial
		 	fin.getline(str, 100);	 // input book or start & end

		 	char* p = strtok(str, "\t");

			if(!p) {
				delete[] str;
				delete[] cmd;
				cmd = nullptr;
				printErrorCode(300);
				continue;
			}

		 	//char* p = strtok(str, " ");
		 	string s1;
		 	s1 = p;
		 	p = strtok(NULL, "\t");
		 	//p = strtok(NULL, " ");
		 	if(!p) {					// only one factor
		 		if(SEARCH_BP_BOOK(s1));
		 		else printErrorCode(300);	// print error code 300
		 	}
		 	else {						// two factors
		 		string s2;
		 		s2 = p;
		 		if(SEARCH_BP_RANGE(s1, s2));
		 		else  printErrorCode(300);	// print error code 300S
		 	}

		 	if(str) delete[] str;
		 }

		// if cmd is "PRINT_BP"
		else if(!strcmp(cmd, "PRINT_BP")) {
			if(PRINT_BP());
			else printErrorCode(400);	// print error code 400
		}

		 // if cmd is "PRINT_ST"
		 else if(!strcmp(cmd, "PRINT_ST")) {
			int code = 0;
			fin >> code;
		 	if(PRINT_ST(code));
		 	else printErrorCode(500);	// print error code 500
		 }

		 // if cmd is "DELETE"
		 else if(!strcmp(cmd, "DELETE")) {
			if (DELETE()) printSuccessCode("DELETE");
		 	else printErrorCode(600);	// print error code 600
		 }

		 // if cmd is "EXIT"
		 else if(!strcmp(cmd, "EXIT")) {

		 	printSuccessCode("EXIT");
		 	break;
		 }
		 // the other command
		 else {
			printErrorCode(700);
		 }

		flog.close();
		flog.open("log.txt", ios::app);

		delete[] cmd;
		
	}	
	fin.close();
	return;
}

bool Manager::LOAD() // Functions to load data
{
	ifstream load_data;
	load_data.open("loan_book.txt");

	if(!load_data || bptree->getRoot() || stree->getRoot()) return false;

	string str;

	while(!load_data.eof()) {
		getline(load_data, str);

     	int tab = 0; 
      	int pos = 0;   //start point

      	tab = str.find("\t");	//find tab
      	string name = str.substr(pos, tab - pos);   //copy name

      	pos = tab + 1;
      	tab = str.find("\t", pos);	//find tab
      	int  code = atoi((str.substr(pos, tab - pos)).c_str());

      	pos = tab + 1;        	
      	tab = str.find("\t", pos);	//find tab
      	string  author(str.substr(pos, tab - pos));   //copy author
      	
		pos = tab + 1;
      	tab = str.find("\t", pos);	//find tab
      	int  year = atoi((str.substr(pos, tab - pos)).c_str()); // year
      	
		pos = tab + 1;      	
      	int  loan_count = atoi((str.substr(pos)).c_str()); // loan_count

		LoanBookData* data = new LoanBookData();
		data->setBookData(name, code, author, year, loan_count);

		//cout << name << ' ' << code << ' ' << author <<' ' << year << ' ' << loan_count << endl;

		bptree->Insert(data); // insert
	}

	load_data.close();
	return true;
}


bool Manager::ADD() { // Functions to add data

	char* info = new char [100]; // allocation
	info[0] = 0; // initialization

	// input information with white space
	fin.getline(info, 100);

	// extract name(title)
	char* p = strtok(info, "\t");
	if(!p) {
		delete[] info;
		return false;
	}
	string name;
	name = p;

	// extract code
	p = strtok(NULL, "\t");
	if(!p) {
		delete[] info;
		return false;
	}
	int code = atoi(p);

	// extract author
	p = strtok(NULL, "\t");
	if(!p) {
		delete[] info;
		return false;
	}
	string author;
	author = p;

	// extract year
	p = strtok(NULL, "\t");
	if(!p) {
		delete[] info;
		return false;
	}
	int year = atoi(p);

	// set new data
	LoanBookData* newData = new LoanBookData();
	newData->setBookData(name, code, author, year);

	if(bptree->Insert(newData)) {
		// print success code
		flog << "========ADD========" << endl;
		if(code) flog << name << '/' << code << '/' << author << '/' << year << endl; // the other cases 
		else flog << name << '/' << "000" << '/' << author << '/' << year << endl; // when code  is 000
		flog << "====================" << endl << endl;

		delete[] info;

		LoanBookData* data = new LoanBookData(bptree->searchDataNode(name)->getDataMap()->find(name)->second);
		int loan_count = data->getLoanCount();

		////////////////////////////////////////////////////////////////////////////
		// After inserting from bptree, if it exceeds the number of available loans,
		//  it inserts to the stree, and in bptree,
		//  a deletion operation is performed.
		///////////////////////////////////////////////////////////////////////////////

		bool flag = 0;

		switch (code) {
		case 0: 
			if (loan_count == 3) {
				stree->Insert(data);
				bptree->Delete(name);
				flag = 1;
			}
			break;
		case 100: 
			if (loan_count == 3) {
				stree->Insert(data);
				bptree->Delete(name);
				flag = 1;
			}
			break;
		case 200:
			if (loan_count == 3) {
				stree->Insert(data);
				bptree->Delete(name);
				flag = 1;
			}
			break;
		case 300:
			if (loan_count == 4) {
				stree->Insert(data);
				bptree->Delete(name);
				flag = 1;
			}
			break;
		case 400:
			if (loan_count == 4) {
				stree->Insert(data);
				bptree->Delete(name);
				flag = 1;
			}
			break;
		case 500:
			if (loan_count == 2) {
				stree->Insert(data);
				bptree->Delete(name);
				flag = 1;
			}
			break;
		case 600:
			if (loan_count == 2) {
				stree->Insert(data);
				bptree->Delete(name);
				flag = 1;
			}
			break;
		case 700:
			if (loan_count == 2) {
				stree->Insert(data);
				bptree->Delete(name);
				flag = 1;
			}
			break;
		}

		if(!flag) delete data;

		return true;	
	}

	else {
		delete[] info;
		delete newData;

		return false;
	}
}

bool Manager::SEARCH_BP_BOOK(string book) { // Functions to search for the book specipic names
	if(bptree->searchBook(book)) return true;
	else return false;
}

bool Manager::SEARCH_BP_RANGE(string s, string e) { // Functions to search for the book in the range
	if(bptree->searchRange(s, e)) return true;
	else return false;
}

bool Manager::PRINT_BP() { //  Functions to print all of the data in bptree
	if(bptree) if(bptree->PRINT_BP()) return true;
	return false;
}

bool Manager::PRINT_ST(int code) { // Fuctions to print all of the data specipic code in selection tree 
	// Classification code that does not exist
	switch (code) {
	case 0: break;
	case 100: break;
	case 200: break;
	case 300: break;
	case 400: break;
	case 500: break;
	case 600: break;
	case 700: break;
	default: return false;
	}

	if (stree->printBookData(code)) return true;
	return false;
}

bool Manager::DELETE() {	// Fuctions to delete min data in selection tree 
	if (stree->Delete()) return true;
	else return false;
}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << "========ERROR========" << endl;
	flog << n << endl;
	flog << "======================" << endl << endl;
}

void Manager::printSuccessCode(const char* cmd) {//SUCCESS CODE PRINT 
	flog << "========" << cmd << "========" << endl;
	flog << "Success" << endl;
	flog << "====================" << endl << endl;
}



#pragma once

#include<iostream>
#include<cstring>
#include<map>
using namespace std;

class LoanBookData
{
private:
    string name;
    int code;
    string author;
    int year;
    int loan_count;

public:
    LoanBookData() {
        this->code = 0;
        this->loan_count = 0;
        this->year = 0;
    }
    LoanBookData(LoanBookData* data) {
        this->code = data->getCode();
        this->year = data->getYear();
        this->loan_count = data->getLoanCount();
        this->name = data->getName();
        this->author = data->getAuthor();
    }

    ~LoanBookData() {
        name.clear();
        author.clear();
    };

    void setBookData(string name, int code, string author, int year, int loan_count = 0) {
        this->name = name;
        this->code = code;
        this->author = author;
        this->year = year;
        this->loan_count = loan_count;
    }

    void setName(string name) { this->name = name; }
    void setCode(int code) { this->code = code; }
    void setAuthor(string author) { this->author = author; }
    void setYear(int year) { this->year = year; }
    void updateCount() { this->loan_count += 1; }

    string getName() { return name; }
    int getCode() { return code; }
    string getAuthor() { return author; }
    int getYear() { return year; }
    int getLoanCount() { return loan_count; }
};
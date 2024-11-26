#include <iostream>
#include <stdio.h>
#include "Guest.h"
#include "Admin.h"
#include "Test.h"
using namespace std;

int main()
{
    //Guest gues((char*)"Name", (char*)"MiddleName", (char*)"SurName", (char*)"HomeAddress", (char*)"HomeNumber", (char*)"Login", (char*)"Password");
    
    //Test test;
    //test.CreateTheTest();
    //test.TakeFromFile((char*)"Math");
    //test.PassTest((char*)"vafla7712", (char*)"Math");
    //test.ShowInfoPassedTest((char*)"vafla7712");
    //if (remove((char*)"C:\\Users\sasha\\Desktop\c++_ex\\Tests\\qwerrt.txt")) { cout << "oops\n"; }
    //remove((char*)"C:\\Users\sasha\\Desktop\c++_ex\\Tests\\qwerrt.txt");

    Admin admin;
    //char* login = new char[101];
    //char* password = new char[101];
    //char* keyword = new char[101];
    //char* formerPass = new char[101];
    //char* newPass = new char[101];
    //cout << "input yours login: "; cin.getline(login, 101);
    //cout << "input password: "; cin.getline(password, 101);
    //cout << "input key word for reset password: "; cin.getline(keyword, 101);
    admin.CreateAdmin((char*)"balbes", (char*)"afsdgsdfgs", (char*)"lol");
    admin.TakeFromFile((char*)"balbes");
    //int yesNot;
    //do {
    //    cout << "\ndo you want to reset password\n1 - yes\n2 - not\n- "; cin >> yesNot;
    //    cin.ignore();
    //    if (yesNot < 1 && yesNot > 2) { cout << "input 1 or 2"; }
    //} while ((yesNot < 1 && yesNot > 2));
    //if (yesNot == 1) {
    //    cout << "input your former password: "; cin.getline(formerPass, 101);
    //    cout << "input your new password: "; cin.getline(newPass, 101);
    //    admin.ChangePass(formerPass, newPass, login);
    //}

    //delete[] newPass;
    //delete[] formerPass;
    //delete[] login;
    //delete[] password;
    //delete[] keyword;

    admin.ChangePassWithKeyWord((char*)"12345", (char*)"balbes", (char*)"lol");
}


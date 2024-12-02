#include <iostream>
#include <stdio.h>
#include "Interface.h"
#include "Guest.h"
#include "Admin.h"
#include "Test.h"
using namespace std;

int main()
{

    //Test test;
    //test.ShowAllTests();
    //test.CreateTheTest();
    //test.TakeFromFile((char*)"Math");
    //test.PassTest((char*)"vafla7712", (char*)"Math");
    //test.ShowInfoPassedTest((char*)"vafla7712");

    //Admin admin;
    

    Interface interface;
    interface.Program();
 
    //Guest guest;
    //guest.CreateGuest((char*)"qwerty", (char*)"123", (char*)"Sasha", (char*)"Pupkin", (char*)"Vitaliovych", (char*)"lviv", (char*)"05512213");
    //guest.ShowAllGuests();
    //guest.GuestChangePass((char*)"qwerty", (char*)"123", (char*)"1");
    //guest.RemoveGuest((char*)"qwerty");
    //guest.LogIn((char*)"qwerty", (char*)"qwerty");
    //guest.TakeFromFile((char*)"1");
    //guest.GuestChangePass((char*)"1", guest.GetPass(), (char*)"000");
}


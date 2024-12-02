#pragma once
#include "Guest.h"
#include "Admin.h"
#include "Test.h"

class Interface : protected Guest, protected Admin
{
	Admin admin;
public:
	Interface() {}

	void Program() {


		cout << "\n\t\tGood day! Welcome to the test taking program\n";
		cout << "\t-----------------------------------------------------------\n\n\n";
		int LoginOptions;

		char* login = nullptr;
		char* password = nullptr;
		char* keyword = nullptr;

		try {
			while (true) {
				do {
					cout << "Select Mode:\n1 - Administrator\n2 - User\n-> "; cin >> LoginOptions;
					if (cin.fail()) { throw 1; }
					if (LoginOptions < 1 || LoginOptions > 2) { 
						system("cls");
						cout << "Please input 1 or 2!\n\n"; 
					}
				} while (LoginOptions < 1 || LoginOptions > 2);


				system("cls");
				if (LoginOptions == 1) {
					int AdminOptions;
					login = new char[101];
					password = new char[101];
					keyword = new char[101];
					while (true) {
						do
						{
							cout << "\n1 - Log In\n2 - Sign Up\n3 - Reset password\n4 - Exit\n-> "; cin >> AdminOptions;
							if (cin.fail()) { throw 1; }
							cin.ignore();
							cout << "\n";
							if (AdminOptions < 1 || AdminOptions > 4) {
								system("cls");
								cout << "Please input from 1 or 4!\n"; 
							}
						} while (AdminOptions < 1 || AdminOptions > 4);

						if (AdminOptions == 1) {
							system("cls");

							cout << "Input your login: "; cin.getline(login, 101);
							cout << "\n";
							cout << "Input your password: "; cin.getline(password, 101);
							cout << "\n";
							system("cls");
							if (AdminLogIn(login, password)) { break; }
							else {
								login[0] = '\n';
								password[0] = '\n';
								keyword[0] = '\n';
							}
						}

						else if (AdminOptions == 2) {

							while (true) {
								if (ExistAdmin()) {
									system("cls");
									cout << "The administrator already exists, please log in!\n";
									break;
								}
								system("cls");
								cout << "Input your login: "; cin.getline(login, 101);
								cout << "\n";
								cout << "Input your password: "; cin.getline(password, 101);
								cout << "\n";
								cout << "Input your keyword (for resetting password): "; cin.getline(keyword, 101);
								cout << "Please remember this!!!\n";
								cout << "\n";

								system("cls");

								cout << "login:" << login << endl;
								cout << "password:" << password << endl;
								cout << "keyword:" << keyword << endl;
								int SaveAdmin;
								do
								{
									cout << "\n1 - Save\n2 - Create another\n3 - Exit without saving\n-> "; cin >> SaveAdmin;
									cin.ignore();
									if (cin.fail()) { throw 1; }

									if (SaveAdmin < 1 || SaveAdmin > 3) { cout << "\nInput 1, 2 or 3!\n"; }

								} while (SaveAdmin < 1 || SaveAdmin > 3);

								if (SaveAdmin == 1) {
									system("cls");
									CreateAdmin(login, password, keyword);
									break;
								}
								else if (SaveAdmin == 2) {
									
									login[0] = '\n';
									password[0] = '\n';
									keyword[0] = '\n';
									continue;
								}
								else { 
									system("cls");
									break; 
								}
							}
							login[0] = '\n';
							password[0] = '\n';
							keyword[0] = '\n';
						}

						else if (AdminOptions == 3) {
							
							bool IsChanged;
							system("cls");
							do
							{

								cout << "\nInput login: "; cin.getline(login, 101);
								if (!strcmp(login, "0")) { break; }
								cout << "\n";

								cout << "Input keyword: "; 
								cin.getline(keyword, 101);
								cout << "\n";
								
								cout << "Input new password: "; 
								cin.getline(password, 101);
								cout << "\n";

								system("cls");
								IsChanged = AdminChangePassWithKeyWord(password, login, keyword);
								if (!IsChanged) {
									cout << "Input correct data!\n";
									cout << "\nIf you want to go back, then instead of the login, you will enter zero!\n";
								}

							} while (!IsChanged);
						
							login[0] = '\n';
							password[0] = '\n';
							keyword[0] = '\n';
						}

						else if (AdminOptions == 4) {
							return;
						}
					}
					delete[] login;
					delete[] password;
					delete[] keyword;

					int AdminMenuOptions;
					system("cls");
					cout << "\n\t\tYou have successfully logged into your account!\n";
					cout << "\t-----------------------------------------------------------\n\n\n";
					while (true) {
						do
						{
							cout << "\n1 - Create test" <<
								"\n\n2 - View test" <<
								"\n\n3 - View all tests" <<
								"\n\n4 - Pass the test" <<
								"\n\n5 - Remove test" <<
								"\n\n6 - Change password" <<
								"\n\n7 - Change password using keyword"
								"\n\n8 - Remove admin(tests will also be removed)" <<
								"\n\n9 - Create guest" <<
								"\n\n10 - Change guest's password" << 
								"\n\n11 - Show guest" <<
								"\n\n12 - Show all guests" <<
								"\n\n13 - Remove guest" <<
								"\n\n14 - Show information about passing test" <<
								"\n\n15 - Exit" <<
								"\n\n-> ";

							cin >> AdminMenuOptions;
							if (cin.fail()) { throw 1; }
							cin.ignore();
							if (AdminMenuOptions < 1 || AdminMenuOptions > 15) {
								system("cls");
								cout << "Please input from 1 to 10!\n"; 
							}
						} while (AdminMenuOptions < 1 || AdminMenuOptions > 15);

						if (AdminMenuOptions == 1) {
							system("cls");
							CreateTheTest();
							continue;
						}

						else if (AdminMenuOptions == 2) {
							char* TestName = new char[101];
							system("cls");
							cout << "\nInput name of test: ";
							cin.getline(TestName, 101);
							system("cls");
							if (Test::TakeFromFile(TestName)) {
								Display(1);
							}
							delete[] TestName;
							continue;
						}

						else if (AdminMenuOptions == 3) {
							system("cls");
							if (!ShowAllTests()) { cout << "Ooooops, no tests yet!\n"; }
							continue;
						}

						else if (AdminMenuOptions == 4) {
							char* TestName = new char[101];
							system("cls");
							cout << "\nInput name of test: ";
							cin.getline(TestName, 101);
							system("cls");

							PassTest(GetAdminLogAndPass().login, TestName);
							delete[] TestName;
							continue;
						}

						else if (AdminMenuOptions == 5) {
							char* TestName = new char[101];
							system("cls");
							cout << "\nInput name of test: ";
							cin.getline(TestName, 101);
							system("cls");
							RemoveTest(TestName);
							delete[] TestName;
							continue;
						}

						else if (AdminMenuOptions == 6) {

							char* FormerPass = new char[101];
							char* NewPass = new char[101];
							char* Login = new char[101];

							bool IsPassChanged;
							system("cls");
							do
							{
								cout << "\nInput your login: ";
								cin.getline(Login, 101);

								if (!strcmp(Login, "0")) {
									system("cls");
									break;
								}

								cout << "Input your password: ";
								cin.getline(FormerPass, 101);
								cout << "\n";

								cout << "Input your new password: ";
								cin.getline(NewPass, 101);
								cout << "\n";
								system("cls");
								IsPassChanged = AdminChangePass(Login,FormerPass, NewPass);
								if (!IsPassChanged) {
									system("cls");
									cout << "Input correct data!\n";
									cout << "\nIf you want to go back, then instead of the login, you will enter zero!\n";
									FormerPass[0] = '\n';
									NewPass[0] = '\n';
									Login[0] = '\n';
								}
							} while (!IsPassChanged);

							delete[] FormerPass;
							delete[] NewPass;
							delete[] Login;
						}

						else if (AdminMenuOptions == 7) {
							char* NewPass = new char[101];
							char* KeyWord = new char[101];
							char* Login = new char[101];

							bool IsPassChanged;
							do
							{
								cout << "\nInput your login: ";
								cin.getline(Login, 101);
								cout << "\n";

								if (!strcmp(Login, "0")) {
									system("cls");
									break;
								}

								cout << "Input your new password: ";
								cin.getline(NewPass, 101);
								cout << "\n";

								cout << "Input keyword: ";
								cin.getline(KeyWord, 101);
								cout << "\n";

								IsPassChanged = AdminChangePassWithKeyWord(NewPass, Login, KeyWord);
								if (!IsPassChanged) {
									cout << "\nInput correct data!\n";
									cout << "\nIf you want to go back, then instead of the login, you will enter zero!\n";
									KeyWord[0] = '\n';
									NewPass[0] = '\n';
									Login[0] = '\n';
								}
							} while (!IsPassChanged);

							delete[] NewPass;
							delete[] KeyWord;
							delete[] Login;
						}

						else if (AdminMenuOptions == 8) {
							char* Pass = new char[101];
							char* Login = new char[101];

							bool IsPassChanged;
							do
							{
								cout << "\nInput your login: ";
								cin.getline(Login, 101);
								cout << "\n";

								if (!strcmp(Login, "0")) {
									system("cls");
									break;
								}

								cout << "Input your password: ";
								cin.getline(Pass, 101);
								cout << "\n";

								IsPassChanged = RemoveAdminAndTests(Login, Pass);
								if (!IsPassChanged) {
									cout << "\nInput correct data!\n";
									cout << "\nIf you want to go back, then instead of the login, you will enter zero!\n";
									Pass[0] = '\n';
									Login[0] = '\n';
								}
							} while (!IsPassChanged);
							system("cls");
							cout << "Well done!\n";
							delete[] Pass;
							delete[] Login;
							continue;
						}

						else if (AdminMenuOptions == 9) {
							char* Login = new char[101];
							char* Pass = new char[101];
							char* Name = new char[101];
							char* Surname = new char[101];
							char* MiddleName = new char[101];
							char* HomeAddress = new char[101];
							char* PhoneNumber = new char[101];
							while (true) {
								system("cls");

								cout << "Input guest's login: ";
								cin.getline(Login, 101);
								cout << "\n";

								cout << "Input guest's password: ";
								cin.getline(Pass, 101);
								cout << "\n";

								cout << "Input guest's name: ";
								cin.getline(Name, 101);
								cout << "\n";

								cout << "Input guest's surname: ";
								cin.getline(Surname, 101);
								cout << "\n";

								cout << "Input guest's middle name: ";
								cin.getline(MiddleName, 101);
								cout << "\n";

								cout << "Input guest's home address: ";
								cin.getline(HomeAddress, 101);
								cout << "\n";

								cout << "Input guest's phone number: ";
								cin.getline(PhoneNumber, 101);
								cout << "\n";

								system("cls");

								cout << "login:" << Login << endl;
								cout << "password:" << Pass << endl;
								cout << "name:" << Name << endl;
								cout << "surname:" << Surname << endl;
								cout << "middle name:" << MiddleName << endl;
								cout << "home address:" << HomeAddress << endl;
								cout << "phone number:" << PhoneNumber << endl;
								
								int SaveGuest;
								do
								{
									cout << "\n1 - Save\n2 - Create another\n3 - Exit without saving\n-> "; cin >> SaveGuest;
									cin.ignore();
									if (cin.fail()) { throw 1; }

									if (SaveGuest < 1 || SaveGuest > 3) { cout << "\nInput 1, 2 or 3!\n"; }

								} while (SaveGuest < 1 || SaveGuest > 3);

								if (SaveGuest == 1) {
									system("cls");
									if (CreateGuest(Login, Pass, Name, Surname, MiddleName, HomeAddress, PhoneNumber)) { cout << "Well done!\n"; }
									break;
								}

								else if (SaveGuest == 2) {
									Login[0] = '\0';
									Pass[0] = '\0';
									Name[0] = '\0';
									Surname[0] = '\0';
									MiddleName[0] = '\0';
									HomeAddress[0] = '\0';
									PhoneNumber[0] = '\0';
									system("cls");
									continue; 
								}

								else if (SaveGuest == 3) { 
									system("cls");
									break; 
								}
							}

							delete[] Login;
							delete[] Pass;
							delete[] Name;
							delete[] Surname;
							delete[] MiddleName;
							delete[] HomeAddress;
							delete[] PhoneNumber;
							continue;
						}

						else if (AdminMenuOptions == 10) {
							char* Login = new char[101];
							char* NewPass = new char[101];
							system("cls");

							bool HadTaken;
							do
							{
								cout << "\nInput guest's login: ";
								cin.getline(Login, 101);


								HadTaken = Guest::TakeFromFile(Login);
								if (!strcmp(Login, "0")) { break; }
								

								if (!HadTaken) {
									system("cls");
									cout << "\nInput correct data!\n";
									cout << "\nIf you want to go back, then instead of the login, you will enter zero!\n";
									Login[0] = '\0';
								}
								else {
									cout << "Input new password for guest: ";
									cin.getline(NewPass, 101);

									if (!GuestChangePass(Login, GetLogAndPass().Password, NewPass,true)) {
										cout << "\nInput correct data!\n";
									}
								}

							} while (!HadTaken);
							
							delete[] Login;
							delete[] NewPass;
							continue; 
						}

						else if (AdminMenuOptions == 11) {
							
							char* Login = new char[101];
							bool Showed;
							system("cls");
							do
							{

								cout << "Input guest's login: ";
								cin.getline(Login, 101);
								if (!strcmp(Login, "0")) {
									system("cls");
									break;
								}

								system("cls");
								Showed = ShowGuest(Login);
								if (!Showed) { 
									cout << "\nInput correct data!\n"; 
									cout << "\nIf you want to go back, then instead of the login, you will enter zero!\n";
									Login[0] = '\n';
								}

							} while (!Showed);

							delete[] Login;
							continue;
						}

						else if (AdminMenuOptions == 12) {
							system("cls");
							if (!ShowAllGuests()) { cout << "Ooooops, no guests yet!\n"; }
							continue;
						}

						else if (AdminMenuOptions == 13) {
							
							char* Login = new char[101];

							bool HaveRemoved;

							system("cls");
							do
							{

								cout << "Input guest's login: ";
								cin.getline(Login, 101);
								if (!strcmp(Login, "0")) {
									system("cls");
									break;
								}

								system("cls");
								HaveRemoved = RemoveGuestWithLog(Login);
								if (!HaveRemoved) {
									cout << "Input correct data!\n";
									cout << "\nIf you want to go back, then instead of the login, you will enter zero!\n";
									Login[0] = '\n';
								}

							} while (!HaveRemoved);

							delete[] Login;
							continue;
						}

						else if (AdminMenuOptions == 14) {
							char* Login = new char[101];
							bool Showed;
							system("cls");
							do
							{

								cout << "Input guest's login: ";
								cin.getline(Login, 101);
								if (!strcmp(Login, "0")) {
									system("cls");
									break;
								}

								system("cls");
								Showed = ShowInfoPassedTest(Login);
								if (!Showed) {
									cout << "\nInput correct data!\n";
									cout << "\nIf you want to go back, then instead of the login, you will enter zero!\n";
									Login[0] = '\n';
								}

							} while (!Showed);

							delete[] Login;
							continue;
						}

						else if (AdminMenuOptions == 15) {
							cout << "Good bye!\n";
							break;
						}
						break;
					}
				}

				//////////////////////////////////////////////////////////////////////////////////
				if (LoginOptions == 2) {
					int GuestOptions;
					while (true) {
						while (true) {

							do
							{
								cout << "\n1 - Log In\n2 - Sign Up\n3 - Exit\n-> "; cin >> GuestOptions;
								if (cin.fail()) { throw 1; }
								cin.ignore();
								cout << "\n";
								if (GuestOptions < 1 || GuestOptions > 3) {
									system("cls");
									cout << "Please input from 1 or 3!\n";
								}
							} while (GuestOptions < 1 || GuestOptions > 3);

							if (GuestOptions == 1) {
								system("cls");

								char* Login = new char[101];
								char* Password = new char[101];

								cout << "Input your login: "; cin.getline(Login, 101);
								cout << "\n";
								cout << "Input your password: "; cin.getline(Password, 101);
								cout << "\n";
								system("cls");
								if (LogIn(Login, Password)) {
									delete[] Login;
									delete[] Password;
									break;
								}
								else {
									Login[0] = '\n';
									Password[0] = '\n';
								}
							}

							else if (GuestOptions == 2) {

								while (true) {
									char* Login = new char[101];
									char* Pass = new char[101];
									char* Name = new char[101];
									char* Surname = new char[101];
									char* MiddleName = new char[101];
									char* HomeAddress = new char[101];
									char* PhoneNumber = new char[101];

									system("cls");

									cout << "Input login: ";
									cin.getline(Login, 101);
									cout << "\n";

									cout << "Input password: ";
									cin.getline(Pass, 101);
									cout << "\n";

									cout << "Input name: ";
									cin.getline(Name, 101);
									cout << "\n";

									cout << "Input surname: ";
									cin.getline(Surname, 101);
									cout << "\n";

									cout << "Input middle name: ";
									cin.getline(MiddleName, 101);
									cout << "\n";

									cout << "Input home address: ";
									cin.getline(HomeAddress, 101);
									cout << "\n";

									cout << "Input phone number: ";
									cin.getline(PhoneNumber, 101);
									cout << "\n";

									system("cls");

									cout << "login:" << Login << endl;
									cout << "password:" << Pass << endl;
									cout << "name:" << Name << endl;
									cout << "surname:" << Surname << endl;
									cout << "middle name:" << MiddleName << endl;
									cout << "home address:" << HomeAddress << endl;
									cout << "phone number:" << PhoneNumber << endl;


									int SaveAdmin;
									do
									{
										cout << "\n1 - Save\n2 - Create another\n3 - Exit without saving\n-> "; cin >> SaveAdmin;
										cin.ignore();
										if (cin.fail()) { throw 1; }

										if (SaveAdmin < 1 || SaveAdmin > 3) {
											system("cls");
											cout << "\nInput from 1 to 4!\n"; 
										}

									} while (SaveAdmin < 1 || SaveAdmin > 3);

									if (SaveAdmin == 1) {
										CreateGuest(Login, Pass, Name, Surname, MiddleName, HomeAddress, PhoneNumber);
										system("cls");
										cout << "Well done!\n";
										break;
									}
									else if (SaveAdmin == 2) {

										Login[0] = '\n';
										Pass[0] = '\n';
										Name[0] = '\n';
										Surname[0] = '\n';
										MiddleName[0] = '\n';
										HomeAddress[0] = '\n';
										PhoneNumber[0] = '\n';
										continue;
									}
									else {
										system("cls");
										delete[] Login;
										delete[] Pass;
										delete[] Name;
										delete[] Surname;
										delete[] MiddleName;
										delete[] HomeAddress;
										delete[] PhoneNumber;
										break;
									}
								}
							}
						}
						int GuestMenuOptions;
						system("cls");
						cout << "\n\t\tYou have successfully logged into your account!\n";
						cout << "\t-----------------------------------------------------------\n\n\n";
						while (true) {
							do
							{
								cout << "\n1 - Pass the test" <<
									"\n\n2 - Show information about passed test" <<
									"\n\n3 - Show test" <<
									"\n\n4 - Change password" <<
									"\n\n5 - Remove guest" <<
									"\n\n6 - Show Information" <<
									"\n\n7 - Exit" <<
									"\n\n-> ";

								cin >> GuestMenuOptions;
								if (cin.fail()) { throw 1; }
								cin.ignore();
								if (GuestMenuOptions < 1 || GuestMenuOptions > 7) {
									system("cls");
									cout << "Please input from 1 to 7!\n";
								}
							} while (GuestMenuOptions < 1 || GuestMenuOptions > 6);

							if (GuestMenuOptions == 1) {
								char* FileName = new char[101];

								bool IsPassed;
								system("cls");
								do
								{
									cout << "Input name of test: ";
									cin.getline(FileName, 101);

									if (!strcmp(FileName, "0")) {
										system("cls");
										break;
									}

									IsPassed = PassTest(GetLogAndPass().Login, FileName);
									if (!IsPassed) {
										cout << "\nInput correct data!\n";
										cout << "\nIf you want to go back, then instead of the login, you will enter zero!\n";
										FileName[0] = '\n';
									}

								} while (!IsPassed);
								delete[] FileName;
							}

							else if (GuestMenuOptions == 2) {

								bool IsShowed;
								system("cls");
							
								if (!ShowInfoPassedTest(GetLogAndPass().Login)){
									cout << "Test not exist!\n";
									continue;
								}	
							}

							else if (GuestMenuOptions == 3) {
								char* FileName = new char[101];

								bool HadTaken;
								system("cls");
								do
								{
									cout << "Input name of test: ";
									cin.getline(FileName, 101);
									system("cls");
									if (!strcmp(FileName, "0")) {
										system("cls");
										break;
									}

									HadTaken = Test::TakeFromFile(FileName);
									if (!HadTaken) {
										cout << "\nInput correct data!\n";
										cout << "\nIf you want to go back, then instead of the login, you will enter zero!\n";
										FileName[0] = '\n';
									}
									else {
										Display(0);
									}
								} while (!HadTaken);
								delete[] FileName;
							}

							else if (GuestMenuOptions == 4) {
								char* FormerPass = new char[101];
								char* Pass = new char[101];
								char* Login = new char[101];

								bool IsPassChanged;
								system("cls");
								do
								{
									cout << "\nInput your login: ";
									cin.getline(Login, 101);

									if (!strcmp(Login, "0")) {
										system("cls");
										break;
									}

									cout << "Input your password: ";
									cin.getline(FormerPass, 101);
									cout << "\n";

									cout << "Input your new password: ";
									cin.getline(Pass, 101);
									cout << "\n";
									system("cls");
									IsPassChanged = GuestChangePass(Login, FormerPass, Pass,0);
									if (!IsPassChanged) {
										system("cls");
										cout << "Input correct data!\n";
										cout << "\nIf you want to go back, then instead of the login, you will enter zero!\n";
										FormerPass[0] = '\n';
										Pass[0] = '\n';
										Login[0] = '\n';
									}
								} while (!IsPassChanged);

							}

							else if (GuestMenuOptions == 5) {
								char* Login = new char[101];
								char* Pass = new char[101];

								bool HaveRemoved;
								system("cls");

								do
								{
									cout << "Input login: ";
									cin.getline(Login, 101);

									cout << "Input password: ";
									cin.getline(Pass, 101);

									system("cls");
									if (!strcmp(Login, "0")) {
										system("cls");
										break;
									}

									HaveRemoved = Guest::RemoveGuestWithLogAndPass(Login,Pass);
									if (!HaveRemoved) {
										cout << "\nInput correct data!\n";
										cout << "\nIf you want to go back, then instead of the login, you will enter zero!\n";
										Login[0] = '\n';
										Pass[0] = '\n';
									}
									else {
										system("cls");
										cout << "Well done!\n\n"; 
									}
									
								} while (!HaveRemoved);
								delete[] Login;
								delete[] Pass;
								break;
							}

							else if (GuestMenuOptions == 6) {
								system("cls");
								ShowGuest(Guest::GetLogAndPass().Login);
							}

							else if(GuestMenuOptions == 7){
								cout << "Good bye!\n";
								return;
							}
						}
						break;
					}
				}
			}
		}
		catch (int) {
			cout << "something went wrong!\n";
			return;
		}
		if (password) { delete[]password; }
		if (login) { delete[]login; }
		if (keyword) { delete[]keyword; }

	}
};


//PassTest
//ShowInfoPassedTest
//Display
//GuestChangePass
//ShowGuest
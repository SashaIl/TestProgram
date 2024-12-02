#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <io.h>
using namespace std;
class Admin
{
private:
	struct AdminData
	{
		char* login;
		char* password;
		char* keyword;
			AdminData() : login{ nullptr }, password{ nullptr }, keyword{ nullptr } {}
	};
	AdminData AdminLogAndPass;
public:
	Admin(char* login_f, char* password_f)
	{
		if (login_f) {
			AdminLogAndPass.login = new char[strlen(login_f) + 1];
			strcpy_s(AdminLogAndPass.login, strlen(login_f) + 1, login_f);
		}
		if (password_f) {
			AdminLogAndPass.password = new char[strlen(password_f) + 1];
			strcpy_s(AdminLogAndPass.password, strlen(password_f) + 1, password_f);
		}
	}
	Admin() : Admin{ nullptr,nullptr } {}

	~Admin() {
		delete[] AdminLogAndPass.login;
		delete[] AdminLogAndPass.password;
	}

	AdminData& GetAdminLogAndPass();

	Admin(const Admin& obj);

	Admin& operator=(const Admin& obj);

	void TakeFromFile(char* FileName);

	char* FullPathToAdminInfo(char* File) const;

	void CreateAdmin(char* Login, char* Password, char* KeyWord);

	bool DoesAdminExist(char* FileName) const;

	bool RemoveAdmin(char* FileName);

	bool AdminChangePass(char* Login, char* Pass, char* NewPass);

	bool AdminChangePassWithKeyWord(char* Login, char* NewPass, char* KeyWord);

	bool AdminLogIn(char* Login, char* Pass);

	char* FullPathForRemoveTests(char* File) const;

	bool RemoveAdminAndTests(char* Login, char* Pass);
};



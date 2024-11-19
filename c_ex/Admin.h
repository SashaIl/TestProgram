#pragma once
#include <iostream>
#include <cstring>
using namespace std;
class Admin
{
private:
	struct AdminData
	{
		char* login;
		char* password;
		AdminData() : login{ nullptr }, password{ nullptr } {}
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

	~Admin() {
		delete[] AdminLogAndPass.login;
		delete[] AdminLogAndPass.password;
	}

	Admin(const Admin& obj) {
		if (obj.AdminLogAndPass.login) {
			AdminLogAndPass.login = new char[strlen(obj.AdminLogAndPass.login) + 1];
			strcpy_s(AdminLogAndPass.login, strlen(obj.AdminLogAndPass.login) + 1, obj.AdminLogAndPass.login);
		}

		if (obj.AdminLogAndPass.password) {
			AdminLogAndPass.password = new char[strlen(obj.AdminLogAndPass.password) + 1];
			strcpy_s(AdminLogAndPass.password, strlen(obj.AdminLogAndPass.password) + 1, obj.AdminLogAndPass.password);
		}
	}

	Admin& operator=(const Admin& obj) {
		if (&obj != this) {
			delete[] AdminLogAndPass.login;
			delete[] AdminLogAndPass.password;
			
			AdminLogAndPass.login = obj.AdminLogAndPass.login ? new char[strlen(obj.AdminLogAndPass.login) + 1] : nullptr;
			AdminLogAndPass.password = obj.AdminLogAndPass.password ? new char[strlen(obj.AdminLogAndPass.password) + 1] : nullptr;

			if (obj.AdminLogAndPass.login) {
				strcpy_s(AdminLogAndPass.login, strlen(obj.AdminLogAndPass.login) + 1, obj.AdminLogAndPass.login);
			}

			if (obj.AdminLogAndPass.password) {
				strcpy_s(AdminLogAndPass.password, strlen(obj.AdminLogAndPass.password) + 1, obj.AdminLogAndPass.password);
			}
		}
		return *this; 
	}
};


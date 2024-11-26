#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
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

	void TakeFromFile(char* FileName) {
		fstream file(FullPathToLogPass(FileName), ios::in);
		if (!file.is_open()) {
			cout << "something went wrong!\n";
			return;
		}
		char buffer[101];
		char* key;
		char* value;
		char* context = nullptr;
		while (!file.eof()) {
			file.getline(buffer, 101);
			key = strtok_s(buffer, ":", &context);
			value = strtok_s(nullptr, ":", &context);
			if (!key || !value) { break; }
			else {
				if (!strcmp(key, (char*)"login")) {

					if (this->AdminLogAndPass.login) { delete[] this->AdminLogAndPass.login; }
					this->AdminLogAndPass.login = new char[101];
					strcpy_s(this->AdminLogAndPass.login, strlen(value) + 1, value);
				}
				else if (!strcmp(key, (char*)"password")) {

					if(this->AdminLogAndPass.password) { delete[] this->AdminLogAndPass.password; }
					this->AdminLogAndPass.password = new char[101];
					strcpy_s(this->AdminLogAndPass.password, strlen(value) + 1, value);
				}
				else if (!strcmp(key, (char*)"keyword")) {

					if (this->AdminLogAndPass.keyword) { delete[] this->AdminLogAndPass.keyword; }
					this->AdminLogAndPass.keyword = new char[101];
					strcpy_s(this->AdminLogAndPass.keyword, strlen(value) + 1, value);
				}
			}
		}
	}

	char* FullPathToLogPass(char* File) const{

		const char* BasePath = "C:\\Users\\sasha\\Desktop\\c++_ex\\LoginsAndPasswords\\";
		const char* Prefix = "AdminLoginAndPassword_";
		const char* Extension = ".txt";

		int PathLength = strlen(BasePath) + strlen(Prefix) + strlen(File) + strlen(Extension) + 1;

		char* Path = new char[PathLength];
		strcpy_s(Path, PathLength, BasePath);
		strcat_s(Path, PathLength, Prefix);
		strcat_s(Path, PathLength, File);
		strcat_s(Path, PathLength, Extension);

		return Path;
	}

	void CreateAdmin(char* Login, char* Password, char* KeyWord) {

		
		if (!DoesFileExist(Login)) {
			fstream fileCreate(FullPathToLogPass(Login), ios::out);
			
			if (this->AdminLogAndPass.login) { delete[] this->AdminLogAndPass.login; }
			if (this->AdminLogAndPass.password) { delete[] this->AdminLogAndPass.password; }
			if (this->AdminLogAndPass.keyword) { delete[] this->AdminLogAndPass.keyword; }

			this->AdminLogAndPass.login = new char[strlen(Login) + 1];
			this->AdminLogAndPass.password = new char[strlen(Password) + 1];
			this->AdminLogAndPass.keyword = new char[strlen(KeyWord) + 1];

			strcpy_s(this->AdminLogAndPass.login, strlen(Login) + 1, Login);
			strcpy_s(this->AdminLogAndPass.password, strlen(Password) + 1, Password);
			strcpy_s(this->AdminLogAndPass.keyword, strlen(KeyWord) + 1, KeyWord);

			fileCreate << "login:" << Login << endl;
			fileCreate << "password:" << Password << endl;
			fileCreate << "keyword:" << KeyWord << endl;

			
			cout  << "\nlogin: " << Login << endl;
			cout << "password: " << Password << endl;
			cout << "keyword: " << KeyWord << endl;
		}
		else {
			cout << "administrator already exists!\n";
		}
	}

	bool DoesFileExist(char* FileName) const{
		fstream file(FullPathToLogPass(FileName), ios::in);
		if (!file.is_open()) {
			file.close();
			return false;
		}
		file.close();
		return true;
	}

	bool RemoveAdmin(char* FileName) {

		if (DoesFileExist(FileName)) {
			remove(FullPathToLogPass(FileName));
			cout << "well done!\n";
			return true;
		}
		return false;
	}

	bool ChangePass(char* FormerPass, char* NewPass, char* Login) {
		if (DoesFileExist(Login)) {
			fstream fileCreate(FullPathToLogPass(Login), ios::in);
			char* key;
			char* value;
			char* context = nullptr;

			char* tempKeyWord;

			bool isLogin = false;
			bool isPassword = false;
			char buffer[101];
			while (!fileCreate.eof()) {
				
				fileCreate.getline(buffer, 101);
				key = strtok_s(buffer, ":", &context);
				value = strtok_s(nullptr, ":", &context);

				if (!key || !value) { break; }
				else {
					if (!(strcmp(key, (char*)"login")) && !(strcmp(value, Login))) { isLogin = true; }
					else if(!(strcmp(key, (char*)"password")) && !(strcmp(value, FormerPass))) { isPassword = true; }
					else if (!(strcmp(key, (char*)"keyword"))) {
						tempKeyWord = new char[strlen(value) + 1];
						strcpy_s(tempKeyWord, strlen(value) + 1, value);
					}
				}
			}
			if (isLogin && isPassword) {
				fileCreate.close();
				RemoveAdmin(Login);
				CreateAdmin(Login, NewPass, tempKeyWord);
				if (tempKeyWord) { delete[] tempKeyWord; }
				return true;
			}
			else {
				fileCreate.close();
				if (tempKeyWord) { delete[] tempKeyWord; }
				return false;
			}
		}
		return false;
	}

	bool ChangePassWithKeyWord(char* NewPass, char* Login, char* KeyWord) {
		if (DoesFileExist(Login)) {
			fstream fileCreate(FullPathToLogPass(Login), ios::in);
			char* key;
			char* value;
			char* context = nullptr;

			bool isLogin = false;
			bool isKeyWord = false;
			char buffer[101];
			while (!fileCreate.eof()) {

				fileCreate.getline(buffer, 101);
				key = strtok_s(buffer, ":", &context);
				value = strtok_s(nullptr, ":", &context);

				if (!key || !value) { break; }
				else {
					if (!(strcmp(key, (char*)"login")) && !(strcmp(value, Login))) { isLogin = true; }
					else if (!(strcmp(key, (char*)"keyword")) && !(strcmp(value, KeyWord))) { isKeyWord = true; }
				}
			}
			if (isLogin && isKeyWord) {
				fileCreate.close();
				RemoveAdmin(Login);
				CreateAdmin(Login, NewPass, KeyWord);
				return true;
			}
			else {
				fileCreate.close();
				return false;
			}
		}
		return false;
	}
};


#include "Admin.h"

//////////////////////////////////////////////////////////////////////////////////////////
Admin::AdminData& Admin::GetAdminLogAndPass() { return AdminLogAndPass; }

Admin::Admin(const Admin& obj) {
	if (obj.AdminLogAndPass.login) {
		AdminLogAndPass.login = new char[strlen(obj.AdminLogAndPass.login) + 1];
		strcpy_s(AdminLogAndPass.login, strlen(obj.AdminLogAndPass.login) + 1, obj.AdminLogAndPass.login);
	}

	if (obj.AdminLogAndPass.password) {
		AdminLogAndPass.password = new char[strlen(obj.AdminLogAndPass.password) + 1];
		strcpy_s(AdminLogAndPass.password, strlen(obj.AdminLogAndPass.password) + 1, obj.AdminLogAndPass.password);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////

Admin& Admin::operator=(const Admin& obj) {
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
//////////////////////////////////////////////////////////////////////////////////////////

void Admin::TakeFromFile(char* FileName) {
	char* path = FullPathToAdminInfo(FileName);
	if (!DoesAdminExist(FileName)) {
		cout << "something went wrong!\n";
		return;
	}
	fstream file(path, ios::in);
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

				if (this->AdminLogAndPass.password) { delete[] this->AdminLogAndPass.password; }
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
	file.close();
	delete[]path;
}
//////////////////////////////////////////////////////////////////////////////////////////

char* Admin::FullPathToAdminInfo(char* File) const {

	const char* BasePath = "LoginsAndPasswords\\Admin\\";
	const char* Prefix = "AdminLoginAndPassword_";
	const char* Extension = ".txt";

	size_t PathLength = strlen(BasePath) + strlen(Prefix) + strlen(File) + strlen(Extension) + 1;

	char* Path = new char[PathLength];
	strcpy_s(Path, PathLength, BasePath);
	strcat_s(Path, PathLength, Prefix);
	strcat_s(Path, PathLength, File);
	strcat_s(Path, PathLength, Extension);

	return Path;
}
//////////////////////////////////////////////////////////////////////////////////////////

void Admin::CreateAdmin(char* Login, char* Password, char* KeyWord) {

	if (!DoesAdminExist(Login)) {
		char* path = FullPathToAdminInfo(Login);
		fstream fileCreate(path, ios::out);

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
		cout << "Well done\n";
	}
	else {
		cout << "administrator already exists!\n";
	}
}
//////////////////////////////////////////////////////////////////////////////////////////

bool Admin::DoesAdminExist(char* FileName) const {

	char* path = FullPathToAdminInfo(FileName);
	fstream file(path, ios::in);
	if (!file.is_open()) {
		file.close();
		delete[] path;
		return false;
	}
	file.close();
	delete[] path;
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////

bool Admin::RemoveAdmin(char* FileName) {
	char* path = FullPathToAdminInfo(FileName);
	if (DoesAdminExist(FileName)) {
		remove(path);

		delete[] path;
		return true;
	}

	delete[] path;
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////

bool Admin::AdminChangePass(char* Login,char* Pass, char* NewPass) {
	if (DoesAdminExist(Login)) {
		char* path = FullPathToAdminInfo(Login);
		fstream fileCreate(path, ios::in);
		char* key;
		char* value;
		char* context = nullptr;

		char* tempKeyWord = nullptr;

		bool isLogin = false;
		bool isPassword = false;
		//char buffer[101];
		//while (!fileCreate.eof()) {

		//	fileCreate.getline(buffer, 101);
		//	key = strtok_s(buffer, ":", &context);
		//	value = strtok_s(nullptr, ":", &context);

		//	if (!key || !value) { break; }
		//	else {
		//		if (!(strcmp(key, (char*)"login")) && !(strcmp(value, Login))) { isLogin = true; }
		//		else if (!(strcmp(key, (char*)"password")) && !(strcmp(value, Pass))) { isPassword = true; }
		//		else if (!(strcmp(key, (char*)"keyword"))) {
		//			tempKeyWord = new char[strlen(value) + 1];
		//			strcpy_s(tempKeyWord, strlen(value) + 1, value);
		//		}
		//	}
		//}

		TakeFromFile(Login);

		if (!(strcmp(this->GetAdminLogAndPass().password, Pass)) && !(strcmp(this->GetAdminLogAndPass().login, Login))) {
			isPassword = true;
			isLogin = true; 
		}
		
		if (this->GetAdminLogAndPass().keyword) {
			tempKeyWord = new char[strlen(this->GetAdminLogAndPass().keyword) + 1];
			strcpy_s(tempKeyWord, strlen(this->GetAdminLogAndPass().keyword) + 1, this->GetAdminLogAndPass().keyword);
		}

		if (isLogin && isPassword) {
			fileCreate.close();
			RemoveAdmin(Login);
			CreateAdmin(Login, NewPass, tempKeyWord);
			if (tempKeyWord) { delete[] tempKeyWord; }
			delete[] path;
			return true;
		}
		else {
			fileCreate.close();
			if (tempKeyWord) { delete[] tempKeyWord; }
			delete[] path;
			return false;
		}
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////

bool Admin::AdminChangePassWithKeyWord(char* Login, char* NewPass, char* KeyWord) {
	if (DoesAdminExist(Login)) {
		char* path = FullPathToAdminInfo(Login);
		fstream fileCreate(path, ios::in);
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
			delete[] path;
			return true;
		}
		else {
			fileCreate.close();
			delete[] path;
			return false;
		}
	}
	else { return false; }
}
//////////////////////////////////////////////////////////////////////////////////////////

bool Admin::AdminLogIn(char* Login, char* Pass) {
	if (DoesAdminExist(Login)) {
		TakeFromFile(Login);
		if (!strcmp(Login, this->AdminLogAndPass.login) && !strcmp(Pass, this->AdminLogAndPass.password)) {
			return true;
		}
		else {
			cout << "please input correct data!\n";
			return false;
		}
	}
	cout << "Administrator not exist!\n\n";
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////

char* Admin::FullPathForRemoveTests(char* File) const {

	const char* BasePath = "Tests\\";

	size_t PathLength = strlen(BasePath) + strlen(File) + 1;

	char* Path = new char[PathLength];
	strcpy_s(Path, PathLength, BasePath);
	strcat_s(Path, PathLength, File);

	return Path;
}
//////////////////////////////////////////////////////////////////////////////////////////

bool Admin::RemoveAdminAndTests(char* Login, char* Pass) {
	if (!strcmp(Login, this->AdminLogAndPass.login) && !strcmp(Pass, this->AdminLogAndPass.password)) {
		char* path = FullPathToAdminInfo(Login);
		remove(path);
		delete[] path;

		_finddata_t file;
		intptr_t done = _findfirst("Tests\\*.txt", &file);
		if (done == -1) {return  true; }

		do
		{
			char* path2 = FullPathForRemoveTests(file.name);
			remove(path2);
			delete[] path2;
		} while (_findnext(done, &file) == 0);
		system("cls");
		cout << "Well done!\n";
		return true;
	}
	else { return false; }
}
//////////////////////////////////////////////////////////////////////////////////////////


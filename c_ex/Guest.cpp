#include "Guest.h"


void Guest::Clear(){
	delete[] this->GuestInfo.Name;
	delete[] this->GuestInfo.Surname;
	delete[] this->GuestInfo.MiddleName;
	delete[] this->GuestInfo.HomeAddress;
	delete[] this->GuestInfo.PhoneNumber;

	delete[] this->GuestLogAndPass.Login;
	delete[] this->GuestLogAndPass.Password;
}

Guest::GuestData& Guest::GetLogAndPass() {
	return GuestLogAndPass; 
}

bool Guest::TakeFromFile(char* Login) {
	if (!DoesGuestExist(Login)) {
		return false;
	}
	char* path = FullPathToGuestInfo(Login);
	fstream file(path, ios::in);

	char buffer[101];
	while (!file.eof()) {
		file.getline(buffer, 101);
		char* context = nullptr;
		char* key = strtok_s(buffer, ":", &context);
		char* value = strtok_s(nullptr, ":", &context);
		if (key || value) {
			if (!strcmp(key, "login")) {
				if (this->GuestLogAndPass.Login) { delete[] this->GuestLogAndPass.Login; }
				this->GuestLogAndPass.Login = new char[101];
				strcpy_s(GuestLogAndPass.Login, strlen(value) + 1, value);
			}

			else if (!strcmp(key, "password")) {
				if (this->GuestLogAndPass.Password) { delete[] this->GuestLogAndPass.Password; }
				this->GuestLogAndPass.Password = new char[101];
				strcpy_s(GuestLogAndPass.Password, strlen(value) + 1, value);
			}

			else if (!strcmp(key, "name")) {
				if (this->GuestInfo.Name) { delete[] this->GuestInfo.Name; }
				this->GuestInfo.Name = new char[101];
				strcpy_s(GuestInfo.Name, strlen(value) + 1, value);
			}

			else if (!strcmp(key, "surname")) {
				if (this->GuestInfo.Surname) { delete[] this->GuestInfo.Surname; }
				this->GuestInfo.Surname = new char[101];
				strcpy_s(GuestInfo.Surname, strlen(value) + 1, value);
			}


			else if (!strcmp(key, "middle name")) {
				if (this->GuestInfo.MiddleName) { delete[] this->GuestInfo.MiddleName; }
				this->GuestInfo.MiddleName = new char[101];
				strcpy_s(GuestInfo.MiddleName, strlen(value) + 1, value);
			}

			else if (!strcmp(key, "address")) {
				if (this->GuestInfo.HomeAddress) { delete[] this->GuestInfo.HomeAddress; }
				this->GuestInfo.HomeAddress = new char[101];
				strcpy_s(GuestInfo.HomeAddress, strlen(value) + 1, value);
			}

			else if (!strcmp(key, "phone number")) {
				if (this->GuestInfo.PhoneNumber) { delete[] this->GuestInfo.PhoneNumber; }
				this->GuestInfo.PhoneNumber = new char[101];
				strcpy_s(GuestInfo.PhoneNumber, strlen(value) + 1, value);
			}

			else if (!strcmp(key, "id")) { UniqueId = atoi(value); }
		}
		else { return true; }
	}

	file.close();
	delete[] path;
}

char* Guest::FullPathToGuestInfo(char* Login) {
	const char* BasePath = "LoginsAndPasswords\\Guest\\";
	const char* Prefix = "GuestLoginAndPassword_";
	const char* Extension = ".txt";

	size_t PathLength = strlen(BasePath) + strlen(Prefix) + strlen(Login) + strlen(Extension) + 1;

	char* Path = new char[PathLength];
	strcpy_s(Path, PathLength, BasePath);
	strcat_s(Path, PathLength, Prefix);
	strcat_s(Path, PathLength, Login);
	strcat_s(Path, PathLength, Extension);

	return Path;
}

bool Guest::DoesGuestExist(char* Login) {
	char* path = FullPathToGuestInfo(Login);
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

bool Guest::CreateGuest(char* Login, char* Pass, char* Name, char* Surname, char* MiddleName, char* Address, char* PhoneNum) {
	if (!DoesGuestExist(Login)) {
		char* path = FullPathToGuestInfo(Login);
		fstream file(path, ios::out);

		file << "login:" << Login << endl;
		file << "password:" << Pass << endl;
		file << "name:" << Name << endl;
		file << "surname:" << Surname << endl;
		file << "middle name:" << MiddleName << endl;
		file << "address:" << Address << endl;
		file << "phone number:" << PhoneNum << endl;
		file << "id:" << 1000000 + rand() % 9000000 << endl;

		TakeFromFile(Login);
		file.close();
		delete[] path;
		return true;
	}
	else {
		cout << "Such guest already exist!\n";
		return false;
	}
}

bool Guest::LogIn(char* Login, char* Pass) {
	if (DoesGuestExist(Login)) {
		TakeFromFile(Login);
		if (!strcmp(Login, this->GuestLogAndPass.Login) && !strcmp(Pass, this->GuestLogAndPass.Password)) {
			return true;
		}
		else {
			cout << "please input correct data!\n";
			return false;
		}
	}
	cout << "Guest not exist!\n\n";
	return false;
}

bool Guest::RemoveGuestWithLog(char* Login) {
	if (DoesGuestExist(Login)) {

		char* path = FullPathToGuestInfo(Login);
		remove(path);
		char* path2 = Test::FullPathInfoPassingTest(Login);
		remove(path2);

		delete[] path2;
		delete[] path;
		return true;
	}

	return false;
}

bool Guest::GuestChangePass(char* Login, char* Pass, char* NewPass, bool admin) {
	if (!TakeFromFile(Login)) { return false; }

	if (admin) {
		
		strcpy_s(Pass, strlen(this->GuestLogAndPass.Password) + 1, this->GuestLogAndPass.Password);
	}
	bool isLogin = false;
	bool isPassword = false;

	if (!(strcmp(this->GuestLogAndPass.Login, Login)) && !(strcmp(this->GuestLogAndPass.Password, Pass))) {
		isPassword = true;
		isLogin = true;
	}

	if (isLogin && isPassword) {
		RemoveGuestWithLog(Login);
		CreateGuest(Login, NewPass, this->GuestInfo.Name, this->GuestInfo.Surname, this->GuestInfo.MiddleName, this->GuestInfo.HomeAddress, this->GuestInfo.PhoneNumber);
		cout << "Well done!\n";
		delete[] Pass;
		return true;
	}
	else {
		delete[] Pass;
		return false;
	}
}

bool Guest::RemoveGuestWithLogAndPass(char* Login, char* Pass) {
	if (!DoesGuestExist(Login)) {
		cout << "please input correct data!\n";
		return false;
	}

	TakeFromFile(Login);
	if (!strcmp(Login, this->GuestLogAndPass.Login) && !strcmp(Pass, this->GuestLogAndPass.Password)) {
		char* path = FullPathToGuestInfo(Login);
		char* path2 = Test::FullPathInfoPassingTest(Login);

		remove(path2);
		remove(path);

		delete[] path2;
		delete[] path;
		return true;
	}
	return false;
}

bool Guest::ShowAllGuests() {
	_finddata_t file;
	intptr_t done = _findfirst("LoginsAndPasswords\\Guest\\*.txt", &file);
	if (done == -1) { return false; }

	bool Showed = false;
	
	char* context = nullptr;
	do
	{
		
		char* key = strtok_s(file.name, "_", &context);
		char* value = strtok_s(nullptr, ".", &context);
		cout << "Guest: " << value << endl;
		Showed = true;
	} while (_findnext(done, &file) == 0);

	if (Showed) {
		_findclose(done);
		return true; 
	}
	return false;
	_findclose(done);
}

bool Guest::ShowGuest(char* Login) {
	if (!DoesGuestExist(Login)) { return false; }
	char* path = FullPathToGuestInfo(Login);
	fstream file(path, ios::in);

	char buffer[101];
	while (!file.eof()) {
		file.getline(buffer, 101);
		cout << buffer << endl;
	}
	cout << "\n";
	return true;
	file.close();
	delete[] path;
}

#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <io.h>
#include "Test.h"
using namespace std;

class Guest : protected Test
{
private:
	struct GuestInformation {
		char* Name;
		char* Surname;
		char* MiddleName;
		char* HomeAddress;
		char* PhoneNumber;
		GuestInformation() : Name{ nullptr }, Surname{ nullptr }, MiddleName{ nullptr }, HomeAddress{ nullptr }, PhoneNumber{ nullptr } {}
	};
	struct GuestData {
		char* Login;
		char* Password;
		GuestData() : Login{ nullptr }, Password{ nullptr } {}
	};

	GuestInformation GuestInfo;
	GuestData GuestLogAndPass;
	int UniqueId;
public:

	Guest() {}


	Guest(char* Name_f, char* Surname_f, char* MiddleName_f, char* HomeAddress_f, char* PhoneNumber_f, char* Login_f, char* Password_f) :
		UniqueId{ 1000000 + rand() % 9000000 }
	{
		if (Name_f) {
			GuestInfo.Name = new char[strlen(Name_f) + 1];
			strcpy_s(GuestInfo.Name, strlen(Name_f) + 1, Name_f);
		}

		if (Surname_f) {
			GuestInfo.Surname = new char[strlen(Surname_f) + 1];
			strcpy_s(GuestInfo.Surname, strlen(Surname_f) + 1, Surname_f);
		}

		if (MiddleName_f) {
			GuestInfo.MiddleName = new char[strlen(MiddleName_f) + 1];
			strcpy_s(GuestInfo.MiddleName, strlen(MiddleName_f) + 1, MiddleName_f);
		}

		if (HomeAddress_f) {
			GuestInfo.HomeAddress = new char[strlen(HomeAddress_f) + 1];
			strcpy_s(GuestInfo.HomeAddress, strlen(HomeAddress_f) + 1, HomeAddress_f);
		}

		if (PhoneNumber_f) {
			GuestInfo.PhoneNumber = new char[strlen(PhoneNumber_f) + 1];
			strcpy_s(GuestInfo.PhoneNumber, strlen(PhoneNumber_f) + 1, PhoneNumber_f);
		}

		if (Login_f) {
			GuestLogAndPass.Login = new char[strlen(Login_f) + 1];
			strcpy_s(GuestLogAndPass.Login, strlen(Login_f) + 1, Login_f);
		}

		if (Password_f) {
			GuestLogAndPass.Password = new char[strlen(Password_f) + 1];
			strcpy_s(GuestLogAndPass.Password, strlen(Password_f) + 1, Password_f);
		}
	}

	~Guest() {
		Clear();
	}


	Guest(const Guest& obj) {
		if (obj.GuestInfo.Name) {
			this->GuestInfo.Name = new char[strlen(obj.GuestInfo.Name) + 1];
			strcpy_s(this->GuestInfo.Name, strlen(obj.GuestInfo.Name) + 1, obj.GuestInfo.Name);
		}

		if (obj.GuestInfo.Surname) {
			this->GuestInfo.Surname = new char[strlen(obj.GuestInfo.Surname) + 1];
			strcpy_s(this->GuestInfo.Surname, strlen(obj.GuestInfo.Surname) + 1, obj.GuestInfo.Surname);
		}

		if (obj.GuestInfo.MiddleName) {
			this->GuestInfo.MiddleName = new char[strlen(obj.GuestInfo.MiddleName) + 1];
			strcpy_s(this->GuestInfo.MiddleName, strlen(obj.GuestInfo.MiddleName) + 1, obj.GuestInfo.MiddleName);
		}

		if (obj.GuestInfo.HomeAddress) {
			this->GuestInfo.HomeAddress = new char[strlen(obj.GuestInfo.HomeAddress) + 1];
			strcpy_s(this->GuestInfo.HomeAddress, strlen(obj.GuestInfo.HomeAddress) + 1, obj.GuestInfo.HomeAddress);
		}

		if (obj.GuestInfo.PhoneNumber) {
			this->GuestInfo.PhoneNumber = new char[strlen(obj.GuestInfo.PhoneNumber) + 1];
			strcpy_s(this->GuestInfo.PhoneNumber, strlen(obj.GuestInfo.PhoneNumber) + 1, obj.GuestInfo.PhoneNumber);
		}

		if (obj.GuestLogAndPass.Login) {
			this->GuestLogAndPass.Login = new char[strlen(obj.GuestLogAndPass.Login) + 1];
			strcpy_s(this->GuestLogAndPass.Login, strlen(obj.GuestLogAndPass.Login) + 1, obj.GuestLogAndPass.Login);
		}

		if (obj.GuestLogAndPass.Password) {
			this->GuestLogAndPass.Password = new char[strlen(obj.GuestLogAndPass.Password) + 1];
			strcpy_s(this->GuestLogAndPass.Password, strlen(obj.GuestLogAndPass.Password) + 1, obj.GuestLogAndPass.Password);
		}

		if (obj.UniqueId) { UniqueId = obj.UniqueId; }

	}
	
	Guest& operator=(const Guest& obj) {
		if (this != &obj) {
			Clear();

			if (obj.GuestInfo.Name) {
				this->GuestInfo.Name = new char[strlen(obj.GuestInfo.Name) + 1];
				strcpy_s(this->GuestInfo.Name, strlen(obj.GuestInfo.Name) + 1, obj.GuestInfo.Name);
			}

			if (obj.GuestInfo.Surname) {
				this->GuestInfo.Surname = new char[strlen(obj.GuestInfo.Surname) + 1];
				strcpy_s(this->GuestInfo.Surname, strlen(obj.GuestInfo.Surname) + 1, obj.GuestInfo.Surname);
			}

			if (obj.GuestInfo.MiddleName) {
				this->GuestInfo.MiddleName = new char[strlen(obj.GuestInfo.MiddleName) + 1];
				strcpy_s(this->GuestInfo.MiddleName, strlen(obj.GuestInfo.MiddleName) + 1, obj.GuestInfo.MiddleName);
			}

			if (obj.GuestInfo.HomeAddress) {
				this->GuestInfo.HomeAddress = new char[strlen(obj.GuestInfo.HomeAddress) + 1];
				strcpy_s(this->GuestInfo.HomeAddress, strlen(obj.GuestInfo.HomeAddress) + 1, obj.GuestInfo.HomeAddress);
			}

			if (obj.GuestInfo.PhoneNumber) {
				this->GuestInfo.PhoneNumber = new char[strlen(obj.GuestInfo.PhoneNumber) + 1];
				strcpy_s(this->GuestInfo.PhoneNumber, strlen(obj.GuestInfo.PhoneNumber) + 1, obj.GuestInfo.PhoneNumber);
			}

			if (obj.GuestLogAndPass.Login) {
				this->GuestLogAndPass.Login = new char[strlen(obj.GuestLogAndPass.Login) + 1];
				strcpy_s(this->GuestLogAndPass.Login, strlen(obj.GuestLogAndPass.Login) + 1, obj.GuestLogAndPass.Login);
			}

			if (obj.GuestLogAndPass.Password) {
				this->GuestLogAndPass.Password = new char[strlen(obj.GuestLogAndPass.Password) + 1];
				strcpy_s(this->GuestLogAndPass.Password, strlen(obj.GuestLogAndPass.Password) + 1, obj.GuestLogAndPass.Password);
			}
		}

		return *this;
	}

	GuestData& GetLogAndPass();

	void Clear();

	bool TakeFromFile(char* Login);

	char* FullPathToGuestInfo(char* Login);

	bool DoesGuestExist(char* Login);

	bool CreateGuest(char* Login, char* Pass, char* Name, char* Surname, char* MiddleName, char* Address, char* PhoneNum);

	bool LogIn(char* Login, char* Pass);

	bool RemoveGuestWithLog(char* Login);

	bool GuestChangePass(char* Login, char* Pass, char* NewPass,bool);

	bool RemoveGuestWithLogAndPass(char* Login, char* Pass);

	bool ShowAllGuests();

	bool ShowGuest(char* Login);
};


#include "Guest.h"

int Guest::IdCounter{ 0 };

void Guest::Clear(){
	delete[] this->GuestInfo.Name;
	delete[] this->GuestInfo.Surname;
	delete[] this->GuestInfo.MiddleName;
	delete[] this->GuestInfo.HomeAddress;
	delete[] this->GuestInfo.PhoneNumber;

	delete[] this->GuestLogAndPass.Login;
	delete[] this->GuestLogAndPass.Password;
}
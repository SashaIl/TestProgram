#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
using namespace std;
class Test
{
private:
	struct QuestionAnswer {
		char* Question;
		char* Answer;
		char** AnswerOptions;
		int CountAnswerOptions;
		QuestionAnswer() : Question{ nullptr }, Answer{ nullptr }, AnswerOptions{ nullptr }, CountAnswerOptions{0} {}
	};
	char* Name;
	int CountOfQuestions;
	QuestionAnswer* QuestionAnswerTest;
public:
	Test() : Name{ nullptr }, CountOfQuestions{ 0 }, QuestionAnswerTest{ nullptr } {}


	void Clear() {
		delete[] Name;
		Name = nullptr;
		for (int i = 0; i < CountOfQuestions; i++) {
			delete[] QuestionAnswerTest[i].Question;
			delete[] QuestionAnswerTest[i].Answer;
			for (int j = 0; j < QuestionAnswerTest[i].CountAnswerOptions; j++) {
				delete[] QuestionAnswerTest[i].AnswerOptions[j];
			}
			delete[] QuestionAnswerTest[i].AnswerOptions;
		}
		delete[] QuestionAnswerTest;
		QuestionAnswerTest = nullptr;
		CountOfQuestions = 0;
	}
	//////////////////////////////////////////////////////////////////////////////////////////


	char* FullPath(char* File) const{

		char* NameForFile = new char[strlen(File) + 5];
		strcpy_s(NameForFile, strlen(File) + 5, File);
		strcat_s(NameForFile, strlen(File) + 5, ".txt");

		const char* BasePath = "C:\\Users\\sasha\\Desktop\\c++_ex\\files_txt\\";
		char* Path = new char[strlen(BasePath) + strlen(NameForFile) + 1];
		strcpy_s(Path, strlen(BasePath) + strlen(NameForFile) + 1, BasePath);
		strcat_s(Path, strlen(BasePath) + strlen(NameForFile) + 1, NameForFile);

		delete[] NameForFile;

		return Path;
	}

	//////////////////////////////////////////////////////////////////////////////////////////
	Test& CreateTheTest() {
		try {
			while (true) {
				Name = new char[101];

				cout << "Input the name of test: "; 
				cin.getline(Name, 101);
		
				cout << "\n";
				
				cout << "How many questions will the test have\n- "; 
				cin >> CountOfQuestions;
				cin.ignore();
				if (cin.fail()) { throw 1; }

				cout << "\n";

				QuestionAnswerTest = new QuestionAnswer[CountOfQuestions];

				for (int i = 0; i < CountOfQuestions; i++) {
					QuestionAnswerTest[i].Question = new char[101];
					QuestionAnswerTest[i].Answer = new char[101];

					cout << "input question number " << i + 1 << " :"; 
					cin.getline(QuestionAnswerTest[i].Question, 101);
			
					cout << "\n";

					cout << "How many answer options for this question\n- ";
					cin >> QuestionAnswerTest[i].CountAnswerOptions;
					cin.ignore();
					if (cin.fail()) { throw 1; }
					cout << "\n";

					QuestionAnswerTest[i].AnswerOptions = new char* [QuestionAnswerTest[i].CountAnswerOptions];

					for (int j = 0; j < QuestionAnswerTest[i].CountAnswerOptions; j++) {

						QuestionAnswerTest[i].AnswerOptions[j] = new char[101];

						cout << "input the " << j + 1 << " option: ";  
						cin.getline(QuestionAnswerTest[i].AnswerOptions[j], 101);
					}
			
					while (true) {
						bool IsAnswerCorrect = false;
						cout << "\n";

						cout << "input the correct answer to the question: ";
						cin.getline(QuestionAnswerTest[i].Answer, 101);
						cout << "\n";
						for (int j = 0; j < QuestionAnswerTest[i].CountAnswerOptions; j++) {
							if (!strcmp(QuestionAnswerTest[i].Answer, QuestionAnswerTest[i].AnswerOptions[j])) {
								IsAnswerCorrect = true;
								break;
							}
						}
				
						if (IsAnswerCorrect) { break; }
						else { cout << "Choose an answer from the options!\n"; }
					}
				}

				system("cls");
				Display(1);

				int Menu;
				do
				{
					cout << "What would you like to do:\n1 - save\n2 - create another\n3 - exit without saving\n- ";
					cin >> Menu;
					cin.ignore();
					if (cin.fail()) { throw 1; }
					cout << "\n";
					if (Menu < 1 || Menu > 3) { cout << "Input 1, 2 or 3!\n"; }
				} while (Menu < 1 || Menu > 3);

				if (Menu == 1) {
					WriteToFile();
					return *this;
				}

				else if (Menu == 2) {
					Clear();
				}

				else {
					Clear();
					return *this;
				}
			}
		}
		catch (int) {
			cout << "something went wrong\n";
			Clear();
			return *this;
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////

	void Display(bool answer)const {
		cout << "\n\n\t" << Name << "\n\n";
		for (int i = 0; i < CountOfQuestions; i++) {
			cout << "Question number " << i + 1 << ": " << QuestionAnswerTest[i].Question << endl;
			for (int j = 0; j < QuestionAnswerTest[i].CountAnswerOptions; j++) {
				cout << j + 1 << ")  " << QuestionAnswerTest[i].AnswerOptions[j] << endl;
			}
			if (answer) { cout << "Answer: " << QuestionAnswerTest[i].Answer << endl; }
			cout << "\n\n";
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////
	
	void WriteToFile()const {
		
		ofstream file(FullPath(Name), ios::out);
		if (!file.is_open()) {
			cout << "something went wrong!\n";
			return;
		}
		file << "name:" << Name << endl;
		file << "count of question:" << CountOfQuestions << "\n\n";
		for (int i = 0; i < CountOfQuestions; i++) {
			file << "question:" << QuestionAnswerTest[i].Question << endl;
			file << "count of options:" << QuestionAnswerTest[i].CountAnswerOptions << endl;
			for (int j = 0; j < QuestionAnswerTest[i].CountAnswerOptions; j++) {
				file << "answer option:" << QuestionAnswerTest[i].AnswerOptions[j] << endl;
			}
			file << "answer:" << QuestionAnswerTest[i].Answer << "\n\n";
		}
		cout << "Well done, information saved!\n";
	}

	//////////////////////////////////////////////////////////////////////////////////////////

	void ReadKeyValue(ifstream& file, char buffer[], char* context, char*& key, char*& value) {
		file.getline(buffer, 101);
		
		key = strtok_s(buffer, ":", &context);
		value = strtok_s(nullptr, ":", &context);
	}

	//////////////////////////////////////////////////////////////////////////////////////////

	void TakeFromFile(char* FileName) {
		

		ifstream file(FullPath(FileName), ios::in);
		
		if (!file.is_open()) {
			cout << "something went wrong!\n";
			return;
		}

		char* Context = nullptr;
		char* key = nullptr;
		char* value = nullptr;
		char buffer[101];
		while (!file.eof()) {

			ReadKeyValue(file, buffer, Context, key, value);
			if (key || value) {

				if (!strcmp(key, (char*)"name")) {
					Name = new char[strlen(value) + 1];
					strcpy_s(Name, strlen(value) + 1, value);
				}

				else if (!strcmp(key, (char*)"count of question")) {
					CountOfQuestions = atoi(value);
					QuestionAnswerTest = new QuestionAnswer[CountOfQuestions];
				}

				else {

					for (int i = 0; i < CountOfQuestions; i++) {
						if (i != 0) {
							ReadKeyValue(file, buffer, Context, key, value);
							if (!key && !value) { i--; }
						}
						if (key || value) {
							if (!strcmp(key, (char*)"question")) {
								QuestionAnswerTest[i].Question = new char[strlen(value) + 1];
								strcpy_s(QuestionAnswerTest[i].Question, strlen(value) + 1, value);

								ReadKeyValue(file, buffer, Context, key, value);
							}

							if (!strcmp(key, (char*)"count of options")) {

								QuestionAnswerTest[i].CountAnswerOptions = atoi(value);
								QuestionAnswerTest[i].AnswerOptions = new char* [QuestionAnswerTest[i].CountAnswerOptions];

								for (int j = 0; j < QuestionAnswerTest[i].CountAnswerOptions; j++) {

									ReadKeyValue(file, buffer, Context, key, value);

									QuestionAnswerTest[i].AnswerOptions[j] = new char[strlen(value) + 1];
									strcpy_s(QuestionAnswerTest[i].AnswerOptions[j], strlen(value) + 1, value);
								}
								ReadKeyValue(file, buffer, Context, key, value);
							}

							if (!strcmp(key, (char*)"answer")) {
								QuestionAnswerTest[i].Answer = new char[strlen(value) + 1];
								strcpy_s(QuestionAnswerTest[i].Answer, strlen(value) + 1, value);
							}
							else {
								ReadKeyValue(file, buffer, Context, key, value);
							}
						}
					}
				}
			}
		}
		delete[] Context;
		Display(1);
	}

};						


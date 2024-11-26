#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <ctime>

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


	~Test() { Clear(); }

	void Clear();

	char* FullPathToFileWithTests(char* File) const;

	char* FullPathInfoPassingTest(char* File) const;

	char* FullPathTempFiles(char* File) const;
	
	Test& CreateTheTest();

	void Display(bool answer)const;

	void WriteToFile()const;

	void ReadKeyValue(ifstream& file, char buffer[], char* context, char*& key, char*& value);

	void TakeFromFile(char* FileName);
	
	/*void SavingDuringTesting(char* login, bool correct,int mark) {
		ofstream file(FullPathInfoPassingTest(login), ios::out | ios::ate);
		file << "name:" << Name << endl;
		for (int i = 0; i < CountOfQuestions; i++) {
			
		}
	}*/


	void PassTest(char* login, char* FileName);

	void ShowInfoPassedTest(char* login);

	void RemoveTest(char* FileName);
};						


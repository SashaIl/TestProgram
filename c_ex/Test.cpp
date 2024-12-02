#include "Test.h"

//////////////////////////////////////////////////////////////////////////////////////////
void Test::Clear() {
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

char* Test::FullPathToFileWithTests(char* File) const {

	char* NameForFile = new char[strlen(File) + 5];
	strcpy_s(NameForFile, strlen(File) + 5, File);
	strcat_s(NameForFile, strlen(File) + 5, ".txt");

	const char* BasePath = "Tests\\";
	char* Path = new char[strlen(BasePath) + strlen(NameForFile) + 1];
	strcpy_s(Path, strlen(BasePath) + strlen(NameForFile) + 1, BasePath);
	strcat_s(Path, strlen(BasePath) + strlen(NameForFile) + 1, NameForFile);

	delete[] NameForFile;

	return Path;
}
//////////////////////////////////////////////////////////////////////////////////////////

char* Test::FullPathInfoPassingTest(char* File) const {

	char* NameForFile = new char[strlen(File) + 21];
	strcpy_s(NameForFile, 17, "InfoPassingTest_");
	strcat_s(NameForFile, 17 + strlen(File), File);

	strcat_s(NameForFile, strlen(NameForFile) + 5, ".txt");

	const char* BasePath = "InfoPassingTest\\";
	char* Path = new char[strlen(BasePath) + strlen(NameForFile) + 1];
	strcpy_s(Path, strlen(BasePath) + strlen(NameForFile) + 1, BasePath);
	strcat_s(Path, strlen(BasePath) + strlen(NameForFile) + 1, NameForFile);

	delete[] NameForFile;

	return Path;
}
//////////////////////////////////////////////////////////////////////////////////////////

char* Test::FullPathTempFiles(char* File) const {

	const char* BasePath = "TempFiles\\";
	const char* Prefix = "TempFiles_";
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

Test& Test::CreateTheTest() {
	try {
		while (true) {
			Name = new char[101];

			cout << "\n\nInput the name of test: ";
			cin.getline(Name, 101);

			cout << "\n";

			ifstream file(FullPathToFileWithTests(Name));
			if (file.is_open()) {
				int SameCreateOrNot;
				cout << "Such a test already exists!\n";
				do
				{
					cout << "------------------------------------------\n";
					cout << "Do you want to overwrite it\n1 - yes\n2 - not\n-> ";
					cin >> SameCreateOrNot;
					cin.ignore();
					if (cin.fail()) { throw 1; }
					if (SameCreateOrNot < 1 || SameCreateOrNot > 2) { cout << "Input 1 or 2!\n"; }
				} while (SameCreateOrNot < 1 || SameCreateOrNot > 2);
				if (SameCreateOrNot == 2) { 
					delete[] Name;
					Name = nullptr;
					file.close();
					break; 
				}
			}
			file.close();

			cout << "\nHow many questions will the test have\n- ";
			cin >> CountOfQuestions;
			cin.ignore();
			if (cin.fail()) { throw 1; }

			cout << "\n";

			QuestionAnswerTest = new QuestionAnswer[CountOfQuestions];

			for (int i = 0; i < CountOfQuestions; i++) {
				QuestionAnswerTest[i].Question = new char[101];
				QuestionAnswerTest[i].Answer = new char[101];
				system("cls");
				cout << "Input question number " << i + 1 << " :";
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

					cout << "Input the " << j + 1 << " option: ";
					cin.getline(QuestionAnswerTest[i].AnswerOptions[j], 101);
				}

				while (true) {
					bool IsAnswerCorrect = false;
					cout << "\n";

					cout << "Input the correct answer to the question: ";
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
				cout << "What would you like to do:\n1 - Save\n2 - Create another\n3 - Exit without saving\n-> ";
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
	return *this;
}
//////////////////////////////////////////////////////////////////////////////////////////

void Test::Display(bool answer)const {
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

void Test::WriteToFile()const {

	char* path = FullPathToFileWithTests(Name);
	ofstream file(path, ios::out);
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
	delete[] path;
	file.close();
}
//////////////////////////////////////////////////////////////////////////////////////////

void Test::ReadKeyValue(ifstream& file, char buffer[], char* context, char*& key, char*& value) {
	file.getline(buffer, 101);

	key = strtok_s(buffer, ":", &context);
	value = strtok_s(nullptr, ":", &context);
}
//////////////////////////////////////////////////////////////////////////////////////////

bool Test::TakeFromFile(char* FileName) {
	if (!DoesTestExist(FileName)) {
		cout << "\nSuch a test does not exist!\n";
			return false;
	}
	else {
		char* path = FullPathToFileWithTests(FileName);
		ifstream file(path, ios::in);


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
		file.close();
		delete[]path;
		return true;
		//Display(1);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////


bool Test::PassTest(char* login, char* FileName) {
	if (!DoesTestExist(FileName)) {
		return false;
	}
	else {
		try {
			time_t CurrentTime = time(nullptr);
			struct tm LocalTime;


			char time[20];
			if (localtime_s(&LocalTime, &CurrentTime) == 0) {
				strftime(time, sizeof(time), "%d.%m.%Y, %H:%M", &LocalTime);
			}
			else {
				strcpy_s(time, 20, "00.00.0000, 00:00");
			}

			TakeFromFile(FileName);

			char* path3 = FullPathTempFiles(login);
			ofstream file_temporary(path3);
			if (!file_temporary.is_open()) {
				cout << "something went wrong!\n";
				file_temporary.close();
				return false;
			}
			ofstream delete_file_temporary(path3, ios::trunc);
			delete_file_temporary.close();

			file_temporary << "date:" << time << endl;
			file_temporary << "name:" << Name << endl;
			cout << "\t\t\n" << Name << endl;

			int CountCorrect = 0;
			for (int i = 0; i < CountOfQuestions; i++) {
				bool correct = false;
				cout << "Question number " << i + 1 << ": " << QuestionAnswerTest[i].Question << "\n";
				int AnswerNum = 0;
				int UsersAnswer;
				for (int j = 0; j < QuestionAnswerTest[i].CountAnswerOptions; j++) {
					cout << j + 1 << ") " << QuestionAnswerTest[i].AnswerOptions[j] << endl;
					if (!strcmp(QuestionAnswerTest[i].AnswerOptions[j], QuestionAnswerTest[i].Answer)) {
						AnswerNum = j + 1;
					}
				}

				do
				{
					cout << "input your answer:"; cin >> UsersAnswer;
					cin.ignore();
					if (cin.fail()) { throw 1; }
					if (UsersAnswer <= 0 || UsersAnswer > QuestionAnswerTest[i].CountAnswerOptions) {
						cout << "input an answer option from the list!\n\n";
					}
				} while (UsersAnswer <= 0 || UsersAnswer > QuestionAnswerTest[i].CountAnswerOptions);
				cout << "\n";
				if (AnswerNum == UsersAnswer) {
					correct = true;
					CountCorrect += 1;
				}
				file_temporary << "question:" << QuestionAnswerTest[i].Question << endl;
				file_temporary << "user's answer:" << QuestionAnswerTest[i].AnswerOptions[UsersAnswer - 1] << endl;
				file_temporary << "is correct:" << (correct ? "yes" : "no") << endl;
			}
			cout << "correct answers: " << CountCorrect << "\n";
			double mark = static_cast<double>(CountCorrect) / CountOfQuestions * 12;
			cout << "mark:" << mark << "\n";

			file_temporary << "mark:" << mark << "\n\n";


			file_temporary.close();
			ifstream file_temporary2(path3);

			//information transfer
			char* path2 = FullPathInfoPassingTest(login);
			ofstream file(path2, ios::out | ios::app);
			if (!file.is_open()) {
				cout << "something went wrong!\n";

			}

			while (!file_temporary2.eof()) {
				char buffer[101];
				file_temporary2.getline(buffer, 101);
				file << buffer << endl;
			}

			file_temporary2.close();
			file.close();

			ofstream delete_file_temporary2(path3, ios::trunc);
			delete_file_temporary2.close();
			delete[] path3;
			delete[] path2;
		}
		catch (int) {
			cout << "something went wrong!\n";
			return false;
		}
		return true;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////

bool Test::ShowInfoPassedTest(char* login) {
	char* path = FullPathInfoPassingTest(login);
	ifstream file(path, ios::in);

	if (!file.is_open()) {
		file.close();
		delete[] path;
		cout << "Not found\n";
		return true;
	}
	char buffer[101];

	while (!file.eof()) {
		file.getline(buffer, 101);

		cout << buffer << "\n\n";
	}
	file.close();
	delete[] path;
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////

void Test::RemoveTest(char* FileName) {
	if (!DoesTestExist(FileName)) {
		cout << "Such a test does not exist!\n";
	}
	else {
		char* path = FullPathToFileWithTests(FileName);
		fstream file(path, ios::out);

		file.close();
		remove(FileName);
		cout << "Well done!\n";
	}
}
//////////////////////////////////////////////////////////////////////////////////////////

bool Test::DoesTestExist(char* FileName) const {

	char* path = FullPathToFileWithTests(FileName);
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

bool Test::ShowAllTests() {

	_finddata_t file;
	intptr_t done = _findfirst("Tests\\*.txt", &file);
	if (done == -1) { return false; }

	bool MoreThanTwo = false;

	char* context = nullptr;
	int i = 0;
	do
	{
		//if (i >= 2) {
			char* key = strtok_s(file.name, ".", &context);
			MoreThanTwo = true;
			TakeFromFile(key);
			Display(1);
			cout << "------------------------------------------\n";
		//}
		i += 1;
	} while (_findnext(done, &file) == 0);
	if (MoreThanTwo) {
		_findclose(done);
		return true; 
	}
	_findclose(done);
	return false;

}
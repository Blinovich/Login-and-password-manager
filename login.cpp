#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

bool isFileExist(const const char* DATA);
void showMenu();
void showCourse(const int i);
bool showChoice();

class User {
public:
	bool isRegistrated() {
		return isFileExist(DATA_USER);
	}
	bool registrationUser() {
		cout << "Придумайте логин: ";
		cin >> this->login;
		
		auto* temp = new string;
		do
		{
			while (true) {
				cout << "Придумайте пароль: ";
				cin >> this->password;
				auto* i = new int(0);
				auto* a = new int(0);
				auto* c = new int(0);
				while (true)
				{
					if (this->password[*i] >= 'A' && this->password[*i] <= 'Z') *a = 1;
					if (this->password[*i] >= '!' && this->password[*i] <= '/') *c = 1;
					++*i;
					if (*a == 1 && *c == 1) break;
					if (*i > this->password.size()) {
						cout << "В пароле должна быть хотя бы одна заглавная буква и хотя бы один символ!(!, -, ~)" << endl;
						break;
					}
				}
				if (*a == 1 && *c == 1) break;
				delete i;
				delete a;
				delete c;
			}
			cout << "Повторите пароль: ";
			cin >> *temp;
			if (*temp != this->password) cout << "Ошибка! Пароли не совпали, повторите попытку!\n" << endl;

		} while (*temp != this->password);
		delete temp;

		ofstream fout(DATA_USER);

		if (!fout) {
			cout << "Ошибка регистрации!";
			fout.close();
			return false;
		}

		fout << this->login << endl;
		fout << this->password << endl;

		fout.close();
	}

	bool logIn() {
		auto* data = new string[2];
		cout << "Введите логин: ";
		cin >> data[0];
		cout << "Введите пароль: ";
		cin >> data[1];

		ifstream fin(DATA_USER);

		if (!fin) cout << "Ошибка входа! Попробуйте позже" << endl;

		auto* index = new int(0);
		while (fin) {
			if (*index == 2) return true;

			string examination;
			fin >> examination;

			if (examination != data[*index])
			{
				delete index;
				return false;
			}
			*index += 1;
		}
		delete index;
		fin.close();
		return true;
	}
	bool addPassword() {
	/*	++rows;

		temp_pass = new string * [rows];

		for (size_t i = 0; i < rows; i++)
		{
			temp_pass[i] = new string[3];
		}*/


		auto* answer = new string;
		while (true) {
			cout << "Очистить старые данные? (да или нет) : ";
			cin >> *answer;
			if (*answer == "да") { 
				dataRecording(answer);
				break; 
			}
			else if (*answer == "нет") { 
				dataRecording(answer);
				break; 
			}
			else cout << "Такого ответа не предвиделось, повторите запрос." << endl;
		}
		delete answer;
		

		return true;
	}
	int showPasswords() {
		ifstream fin(USER_PASS);
		if (!fin) {
			cout << "Ошибка открытия файла!" << endl;
			fin.close();
			return 0;
		}
		system("cls");
		cout << "\tList\n";
		cout << "num\tsocial network\t" << "login\t" << "password" << endl;
		auto* i = new int(0);
		auto* num = new int(1);
		auto* temp = new string;
		auto* a = new string;
		cout << *num << "\t";
		while (fin) {
			fin >> *temp;
			if (*a == *temp) break;
			if (*i == 3) cout << endl;
			if (* i == 4) {
				*i = 0;
				++*num;
				cout << endl;
				cout << *num << "\t";
			}
			cout << *temp << "\t";
			++*i;
			*a = *temp;
		}
		delete temp;
		delete i;
		delete num;
		delete a;

		auto* temp1 = new string;
		while (true) {
			cout << "\nВыход?(да): ";
			cin >> *temp1;
			if (*temp1 == "да") return 0;
		}
		delete temp1;
		fin.close();
	}

	static int getCount() {
		return rows;
	}

	bool dataRecording(const string *answer) {
		if (*answer == "да") {
			ofstream fout(USER_PASS);
			if (!fout) {
				cout << "Ошибка открытия файла для записи!" << endl;
				fout.close();
				return false;
			}
			do {
				auto* i = new int(0);
				while (*i < 3) {
					string answer;
					showCourse(*i);
					cin >> answer;
					fout << answer << endl;
					++* i;
				}
				fout << "-----------------------------------" << endl;

				delete i;
			} while (showChoice());
			fout.close();
		}else {
			ofstream fout(USER_PASS, ios::app);
			if (!fout) {
				cout << "Ошибка открытия файла для записи!" << endl;
				fout.close();
				return false;
			}
			do {
				auto* i = new int(0);
				while (*i < 3) {
					string answer;
					showCourse(*i);
					cin >> answer;
					fout << answer << endl;
					++* i;
				}
				fout << "-----------------------------------" << endl;

				delete i;
			} while (showChoice());
			fout.close();
		}
		return true;
	}

	bool changePassword() {
		system("cls");

		string* answer = new string;
		cout << "Введите логин аккаунта: ";
		cin >> *answer;

		fstream fin(USER_PASS);

		auto* temp = new string;
		auto* a = new int(0);
		while (fin) {
			fin >> *temp;
			if (*temp == *answer) {
				while (true) {
					cout << "Введите старый пароль: ";
					cin >> *answer;
					*a = fin.tellg();
					fin >> *temp;

					if (*temp == *answer) {
						cout << "Введите новый пароль: ";
						cin >> *answer;
						fin.seekg(*a + 1);
						fin << *answer;

						fin.close();
						delete answer;
						delete temp;
						delete a;
						return true;
					}
					else {
						cout << "Пароль неверный!" << endl;
						Sleep(500);
						system("cls");
						string* at = new string;
						cout << "Повторить? (да или нет)";
						cin >> *at;
						fin.seekg(*a + 1);
						if (*at == "да"){ 
							system("cls"); 
							delete at;
						}
						else {
							delete at;  
							return false;
						}
					}
				}
			}
		}

		fin.close();
		delete answer;
		delete temp;
		delete a;
		return false;
	}
private:
	string login;
	string password;

	const const char* DATA_USER = "data_user.txt";
	const const char* USER_PASS = "user_pass.txt";
	// Сохранение новых паролей:
	int cols = 3;
	static int rows;
	static string** passwords;
	static string** temp_pass;

	friend void rewrite(string**, string**);
};

int User::rows = 1;
string** User::temp_pass = new string*[rows];
string** User::passwords = new string*[rows];

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	User user;

	auto* answer = new int(1);
	if (!user.isRegistrated())
	{
		while (*answer != 0) {
			if (!user.registrationUser())
			{
tp290:			system("cls");
				cout << "Ошибка! Повторить заново? (1 - Yes, 2 - No)";
				cin >> *answer;
				if (cin.fail()) {
					cin.clear();
					goto tp290;
				}
				if (*answer == 2) return 0;
			}
			else {
				*answer = 0;
			}
		}
		delete answer;
	} else {
		while (*answer != 0) {
			if (!user.logIn()) {
tp306:			system("cls");
				cout << "Ошибка! Повторить заново? (1 - Yes, 2 - No)";
				cin >> *answer;
				if (cin.fail()) {
					cin.clear();
					goto tp306;
				}
				if (*answer == 2) return 0;
			}
			else {
				*answer = 0;
			}
		}
		delete answer;
	}

	char choice;
	
	while (true)
	{
		cin.clear();
		showMenu();
		cin >> choice;
		switch (choice)
		{
		case '1': user.addPassword();
			break;
		case '2': user.showPasswords();
			break;
		case '3': user.changePassword();
			break;
		case '4': return 0;
			break;
		default: cout << "Такого пункта нет";
			Sleep(300);
			break;
		}
	}
}

bool isFileExist(const const char* DATA) {
	ifstream fin(DATA); 
	return fin.is_open() ? true : false;
}

void showMenu() {
	system("cls");
	cout << "\n\tMenu" << endl << endl;
	cout << "1. Сохранить новый пароль" << endl;
	cout << "2. Посмотреть пароли" << endl;
	cout << "3. Изменить пароль" << endl;
	cout << "4. Выход" << endl;
}

void showCourse(const int i) {
	if (i == 0) cout << "Введите соц.сеть: ";
	else if (i == 1) cout << "Введите логин: ";
	else if (i == 2) cout << "Введите пароль: ";
}

bool showChoice() {
	system("cls");
	auto* i = new int(0);
	cout << "1. Записать новый пароль" << endl;
	cout << "2. Выход" << endl;
	cin >> *i;
	if (*i == 1) return true;
	else if (*i == 2) return false;
	delete i;
}

void rewrite(string** temp, string** arr) {
	for (size_t i = 0; i < User::getCount() - 1; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			temp[i][j] = arr[i][j];
		}
	}
}
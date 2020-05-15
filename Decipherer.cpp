#include <Windows.h>
#undef max
#include <iostream>
#include <clocale>
#include <algorithm>
#include <limits>
#include <string>

#include "Hamming.h"
#include "Elias.h"
#include "Siberia.h"

using namespace std;

// For debug:
//
// Hamming test input : 111111011100111 001010111000000
// correct result :     1110110011111011000000
//
// Elias test input : 10100010011011010110010100100011101010010010111
// correct result : 0011110101011110010111110101111000111101
//
// ASCII test input : 1100001011100101111100001110110111101110
// correct result : Верно
//
// Siberia test input : 
// correct result : 


void unencrypt_ascii_text(vector <int> txt)
{
	cout << "Answer: " << endl;
	for (auto it = txt.begin(); it < txt.end(); ++it)
	{
		cout << (char)((*it + 256) % 256);
	}
	cout << endl;
}

vector <int> fromVStrToVInt(vector <string> txt)
{
	vector <int> v;
	v.resize(txt.size());
	auto iti = v.begin();
	for (auto its = txt.begin(); its < txt.end(); ++its, ++iti)
	{
		*iti = stoi(*its, nullptr, 2);
	}
	return v;
}

vector <string> fromStrToVStr(string txt)
{
	vector <string> v;
	int n = txt.size() / 8;
	std::string s(txt);
	while (s.size() % 8 != 0)
	{
		s.insert(s.size() - 1, "0");
	}
	for (int i = 0; i < n; ++i)
	{
		std::string str(s, 0, 8);
		int t = stoi(str);
		s.erase(0, 8);
		v.push_back(str);
	}
	return v;
}

void workWithHamming(string text)
{
	Hamming code(text);
	string anws = code.get_clear_text();
	cout << "Answer: " << endl;
	cout << anws << endl;
}

void workWithElias(string text)
{
	Elias code(text);
	string anws = code.get_final_text();
	cout << "Answer: " << endl;
	cout << anws << endl;
}

void workWithSiberia(wstring text)
{
	Siberia code(text);
	wstring anws = code.get_decrypted_text();
	cout << "Answer: " << endl;
	wcout << anws << endl;
}

bool pred(char x)
{
	return (x == ' ' ? true : false);
}

bool check_user_input(string& str) {
	str.erase(remove_if(str.begin(), str.end(), pred), str.end());

	for (auto& c : str) {
		if (c != '0' && c != '1') {
			return false;
		}
	}
	return true;
}	

string user_text_input()
{
	string text;
	do {
		cout << "Put the encrypted text (format: \"1100101 10101 101101\"):" << endl;
		string text;
		getline(cin, text);
		if (!check_user_input(text))
		{
			cerr << "Incorrect input text! Try again!" << endl;
		}
	} while (!check_user_input(text));
	return text;
}

void user_input()
{
	string uin;
	cout << "Put the encoding type (Exampl: \"Hamming\"; \"alltyipes\" for output of all types):" << endl;
	getline(cin, uin);

	if (uin == "alltypes")
	{
		cout << "All Types:" << endl;
		cout << "\"Hamming\"" << endl;
		cout << "\"Elias\"" << endl;
		cout << "\"ASCII\"" << endl;
		cout << "\"Siberia\"" << endl;
		cout << "Put the encoding type:" << endl;
		getline(cin, uin);
	}
	if (uin == "Hamming")
	{
		string text = user_text_input();
		workWithHamming(text);
	}
	else if (uin == "Elias")
	{
		string text = user_text_input();
		workWithElias(text);
	}
	else if (uin == "ASCII")
	{
		string text = user_text_input();
		unencrypt_ascii_text(fromVStrToVInt(fromStrToVStr(text)));
	}
	else if (uin == "Siberia")
	{
		cout << "Put the encrypted text (format: \"very G00D\"):" << endl;
		wstring text;
		getline(wcin, text);
		workWithSiberia(text);
	}
	else
	{
		cerr << "Incorrect input! Try again!" << endl;
		user_input();
	}
}

bool check_continue(char s)
{
	s = toupper(s);
	if (s == 'Y' || s == 'N')
		return true;
	return false;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	char* locale = setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool cont;
	do {
		user_input();
		char c;
		do {
			cout << "Do you want continue working? (Y / N)" << endl;
			cin.get(c); 
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (!check_continue(c));
		cont = (c == 'y' ? true : false);
	} while (cont);
}
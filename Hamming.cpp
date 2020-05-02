#include <iostream>
#include <cstring>

#include "Hamming.h"
#include "HammingPacket.h"

HammingPacket& Hamming::get_packet(int index) // Возвращает копию HammingPacket из вектора по индексу
{
	return text.at(index); // тоже самое что return HammingPacket(text.at(index))
}

std::string Hamming::get_clear_text()
{
	std::string str;
	for (auto& h : text) {
		str += h.clean_in_string();
	}
	return str;
}

bool check_user_input(std::string& str) {
	std::size_t pos = str.find_first_of(' ');
	while (pos != std::string::npos) {
		str.erase(pos, 1);
		pos = str.find_first_of(' ', pos);
	}

	for (auto& c : str) {
		if (c != '0' && c != '1') {
			return false;
		}
	}
	return true;
}

std::istream& operator>>(std::istream& in, Hamming& tmp) // inputs text with the Hamming encoding
{
	// getting user input
	std::string str;
	std::cout << "Put your input here (format: \"1100101 10101 101101\"): ";
	do {
		std::getline(in, str);
		if (!check_user_input(str)) {
			std::cerr << "Incorrect input found! Try again: ";
		}
	} while (!check_user_input(str));

	int n;
	n = str.size() / 15;

	std::vector <HammingPacket> t(str.size() % 15 == 0 ? (n) : (n + 1));
	std::vector <HammingPacket>::iterator it = t.begin();

	int i = 0;
	for (; it < (str.size() % 15 == 0 ? (t.end()) : (t.end() - 1)); ++it)
	{
		char s[16] = {};
		for (int j = 0; j < 15; ++j, ++i)
		{
			s[j] = str[i];
		}
		HammingPacket a(s);
		*it = a;
	}
	if (t.size() - n != 0)
	{
		char s[16] = {};
		for (int j = 0; j < 15; ++j, ++i)
		{
			if (i < (int)str.size())
			{
				s[j] = str[n * 15 + j];
			}
			else
			{
				s[j] = '0';
			}
		}
		HammingPacket a(s);
		t[n] = a;
	}

	tmp.text = t;

	return in;
}

std::ostream& operator<<(std::ostream& out, const Hamming& tmp) // formatted text output in Hamming encoding
{
	std::cout << "Total of " << tmp.text.size() << " elements:" << std::endl;
	int i = 1;
	for (auto& h : tmp.text) {
		std::cout << i++ << " - " << h << std::endl;
	}
	return out;
}
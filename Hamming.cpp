#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>

#include "Hamming.h"
#include "HammingPacket.h"


Hamming::Hamming()
{
	clearText = "";
}

Hamming::Hamming(HammingPacket tmp)
{
	this->text.push_back(tmp);
}

HammingPacket& Hamming::get_packet(int index)
{
	HammingPacket h;
	h = text[index];
	return h;
}

std::string Hamming::get_clear_text()
{
	std::vector <HammingPacket>::iterator it;
	std::string str;
	for (it = text.begin(); it < text.end(); ++it)
	{
		str += (*it).clean_in_string();
	}
	return str;
}

int Hamming::size()
{
	return this->text.size();
}

std::istream& operator>>(std::istream& in, Hamming& tmp) // inputs text with the Hamming encoding
{
	std::string str;
	getline(in, str);

	str.erase(remove_if(str.begin(), str.end(), std::not1(std::ptr_fun(isdigit))), str.end()); // deletes all non-digit symbols

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

std::ostream& operator<<(std::ostream& out, Hamming& tmp) // formatted text output in Hamming encoding
{
	std::cout << "Total of " << tmp.size() << " elements:" << std::endl;
	std::vector <HammingPacket>::iterator it;
	int i = 0;
	for (it = tmp.text.begin(); it < tmp.text.end(); ++it, ++i)
	{
		std::cout << i + 1 << " - " << *it << std::endl;
	}
	return out;
}
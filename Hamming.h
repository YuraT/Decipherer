#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "HammingPacket.h"

class Hamming
{
public:
	Hamming();
	Hamming(HammingPacket tmp);

	HammingPacket& get_packet(int index);
	std::string get_clear_text();
	int size();

	friend std::istream& operator >>(std::istream& in, Hamming& tmp);
	friend std::ostream& operator <<(std::ostream& out, Hamming& tmp);

private:
	std::vector <HammingPacket> text;
	std::string clearText;
};
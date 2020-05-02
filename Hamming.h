#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "HammingPacket.h"

class Hamming
{
public:
	HammingPacket& get_packet(int index);
	std::string get_clear_text();

	friend std::istream& operator >>(std::istream& in, Hamming& tmp);
	friend std::ostream& operator <<(std::ostream& out, const Hamming& tmp);

private:
	std::vector <HammingPacket> text;
	std::string clearText;
};
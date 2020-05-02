#include <iostream>

#include "Hamming.h"
#include "HammingPacket.h"

using namespace std;

// For debug:
// Hamming test input : 001010011110111
// correct result :     001010011010111

int main()
{
	Hamming h;
	cin >> h;
	std::string str;
	str = h.get_clear_text();
	cout << str;
}
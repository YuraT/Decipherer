#include <iostream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <vector>

#include "Hamming.h"
#include "HammingPacket.h"

using namespace std;


int main()
{
	Hamming h;
	cin >> h;
	cout << h << endl;
	HammingPacket f;
	f = h.get_packet(1);
	cout << f;
}
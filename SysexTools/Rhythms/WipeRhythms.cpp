/*
This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <sys/stat.h>
#include <iostream>
#include <fstream>	// read/write files
#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstddef>

//
// Version 1.0 Steve Hookings
// Find this on www.sourceforge.net project: Miniaktools
//
// Full credit for the algorithm goes to "mpathiuk" 
//
// See the post on http://tech.groups.yahoo.com/group/alesis-ion/message/21720
//
// I dont know why no one thought to just test the claim :-)
// It clearly works, and will save you an encode.
//
// Build and run this program to generate DeleteMiniakRhythms.syx
//
// CAREFUL!!! Ensure you can load system exclusive dumps to your synth
// else .. you will have lost data!!!
// If you are a newbie, and dont know what this means .... please mail me.
// I will be happy to guide you thru.
// Consult alesis-ion tech groups for more help (wiki article to follow soon)

using namespace std;

typedef unsigned char byte;

int main()
{

	// write out file
	//
	string	outName = "DeleteMiniakRhythms.syx";
	char Outfname[100];

	outName.copy(Outfname, outName.size(), 0);
	Outfname[outName.size()] = '\0';
	printf("Outname: <%s>\n", Outfname);
	ofstream	mySysExOutput(Outfname, ios::out | ios::binary);

	if (!mySysExOutput.is_open())
	{
		std::cout << "Problem opening file " << Outfname;
		exit(1);
	}

	// generate banks 0 ... 5 and patches 0 ... 127
	// F0 00 00 0E 26 21 bank 00 patch F7
	// F0 00 00 0E 26 22 00 00 01 F7 for multis
	// F0 00 00 0E 26 23 00 00 01 F7 for sequences
	// F0 00 00 0E 26 24 00 00 01 F7 for rhythms
	byte stub[6] = {0xF0, 0x00,  0x00,  0x0E,  0x26,  0x24};
	byte zero[1] = {0x00};
	byte eom[1] = {0xf7};
	byte patchByte[1];
	byte bankByte[1];	
	for (int bank = 0; bank < 6; bank++)
	{
		for (int patch = 0; patch < 128; patch++)
		{
			bankByte[0] = bank;
			patchByte[0] = patch;

			if (!mySysExOutput.write((char *)stub, 6))
			{
				cout << "Error occurred whilst writing file" << endl;
				exit(1);
			}
			if (!mySysExOutput.write((char *)bankByte, 1))
			{
				cout << "Error occurred whilst writing file" << endl;
				exit(1);
			}
			if (!mySysExOutput.write((char *)zero, 1))
			{
				cout << "Error occurred whilst writing file" << endl;
				exit(1);
			}
			if (!mySysExOutput.write((char *)patchByte, 1))
			{
				cout << "Error occurred whilst writing file" << endl;
				exit(1);
			}
			if (!mySysExOutput.write((char *)eom, 1))
			{
				cout << "Error occurred whilst writing file" << endl;
				exit(1);
			}
		}
	}
	mySysExOutput.close();
}


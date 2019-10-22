#include <iostream>
#include <string>
#include <cassert>
using namespace std;

char encodeNote(int octave, char noteLetter, char accidentalSign)
{
	// This check is here solely to report a common CS 31 student error.
	if (octave > 9)
	{
		cerr << "********** encodeNote was called with first argument = "
			<< octave << endl;
	}

	// Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
	//      to -1, 0,   1,   2,   3, ...,  11, 12

	int note;
	switch (noteLetter)
	{
	case 'C':  note = 0; break;
	case 'D':  note = 2; break;
	case 'E':  note = 4; break;
	case 'F':  note = 5; break;
	case 'G':  note = 7; break;
	case 'A':  note = 9; break;
	case 'B':  note = 11; break;
	default:   return ' ';
	}
	switch (accidentalSign)
	{
	case '#':  note++; break;
	case 'b':  note--; break;
	case ' ':  break;
	default:   return ' ';
	}

	// Convert ..., A#1, B1, C2, C#2, D2, ... to
	//         ..., -2,  -1, 0,   1,  2, ...

	int sequenceNumber = 12 * (octave - 2) + note;

	string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
	if (sequenceNumber < 0 || sequenceNumber >= keymap.size())
		return ' ';
	return keymap[sequenceNumber];
}

bool hasCorrectSyntax(string song)
{
	if (song == "") return true; //if song is empty return true
	int denote = 1;
	int i = 0;
	while (i != song.size() - 1)
	{
		if (song[i] == '/')  //if the character is กฎ/กฏ, the next character we are looking at must be a letter;
		{
			denote = 1;
			i++;
		}

		else if ((song[i] >= 'A') && (song[i] <= 'G'))  //if the character is a letter, the next character we are looking at must be accidental sign or number
		{
			denote = 2;
			i++;
		}
		else
			switch (denote)
			{
			case 1:
				if ((song[i] < 'A') || (song[i] > 'G')) return false;  // if it is the letter is not 'A' to 'G' return false
				break;
			case 2:
				if ((song[i] != '#') && (song[i] != 'b') && ((song[i] < '0') || (song[i] > '9'))) return false;  //if it is an accidental sign, the next character may be a letter or a number;
				else {
					i++;
					denote++;
				}
				break;
			case 3:
				if ((song[i] < '0') || (song[i] > '9')) return false;   // if it is an accidental sign, the next character may be a letter or a number;
				else {
					i++;
					denote++;
				}
				break;
			default:
				return false;
			}
	}
	if (song[song.size() - 1] == '/') return true;  // the last character must be a '/'
	else return false;
}

string onebeat(string s, int count)
{
	int oct = 0;
	int i = 0;
	char letter, acci;  //define oct, letter, acci which we need for function encodeNote
	string temp;       //define a string that temporarily record the converted version of one beat
	if (count > 1) temp += '[';  //if count is larger than 1 the first character in the temporary string is กฎ[กฎ
	while (s[i] != '/')
	{
		if ((s[i] >= 'A') && (s[i] <= 'G')) { //if the character we are looking at is a letter. Let variable letter equal to this letter. Move to the next character
			letter = s[i];
			i++;
		}
		if ((s[i] == '#') || (s[i] == 'b')) {  //if the character we are looking at is an accidental sign. Let variable acci equal to this sign. Move to the next character. If it is not an accidental sign, let variable acci equal to กฎ กฎ. Move to the next character
			acci = s[i];
			i++;
		}
		else acci = ' ';
		if ((s[i] >= '0') && (s[i] <= '9')) {  //if the character we are looking at is a number. Let variable oct equal to this number. Move to the next character. If it is not a number, let variable occi equal to 4
			oct = s[i] - '0'; 
			i++;
		}
		else oct = 4;
		if ((letter != ' ') && (encodeNote(oct, letter, acci) == ' ')) return "";  //if letter is not กฎ กฎ and encodeNote returns a กฎ กฎ return an empty string to tell that it is not playable, else call encodeNote and add the result into string we defined
		temp += encodeNote(oct, letter, acci);
	}
	if (temp[0] == '[') temp += ']';  //if the first character in the string is กฎ[กฎ, add กฎ]กฏ to it
	return temp;
}

int encodeSong(string song, string& instructions, int& badBeat)
{
	if (!hasCorrectSyntax(song)) return 1; //If hasCorrectSyntax is false, return 1
	int i = 0;
	int bad = 0;
	string temp;
	while (i<song.size())
	{
		int j = i;
		int count = 0; //Count the number of notes in a beat
		while (song[j] != '/')
		{
			if ((song[j] >= 'A') && (song[j] <= 'G')) count++;
			j++;
		}
		if (count == 0) { //If the number is 0, add a กฎ กฎ into the temporary string. Look at the next beat. 
			temp += ' ';
			i = j+1;
			bad++;
		}
		else {
			bad++;
			if (onebeat(song.substr(i, j - i + 1),count) == "") { //If the result of function onebeat is empty return 2 and let badBeat be the number of the beat we are looking at
				badBeat = bad;
				return 2;
			}
			temp += onebeat(song.substr(i, j - i + 1), count);  //If the number is not zero, call function onebeat.
			i = j + 1;
		}
	

	}
	instructions = temp; //Let instructions get the value of the temporary string
	return 0;

	
}






	int main()
	{
		assert(hasCorrectSyntax("C34/"));
		assert(!hasCorrectSyntax("D5//Z/"));
		assert(hasCorrectSyntax("C/C/G/G/A/A/G/"));
		assert(hasCorrectSyntax("G3B3DD5//G/A/A3B/C5/B3D5//G//G//CE5//C5/D5/E5/F#5/B3G5//G//G/"));
		assert(!hasCorrectSyntax("G3B3DD5//G/A/A3B/C5/B3D5//G//G//CE5//C5/D5/E5/F#5/B3G5//G//G"));
		assert(hasCorrectSyntax("D3/F#3/A3/D4//D3F#3A3D4/"));
		assert(!hasCorrectSyntax("D3/F##3/A3/D4//D3F#3A3D4/"));
		assert(!hasCorrectSyntax("D3/Fb#3/A3/D4//D3F#3A3D4/"));
		assert(!hasCorrectSyntax("D3/F#33/A3/D4//D3F#3A3D4/"));
		assert(hasCorrectSyntax("D3//F#3/A3/D4//D3F#3A3D4/"));
		assert(hasCorrectSyntax("G/"));
		assert(hasCorrectSyntax("A3C#E//E//F#3A3D4/A3C#E/"));
		assert(!hasCorrectSyntax("C0C0D$C0DD/E#FbB#Cb/B#9/"));
		assert(hasCorrectSyntax("///"));
		assert(hasCorrectSyntax(""));
		assert(!hasCorrectSyntax(" "));
		assert(hasCorrectSyntax("/"));
		assert(!hasCorrectSyntax("B3"));
		assert(hasCorrectSyntax("B#1C6/"));
		assert(hasCorrectSyntax("Cb2/"));
		assert(!hasCorrectSyntax("F6#/"));
		assert(!hasCorrectSyntax("F6/#"));




		string instrs;
		int badb;
		instrs = "xxx"; badb = -999; // so we can detect whether these get changed
		assert(encodeSong("D5//D/", instrs, badb) == 0 && instrs == "R H"  &&  badb == -999);
		instrs = "xxx"; badb = -999; // so we can detect whether these get changed
		assert(encodeSong("D5//Z/", instrs, badb) == 1 && instrs == "xxx"  &&  badb == -999);
		assert(encodeSong("D5//D8/", instrs, badb) == 2 && instrs == "xxx"  &&  badb == 3);
		instrs = "xxx"; badb = -999;
		assert(encodeSong("D3/F#3/A3/D4//D3F#3A3D4/", instrs, badb) == 0 && instrs == ".8DH [.8DH]"  &&  badb == -999);
		assert(encodeSong("G3B3DD5//G/A/A3B/C5/B3D5//G//G//CE5//C5/D5/E5/F#5/B3G5//G//G/", instrs, badb) == 0 && instrs == "[SFHR] LQ[DW]E[FR] L L [GT] ERT*[FU] L L"  &&  badb == -999);
		instrs = "xxx"; badb = -999;
		assert(encodeSong(" ", instrs, badb) == 1 && instrs == "xxx"  &&  badb == -999);
		instrs = "xxx"; badb = -999;
		assert(encodeSong("G3B3DD5//G/A/A3B/C5/B3D5//G//G//CE5//C5/D5/E5/F#5/B3G5//G//G", instrs, badb) == 1 && instrs == "xxx"  &&  badb == -999);
		instrs = "xxx"; badb = -999;
		assert(encodeSong("DADDA", instrs, badb) == 1 && instrs == "xxx"  &&  badb == -999);
		instrs = "xxx"; badb = -999;
		assert(encodeSong("", instrs, badb) == 0 && instrs == ""  &&  badb == -999);
		instrs = "xxx"; badb = -999;
		assert(encodeSong("DADDA9/", instrs, badb) == 2 && instrs == "xxx"  &&  badb == 1);
		instrs = "xxx"; badb = -999;
		assert(encodeSong("/B#1C6/Cb2/", instrs, badb) == 2 && instrs == "xxx"  &&  badb == 3);
		instrs = "xxx"; badb = -999;
		assert(encodeSong("//B#1C6/G6//", instrs, badb) == 2 && instrs == "xxx"  &&  badb == 4);
		assert(encodeSong("/G3B3DD5//G/A9/A3B/C5/B3D5//G//G//CE5//C5/D5/E5/F#5/B3G5//G//G/", instrs, badb) == 2 && instrs == "xxx"  &&  badb == 5);






		cerr << "All tests succeeded" << endl;

		
	}



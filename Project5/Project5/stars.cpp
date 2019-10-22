#define _CRT_SECURE_NO_DEPRECATE
#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
using namespace std;

int check(const char reader[])
{
	if ((strlen(reader) > 6) || (strlen(reader) < 4)) return 1;   //check for if the input word is a word of 4 to 6 lower case letters.
	else for (int i = 0; i < strlen(reader); i++)
		if (!islower(reader[i])) return 1;
	return 0;
}

int runOneRound(const char words[][7], int nWords, int wordnum)
{
	
	char readerin[10000];
	int guess = 1;
	do {		            
		if ((nWords <= 0) || (wordnum < 0) || (wordnum >= nWords)) return -1;    //check if we need to return -1
		cout << "Probe word: ";
		cin.getline(readerin, 10000);
		bool exist = false;
		for (int i = 0; i < nWords; i++)                         //check if the input word is in the word bank
		{
			if (!strcmp(readerin, words[i])) {
				exist = true;
			break;
			}
		}
		if (check(readerin) == 1) cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
		else if (exist) {
			if (strcmp(readerin, words[wordnum])) {            //see if the input is correct
				int tmpre[7] = { 1,1,1,1,1,1,1 };
				int tmpli[7] = { 1,1,1,1,1,1,1 };                  //define two arrays to record which letters have been counted, if used, corresponding element in the array becomes 0
				int star = 0;
				int planet = 0;
				for (int i = 0; i < strlen(readerin); i++)
				{
					if (readerin[i] == words[wordnum][i]) {              //count stars
						star++;
						tmpre[i] = 0;
						tmpli[i] = 0;
				  }
				}
				for (int i = 0; i < strlen(readerin); i++)
					for (int j = 0; j < strlen(words[wordnum]); j++)
					{
						if ((readerin[i] == words[wordnum][j]) && (tmpre[i] == 1) && (tmpli[j] == 1)) {
							planet++;
							tmpli[j] = 0;
							break;           //count planets
						}
					}
				cout << "Stars: " << star << ", Planets: " << planet << endl;
				guess++;

			}
			else return guess;
				}
		else cout << "I don't know that word." << endl;    // if the word is not in the word bank, return idk
	} while (1);
}

int main()
{
	char list[10000][7];
	int nWord = getWords(list, 10000, "D:/projects/project5files/smallwords2.txt");  //read wordfile
	if (nWord < 1) {
		cout << "No words were loaded, so I can't play the game." << endl;
		return 0;                                 //see if the file is empty
	}
	else cout << "How many rounds do you want to play? ";
	int nRound;
	cin >> nRound;
	cin.ignore(1000, '\n');
	if (nRound <= 0)  cout << "The number of rounds must be positive." << endl;   //see if the number of round is positive
	int min = 0;
	int ttl = 0;
	int max = 0;
	for (int i = 1; i <= nRound; i++)
	{
		int nround;
		cout << endl;
		cout << "Round " << i << endl;
		int wordnum;
		wordnum = randInt(0, nWord-1);   //get a random word
		cout << "The secret word is " << strlen(list[wordnum]) << " letters long." << endl;
		nround = runOneRound(list, nWord, wordnum);
		if (nround == -1) break;    //if runOneRound returns -1, then do nothing
		ttl += nround;
		if (min == 0) min = nround; //initialize min
		if (min > nround) min = nround;
		if (max < nround) max = nround; //record max and min
		if (nround == 1) cout << "You got it in " << nround << " try." << endl;
		else cout << "You got it in " << nround << " tries." << endl;
		cout.precision(2);
		cout.setf(ios::fixed); //set to 2 dp
		cout << "Average: " << static_cast<double>(ttl) / i << ", minimum: " << min << ", maximum: " << max << endl;
    }
}

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int rotateRight(string a[], int n, int pos)
{
	if (n < 0) return -1;
	else if ((pos >= n) || (pos < 0)) return -1;
	else {
		string tmp = a[pos];
		for (int i = pos; i > 0; i--)
			a[i] = a[i - 1];
		a[0] = tmp;
		return pos;             //do the opposite as rotateLeft
	}
}

int appendToAll(string a[], int n, string value)
{
	if (n < 0) return -1;
	else {
		for (int i = 0; i < n; i++)
			a[i] += value;
		return n;                   //if n=0, return 0
	}
}

int lookup(const string a[], int n, string target)
{
	if (n < 0) return -1;
	else {
		for (int i = 0; i < n; i++)
			if (a[i] == target) return i;
		return -1;                // if n=0, return -1
	}
}

int positionOfMax(const string a[], int n)
{
	if (n <= 0) return -1;
	else {
		int pos = 0;
		for (int i = 1; i < n; i++)
			if (a[i] > a[pos]) pos = i;
		return pos;               
	}

}

int rotateLeft(string a[], int n, int pos)
{
	if (n < 0) return -1;
	else if ((pos >= n)||(pos < 0)) return -1;      // if n=0, return -1
	else {
		string tmp = a[pos];                       //tmp stores the string at pos
		for (int i = pos; i < n-1; i++)            //shift to left
			a[i] = a[i + 1];
		a[n - 1] = tmp;
		return pos;                              
	}
}

int countRuns(const string a[], int n)
{
	if (n < 0) return -1;
	else if (n == 0) return 0;                  
	else {
		int count = 1;
		for (int i = 0; i < n-1; i++)           //use i<n-1 here to avoid the situation that i+1=n
			if (a[i] != a[i + 1]) count++;             
		return count;                          //if n=0, return 0
	}
}

int flip(string a[], int n)
{
	if (n < 0) return -1;
	else {
		string tmp;
		for (int i = 0; i < (n / 2); i++)
		{
			tmp = a[i];                      
			a[i] = a[n - 1 - i];
			a[n - 1 - i] = tmp;              //exchange pairs of strings at the start and the end
		}
		return n;                            //if n=0, return 0
	}
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
	int min;
	if ((n1 < 0) || (n2 < 0)) return -1;
	if (n1 <= n2) min = n1;               //min is the maximum number of loops
	else min = n2;
	for (int i = 0; i < min; i++)
		if (a1[i] != a2[i]) return i;
	return min;                           // if any n=0, return 0
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	int j = 0;
	if ((n1 < 0)||(n2 < 0)) return -1;
	else if (n2 == 0) return 0;
	else 
	{
		for (int i = 0; i < n1; i++)
		{
			if (a1[i] == a2[j]) j++;
			else j = 0;                     // j denotes which string we are looking at in a2
			if  (j == n2) return i - j + 1;  // only when all strings are present in a consecutive manner we return the position
		}
		return -1;                        //if n1=0, return -1 unless n2 = 0
	}          
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	if ((n1 < 0) || (n2 < 0)) return -1;
	else {
		for (int i = 0; i < n1; i++)
			for (int j = 0; j < n2; j++)
				if (a1[i] == a2[j]) return i;
		return -1;       // if n1 or n2=0, return -1
	}
}

int split(string a[], int n, string splitter)
{
	int j = 0;
	if (n < 0) return -1;
	else {
		for (int i = 0; i < n; i++)
		{
			if (a[j] > splitter) rotateLeft(a, n, j);
			else if (a[j] < splitter) {                               //i use rotateLeft and a new function rotateRight to do the shift
				rotateRight(a, n, j);
				j++;
			}
			else j++;                                  //if a[i] equals splitter, do nothing
		}
		for (int i = 0; i < n; i++)
			if (a[i] >= splitter) return i;
		return n;                                    //return 0 if n=0
	}
}



int main()
{
	string n[1] = { "" };
	assert(appendToAll(n, 1, "?") == 1 && n[0] == "?");
	assert(appendToAll(n, 0, "?") == 0);
	assert(appendToAll(n, -1, "?") == -1);
	string h[7] = { "selina", "reed", "diana", "tony", "", "logan", "peter" };
	string h2[7] = { "selina", "reed", "diana", "tony", "", "logan", "peter" };
	string h3[7] = { "selina", "reed", "diana", "tony", "", "logan", "peter" };
	assert(lookup(h, 0, "logan") == -1);
	assert(lookup(h, 7, "logan") == 5);
	assert(lookup(h, 7, "diana") == 2);
	assert(lookup(h, 2, "diana") == -1);
	assert(lookup(h, -1, "diana") == -1);
	assert(lookup(h, 7, "") == 4);
	assert(positionOfMax(h, 7) == 3);
	assert(positionOfMax(h, 0) == -1);
	assert(positionOfMax(h, -1) == -1);
	assert(positionOfMax(n, 1) == 0);
	string h1[7] = { "" };
	assert(lookup(h1, 1, "logan") == -1);

	string g[4] = { "selina", "reed", "peter", "sue" };
	assert(differ(h, 4, g, 4) == 2);
	assert(differ(h, 4, g, 0) == 0);
	assert(differ(h, 0, g, 4) == 0);
	assert(differ(h, 0, g, -1) == -1);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "selina?" && g[3] == "sue?");
	assert(rotateLeft(g, 0, 0) == -1);
	assert(rotateLeft(g, 0, -1) == -1);
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "peter?" && g[3] == "reed?");
	assert(rotateLeft(h2, 7, 7) == -1);
	assert(rotateLeft(h2, -1, 7) == -1);
	assert(rotateLeft(h2, 7, 6) == 6 && h2[1] == "reed" && h2[6] == "peter");
	assert(rotateLeft(h2, 7, 0) == 0 && h2[1] == "diana" && h2[6] == "selina");
	assert(rotateLeft(h1, 1, 0) == 0 && h1[0] == "");

	string e[4] = { "diana", "tony", "", "logan" };
	string e1[4] = { "diana", "diana", "", "logan" };
	assert(subsequence(e1, 4, e, 1) == 0);
	assert(subsequence(h, 7, e, 4) == 2);
	assert(subsequence(h, 0, e, 0) == 0);
	assert(subsequence(h, -1, e, 0) == -1);
	assert(subsequence(h, 0, e, -1) == -1);
	assert(subsequence(h, 0, e, 4) == -1);
	assert(subsequence(h1, 1, e, 4) == -1);
	assert(subsequence(h1, 3, e, 4) == -1);
	assert(subsequence(h1, 0, e, 1) == -1);
	assert(subsequence(e, 3, e, 4) == -1);
	string d[6] = { "reed", "reed", "reed", "tony", "tony","" };
	assert(countRuns(d, 6) == 3);
	assert(countRuns(d, 0) == 0);
	assert(countRuns(d, -9) == -1);
	assert(countRuns(d, 1) == 1);

	string f[3] = { "peter", "diana", "steve" };
	string g1[4] = { "selina", "reed", "peter", "sue" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(lookupAny(h, 2, f, 3) == -1);
	assert(lookupAny(h, 7, f, 1) == 6);
	assert(lookupAny(h, 7, h, 7) == 0);
	assert(lookupAny(h, 0, h, 7) == -1);
	assert(lookupAny(h, 7, h, 0) == -1);
	assert(lookupAny(h, 7, g1, 4) == 0);
	assert(flip(f, 3) == 3 && f[0] == "steve" && f[2] == "peter");
	assert(flip(h3, 7) == 7 && h3[0] == "peter" && h3[5] == "reed");
	assert(flip(h3, 0) == 0);
	assert(flip(h3, -1) == -1);


	assert(split(h, 7, "peter") == 3);
	string hh[7] = { "selina", "reed", "diana", "tony", "", "logan", "peter" };
	assert(split(hh, 7, "reed") == 4);
	assert(split(hh, 0, "reed") == 0);
	assert(split(hh, 7, "z") == 7);
	string f1[3] = { "peter", "diana", "steve" };
	assert(split(f1, 3, "steve") == 2);
	assert(split(f1, 3, "zzz") == 3);
	assert(split(f1, -1, "zzz") == -1);
	string k[3] = { "", "", "" };
	assert(split(k, 3, "") == 0);
	assert(split(k, 3, "s") == 3);
	assert(split(k, 1, "") == 0);
	assert(split(k, 1, "@") == 1);
	string hh1[7] = { "selina", "reed", "diana", "tony", "fa", "logan", "peter" };
	assert(split(hh1, 7, "a") == 0);

	cerr << "All tests succeeded" << endl;
}
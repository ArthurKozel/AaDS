#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const long long negative = -100000000000, positive = 100000000000;

class Interval
{
public:
	long long begin;
	long long end;
	Interval()
	{
		begin = negative;
		end = positive;
	}
};

vector <int> keys;
vector <bool> side;   // 0 - left, 1 - right
vector <int> father;

void Create_intervals(Interval* interval, int n)
{
	for(int i = 2; i <= n; i++)
	{
		if(side[i] == 0)
		{
			interval[i].begin = interval[father[i]].begin;
			interval[i].end = keys[father[i]];
		}
		if(side[i] == 1)
		{
			interval[i].end = interval[father[i]].end;
			interval[i].begin = keys[father[i]];
		}

	}
}

bool Proverka(Interval* interval, int n)
{
	for(int i = 2; i <= n; i++)
	{
		if(side[i] == 0 && (keys[i] >= interval[i].end || keys[i] < interval[i].begin))
		{
			return false;
		}

		if(side[i] == 1 && (keys[i] >= interval[i].end || keys[i] < interval[i].begin))
		{
			return false;
		}
	}
	return true;
}

Interval* Read_from_file(int& n)
{
	ifstream fin;
	fin.open("bst.in");
	fin >> n;

	Interval* interval = new Interval[n + 1];
	keys.resize(n + 1);
	side.resize(n + 1);
	father.resize(n + 1);
	fin >> keys[1];

	char side_char;
	for(int i = 2; i <= n; i++)
	{
		fin >> keys[i];
		fin >> father[i];
		fin >> side_char;
		if (side_char == 'L')
			side[i] = 0;
		else
			side[i] = 1;
	}
	fin.close();
	return interval;
}

void Write_to_file(bool is_bst)
{
	ofstream fout;
	fout.open("bst.out");
	if (is_bst == true)
		fout << "YES";
	else 
		fout << "NO";
	fout.close();
}

int main()
{
	int n;
	Interval* interval = Read_from_file(n);
	Create_intervals(interval, n);
	bool is_bst = Proverka(interval, n);
	Write_to_file(is_bst);

	return 0;
}
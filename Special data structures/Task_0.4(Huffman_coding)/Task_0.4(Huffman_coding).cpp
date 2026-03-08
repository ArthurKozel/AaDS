#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

long long length = 0;

void Read_from_file(queue<long long>& massive, int& n)
{
	ifstream fin;
	fin.open("huffman.in");

	fin >> n;

	int temp = 0;
	for (int i = 0; i < n; i++)
	{
		fin >> temp;
		massive.push(temp);
	}

	fin.close();
}

void Min(queue<long long>& massive, queue<long long>& others, long long& min)
{
	if (!massive.empty() && !others.empty())
	{
		if (massive.front() <= others.front())
		{
			min = massive.front();
			massive.pop();
		}
		else
		{
			min = others.front();
			others.pop();
		}
	}
	else
	{
		if (massive.empty())
		{
			min = others.front();
			others.pop();
		}
		else
		{
			min = massive.front();
			massive.pop();
		}
	}
}

void Find_length(queue<long long>& massive, int n)
{
	queue<long long> others;

	while (massive.size() + others.size() > 1)
	{
		long long min_1 = 0;
		long long min_2 = 0;

		Min(massive, others, min_1);
		Min(massive, others, min_2);

		long long sum = min_1 + min_2;
		others.push(sum);
		length += sum;
	}	

}

void Write_to_file()
{
	ofstream fout;
	fout.open("huffman.out");
	fout << length;
	fout.close();

}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n = 0;
	queue<long long> massive;
	Read_from_file(massive, n);
	Find_length(massive, n);
	Write_to_file();

	return 0;
}
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const long plus_infinity = 2000000000;

vector<long> Read_from_file(int& n)
{
	ifstream fin;
	fin.open("input.txt");

	fin >> n;
	vector<long> massive;
	for(int i = 0; i < n; i++)
	{
		int temp;
		fin >> temp;
		massive.push_back(temp);
	}

	fin.close();
	return massive;
}

int Low_limit(vector<long>& massive, int left, int right, long& request_number)
{
	while(left < right)
	{
		int middle = (left + right) / 2;
		if (request_number > massive[middle]) left = middle + 1;
		else  right = middle;
	}
	return left;
}

int Create_length_massive(vector<long>& massive, vector<long>& length)
{
	int size = 0;
	for(size_t i = 0; i < massive.size(); i++)
	{
		int index = Low_limit(length, 0, length.size(), massive[i]);
		length[index] = massive[i];
		if (index > size)
		{
			size++;
		}
	}

	return size;
}

void Write_to_file(int sequence_length)
{
	ofstream fout;
	fout.open("output.txt");

	fout << sequence_length;

	fout.close();
}

int main()
{
	int n = 0;
	vector<long> massive = Read_from_file(n);
	vector<long> length(n + 1, plus_infinity);
	length[0] = -plus_infinity;
	int sequence_length = Create_length_massive(massive, length);
	Write_to_file(sequence_length);

	return 0;
}
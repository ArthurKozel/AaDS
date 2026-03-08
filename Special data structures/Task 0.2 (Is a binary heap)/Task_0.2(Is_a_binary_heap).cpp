#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> Read_from_file(int& n)
{
	ifstream fin;
	fin.open("input.txt");
	fin >> n;
	vector<int> elements;
	elements.push_back(-1);
	int elem;
	while(fin >> elem)
	{
		elements.push_back(elem);
	}
	return elements;
}

void Write_to_file(bool is_binary_heap)
{
	ofstream fout;
	fout.open("output.txt");
	if (is_binary_heap == true)
		fout << "Yes";
	else
		fout << "No";
	fout.close();
}

bool Proverka(vector<int>& massive)
{
	int i = 1;
	while(i <= massive.size()/2)
	{
		if(2*i < massive.size() && massive[i] > massive[2*i])
			return false;
		if ((2 * i + 1) < massive.size() && massive[i] > massive[2 * i + 1])
			return false;
		i = i + 1;
	}
	return true;
}

int main()
{
	int n;
	vector<int> massive = Read_from_file(n); 
	Write_to_file(Proverka(massive));
	return 0;
}
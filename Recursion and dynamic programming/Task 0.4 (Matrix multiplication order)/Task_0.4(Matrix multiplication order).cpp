#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int infinity = 2000000000;

void Read_from_file(int& s, vector<int>& rows, vector<int>& coloums)
{
	ifstream fin;
	fin.open("input.txt");
	fin >> s;
	rows.resize(s);
	coloums.resize(s);
	for(int i = 0; i < s; i++)
	{
		fin >> rows[i] >> coloums[i];
	}
	fin.close();
}

int** Find_best_order(int& s, vector<int> rows, vector<int> coloums)
{
	int** table = new int*[s];
	for(int i = 0; i < s; i++)
	{
		table[i] = new int[s];
	}

	for(int j = 0; j < s; j++)
	{
		for(int i = j; i < s; i++)
		{
			table[i][j] = -1;
		}
	}


	for (int j = 0; j < s; j++)
	{
		for (int i = j; i >= 0; i--)
		{
			if(i == j)
			{
				table[i][j] = 0;
			}
			else if(j == i + 1)
			{
				table[i][j] = rows[i] * coloums[i] * coloums[j];
			}
			else
			{
				int k = i;
				int min = infinity;
				while(k < j)
				{
					int amount = table[i][k] + table[k + 1][j] + rows[i] * coloums[k] * coloums[j];
					if(amount < min)
					{
						min = amount;
					}

					k++;
				}

				table[i][j] = min;
			}
		}
	}

	return table;
}

void Write_to_file(int result)
{
	ofstream fout;
	fout.open("output.txt");
	fout << result;
	
	fout.close();
}

int main()
{
	int s = 0;
	vector<int> rows;
	vector<int> coloums;
	Read_from_file(s, rows, coloums);
	int** table = Find_best_order(s, rows, coloums);
	Write_to_file(table[0][s - 1]);

	return 0;
}


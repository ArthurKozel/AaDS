#include <iostream>

using namespace std;

void Create_table(int** table, int* A, int* B, int n)
{
	for(int i = 0; i <= n; i++)
	{
		table[0][i] = table[i][0] = 0;
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if(A[i - 1] == B[j - 1])
			{
				table[i][j] = table[i - 1][j - 1] + 1;
			}
			else
			{
				if(table[i - 1][j] >= table[i][j - 1])
				{
					table[i][j] = table[i - 1][j];
				}
				else
				{
					table[i][j] = table[i][j - 1];
				}
			}
		}
	}
}

int Find_sequence(int** table, int* A, int* B, int n, int* Posled_1, int* Posled_2)
{
	int i = n, j = n, k = 0;
	while (i > 0 && j > 0)
	{
		if (A[i - 1] == B[j - 1])
		{
			Posled_1[k] = i - 1;
			Posled_2[k] = j - 1;
			k = k + 1;
			i = i - 1;
			j = j - 1;
		}
		else
		{
			if(table[i - 1][j] == table[i][j])
			{
				i = i - 1;
			}
			else
			{
				j = j - 1;
			}
		}
	}
	return k - 1;
}

void Output(int* Sequence, int k)
{
	cout << endl << Sequence[k];
	k = k - 1;
	for (k; k >= 0; k--)
		cout << " " << Sequence[k];
}

int main()
{
	int n;
	cin >> n;
	int* A = new int[n];
	int* B = new int[n];
	for(int i = 0; i < n; i++)
		cin >> A[i];
	for(int i = 0; i < n; i++)
		cin >> B[i];

	int** table = new int* [n + 1];
	for (int i = 0; i < n + 1; i++)
		table[i] = new int[n + 1] {};

	Create_table(table, A, B, n);
	int* Sequence_of_ind_A = new int[n + 1] {};
	int* Sequence_of_ind_B = new int[n + 1] {};
	int k = Find_sequence(table, A, B, n, Sequence_of_ind_A, Sequence_of_ind_B);
	cout << table[n][n];
	if(table[n][n] != 0)
	{
		Output(Sequence_of_ind_A, k);
		Output(Sequence_of_ind_B, k);
	}

	return 0;
}
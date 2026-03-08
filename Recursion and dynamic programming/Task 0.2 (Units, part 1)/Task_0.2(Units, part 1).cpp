#include <iostream>
#include <vector>

using namespace std;

void Create_table(int n, long long** combinations)
{
	int mod = 1000000007;
	for(int i = 0; i <= n; i++)
	{
		combinations[0][i] = combinations[i][i] = 1;
	}
	
	for (int i = 2; i <= n ; i++)
	{
		for (int j = 1; j <= i - 1; j++)
		{
			combinations[j][i] = (combinations[j - 1][i - 1] + combinations[j][i - 1]) % mod;
		}
	}
}

long long Find_elem(int k,int n, long long** combinations)
{
	return combinations[k][n];
}

int main()
{
	int n, k;
	cin >> n >> k;
	long long** combinations = new long long* [n + 1];
	for(int i = 0; i < n + 1; i++)
	{
		combinations[i] = new long long[n + 1] {};
	}

	Create_table(n, combinations);
	cout << Find_elem(k,n, combinations);

	for (int i = 0; i < n + 1; i++)
	{
		delete[] combinations[i];
	}
	delete[] combinations;
	return 0;
}
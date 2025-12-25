#include <iostream>

using namespace std;

int mod = 1000000007;

void Fact(long long* factorial, int n)
{
	for(int i = 1; i <= n; i++)
	{
		factorial[i] = ((factorial[i - 1] % mod) * (i % mod)) % mod;
	}
}

long long Binary_degree(long long a, int degree)
{
	a = a % mod;
	long long result = 1;
	while(degree > 0)
	{
		if(degree % 2 == 1)
		{
			result = (result * a) % mod;
		}
		a = (a * a) % mod;
		degree = degree >> 1;
	}
	return result;
}

long long Product_remainder(long long a, long long b, long long c)
{
	return (((a * b) % mod) * c) % mod;
}

int main()
{
	int n, k;
	cin >> n >> k;
	long long* factorial = new long long[n+1];
	factorial[0] = 1;
	Fact(factorial, n);
	cout << (Product_remainder(factorial[n], Binary_degree(factorial[k], mod - 2), Binary_degree(factorial[n - k], mod - 2)));

	return 0;
}
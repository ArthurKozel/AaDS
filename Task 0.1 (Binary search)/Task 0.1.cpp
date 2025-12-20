#include <iostream>

using namespace std;


bool Binary_search(int* massive, int left, int right, int& request_number)
{
	if ((right - left) == 1 || left == right)
	{
		if (massive[left] == request_number || massive[right] == request_number)  return true;
		else return false;
	}

	int middle = (right + left) / 2;
	if (request_number < massive[middle])
	{
		return Binary_search(massive, left, (middle - 1), request_number);
	}
	else if (request_number > massive[middle])
	{
		return Binary_search(massive, (middle + 1), right, request_number);
	}
	else if (request_number == massive[middle])
	{
		return true;
	}

}


int Low_limit(int* massive, int left, int right, int& request_number)
{
	while (left < right)
	{
		int middle = (left + right) / 2;
		if (request_number > massive[middle]) left = middle + 1;
		else  right = middle;
	}
	return left;
}

int Upper_limit(int* massive, int left, int right, int& request_number)
{
	while (left < right)
	{
		int middle = (left + right) / 2;
		if (request_number < massive[middle]) right = middle;
		else  left = middle + 1;
	}
	return left;
}

int main()
{
	int n;
	cin >> n;
	int* mas = new int[n];
	int i = 0;
	while (i < n) 
	{
		cin >> mas[i];
		i = i + 1;
	}
	int k;
	cin >> k;
	int* reqest_list = new int[k];
	i = 0;
	while (i < k)
	{
		cin >> reqest_list[i];
		i = i + 1;
	}
	i = 0;
	while (i < k)
	{
		cout << Binary_search(mas, 0, n, reqest_list[i]) << " " << Low_limit(mas, 0, n, reqest_list[i]) << " " << Upper_limit(mas, 0, n, reqest_list[i]) << endl;
		i = i + 1;
	}

	return 0;
}
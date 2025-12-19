#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void create_massive(vector<int>& massive)
{
    ifstream fin;
    fin.open("input.txt");
    if (!fin.is_open())
    {
        throw runtime_error("Ошибка открытия файла");
    }
    int number = 0;
    while (fin >> number)
    {
        massive.push_back(number);
    }
    fin.close();
}

vector<int> merge(vector<int>& left, vector<int>& right)
{
    vector<int> merged_massive;
    int left_index = 0, right_index = 0;
    while (left_index < left.size() && right_index < right.size())
    {
        if (left[left_index] <= right[right_index])
        {
            merged_massive.push_back(left[left_index++]);
        }
        else
        {
            merged_massive.push_back(right[right_index++]);
        }
    }
    while (left_index < left.size())
    {
        merged_massive.push_back(left[left_index++]);
    }
    while (right_index < right.size())
    {
        merged_massive.push_back(right[right_index++]);
    }
    return merged_massive;
}

void massive_sort(vector<int>& massive)
{
    if (massive.size() <= 1)
    {
        return;
    }
    int n = massive.size() / 2;
    vector<int> left, right;
    for (int i = 0; i < n; ++i)
    {
        left.push_back(massive[i]);
    }
    for (int i = n; i < massive.size(); ++i)
    {
        right.push_back(massive[i]);
    }

    massive_sort(left);
    massive_sort(right);

    massive = merge(left, right);
}

void Write_to_file(long long sum)
{
    ofstream fout;
    fout.open("output.txt");
    if (!fout.is_open())
    {
        throw runtime_error("Ошибка открытия файла");
    }
    fout << sum;
    fout.close();
}

int main()
{
    try
    {
        vector<int> massive;
        create_massive(massive);
        massive_sort(massive);
        auto new_end_massive = unique(massive.begin(), massive.end());
        massive.erase(new_end_massive, massive.end());
        int i = 0;
        long long sum = 0;
        while (i < massive.size())
        {
            sum = sum + massive[i];
            i = i + 1;
        }
        Write_to_file(sum);
    }
    catch (exception& e)
    {
        cout << e.what();
    }
    return 0;
}

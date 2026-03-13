#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class DSU
{
public:
	int* parents = NULL;
	int* size = NULL;
	int connected_component = 0;
	string output_str = "";

	vector<int> road_begin;
	vector<int> road_end;
	vector<int> destroyed_roads;
	vector<bool> is_destroyed;

	void Create_DSU(int n)
	{
		connected_component = n;
		size = new int[n + 1];
		parents = new int[n + 1];

		size[0] = parents[0] = -1;
		for (int i = 1; i < n + 1; i++)
		{
			size[i] = 1;
			parents[i] = i;
		}
	}

	int FindSet(int element)
	{
		if (parents[element] == element) 
		{
			return element;
		}
		return parents[element] = FindSet(parents[element]);
	}

	int Union(int x, int y)
	{
		int lider_x = FindSet(x);
		int lider_y = FindSet(y);
		if (lider_x != lider_y)
		{
			if (size[lider_y] < size[lider_x])
			{
				int temp = lider_x;
				lider_x = lider_y;
				lider_y = temp;
			}
			parents[lider_x] = lider_y;
			size[lider_y] = size[lider_y] + size[lider_x];
			connected_component = connected_component - 1;
		}
		return connected_component;
	}
	
	void Read_from_file()
	{
		ifstream fin;
		fin.open("input.txt");
		int n = 0, m = 0, q = 0;
		fin >> n >> m >> q;
		Create_DSU(n);
		road_begin.resize(m + 1);
		road_end.resize(m + 1);

		road_end[0] = road_begin[0] = -1;

		for(int i = 1; i < m + 1; i++)
		{
			fin >> road_begin[i] >> road_end[i];
		}

		is_destroyed.resize(m + 1, false);
		is_destroyed[0] = false;

		destroyed_roads.resize(q);
		for(int i = q - 1; i >= 0; i--)
		{
			fin >> destroyed_roads[i];
			is_destroyed[destroyed_roads[i]] = true;
		}

		Building(m, q);

		fin.close();
	}

	void Building(int m, int q)
	{
		int i = 1;
		while(i < m + 1)
		{
			if(is_destroyed[i] == false)
			{
				Union(road_begin[i], road_end[i]);
			}
			i = i + 1;
		}
		i = 0;
		while(i < q)
		{
			Create_output_str();
			Union(road_begin[destroyed_roads[i]], road_end[destroyed_roads[i]]);
			i = i + 1;
		}
	}

	void Create_output_str()
	{
		if (connected_component == 1)
		{
			output_str.push_back('1');
		}
		else
		{
			output_str.push_back('0');
		}
	}

	void Write_to_file()
	{
		ofstream fout;
		fout.open("output.txt");
		string reverse_output_str;
		for (int i = output_str.size() - 1; i >= 0; i--)
		{
			reverse_output_str.push_back(output_str[i]);
		}

		fout << reverse_output_str;

		fout.close();
	}

};


int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	DSU dsu;
	dsu.Read_from_file();
	dsu.Write_to_file();

	return 0;
}
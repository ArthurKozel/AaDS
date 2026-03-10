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
	vector<int> connected_components_massive;


	void Create_DSU(int n)
	{
		connected_component = n;
		size = new int[n + 1];
		size[0] = -1;
		for(int i = 1; i < n + 1; i++)
		{
			size[i] = 1;
		}

		parents = new int[n + 1];
		parents[0] = -1;
		for (int i = 1; i < n + 1; i++)
		{
			parents[i] = i;
		}
	}

	int FindSet(int element)
	{
		int i = element;
		while (parents[i] != i)
		{
			i = parents[i];
		}
		return i;
	}

	int Union(int x, int y)
	{
		int lider_x = FindSet(x);
		int lider_y = FindSet(y);
		if(lider_x != lider_y)
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
		int n = 0, q = 0;
		fin >> n;
		Create_DSU(n);
		fin >> q;
		for(int i = 0; i < q; i++)
		{
			int x = 0, y = 0;
			fin >> x;
			fin >> y;
			connected_components_massive.push_back(Union(x, y));
		}

		fin.close();
	}

	void Write_to_file()
	{
		ofstream fout;
		fout.open("output.txt");
		fout << connected_components_massive[0];
		for(int i = 1; i < connected_components_massive.size(); i++)
		{
			fout << "\n" << connected_components_massive[i];
		}

		fout.close();
	}
};


int main()
{
	DSU dsu;
	dsu.Read_from_file();
	dsu.Write_to_file();

	return 0;
}
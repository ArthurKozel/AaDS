#include <iostream>
#include <vector>

using namespace std;

const int NEG = -1000000;
vector<int> massive;
vector<int> memory;
vector<int> previous;

void Find_best_way(int n)
{
    memory[1] = massive[1];
    if (n >= 3) 
    {
        memory[3] = massive[1] + massive[3];
        previous[3] = 1;
    }
    if (n >= 4) 
    {
        memory[4] = massive[1] + massive[4];
        previous[4] = 1;
    }

    for (int i = 5; i <= n; ++i)
    {  
        int temp1;
        if (i - 3 >= 1 && memory[i - 3] != NEG)
            temp1 = memory[i - 3];
        else 
            temp1 = NEG;


        int temp2;
        if (i - 2 >= 1 && memory[i - 2] != NEG)
            temp2 = memory[i - 2];
        else
            temp2 = NEG;


        if (temp1 == NEG && temp2 == NEG) 
            continue;

        if (temp1 > temp2) 
        {
            memory[i] = temp1 + massive[i];
            previous[i] = i - 3;
        }
        else 
        {
            memory[i] = temp2 + massive[i];
            previous[i] = i - 2;
        }
    }
}


void Output_path(int n) 
{
    vector<int> path;
    for (int cur = n; cur >= 1; cur = previous[cur]) 
        path.push_back(cur);

    cout << path.back();
    for (int i = static_cast<int>(path.size()) - 2; i >= 0; --i) 
        cout << " " << path[i];
}


int main() {
    int n;
    cin >> n;
    massive.resize(n + 1);
    for (int i = 1; i <= n; ++i) 
        cin >> massive[i];

    if (n == 2) 
    {
        cout << -1;
        return 0;
    }

    memory.resize(n + 1, NEG);
    previous.resize(n + 1, -1);
    Find_best_way(n);    
    int sum = memory[n];
    cout << sum << endl;
    Output_path(n);

    return 0;
}
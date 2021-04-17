#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
//Please put this source code in the same directory with SCC.in
//And do NOT change the file name.
/*
This function computes the number of Strongly Connected Components in a graph
Args:
    n: The number of nodes in the graph. The nodes are indexed as 0~n-1
    edge: The edges in the graph. For each element (a,b) in edge, it means
          there is a directed edge from a to b
          Notice that there may exists multiple edge and self-loop
Return:
    The number of strongly connected components in the graph.
*/
int clock;
int *post;
bool *visited;
bool *visited_2;
void POSTVISIT(int n, int num)
{
    post[n - clock] = num;
    clock++;
}
void EXPLORE(int n, int num, vector<pair<int, int>> &edge)
{
    visited[num] = true;
    for (int i = 0; i < edge.size(); ++i)
    {
        if (edge[i].first == num && !visited[edge[i].second])
        {
            EXPLORE(n, edge[i].second, edge);
        }
    }
    POSTVISIT(n, num);
}

void DFS(int n, vector<pair<int, int>> &edge)
{
    for (int i = 1; i < n + 1; ++i)
        if (!visited[i])
        {
            EXPLORE(n, i, edge);
        }
}

void EXPLORE_2(int num, vector<pair<int, int>> &edge)
{
    visited_2[num] = true;
    for (int i = 0; i < edge.size(); ++i)
    {
        if (edge[i].first == num && !visited_2[edge[i].second])
        {
            EXPLORE_2(edge[i].second, edge);
        }
    }
}
int SCC(int n, vector<pair<int, int>> &edge)
{
    vector<pair<int, int>> reversed_edge;
    int a, b;
    for (int i = 0; i < edge.size(); ++i)
    {
        a = edge[i].first;
        b = edge[i].second;
        reversed_edge.push_back(pair<int, int>(b, a));
    }

    clock = 0;
    visited = new bool[n + 1];
    for (int i = 0; i < n + 1; ++i)
        visited[i] = false;
    post = new int[n + 1];
    for (int i = 0; i < n + 1; ++i)
        post[i] = 0;
    DFS(n, reversed_edge);

    int ans = 0;
    visited_2 = new bool[n + 1];
    for (int i = 0; i < n + 1; ++i)
        visited_2[i] = false;
    for (int i = 1; i < n + 1; ++i)
    {
        int num = post[i];
        if (!visited_2[num])
        {
            EXPLORE_2(num, edge);
            ans++;
        }
    }
    return ans;
}
//Please do NOT modify anything in main(). Thanks!
int main()
{
    int m, n;
    vector<pair<int, int>> edge;
    ifstream fin;
    ofstream fout;
    fin.open("SCC.in");
    cout << fin.is_open() << endl;
    fin >> n >> m;
    cout << n << " " << m << endl;
    int tmp1, tmp2;
    for (int i = 0; i < m; i++)
    {
        fin >> tmp1 >> tmp2;
        edge.push_back(pair<int, int>(tmp1, tmp2));
    }
    fin.close();
    int ans = SCC(n, edge);
    fout.open("SCC.out");
    fout << ans << '\n';
    fout.close();
    return 0;
}

#include <iostream>

using namespace std;

#define MAX 10000

const int n = 7;
double p[n + 1] = {0, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14};
double q[n + 1] = {0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};

int root[n + 1][n + 1]; //Record the root node of the optimal subtree
double e[n + 2][n + 2]; //Record the expected cost of the subtree
double w[n + 2][n + 2]; //Record the probability sum of the subtree

void optimal_binary_search_tree(double *p, double *q, int n)
{
    for (int i = 1; i <= n + 1; ++i)
    {
        e[i][i - 1] = w[i][i - 1] = q[i - 1];
    }
    for (int l = 1; l <= n; ++l)
    {
        for (int i = 1; i <= n - l + 1; ++i)
        {
            int j = i + l - 1;
            e[i][j] = INT_MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; ++r)
            {
                double tmp = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (tmp < e[i][j])
                {
                    e[i][j] = tmp;
                    root[i][j] = r;
                }
            }
        }
    }
}

void construct_optimal_bst(int i, int j)
{
    int r = root[i][j];
    if (i == 1 && j == n)
        cout << "k" << r << " is the root\n";

    if (i == r)
    {
        cout << "d" << i - 1 << " is the left child of "
             << "k" << r << '\n';
    }
    else if (i < r)
    {
        cout << "k" << root[i][r - 1] << " is the left child of "
             << "k" << r << '\n';
        construct_optimal_bst(i, r - 1);
    }

    if (j == r)
    {
        cout << "d" << j << " is the right child of "
             << "k" << r << '\n';
    }
    else if (j > r)
    {
        cout << "k" << root[r + 1][j] << " is the right child of "
             << "k" << r << '\n';
        construct_optimal_bst(r + 1, j);
    }
}

int main()
{
    optimal_binary_search_tree(p, q, n);
    cout << "The cost of the optimal binary search tree is: " << e[1][n] << endl;
    cout << "The structure of the optimal binary search tree is: " << endl;
    construct_optimal_bst(1, n);
}

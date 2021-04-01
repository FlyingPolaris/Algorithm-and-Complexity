#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
/*
The process to calculate the dynamic can be divided into four steps:
1.Create an empty cost matrix DTW with X and Y labels as amplitudes of the two series to be compared.
2.Use the given state transition function to fill in the cost matrix.
3.Identify the warping path starting from top right corner of the matrix and traversing to bottom left. The traversal path is identified based on the neighbor with minimum value.
i.e., When we reach the point (i, j) in the matrix, the next position is to choose the point with the smallest cost among (i-1,j-1), (i,j-1), and (i-1,j),
For the sake of simplicity, when the cost is equal, the priority of the selection is (i-1,j-1), (i,j-1), and (i-1,j) in order.
4.Calculate th time normalized distance. We define it as the average cost of the selected points.
*/
using namespace std;

int constrant(int i, int j, int w, int num)
{
    if (abs(i - j) <= w)
        return num;
    else
        return INT_MAX;
}

int minimal(double a, double b, double c)
{
    if (a < b)
    {
        return (a < c) ? a : c;
    }
    else
    {
        return (b < c) ? b : c;
    }
}

double distance(vector<int> x, vector<int> y, int w)
{
    int n = x.size();
    int m = y.size();
    vector<vector<int>> DTW(m);
    for (int i = 0; i < m; ++i)
    {
        DTW[i].resize(n);
    }

    //Use the given state transition function to fill in the cost matrix.
    /*
    Please write your code here.
    */
    DTW[0][0] = abs(x[0] - y[0]);
    for (int i = 1; i < n; ++i)
    {
        DTW[i][0] = constrant(i, 0, w, DTW[i - 1][0] + abs(x[i] - y[0]));
    }
    for (int i = 1; i < m; ++i)
    {
        DTW[0][i] = constrant(0, i, w, DTW[0][i - 1] + abs(x[0] - y[i]));
    }
    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j < m; ++j)
        {
            DTW[i][j] = constrant(i, j, w, minimal(DTW[i - 1][j], DTW[i][j - 1], DTW[i - 1][j - 1]) + abs(x[i] - y[j]));
        }
    }
    vector<int> d;

    int i = n - 1, j = m - 1;
    while (i > 0 || j > 0)
    {
        d.push_back(DTW[i][j]);
        if (i != 0 && j != 0)
        {
            int min = minimal(DTW[i - 1][j], DTW[i][j - 1], DTW[i - 1][j - 1]);
            if (min == DTW[i - 1][j - 1])
            {
                --i;
                --j;
            }
            else if (min == DTW[i][j - 1])
            {
                --j;
            }
            else
            {
                --i;
            }
        }
        else if (i == 0 && j != 0)
        {
            --j;
        }
        else
        {
            --i;
        }
    }

    //Identify the warping path.
    /*
    Please write your code here.
    */

    double ans = 0;
    //Calculate th time normalized distance
    /*
    Please write your code here.
    */
    for (int i = 0; i < d.size(); ++i)
    {
        ans += d[i];
    }
    ans /= (1.0 * d.size());
    return ans;
}

int main()
{
    vector<int> X, Y;
    int w;
    cin >> w;
    //test case 1
    X = {37, 37, 38, 42, 25, 21, 22, 33, 27, 19, 31, 21, 44, 46, 28};
    Y = {37, 38, 42, 25, 21, 22, 33, 27, 19, 31, 21, 44, 46, 28, 28};

    cout << distance(X, Y, w) << endl;
    //test case 2
    X = {11, 14, 15, 20, 19, 13, 12, 16, 18, 14};
    Y = {11, 17, 13, 14, 11, 20, 15, 14, 17, 14};
    cout << distance(X, Y, w) << endl;
    //Remark: when you modify the code to add the window constraint, the distance function has thus three inputs: X, Y, and the size of window w.
    return 0;
}

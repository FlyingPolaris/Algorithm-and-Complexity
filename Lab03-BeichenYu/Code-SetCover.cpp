#include <iostream>

using namespace std;

void quickSort(int s[], int l, int r)
{
    if (l < r)
    {
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while (i < j && s[j] >= x)
                j--;
            if (i < j)
                s[i++] = s[j];
            while (i < j && s[i] < x)
                i++;
            if (i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quickSort(s, l, i - 1);
        quickSort(s, i + 1, r);
    }
}

int Greedy(int x[], int k, int n)
{
    int ans = 1;
    int index = 0;
    int left = x[0], right = left + k;
    quickSort(x, 0, n - 1);
    while (index <= n)
    {
        index++;
        if (x[index] > right)
        {
            ans++;
            left = x[index];
            right = left + k;
        }
    }
    return ans;
}

int main()
{
    //x is the point set P with n=7 nodes in total, and the length of intervals is k=3.
    int x[7] = {1, 2, 3, 4, 5, 6, -2};
    int k = 3;
    int n = sizeof(x) / sizeof(x[0]);
    int num_interval = Greedy(x, k, n);
    cout << num_interval << endl;
    return 0;
}

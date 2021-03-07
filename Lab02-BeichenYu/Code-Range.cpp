#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int binary_search_for_m(vector<long> &sum, long sum_i, int LOWER, int low, int high)
{
	int left = low, right = high - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (sum[mid] - sum_i >= LOWER)
		{
			if (mid == 0 || sum[mid - 1] - sum_i < LOWER)
				return mid;
			else
				left = mid + 1;
		}
		else
			right = mid - 1;
	}
	return high;
}

int binary_search_for_n(vector<long> &sum, long sum_i, int UPPER, int low, int high)
{
	int left = low, right = high - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (sum[mid] - sum_i > UPPER)
		{
			if (mid == 0 || sum[mid - 1] - sum_i <= UPPER)
				return mid;
			else
				left = mid + 1;
		}
		else
			right = mid - 1;
	}
	return high;
}

int merge_count(vector<long> &sum, int low, int high, int LOWER, int UPPER)
{
	int mid = (low + high) / 2;
	if (mid == low)
		return 0;
	int count = merge_count(sum, low, mid, LOWER, UPPER) + merge_count(sum, mid, high, LOWER, UPPER);
	int m_low = mid, m_high = high, n_low = mid, n_high = high;
	for (int i = low; i < mid; i++)
	{
		int m = binary_search_for_m(sum, sum[i], LOWER, m_low, m_high);
		int n = binary_search_for_n(sum, sum[i], UPPER, n_low, n_high);
		count += n - m;
	}
	sort(sum.begin() + low, sum.begin() + high); 
	return count;
}

int main()
{
	int N, LOWER, UPPER;
	vector<int> A;
	vector<long> sum(1, 0); 

	cin >> N >> LOWER >> UPPER;
	for (int tmp, i = 0; i < N; i++)
	{
		cin >> tmp;
		A.push_back(tmp);
		sum.push_back(sum.back() + A.back());
	}

	cout << merge_count(sum, 0, N + 1, LOWER, UPPER) << endl;

	return 0;
}
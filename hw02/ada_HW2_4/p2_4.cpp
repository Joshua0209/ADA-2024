#include "p2_4.h"

#include <numeric>

void merge(std::vector<int> &arr, int left, int mid, int right)
{
    if (get_result(arr[mid], arr[mid + 1]))
    {
        return;
    }
    std::vector<int> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right)
    {
        if (get_result(arr[i], arr[j]))
        {
            temp.push_back(arr[i++]);
        }
        else
        {
            temp.push_back(arr[j++]);
        }
    }
    while (i <= mid)
        temp.push_back(arr[i++]);
    while (j <= right)
        temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); ++k)
    {
        arr[left + k] = temp[k];
    }
}

void merge_sort(std::vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = (left + right) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

std::vector<int> find_permutation(int n)
{
    std::vector<int> ans(n);
    std::iota(ans.begin(), ans.end(), 1);

    merge_sort(ans, 0, n - 1);
    return ans;
}

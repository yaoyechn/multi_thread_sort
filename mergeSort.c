#include "mergeSort.h"

static void merge(int nums[], int lo, int mid, int hi, int temp[])
{
    int i = lo, j = mid + 1;
    int k;
    for (k = lo; k <= hi; k++)
        temp[k] = nums[k];
    
    for (k = lo; k <= hi; k++)
    {
        if (i > mid)                nums[k] = temp[j++];
        else if (j > hi)            nums[k] = temp[i++];
        else if (temp[i] < temp[j]) nums[k] = temp[i++];
        else                        nums[k] = temp[j++];
    }
}

void mergeSort(int nums[], int lo, int hi, int temp[])
{
    if (lo >= hi)    return;
    
    int mid = lo + (hi - lo) / 2;
    mergeSort(nums, lo, mid, temp);
    mergeSort(nums, mid + 1, hi, temp);
    merge(nums, lo, mid ,hi, temp);
}

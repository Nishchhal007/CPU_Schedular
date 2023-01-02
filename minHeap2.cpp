#include <bits/stdc++.h>

using namespace std;

void swap(int a, int b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}

void heapify(int arr[], int n,int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i;
    if (l < n && arr[l] > arr[largest])
    {
        largest = l;
    }
    else if (r < n && arr[r] > arr[largest])
    {
        largest = r;
    }
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr,n, largest);
    }
}

void Build_max_heap(int arr[], int n)
{
    int startIdx = (n - 2) / 2;

    for (int i = startIdx; i >= 0; i--)
    {
        heapify(arr,n, i);
    }
}

void printArr(int arr[],int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << "  ";
    }
}
int main()
{

    int arr[] = {2, 56, 43, 1, 34, 21, 8};

int n = 7;
    Build_max_heap(arr, n);

    printArr(arr,n);


    return 0;
}
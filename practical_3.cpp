#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

// Function to print array
void printArray(const vector<int> &arr)
{
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}

//------------------ MAX HEAP ------------------//
void maxHeapify(vector<int> &arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void maxHeapSort(vector<int> &arr)
{
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}

//------------------ MIN HEAP ------------------//
void minHeapify(vector<int> &arr, int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i)
    {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void minHeapSort(vector<int> &arr)
{
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        minHeapify(arr, i, 0);
    }

    reverse(arr.begin(), arr.end());
}

//------------------ MAIN ------------------//
int main()
{
    int n, choice;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> original(n);

    cout << "\n1. Manual Input\n2. Random Input\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter " << n << " elements:\n";
        for (int i = 0; i < n; i++)
            cin >> original[i];
    }
    else
    {
        srand(time(0));
        for (int i = 0; i < n; i++)
            original[i] = rand() % 1000;
    }

    vector<int> maxHeapArray = original;
    vector<int> minHeapArray = original;

    if (n <= 20)
    {
        cout << "\nOriginal Array:\n";
        printArray(original);
    }

    // Max Heap Sort
    auto startMax = high_resolution_clock::now();
    maxHeapSort(maxHeapArray);
    auto endMax = high_resolution_clock::now();

    // Min Heap Sort
    auto startMin = high_resolution_clock::now();
    minHeapSort(minHeapArray);
    auto endMin = high_resolution_clock::now();

    if (n <= 20)
    {
        cout << "\nSorted Array (Max Heap Sort):\n";
        printArray(maxHeapArray);

        cout << "\nSorted Array (Min Heap Sort):\n";
        printArray(minHeapArray);
    }

    auto maxMicro = duration_cast<microseconds>(endMax - startMax);
    auto maxMilli = duration_cast<milliseconds>(endMax - startMax);

    auto minMicro = duration_cast<microseconds>(endMin - startMin);
    auto minMilli = duration_cast<milliseconds>(endMin - startMin);

    cout << "\n========== EXECUTION TIME ==========\n";

    cout << "\nMax Heap Sort\n";
    cout << "Milliseconds : " << maxMilli.count() << " ms\n";
    cout << "Microseconds : " << maxMicro.count() << " us\n";

    cout << "\nMin Heap Sort\n";
    cout << "Milliseconds : " << minMilli.count() << " ms\n";
    cout << "Microseconds : " << minMicro.count() << " us\n";

    return 0;
}
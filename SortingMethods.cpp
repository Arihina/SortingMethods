#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void readArray(string fileName, int arr[], const int size);
void printArray(int arr[], const int size);
void fillArray(int arr[], const int size);

pair<int, int> selectionSort(int arr[], const int size);
pair<int, int> bubbleSort(int arr[], const int size);
pair<int, int> inserttionSort(int arr[], const int size);
pair<int, int> binaryInput(int arr[], const int size);
pair<int, int> sheikerSort(int arr[], const int size);
pair<int, int> shellSort(int arr[], const int size);
int findInterval(int arr[], const int size);
pair<int, int> heapSort(int arr[], const int size);
void heap(int arr[], int i, const int size, int& countComparison, int& countSwap);
void quickSortRecursion(int arr[], int left, int right, int& countComparison, int& countSwap);
pair<int, int> quickSort(int arr[], const int size);

typedef pair<int, int>(*func) (int arr[], const int size);

int main()
{
    setlocale(LC_ALL, "ru");

    const int SIZE = 200;

    map<string, func> functions{
        {"Selection Sort", selectionSort},
        {"Bubble Sort", bubbleSort},
        {"Inserttion Sort", inserttionSort},
        {"Binary Input", binaryInput},
        {"Sheiker Sort", sheikerSort},
        {"Shell Sort", shellSort},
        {"Heap Sort", heapSort},
        {"Quick Sort", quickSort}
    };

    int sortArray[SIZE]{};
    int reverseArray[SIZE]{};
    int randomArray[SIZE]{};

    pair<int, int> sortData, reverseData, randomData;

    ofstream out;
    out.open("Result.csv");
    out << " ;" << "Sort Array;" << "Reverse Array;" << "Random Array;" << endl;
    for (pair<string, func> function: functions)
    {
        fillArray(randomArray, SIZE);
        fillArray(sortArray, SIZE);
        fillArray(reverseArray, SIZE);

        sort(sortArray, sortArray + SIZE);
        sort(reverseArray, reverseArray + SIZE);
        reverse(reverseArray, reverseArray + SIZE);

        sortData = functions[function.first](sortArray, SIZE);
        reverseData = functions[function.first](reverseArray, SIZE);
        randomData = functions[function.first](randomArray, SIZE);

        cout << function.first << endl;
		out << function.first << ";" << " Comparison = " << sortData.first << " Swap = " << sortData.second << ";" << " Comparison = " 
            << reverseData.first << " Swap = " << reverseData.second << ";" << " Comparison = " << randomData.first << " Swap = " << randomData.second << endl;
        cout << "Sort Array: " << " Comparison = " << sortData.first << " Swap = " << sortData.second << endl;
        cout << "Reverse Array: " << " Comparison = " << reverseData.first << " Swap = " << reverseData.second << endl;
        cout << "Random Array: " << " Comparison = " << randomData.first << " Swap = " << randomData.second << endl;
        cout << "\n";
    }
    out.close();
}

void readArray(string fileName, int arr[], const int size) {
    ifstream fin; 
    string line;
    fin.open(fileName);

    for (int i = 0; i < size; i++)
    {
        fin >> line;
        arr[i] = stoi(line);
    }

    fin.close();
}

void printArray(int arr[], const int size) {
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }

}

void fillArray(int arr[], const int size) {
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 101;
    }
}

pair<int, int> selectionSort(int arr[], const int size) {

    int index, countComparison = 0, countSwap = 0;
    for (int i = 0; i < size - 1 ; i++)
    {
        index = i;
        countComparison++;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[index]) {
                index = j;
                countSwap++;
            }
        }
        swap(arr[i], arr[index]);
    }
    return make_pair(countComparison, countSwap);
}

pair<int, int> bubbleSort(int arr[], const int size) {

    int countComparison = 0, countSwap = 0;
    for (int i = 0; i < size - 1; i++)
        for (int j = size - 1; j > i; j--) {
            countComparison++;
            if (arr[j - 1] > arr[j]) {
                swap(arr[j - 1], arr[j]);
                countSwap++;
            }
        }
    return make_pair(countComparison, countSwap);
}

pair<int, int> inserttionSort(int arr[], const int size) {

    int temp, j, countComparison = 0, countSwap = 0;

    for (int i = 1; i < size; i++)
    {
        j = i;
        temp = arr[i];
        countComparison++;
        while (j > 0 && temp < arr[j-1])
        {
            arr[j] = arr[j - 1];
            j--;
            countSwap++;
        }
        arr[j] = temp;
    }
    return make_pair(countComparison, countSwap);
}

pair<int, int> sheikerSort(int arr[], const int size) {

    int l = 1, r = size - 1, k = size - 1, countComparison = 0, countSwap = 0;

    while (l<=r)
    {
        for (int i = r; i >= l; i--)
        {
            countComparison++;
            if (arr[i - 1] > arr[i])
            {
                int x = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = x;
                k = i;
                countSwap++;
            }
        }
        l = k + 1;
        for (int i = l; i <= r; i++)
        {
            countComparison++;
            if (arr[i - 1] > arr[i])
            {
                int x = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = x;
                k = i;
                countSwap++;
            }
        }
        r = k - 1;
    }
    return make_pair(countComparison, countSwap);
}

pair<int, int> binaryInput(int arr[], const int size) {

    int x, left, right, middle, countComparison = 0, countSwap = 0;

    for (int i = 1; i < size; i++)
    {
        x = arr[i];
        left = 0;
        right = i - 1;
        do
        {
            countComparison++;
            middle = (left + right) / 2;
            (x < arr[middle]) ? right = middle - 1 : left = middle + 1;
        } while (left<=right);
        for (int j = i - 1; j >= left ; j--)
        {
            arr[j + 1] = arr[j];
            countSwap++;
        }
        arr[left] = x;
    }
    return make_pair(countComparison, countSwap);
}

int findInterval(int arr[], const int size) {
    int mul1 = 1, mul2 = 1, mul3 = 1, counter = -1;
    do
    {
        if (++counter % 2)
        {
            mul2 *= 2;
            arr[counter] = 8 * mul1 - 6 * mul2 + 1;
        }
        else
        {
            arr[counter] = 9 * mul1 - 9 * mul3 + 1;
            mul3 *= 2;
        }
        mul1 *= 2;
    } while (3 * arr[counter] < size);

    return ((counter > 0) ? (--counter) : (0));
}

pair<int, int> shellSort(int arr[], const int size) {
    const int interval_count = 30;
    int interval, counter, j, countComparison = 0, countSwap = 0;
    int interval_arr[interval_count];
    counter = findInterval(interval_arr, size);

    while (counter >= 0)
    {
        interval = interval_arr[counter--];
        for (int i = interval; i < size; i++)
        {
            countComparison++;
            int temp = arr[i];
            for (j = i - interval; (j >= 0) && (arr[j] > temp); j -= interval)
            {
                arr[j + interval] = arr[j];
                countSwap++;
            }
            arr[j + interval] = temp;
        }
    }
    return make_pair(countComparison, countSwap);
}

void heap(int arr[], int i, const int size, int& countComparison, int& countSwap) {
    int max = i;
    while (true)
    {
        int child = 2 * i + 1;
        if (child < size && arr[child] > arr[max])
        {
            countComparison++;
            max = child;
        }
        child++;
        if (child < size && arr[child] > arr[max])
        {
            countComparison++;
            max = child;
        }
        if (max == i)
            break;
        else {
            swap(arr[max], arr[i]);
            countSwap++;
            i = max;
        }
    }
}
pair<int, int> heapSort(int arr[], int size) {
    int countComparison = 0, countSwap = 0;
    for (int i = size / 2; i >= 0; i--)
        heap(arr, i, size, countComparison, countSwap);
    for (int i = size - 1; i >= 1; i--)
    {
        swap(arr[0], arr[i]);
        countSwap++;
        heap(arr, 0, i, countComparison, countSwap);
    }
    return make_pair(countComparison, countSwap);
}

void quickSortRecursion(int arr[], int left, int right, int& countComparison, int& countSwap) {
    int i = left, j = right, mid = arr[(left + right) / 2];
    if (left > right)
        return;
    while (i <= j)
    {
        countComparison++;
        while (arr[i] < mid) { i++; }
        while (arr[j] > mid) { j--; }
        if (i <= j)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
            countSwap++;
        }
    }
    quickSortRecursion(arr, left, j, countComparison, countSwap);
    quickSortRecursion(arr, i, right, countComparison, countSwap);
}

pair<int, int> quickSort(int arr[], const int size) {
    int countComparison = 0, countSwap = 0;
    quickSortRecursion(arr, 0, size-1, countComparison, countSwap);
    return make_pair(countComparison, countSwap);
}
/*
@author Hasan Masum. 
@Id 1805052, Department of CSE BUET
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
using namespace std;

class Sorting
{
private:

    /**
     * swap the value of a and b.
     */
    static void swap(int &a, int &b)
    {
        if (a == b)
            return;

        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }

    /**
     * Apply partition for the part of the array from start idx to end idx
     * by taking last element as pivot.
     * 
     * Partition is the key of Quick sort algorithm.
     * Partition rearrange the array and find the a index between startIdx and endIdx inclusive
     * named partitionIdx which Partition (rearrange) the array a[startIdx .. endIdx] 
     * into two (possibly empty) subarrays a[startIdx : : partitionIdx-1] 
     * and a[partitionIdx + 1 : : endIdx] such that each element of a[startIdx : : partitionIdx-1] is
     * less than or equal to a[partionIdx], which is, in turn, less than or equal to 
     * each element of a[partitionIdx + 1 : : endIdx]
     * 
     * @param a[] is the array for which we will apply partition
     * @param startIdx is the start index of the part of the array(inclusive)
     * @param endIdx is the last index of the part of the array(inclusive)
     * 
     * @return the partition index 
     * 
     */
    static int partition(int a[], int startIdx, int endIdx)
    {
        // take last element as pivot
        int pivot = a[endIdx];
        // pointer to partition idx;
        int partitionIdx = startIdx;

        // traverse from startIdx to endIdx to find the partition idx
        // here we swap all the numbers right of the pivot
        // which are less then the pivot
        for (int i = startIdx; i < endIdx; i++)
        {
            // if the number less than pivot
            if (a[i] <= pivot)
            {
                swap(a[partitionIdx], a[i]);
                partitionIdx++; // point to next number as partition index
            }
        }

        // finally we swap the pivot with partition idx
        swap(a[partitionIdx], a[endIdx]);

        return partitionIdx;
    }

public:

    /**
     * Quick sort applies the divide and conquer paradigm to sort an array
     * 
     * 
     * @param a is the array we want to sort
     * @param startIdx is the start index of the array(inclusive)
     * @param endIdx is the end index of the array(inclusive)
     */
    static void quickSort(int a[], int startIdx, int endIdx)
    {
        // base case
        if (startIdx >= endIdx)
            return;

        int partitionIdx = partition(a, startIdx, endIdx);
        quickSort(a, startIdx, partitionIdx - 1);
        quickSort(a, partitionIdx + 1, endIdx);
    }

    // MERGE SORT
    /**
     * Merge sort applies the divide and conquer paradigm to sort an array
     * 
     * 
     * @param a is the array we want to sort
     * @param startIdx is the start index of the array(inclusive)
     * @param endIdx is the end index of the array(inclusive)
     */
    static void mergeSort(int ar[], int start, int end){
        // RECURSIVE MERGE SORT ===============================
        if (start == end) // BASE CASE
            return;

        int mid = start + (end - start) / 2;

        //cout << start << " " << mid << " " << end<<endl;

        mergeSort(ar, start, mid);
        mergeSort(ar, mid + 1, end);

        // MERGE ==============================================
        int size = end - start + 1;
        int tempAr[size];

        for (int i = start, j = mid + 1, k = 0; k < size; k++)
        {
            if (i == mid + 1)
                tempAr[k] = ar[j++];
            else if (j == end + 1)
                tempAr[k] = ar[i++];

            //else compare elements
            else if (ar[i] < ar[j])
                tempAr[k] = ar[i++];
            else
                tempAr[k] = ar[j++];
        }

        for (int i = 0, j = start; i < size; i++, j++)
        {
            ar[j] = tempAr[i];
        }
    }
};

void createRandom(int a[], int length, int order)
{
    // Use current time as seed for random generator
    srand(time(0));
    //ascending
    if (order == 1)
    {
        a[0] = rand() % 5;
        for (int i = 1; i < length; i++)
        {
            a[i] = a[i - 1] + 1 + rand() % 5;
        }
    }
    //descending
    else if (order == 2)
    {
        a[0] = length + rand() % 5;
        for (int i = 1; i < length; i++)
        {
            a[i] = a[i - 1] - 1 - rand() % 5;
        }
    }
    //random
    else if (order == 3)
    {
        for (int i = 0; i < length; i++)
        {
            a[i] = rand();
        }
    }
}

void createCopy(int a[], int b[], int length)
{
    for (int i = 0; i < length; i++)
    {
        b[i] = a[i];
    }
}

double timeInMs(double diff)
{
    return diff / CLOCKS_PER_SEC;
}

/*
4MB stack size
g++  -Wl,--stack,100000000 main.cpp
g++  -Wl,--stack,10000000000 main.cpp
a.exe

*/
int main(int argc, char const *argv[])
{

    //freopen("out.txt", "w", stdout);

    // take user input
    int n, order;
    cout << "Enter number of intergers: ";
    cin >> n;
    cout << "1 for Ascending, 2 for desending, 3 for random." << endl;
    cout << "Enter order mentioned above: ";
    cin >> order;
    cout << endl;

    if (order > 3)
    {
        cout << "Invalid order!" << endl;
        return 0;
    }

    // CREATE ARRAY ================================================================
    int a[n], merge_copy[n], quick_sort_copy[n];
   
    cout << "Generating random numbers ";
    if(order == 1)
        cout << "in ascending order" << endl;
    else if(order == 2)
        cout << "in descending order" << endl;
    else
        cout << "in random order" << endl;

    clock_t startTime = clock();
    createRandom(a, n, order);
    cout << "Array Creation took: " << timeInMs(clock() - startTime) << " s" << endl;

    //create copy of the random array
    createCopy(a, merge_copy, n);
    createCopy(a, quick_sort_copy, n);
    cout << "Created copy for merge and quick sort" << endl
         << endl;

    ofstream fout("Input_arr.txt");
    cout << "Saving input array to a text file" << endl;
    for (int i = 0; i < n; i++)
    {
        fout << a[i] << " ";
    }
    fout.close();
    cout << "Input array Saved to a file" << endl
         << endl;

    // MERGE SORT ================================================================
    time_t now = time(0);
    // convert now to string form
    char *currentTime = ctime(&now);
    cout << "merge sort started at " << currentTime << "Please wait..." << endl;

    startTime = clock();
    Sorting::mergeSort(merge_copy, 0, n - 1);

    now = time(0);
    // convert now to string form
    currentTime = ctime(&now);
    cout << "merge sort finished at " << currentTime << endl;
    cout << "Mergesort taken: " << timeInMs(clock() - startTime) << " s" << endl
         << endl;
    //cout << "mergesort taken: " << float(clock() - merge_sort_start_time) / CLOCKS_PER_SEC << endl;

    /*  for (int i = 0; i < n; i++)
    {
        cout << merge_copy[i] << " ";
    }
    cout << endl; */

    now = time(0);
    // convert now to string form
    currentTime = ctime(&now);
    cout << "Quick sort started at " << currentTime << "Please wait..." << endl;

    startTime = clock();
    Sorting::quickSort(quick_sort_copy, 0, n - 1);

    now = time(0);
    // convert now to string form
    currentTime = ctime(&now);
    cout << "Quick sort finished at " << currentTime << endl;
    cout << "QuickSort taken: " << timeInMs(clock() - startTime) << " s" << endl
         << endl;
    //cout << "mergesort taken: " << float(clock() - merge_sort_start_time) / CLOCKS_PER_SEC << endl;
    /* for (int i = 0; i < n; i++)
    {
        cout << quick_sort_copy[i] << " ";
    }
    cout << endl; */

    //check if matched========================================
    int stl_sort[n];
    createCopy(a, stl_sort, n);
    cout << endl
         << "stl sort started. " << endl;
    startTime = clock();
    sort(stl_sort, stl_sort + n);
    cout << "stl sort taken: " << timeInMs(clock() - startTime) << " s" << endl
         << endl;

    /*  for (int i = 0; i < n; i++)
    {
        cout << stl_sort[i] << " ";
    }
    cout << endl; */

    int i = 0;
    cout << "Checking if merge and quick sort result match with stl sort" << endl;
    for (i = 0; i < n; i++)
    {
        if (stl_sort[i] != merge_copy[i])
        {
            cout << "mismatch at idx " << i << endl;
            cout << "mismatched value: " << stl_sort[i] << endl;
            break;
        }

        if (stl_sort[i] != quick_sort_copy[i])
        {
            cout << "mismatch at idx " << i << endl;
            cout << "expected value: " << stl_sort[i] << endl;
            cout << "quick sort value: " << quick_sort_copy[i] << endl;
            break;
        }
    }

    if (i == n)
    {
        cout << "all matched" << endl;
        ofstream fout("sorted_arr.txt");
        cout << "saving sorted array to a file" << endl;
        for (int i = 0; i < n; i++)
        {
            fout << stl_sort[i] << " ";
        }
        fout.close();
        cout << "Sorted array saved" << endl;
    }

    return 0;
}

#pragma once
using namespace std;
/**
 * heap class items start from index 0
 * so for node i 
 * parent: floor( (i-1)/2 )
 * left child : 2*i + 1
 * right child: 2*i + 2
 * 
 * if n is the total node
 * leaf node: floor(n/2) to n-1
 * non-leaf node: floor(n/2)-1 to 0
 * 
 * in case a node is empty, we use INT32_MIN(-2147483648) as an invalid number
 */
class Heap
{
private:
    // predefined heap size
    // can't change the size
    int heapSize;
    // length denotes number of nodes in the heap
    // length is also used to insert a new node in length number index
    // before getting overflow.
    int length;
    // array of items.
    int *items;

    /**
     * max hepify a sub-tree of the binary tree.
     * bubble up a greater value than the current root value of the sub-tree.
     * 
     * if h is the hight of the sub-tree.
     * max_hepify takes at most h steps in worst case
     * to hepify the sub-tree.
     * h = log(n), where n is number of items or node
     * so it has O(log(n)) complexity.
     */
    void max_hepify(int root)
    {
        //index out of range
        if (root < 0 || root >= heapSize)
            return;

        // index of the binary tree items start from index 0
        int left = 2 * root + 1;  // left child
        int right = 2 * root + 2; // right child

        // assume root of the sub-tree has max value
        int maxValueIdx = root;

        //check if left child is greater than the root
        if (left < length && items[left] > items[root])
        {
            maxValueIdx = left;
        }

        // check if right child is greater than the root
        if (right < length && items[right] > items[maxValueIdx])
        {
            maxValueIdx = right;
        }

        // if root is less than from one of it's child then
        // we have to hepify the child node sub-tree again.
        if (maxValueIdx != root)
        {
            this->swap(items[maxValueIdx], items[root]);
            max_hepify(maxValueIdx);
        }
    }

    // swap two elements
    void swap(int &a, int &b)
    {
        a ^= b;
        b ^= a;
        a ^= b;
    }

public:
    /**
     * only constructor to create a heap class with predefined size
     * @param size is the maximum possible size of the heap
     */
    Heap(int size)
    {
        this->heapSize = size;
        items = new int[size];
        this->length = 0;

        // initialize with INT32_MIN to denote that
        // items has not inserted at position i yet.
        for (int i = 0; i < size; i++)
            items[i] = INT32_MIN;
    }

    /**
     * copy constructor of heap class
     */
    Heap(const Heap &h)
    {
        heapSize = h.heapSize;
        length = h.length;
        items = new int[heapSize];
        for (int i = 0; i < heapSize; i++)
        {
            items[i] = h.items[i];
        }
    }

    ~Heap()
    {
        delete[] items;
    }

    /**
     * insert a new item in the heap
     * insert the value at the end of the heap
     * than bubble it up if value is larger than it roots
     * 
     * complexity: as in worst case we have to bubbl up the value from bottom to top
     * which is equal to hight of the complete binary tree.
     * so insertion has complexity O(log(n))
     */
    void insert(int value)
    {
        if (length == heapSize)
        {
            cout << "Error inserting! Overflow!! You have reached max heap size " + heapSize << endl;
            return;
        }

        // cout << "inserting " << value << " to index " << length << endl;
        // STEP-1: INSERT ELEMENT AT THE END OF THE ARRAY ====================
        items[length] = value;
        //debugPrint();

        // STEP-2: BUBBLE UP THE VALUE IF NECESSARY ================================
        // if h is the hight of the tree.
        // this takes steps at most h steps at worst case
        int child = length;
        // as heap is started from index 0
        // root of child is floor((i-1)/2)
        int root = (child - 1) / 2;
        while (child > 0 && items[child] > items[root])
        {
            // cout << items[child] << " at index " << child << " is greater than root " << items[root] << " at index " << root << endl;
            this->swap(items[child], items[root]);
            child = root;
            root = (child - 1) / 2;
        }
        //debugPrint();
        //cout << endl;

        //increase the length
        // this also points to the position where next element will be inserted.
        length++; 
    }

    /**
     * return initialy allocated size of the heap.
     */
    int size()
    {
        return this->heapSize;
    }

    /**
     *  return the max in O(1)
     *  return INT32_MIN if Heap is empty
     */
    int getMax()
    {
        return items[0];
    }

    /**
     * delete the top max value of the Heap
     * if Heap is empty print an error message and return.
     * 
     * complexity: O(log(n)) as it calls the max_hepify which has complexity O(log(n))
     */
    void deleteKey()
    {
        if (length == 0)
        {
            cout << "Error deleting key. Heap is empty" << endl;
            return;
        }

        // cout << "deleting max item : "<<items[0]<< endl;
        // STEP-1: BRING LAST ITEM ON TOP TO DELETE THE CURRNT TOP==============
        items[0] = items[length - 1];
        //debugPrint();
        length--; // decrease the length
        // this will ignore the the max value in max hepify call.

        // STEP-2: MAX HEPIFY THE ROOT OF TREE =================================
        max_hepify(0); // has complexity O(log(n) )

        // now set an INVALID number at the last index as it is considered deleted
        items[length] = INT32_MIN;
    }

    void debugPrint()
    {
        for (int i = 0; i < heapSize; i++)
        {
            cout << items[i] << " ";
        }
        cout << endl;
    }
};

void heapsort(vector<int> &v)
{
    //BUILD HEAP ==================================
    int n = v.size();
    Heap h(n);
    // every insert take O(log(n))
    // so complexity : O(nlog(n))
    for (auto i : v)
    {
        h.insert(i);
    }

    // EXTRACT VALUES FROM HEAP ==================
    for (int i = 0; i < n; i++)
    {
        v[i] = h.getMax();
        h.deleteKey();
    }
}



/// EXTRA===================================================================================
// HEAP SORT IN ASCENDING ORDER WITHOUT USING HEAP CLASS.===================================
void swap(int &a, int &b)
{
    a ^= b;
    b ^= a;
    a ^= b;
}

void max_hepify(vector<int> &numbers, int root, int end)
{
    //index out of range
    if (root < 0 || root > end)
        return;

    int left = 2 * root + 1;
    int right = 2 * root + 2;

    int max = root;

    //check if left child is greater than the root
    if (left <= end && numbers[left] > numbers[root])
    {
        max = left;
    }

    // check if right child is greater than the root
    if (right <= end && numbers[right] > numbers[max])
    {
        max = right;
    }

    //if root is swaped with one of it's child then
    // we have to hepify the child node again.
    if (max != root)
    {
        swap(numbers[max], numbers[root]);
        max_hepify(numbers, max, end);
    }
}

/* void debugVector(vector<int> v)
{
    for (auto i : v)
        cout << i << " ";
    cout << endl;
} */
void heapsortAsc(vector<int> &numbers)
{
    // BUILD HEAP ===================================
    int n = numbers.size();
    // max-hepfiy the non-laef nodes
    // non-leaf node starts from floor(n)
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        max_hepify(numbers, i, n - 1);
    }

    // debugVector(numbers);
    //cout << " yo" << endl;

    // EXTRACT THE MAX ==============================
    int end = n - 1;
    while (end > 0)
    {
        swap(numbers[0], numbers[end]);
        //debugVector(numbers);
        max_hepify(numbers, 0, --end);
    }
}

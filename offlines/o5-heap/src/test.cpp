#include<iostream>
#include<queue>
#include "heap.h"
using namespace std;

vector<string> convertQueueToVector(priority_queue<string> pq){
    vector<string> v;
    while(!pq.empty()){
        v.push_back(pq.top());
        pq.pop();
    }
    return v;
}

void test(){
    priority_queue<string> pq;

    pq.emplace("orange");
    pq.emplace("strawberry");
    pq.emplace("apple");
    pq.emplace("pear");

    cout << "size: " << pq.size() << endl;

    for (auto s : convertQueueToVector(pq))
        cout << s << " ";

    cout << endl
         << "size: " << pq.size() << endl;

    while (!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl
         << "size: " << pq.size() << endl;
}

/* void debugVector(vector<int> v)
{
    for (auto i : v)
        cout << i << " ";
    cout << endl;
} */

/*
g++ test.cpp
a.exe
*/
int main()
{
    vector<int> v = {1, 5, 10, 15, 20, 30, 100};

    Heap heap(v.size());
    cout << "heap size is : " << heap.size() << endl;
    heap.debugPrint();
    

    for(auto i: v)
        heap.insert(i);

    heap.debugPrint();

    for (int i = 0; i < heap.size(); i++){
        heap.deleteKey();
        heap.debugPrint();
    }
       

   // debugVector(v);
    heapsort(v);
    for (auto i : v)
    {
        cout << i << " ";
    }
    cout << endl;
    heapsortAsc(v);
    for (auto i : v)
    {
        cout << i << " ";
    }
    cout << endl;
    // debugVector(v);
    return 0;
}

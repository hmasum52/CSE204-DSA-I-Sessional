#include<iostream>
using namespace std;

class Array{
private:
    /* data */
    string *ar;
public:
    Array(/* args */);
    ~Array();
};

Array::Array(){
    ar = new string[16];
}

Array::~Array(){
    delete ar;
}


int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

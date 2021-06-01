
#include <iostream>
#include <queue>

using namespace std;
class Person
{
    int id;
    int cityId;
    

public:
    struct PersonCmp
    {
        bool operator()(Person &a, Person &b)
        {
            return a.getId() > b.getId();
        }
    };
    
    Person(int cityId, float id)
    {
        this->id = id;
        this->cityId = cityId;
    }

    int getId() { return id; }
    int getCityId() { return cityId; }
    
};



main(int argc, char const *argv[])
{

    priority_queue<Person, vector<Person>, Person::PersonCmp> mypq;
    //priority_queue<int, vector<int>, greater<int>> mypq;

    mypq.push(Person(4, 0));
    mypq.push(Person(1, 2));
    mypq.push(Person(1, 1));
    mypq.push(Person(7, 3));

    while (!mypq.empty())
    {
        Person person = mypq.top();
        cout << person.getId() << " " << person.getCityId()<<endl;
        mypq.pop();
    }

    return 0;
}

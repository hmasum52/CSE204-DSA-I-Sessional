// author: Hasan Masum
// created: 29/04/2021
// last edited : 02/05/2021
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

class Person
{
    //id of the person
    int id;
    //id of the city from where the person star traversal
    int cityId;

public:
    /**
     * comparator to make a min heap using priority queue
     */
    struct PersonCmp
    {
        bool operator()(Person &a, Person &b)
        {
            return a.getId() > b.getId();
        }
    };

    Person(int cityId, float id){
        this->id = id;
        this->cityId = cityId;
    }

    int getId() { return id; }
    int getCityId() { return cityId; }
};

class CityGraph
{
private:
    const string DEBUG = "CityGraph->";

    //graph data ===================================================
    //number of node in the graph
    int numberOfCity;
    //store graph in this adajacency list
    vector<vector<int>> adjancencyList; //adjacency list
    //for graph traversal
    vector<int> visited;

    //mission data==================================================

    // total pieces to collect to accomplish the mission
    int totalPieces;

    // this map store the information where pieces are hidden
    // key : city id
    // value: number of pieces hidden in that city
    map<int, int> pieceMap;

    // create a min heap using priority queue by person id(friend id)
    // In piece collection mission friends will work following their ID in asending order.
    // So using a min heap we can easily get the person(friend) who will collect next.
    priority_queue<Person, vector<Person>, Person::PersonCmp> missionQueue;

    /**
     * recursive dfs function.
     * 
     * @param startCity is the node where a friend start collecting pieces
     */
    int dfs(int startCity)
    {
        // check if a freind already visited the city
        if (visited[startCity]){
            //cout << startCity << "-visited"<< " ";
            return 0;
        }
           

        //cout << "start: " << startCity << endl;

        // STEP-1: MARK THE CURRENT NODE IN RECURSIVE CALL AS VISITED
        visited[startCity] = 1;
        //cout << startCity << " ";
        int totalCollectedPieces = this->pieceMap[startCity];

        for (auto endCity : adjancencyList[startCity])
            // STEP-2: IF A NODE IS NOT VISITED
            // GO TO THAT ADJACENT NODE
            if (!visited[endCity])
                totalCollectedPieces += dfs(endCity);

        return totalCollectedPieces;
    }

    /**
     * bfs implementation using queue
     * 
     * @param startCity is the node where a friend start collecting pieces
     */
    int bfs(int startCity)
    {
        // cout << DEBUG << "bfs()" << endl;
        // check if a freind already visited the city
        if (visited[startCity])
            return 0;

        // STEP-1: TAKE A QUEUE AND PUSH THE START NODE
        queue<int> q;
        q.push(startCity);

        // STEP-2: MARK START NODE AS VISITED
        visited[startCity] = 1;

        int totalCollectedPieces = 0;
        while (!q.empty())
        {
            // STEP-3: TAKE THE FRONT NODE FROM QUEUE AND POP IT
            int next = q.front();
            q.pop();

            // cout << next << " ";

            totalCollectedPieces += pieceMap[next];

            // STEP-4: VISIT ALL THE ADJACENT NODES
            for (auto v : adjancencyList[next])
            {
                if (!visited[v])
                {
                    visited[v] = 1;
                    q.push(v);
                }
            }
        }

        return totalCollectedPieces;
    }

public:
    static const int TRAVERSE_USING_BFS = 0;
    static const int TRAVERSE_USING_DFS = 1;

    CityGraph(int numberOfCity)
    {
        this->numberOfCity = numberOfCity;
        adjancencyList.assign(numberOfCity, {});
        visited.assign(numberOfCity, 0);
        totalPieces = 0;
    }

    /**
     * add an edge in the graph
    */
    void addRoad(int start, int end)
    {
        adjancencyList[start].push_back(end);
        adjancencyList[end].push_back(start);
    }

    /**
     * @param city is the city id where computer pieces are hidden.
     * @param pieces is the number of pieces hidden.
     */
    void addPiece(int city, int pieces)
    {
        pieceMap[city] = pieces;
        totalPieces += pieces;
    }

    /**
     * @param startCityId is where a person(friend) will start collecting computer pieces
     * @param personId is the id of the person(friend). person with lower id has higher priority while collecting.
     */
    void addPerson(int startCityId, int personId)
    {
        missionQueue.push(Person(startCityId, personId));
    }

    void addPerson(Person person)
    {
        missionQueue.push(person);
    }

    /**
     * must call the method before starting the mission 
     */
    int clearVisited()
    {
        this->visited.assign(numberOfCity, 0);
    }

    /**
     * @param method is the method of traversal
     * method can be either TRAVERSE_USING_BFS or TRAVERSE_USING_DFS
     */
    void startMission(int method)
    {
        //clear visited
        this->clearVisited();

        // STEP-1: create a vector to store number of pieces that person collects ===================
        // index of vector: person id(as person id starts from 0)
        // value at index i: number of collected pieces
        vector<int> ans(missionQueue.size());

        // counter to count total how many pieces that will be collected in the mission
        int total = 0;

        //STEP-2: start collecting pieces
        while (!missionQueue.empty())
        {
            // get the person with higher priority
            Person person = missionQueue.top();
            missionQueue.pop(); //remove ther person from the priority queue
           // cout <<endl<< person.getId() << " : ";

            // STEP-3: traverse the city to collect the pieces
            ans[person.getId()] = (method == TRAVERSE_USING_BFS) 
                                    ? this->bfs(person.getCityId()) : this->dfs(person.getCityId());
            // cout << endl;
            total += ans[person.getId()];
        }

       // cout << endl;
       
        // STEP-4: Check if all the pieces are collected or not
        if (this->totalPieces == total)
        {
            cout << "Mission Accomplished" << endl;
        }
        else
            cout << "Mission Impossible" << endl;

        cout << total << " out of " << this->totalPieces << " pieces are collected" << endl;

        // STEP-5: print person id and number of collected pieces
        for (int i = 0; i < ans.size(); i++)
        {
            cout << i << " collected " << ans[i] << " pieces" << endl;
        }
    }

    /**
     * for debugging
     */
    void printAdj()
    {
        for (int i = 0; i < adjancencyList.size(); i++)
        {
            cout << "city " << i << ": ";
            for (auto c : adjancencyList[i])
                cout << c << ",";
            cout << endl;
        }
    }
};

/*
g++ citygraph.cpp
a.exe<tc1.txt>out.txt
*/
/*
g++ citygraph.cpp
a.exe<tc1.txt
*/
int main(int argc, char const *argv[])
{

   // freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout); //output to a file

    // c = number of cities
    // r = number of roads in mamaland
    // l = total number of locations where pieces are hidden
    // f = number of friends
    int c, r, l, f;
    cin >> c >> r >> l >> f;
    //cout << "c: " << c << " r: " << r << " l: " << l << " f: " << f << endl;

    CityGraph graph(c);

    /*
    Each of the following r lines contains two space-separated
    integers c1 and c2,denoting two cities of Mamaland connected by a road.
     All the roadsare two-way roads
    */
    int c1, c2;
    //cout << "roads: " << endl;
    for (int i = 0; i < r; i++)
    {
        cin >> c1 >> c2;
        // cout << "i: " << i << " c1: " << c1 << " c2: " << c2 << endl;
        graph.addRoad(c1, c2);
    }
    //cout << "End of taking input roads" << endl;

    /*
    Each of the following l lines contains two space-separated integers cx and py
    where 
    cx = the city cx, 
    px = total px number of pieces hidden in city cx
    */
    int cx, px;

    //cout << "Pieces" << endl;
    for (int i = 0; i < l; i++)
    {
        cin >> cx >> px;
        //cout << "cx: " << cx << " px: " << px << endl;
        graph.addPiece(cx, px);
    }

    /*
    Each of the following f lines contains two space-separated integers cy and fy,
    where 
    cy = the city form a friend with id fy will start collecting pieces.
    fy = friend id
    */
    int cy, fy;
    //cout << "Friends" << endl;
    for (int i = 0; i < f; i++)
    {
        cin >> cy >> fy;
        //cout << "cy: " << cy << " fy: " << fy << endl;
        graph.addPerson(cy, fy);
    }

    // START THE MISSION =======================================
    graph.startMission(CityGraph::TRAVERSE_USING_DFS);

    return 0;
}

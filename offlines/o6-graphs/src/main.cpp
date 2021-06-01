#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct Pair
{
    int city; //first
    int friendId; // 2nd
};

struct City
{
    int id;
    int pieces;
};


class CityGraph{
private:
    const string DEBUG = "CityGraph->";
    int numberOfCity;
    vector<vector<int>> adjancencyList; //adjacency list
    map<int, int> pieceMap;
    vector<int> visited;

public:
    CityGraph(int numberOfCity, int numberOfRoads){
        this->numberOfCity = numberOfCity;
        this->adjancencyList.assign(numberOfCity, {});
        this->visited.assign(numberOfCity, 0);
    }
    void setRoads(vector<vector<int>> roads)
    {
        cout <<DEBUG<< "setRoads(): setting roads" << endl;
        this->adjancencyList = roads;
    }

    /**
     * for debugging
     */
    void printAdj(){
        for (int i = 0; i < adjancencyList.size(); i++)
        {
            cout << "city " << i << ": ";
            for (auto c : adjancencyList[i])
                cout<< c << ",";
            cout << endl;
        }
    }

    void setPieceMap(map<int,int> pieceMap){
        this->pieceMap = pieceMap;
    }

    void resetVisited(){
        this->visited.assign(numberOfCity, 0);
    }

    int getTotalPieces(){
        int total = 0;
        for(auto m: pieceMap){
            total += m.second;
        }
        return total;
    }

    int dfs(int start){
        visited[start] = 1;
        cout << start << " ";
        int totalPieces = pieceMap[start];
        for(auto city: adjancencyList[start])
            if(!visited[city]){
                totalPieces += dfs(city);
            }
        return totalPieces;
    }

    int bfs(int start){
        cout << DEBUG << "bfs()" << endl;
        queue<int> q;

        visited[start] = 1;
        q.push(start);

        int totalCollectedPieces = 0;
        while(!q.empty()){
            int next = q.front();
            q.pop();

            cout << next << " ";

            totalCollectedPieces += pieceMap[next];

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
};





/*
g++ main.cpp
a.exe<tc1.txt>out.txt
*/
int main(int argc, char const *argv[])
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    cout << "Hello world" << endl;
    // c = number of cities
    // r = number of roads in mamaland
    // l = total number of locations where pieces are hidden
    // f = number of friends
    int c, r, l, f;
    cin >> c >> r >> l >> f;
    cout << "c: " << c << " r: " << r << " l: " << l << " f: " << f << endl;

    /*
    Each of the following r lines contains two space-separated
    integers c1 and c2,denoting two cities of Mamaland connected by a road.
     All the roadsare two-way roads
    */
    int c1, c2;
    vector<vector<int> > roads(c);
    cout << "roads: " << endl;
    for (int i = 0; i < r; i++)
    {
        cin >> c1 >> c2;
        cout <<"i: "<<i<< " c1: " << c1 << " c2: " << c2 << endl;
        roads[c1].push_back(c2);
        roads[c2].push_back(c1);
       // cout << "haha" << endl;
    }
    cout << "End of taking input roads" << endl;

    /*
    Each of the following l lines contains two space-separated integers cx and py
    where cx = the city cx, px = total px number of pieces hidden in city cx
    */
    int cx, px;
    map<int, int> pieceMap;
    cout << "Pieces" << endl;
    for (int i = 0; i < l; i++)
    {
        cin >> cx >> px;
        cout << "cx: " << cx << " px: " << px << endl;
        pieceMap[cx] = px;
    }
    

    /*
    Each of the following f lines contains two space-separated integers cy and fy,
    where cy = the city form a friend with id fy will start collecting pieces.
    */
    int cy, fy;
    vector<Pair> start(f);
    cout << "Friends" << endl;
    for (int i = 0; i < f; i++)
    {
        cin >> cy >> fy;
        cout << "cy: " << cy << " fy: " << fy << endl;
        start[i].city = cy;
        start[i].friendId = fy;
    }

    cout << "Creating city graph" << endl;

    CityGraph graph(c,r);
    graph.setRoads(roads);
    graph.setPieceMap(pieceMap);
    cout << "Adjacency List: " << endl;
    graph.printAdj();
    cout << endl;

    vector<int> ans(f);
    int total = 0;
    for(auto frnd: start){
        cout << frnd.friendId << " : ";
        ans[frnd.friendId] = graph.bfs(frnd.city);
        cout << endl;
        total += ans[frnd.friendId];
    }

    cout << endl;

    if(graph.getTotalPieces() == total){
        cout << "Mission Accomplished" << endl;
    }else
        cout << "Mission Impossible" << endl;
    

    cout << total << " out of " << graph.getTotalPieces() << " are collected" << endl;

    for (int i = 0; i < ans.size(); i++)
    {
        cout << i << " collected " << ans[i] << endl;
    }
    

    return 0;
}

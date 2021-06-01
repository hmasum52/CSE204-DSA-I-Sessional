// author: Hasan Masum
// created: 29/04/2021
// last edited : 29/05/2021
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

/**
 * 
*/
struct Pair
{
    int city;
    int friendId;
};

class CityGraph{
private:
    const string DEBUG = "CityGraph->";
    
    int numberOfCity;
    vector<vector<int>> adjancencyList; //adjacency list
    int totalPieces;
    map<int, int>pieceMap;
    vector<int> visited;


public:
    CityGraph(int numberOfCity){
        this->numberOfCity = numberOfCity;
        adjancencyList.assign(numberOfCity, {});
        visited.assign(numberOfCity, 0);
        totalPieces = 0;
    }

    /**
     * add an edge in the graph
    */
    void addRoad(int start, int end){
        adjancencyList[start].push_back(end);
        adjancencyList[end].push_back(start);
    }


    void addPiece(int city, int pieces){
        pieceMap[city] = pieces;
        totalPieces += pieces;
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

    int getTotalPieces()
    {
        return totalPieces;
    }

    /**
     * must call the method before starting the mission 
     */
    int clearVisited(){
        this->visited.assign(numberOfCity, 0);
    }

    /**
     * recursive dfs function.
     * 
     * @param startCity is the node where a friend start collecting pieces
     */
    int dfs(int startCity)
    {
        // check if a freind already visited the city 
        if (visited[startCity])
            return 0;

        // STEP-1: MARK THE CURRENT NODE IN RECURSIVE CALL AS VISITED
        visited[startCity] = 1;
        cout << startCity << " ";

        int totalPieces = pieceMap[startCity];

        for (auto endCity : adjancencyList[startCity])
            // STEP-2: IF A NODE IS NOT VISITED 
            // GO TO THAT ADJACENT NODE
            if (!visited[endCity])
                totalPieces += dfs(endCity);

        return totalPieces;
    }

    /**
     * bfs implementation using queue
     * 
     * @param startCity is the node where a friend start collecting pieces
     */
    int bfs(int startCity)
    {
        cout << DEBUG << "bfs()" << endl;
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

            cout << next << " ";

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

    cout << "Hi" << endl;

   // freopen("tc1.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    // c = number of cities
    // r = number of roads in mamaland
    // l = total number of locations where pieces are hidden
    // f = number of friends
    int c, r, l, f;
    cin >> c >> r >> l >> f;
    cout << "c: " << c << " r: " << r << " l: " << l << " f: " << f << endl;
 
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
    where cx = the city cx, px = total px number of pieces hidden in city cx
    */
    int cx, px;

    //cout << "Pieces" << endl;
    for (int i = 0; i < l; i++)
    {
        cin >> cx >> px;
        //cout << "cx: " << cx << " px: " << px << endl;
        graph.addPiece(cx,px);
    }

    /*
    Each of the following f lines contains two space-separated integers cy and fy,
    where cy = the city form a friend with id fy will start collecting pieces.
    */
    int cy, fy;
    vector<Pair> friends(f);
    cout << "Friends" << endl;
    for (int i = 0; i < f; i++)
    {
        cin >> cy >> fy;
        //cout << "cy: " << cy << " fy: " << fy << endl;
        friends[i].city = cy;
        friends[i].friendId = fy;
    }

    // START THE MISSION =======================================
    graph.clearVisited();
    vector<int> ans(f);
    int total = 0;
    for (auto frnd : friends)
    {
        cout << frnd.friendId << " : ";
        ans[frnd.friendId] = graph.bfs(frnd.city);
        cout << endl;
        total += ans[frnd.friendId];
    }

    cout << endl;

    if (graph.getTotalPieces() == total)
    {
        cout << "Mission Accomplished" << endl;
    }
    else
        cout << "Mission Impossible" << endl;

    cout << total << " out of " << graph.getTotalPieces() << " are collected" << endl;

    for (int i = 0; i < ans.size(); i++){
        cout << i << " collected " << ans[i] << endl;
    }

    return 0;
}

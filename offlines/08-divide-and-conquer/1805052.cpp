/*
@Course CSE-204: Data structure and alogrithm-I sessional
@Offline 7 on divide and conquer

@author Hasan Masum, CSE-18, BUET
@ID 1805052
@Created 14 june 2021
@Problem : Closest pair of points using divide and conquer
*/

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

class Point
{
    int id; // index of point in input array
    int x;  // x co-ordinate of the point
    int y;  // y co-ordinate of the point

public:
    void setId(int id)
    {
        this->id = id;
    }

    void setX(int x)
    {
        this->x = x;
    }

    void setY(int y)
    {
        this->y = y;
    }

    int getId()
    {
        return id;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    bool equals(Point p2)
    {
        return id == p2.id;
    }

    /**
     * calculate the euclidian distance from this point to point p2
     * 
     * @param p2 is the point to calucate the distance
     */
    double dist(Point p2)
    {
        return sqrt((x - p2.x) * (x - p2.x) + (y - p2.y) * (y - p2.y));
    }

    /**
     * compare 2 ponts wrt to x co-ordinate
     */
    static bool cmp(Point &p1, Point &p2)
    {
        if (p1.x != p2.x)
            return p1.x < p2.x;
        return p1.y < p2.y;
    }

    /**
     * compare 2 ponts wrt to y co-ordinate
     */
    static bool cmpY(Point &p1, Point &p2)
    {
        return p1.y < p2.y;
    }
};

/**
 * calculate second closest pair of point 
 * from the given array of points
 */
class SecondCPP
{
    struct Pair
    {
        Point start; // start point of the pair
        Point end;   // end point of the pair
    };

    //track the cloest pair of point in recursive calls
    Pair closest;             // pair of points with closest distance
    //track the second closest pair of points in recursive calls
    Pair secondClosest;       // pair of points with second closest distance
    double closestDist;       // closest distance among all the points
    double secondClosestDist; // second closest ditance among all the points

    Point *p;   // given array of points;
    int length; // length of the given array

    /**
     * update 2nd closest pair and dist with new one
     * 
     * @param startPoint is the start point of the closest pair
     * @param endPoint is the end point of the closest
     */
    void updateClosestPair(Point &startPoint, Point &endPoint)
    {
        closestDist = startPoint.dist(endPoint);
        closest.start = startPoint;
        closest.end = endPoint;
    }

    /**
     * update 2nd closest pair and dist with new one
     * 
     * @param startPoint is the start point of the 2nd closest pair
     * @param endPoint is the end point of the 2nd closest pair
     */
    void updateSecondClosestPair(Point &startPoint, Point &endPoint)
    {
        secondClosestDist = startPoint.dist(endPoint);
        secondClosest.start = startPoint;
        secondClosest.end = endPoint;
    }

    /**
     * check if the distance beteen these two point 
     * is has the closest or secondClosest ditance 
     * 
     * @param startPoint is the start of current pair
     * @param endPoint is the end of current pair
     */
    void findClosestFromPair(Point &startPoint, Point &endPoint)
    {
        //calculate the eucledian distance between given points
        double tempDist = startPoint.dist(endPoint);

        if (tempDist < closestDist)
        {
            updateSecondClosestPair(closest.start, closest.end);

            updateClosestPair(startPoint, endPoint);
        }
        else
        {
            //for distance which er greater than closestDist
            // but less than current secondClosestDist
            if (tempDist < secondClosestDist && tempDist > closestDist){
                updateSecondClosestPair(startPoint, endPoint);
            }else if(closestDist == secondClosestDist && tempDist> secondClosestDist){
                updateSecondClosestPair(startPoint, endPoint);
            }
        }
    }

    /**
     * recursive function to find the closest and 2nd closest pair
     * of points from the given array.
     * 
     * when size of the sub array is less than 3 
     * then it applies brute force to find the closest and 2nd closest.
     * it also sorts the sub array with respect to y in the base case.
     * 
     * when size of the array is greater than 3
     * then it applies divide and conquer strategy and divide the array in 2 halves
     * in every recursive call.
     * 
     * after sovling the sub problems it merges the 2 halves in such a way that
     * the array is sorted with respect to y.
     * 
     * finally in the conquer part we check for closest and 2nd closet 
     * points form the pair of points which are inside the stripe of 2*secondClosestDist
     * from the mid.
     * 
     * 
     * @param start in start index of the sub-array in every recursive call.
     * @param end in end index of the sub-array in every recursive call.
     */
    void closestPair(int startIdx, int endIdx)
    {
        //cout << start << " " << end << endl;

        int n = endIdx - startIdx + 1;

        // STEP-1: BASE CASE ============================================
        // brute fource takes almost constant time
        if (n <= 3)
        {
            if (closestDist == INT32_MAX)
            {
                closest.start = p[startIdx];
                closest.end = p[startIdx + 1];
            }

            if (secondClosestDist == INT32_MAX)
            {
                secondClosest.start = p[startIdx];
                secondClosest.end = p[startIdx + 1];
            }

            for (int i = startIdx; i <= endIdx; i++)
            {
                for (int j = i + 1; j <= endIdx; j++)
                {
                    findClosestFromPair(p[i], p[j]);
                }
            }

            // cout << start << " " << end << " base min dist: " << minDist << endl;
            // cout << start << " " << end << " base 2nd min dist: " << fs.secondClosest.start.dist(fs.secondClosest.end) << endl;

            //sort the sub array wrt y co ordinates
            sort(p + startIdx, p + endIdx + 1, Point::cmpY);

            return;
        }

        //STEP-2: DIVIDE ===================================================
        int mid = startIdx + (endIdx - startIdx) / 2;
        double midX = p[mid].getX();

        // complexity O(nlog n)
        closestPair(startIdx, mid);
        // complexity O(nlog n)
        closestPair(mid + 1, endIdx);

        //STEP-3: MERGE ====================================================
        // merge the 2 sorted sub array wrt to y co-ordinate.
        // Complexity O(n)
        Point *tempAr = new Point[n];
        for (int i = startIdx, j = mid + 1, k = 0; k < n; k++)
        {
            if (i == mid + 1)
                tempAr[k] = p[j++];
            else if (j == endIdx + 1)
                tempAr[k] = p[i++];

            //else compare elements
            else if (Point::cmpY(p[i], p[j]))
                tempAr[k] = p[i++];
            else
                tempAr[k] = p[j++];
        }

        for (int i = 0, j = startIdx; i < n; i++, j++)
        {
            p[j] = tempAr[i];
        }

        delete[] tempAr;

        //cout << "merged from idx " << start << " to " << end << endl;

        //STEP-3: Strip =============================================================
        // check for the closest and 2nd closest points
        // in the stripe of width 2*secondClosestDist from the middle.
        // Complexity O(n)
        for (int i = startIdx; i <= endIdx; i++)
        {
            if (abs(p[i].getX() - midX) < secondClosestDist)
            {
                // check for the closest and 2nd closest point
                // only in rectangle of (2secondClosetDist) * (secondClosetDist)
                for (int j = i + 1; j <= endIdx && (p[j].getY() - p[i].getY()) < secondClosestDist; j++)
                {
                    findClosestFromPair(p[i], p[j]);
                }
            }
        }

        // cout << start << " " << end << " merge dist: " << closestDist << endl;
        // cout << start << " " << end << " merge 2nd dist: " << secondClosestDist << endl;

        return;
    }

    void swapPoint(Point &p1, Point &p2)
    {
        Point temp = p1;
        p1 = p2;
        p2 = temp;
    }

public:
    SecondCPP(Point points[], int length)
    {
        // pre sort the elements with respect to x co-ordinate
        // to reduce the complexity
        sort(points, points + length, Point::cmp);

        closestDist = INT32_MAX;
        secondClosestDist = INT32_MAX;

        this->p = points;
        this->length = length;
        this->closestPair(0, length - 1);

        if (secondClosest.start.getId() > secondClosest.end.getId())
            swapPoint(secondClosest.start, secondClosest.end);
    }

    Point getStartPoint()
    {
        return secondClosest.start;
    }

    Point getEndPoint()
    {
        return secondClosest.end;
    }
};

/*
g++ 1805052.cpp
a.exe

 */
int main(int argc, char const *argv[])
{
    freopen("in.txt", "r", stdin);

    //freopen("test-case/tamim/test-b.txt", "r", stdin);

    int n;
    cin >> n;
    Point points[n];

    int x, y;
    for (int i = 0; i < n; i++)
    {
        points[i].setId(i);
        cin >> x;
        points[i].setX(x);
        cin >> y;
        points[i].setY(y);
    }

    //sorted input
    /*  cout << "Printing points sorted by x: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "x: " << points[i].getX() << " y: " << points[i].getY() << endl;
    }
    cout << endl; */

    SecondCPP cpp = SecondCPP(points, n);

    Point start = cpp.getStartPoint();
    Point end = cpp.getEndPoint();

    cout << start.getId() << " " << end.getId() << endl;
    printf("%.4f", start.dist(end));

    /* cout << "Printing points sorted by y:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "x: " << points[i].getX() << " y: " << points[i].getY() << endl;
    } */

    return 0;
}

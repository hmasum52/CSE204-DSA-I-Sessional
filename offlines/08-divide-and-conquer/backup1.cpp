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
    int id;
    int x;
    int y;

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
     * 
     */
    static bool cmp(Point &p1, Point &p2)
    {
        if (p1.x != p2.x)
            return p1.x < p2.x;
        return p1.y < p2.y;
    }

    static bool cmpY(Point &p1, Point &p2)
    {
        return p1.y < p2.y;
    }
};

class SecondCPP
{
    struct Pair
    {
        Point start;
        Point end;
    };

    struct FS
    {
        Pair closest;
        Pair secondClosest;
    };

    Point *p;
    int length;

    Point startPoint;
    Point endPoint;

    FS closestPair(int start, int end)
    {
        //cout << start << " " << end << endl;

        FS fs;

        int n = end - start + 1;
        // given n>3
        // base case
        // brute fource
        if (n <= 3)
        {
            double minDist = p[start].dist(p[start + 1]);
            fs.closest.start = p[start];
            fs.closest.end = p[start + 1];
            double secondMinDist = INT32_MAX;
            fs.secondClosest.start = p[start];
            fs.secondClosest.end = p[start + 1];

            for (int i = start; i <= end; i++)
            {
                for (int j = i + 1; j <= end; j++)
                {
                    double tempDist = p[i].dist(p[j]);
                    if (tempDist < minDist)
                    {
                        minDist = tempDist;
                        fs.secondClosest.start = fs.closest.start;
                        fs.secondClosest.end = fs.closest.end;

                        fs.closest.start = p[i];
                        fs.closest.end = p[j];
                    }
                    else
                    {
                        //cout << "tempDist: " << tempDist << endl;
                        if (tempDist < secondMinDist && tempDist > minDist)
                        {
                            // cout << "updateing 2nd min dist to "<< tempDist << endl;
                            secondMinDist = tempDist;
                            fs.secondClosest.start = p[i];
                            fs.secondClosest.end = p[j];
                        }
                    }
                }
            }

            // cout << start << " " << end << " base min dist: " << minDist << endl;
            // cout << start << " " << end << " base 2nd min dist: " << fs.secondClosest.start.dist(fs.secondClosest.end) << endl;

            sort(p + start, p + end + 1, Point::cmpY);

            return fs;
        }

        //STEP-2 divide
        int mid = start + (end - start) / 2;
        double l = p[mid].getX();

        FS fsLeft = closestPair(start, mid);
        double distLeft = fsLeft.closest.start.dist(fsLeft.closest.end);

        FS fsRight = closestPair(mid + 1, end);
        double distRight = fsRight.closest.start.dist(fsRight.closest.end);

        double minDist;
        if (distLeft < distRight)
        {
            minDist = distLeft;
            fs.closest = fsLeft.closest;

            //second closest
            double leftSecondDist = fsLeft.secondClosest.start.dist(fsLeft.secondClosest.end);
            fs.secondClosest = leftSecondDist < distRight && leftSecondDist != distLeft ? fsLeft.secondClosest : fsRight.closest;
        }
        else
        {
            minDist = distRight;
            fs.closest = fsRight.closest;

            //second closest
            double rightSecondDist = fsRight.secondClosest.start.dist(fsRight.secondClosest.end);
            fs.secondClosest =
                rightSecondDist < distLeft && rightSecondDist != distRight ? fsRight.secondClosest : fsLeft.closest;
        }

        //merge
        Point *tempAr = new Point[n];
        for (int i = start, j = mid + 1, k = 0; k < n; k++)
        {
            if (i == mid + 1)
                tempAr[k] = p[j++];
            else if (j == end + 1)
                tempAr[k] = p[i++];

            //else compare elements
            else if (Point::cmpY(p[i], p[j]))
                tempAr[k] = p[i++];
            else
                tempAr[k] = p[j++];
        }

        for (int i = 0, j = start; i < n; i++, j++)
        {
            p[j] = tempAr[i];
        }

        delete[] tempAr;

        //cout << "merged from idx " << start << " to " << end << endl;

        //STEP-3 Conquer
        double finalMinDist = minDist;
        double seconndMinDist = fs.secondClosest.start.dist(fs.secondClosest.end);
        for (int i = start; i <= end; i++)
        {
            if (abs(p[i].getX() - l) < seconndMinDist)
            {
                for (int j = i + 1; j <= end && (p[j].getY() - p[i].getY()) < seconndMinDist; j++)
                {
                    double tempDist = p[i].dist(p[j]);
                    if (tempDist < finalMinDist)
                    {
                        // cout << "min dist found in strip " << i << " " << j << endl;
                        finalMinDist = tempDist;

                        fs.secondClosest.start = fs.closest.start;
                        fs.secondClosest.end = fs.closest.end;

                        fs.closest.start = p[i];
                        fs.closest.end = p[j];
                    }
                    else
                    {
                        if (tempDist < fs.secondClosest.start.dist(fs.secondClosest.end) && tempDist > finalMinDist)
                        {
                            fs.secondClosest.start = p[i];
                            fs.secondClosest.end = p[j];
                            //cout << start << " " << end << endl;
                            //cout << "yo " << i << " " << j << endl;
                        }
                    }
                }
            }
        }

        cout << start << " " << end << " merge dist: " << finalMinDist << endl;
        cout << start << " " << end << " merge 2nd dist: " << fs.secondClosest.start.dist(fs.secondClosest.end) << endl;

        return fs;
    }

public:
    SecondCPP(Point points[], int length)
    {
        this->p = points;
        this->length = length;
        FS fs = this->closestPair(0, length - 1);
        //cout << "haha closest start: "<<pair.startIdx<<" "<<pair.endIdx<< endl;
        this->startPoint = fs.secondClosest.start;
        this->endPoint = fs.secondClosest.end;
    }

    Point getStartPoint()
    {
        return startPoint;
    }

    Point getEndPoint()
    {
        return endPoint;
    }
};

/*
 g++  -Wl,--stack,10000000000 closest.cpp
 a.exe
 */
int main(int argc, char const *argv[])
{
    //freopen("in2.txt", "r", stdin);
    freopen("test-case/hisam/input_test 3.txt", "r", stdin);

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

    sort(points, points + n, Point::cmp);

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

    cout << endl;
    cout << "start point idx: " << start.getId() << endl;
    cout << start.getX() << " " << start.getY() << endl;
    cout << "end point idx: " << end.getId() << endl;
    cout << end.getX() << " " << end.getY() << endl;

    cout << "Closest distance: " << cpp.getStartPoint().dist(cpp.getEndPoint()) << endl;
    cout << endl;

    /* cout << "Printing points sorted by y:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "x: " << points[i].getX() << " y: " << points[i].getY() << endl;
    } */

    return 0;
}

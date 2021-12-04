#include<bits/stdc++.h>
using namespace std;
class House_Point
{
public:
    int id;
    int x;
    int y;

};
double minimum = FLT_MAX;
int countJ=0;
double second_minimum=minimum;
pair<House_Point,House_Point> closest;
pair<int,int>second_closest;
House_Point previous1,previous2;
vector<House_Point>t;
double distance(House_Point A, House_Point B)
{
    double res= sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
    //cout<<" between "<<A.id<<" "<<B.id<<" "<<res<<endl;
    return res;
}
bool compareX(const House_Point &a, const House_Point &b)
{
    return (a.x <b.x);
}
bool compareY(const House_Point &a, const House_Point &b)
{

    return (a.y < b.y);
}
void updateAll(const House_Point &a, const House_Point &b)
{
    if(distance(a,b)<minimum)
    {
        second_minimum=minimum;
        if(countJ==0)
        {
            second_minimum=FLT_MAX;
            second_closest={a.id,b.id};
            previous1=a;
            previous2=b;
        }

        second_closest={previous1.id,previous2.id};
        minimum=distance(a,b);
        closest.first=a;
        closest.second=b;
        previous1=a;
        previous2=b;
        countJ++;
    }else
    {
        if(distance(a,b)<second_minimum && distance(a,b)>minimum)///1,2,3,4.....
        {
            second_minimum=distance(a,b);
            second_closest={a.id,b.id};
            countJ++;
        }
    }
    //cout<<"minimum is "<<minimum<<endl;
    //cout<<"second minimum is "<<second_minimum<<endl;
}


void Findcloestdist(House_Point p1[],int low,int high)
{
    if(high-low<=3)///base case
    {
        int n=high-low;
        for (int i = low; i < high; i++){
            for (int j = i+1; j < high; j++)
            {
                updateAll(p1[i],p1[j]);
            }
        }

        sort(p1+low,p1+high,compareY);
        return;
    }

    int mid_index=(low+high)/2;
    House_Point mid_point=p1[mid_index];
    Findcloestdist(p1,low,mid_index);
    Findcloestdist(p1,mid_index,high);


    merge(p1+low,p1+mid_index,p1+mid_index,p1+high,t.begin(),compareY);
    copy(t.begin(),t.begin()+high-low,p1+low);

    int j=0;
    for(int i=low;i<high;i++)
    {
        if(abs(p1[i].x - mid_point.x)<second_minimum)
        {
           for(j=i+1;j< high && (p1[j].y - p1[i].y)<second_minimum;j++)
           {
               updateAll(p1[i],p1[j]);
           }
        }
    }

}
void closeMost(House_Point p[],int n)
{
    sort(p,p+n,compareX);
    Findcloestdist(p,0,n);
}

int main()
{
    freopen("../sachin.txt", "r", stdin);
    int j=0;
    int n,x,y;
    cin>>n;
    t.resize(n);
    House_Point P[n];
    for(int i=0;i<n;i++)
    {
        cin>>x>>y;
        P[j].x=x;
        P[j].y=y;
        P[j].id=j;
        j++;
    }
    //int n = sizeof(P) / sizeof(P[0]);
    closeMost(P, n);
    //cout << "The smallest distance is " << second_minimum<<" "<<closest.first.x<<" "<<closest.first.y<<endl;
    //cout<<closest.second.x<<" "<<closest.second.y<<endl;
    cout<<"MINIMUM IS "<<minimum<<endl;
cout<<second_closest.first<<" "<<second_closest.second<<endl;
    printf("%.4f\n",second_minimum);


    return 0;
}

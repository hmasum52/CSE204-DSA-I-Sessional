/**
* @author Hasan Masum, Ugrad student, CSE, BUET
* CSE204 Offline 10 on Greedy A
*/
#include<iostream>
#include<algorithm>
using namespace std;

int main(){
    //freopen("in.txt", "r", stdin);
   // freopen("test-case/hisam/test 5.txt", "r", stdin);

    int n, k;
    // n: the number of plants
    // k: number of friends
    cin >> n>>k;

    // a[i]: the original price of ith plant
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    // reverse sort the price of the plants
    // as our greedy approch to minimize the cost
    // will be to buy the plants with higher price
    // frist as the price of plants will be
    // (number_of_prev_plants + 1)*original price
    sort(a, a + n);
    reverse(a, a + n);

    long long ans = 0;

    //here i points to ith plant in reverse sorted array
    //and j is the number of plants that a friend already bought
    for (int i = 0, j = 0; i < n; i++){
        // here we multiply the original price
        // with (number_of_bought_plants_by_a_friend + 1)
        // and add the price with total price
        ans += a[i] * (j + 1);

        //check if all k friends has bought j number of plants
        if( (i+1)%k == 0 )
            // if so we increase j by 1 
            // and the next k plants original price
            // will be multiplied by (j+1) 
            // for all k friends
            j++;
    }

    cout <<ans<< endl;

    return 0;
}

#include<iostream>
#include<cstring>
using namespace std;
const long long mod = 1e9 + 7;
int dp[101][10001];

/**
 * Complexity: time-> O(dices*sum), space: O(dices*sum)
 * 
 * @param sum is our desired sum
 * @param dices is number of nheterogeneous  dices
 * @param faces is the array of the number of faces of all dices.
 */
int ways(int sum, int dices, int* faces){
    //cout<<"inside ways"<<endl;
    // ============= INIT DP ====================
    memset(dp, 0 , sizeof dp);
   // cout<<"memset compete"<<endl;

    // ============ BASE CASE ===================
    // make 0 sum with 0 dices in 1 way
    dp[0][0] = 1;

    //cout<<"dp start"<<endl;
    
    // ============ CREATE A DP TABLE ==============
    for (int d = 1; d <= dices; d++) //d: number of dices
    {
        // starting from s = d as s = 0 if s<d
        for (int s = d; s <= sum; s++) //s: sum 's' with 'd' dices
        {
            // let's assume n = 3, s = 8 and f=[4,5,3]
            if(s <= faces[d-1]){
                // an example when s < fn
                // here dp[3][3] = dp[2][2](1 in 3rd dice) + d[2][1] (2 in 3rd dice) + dp[2][0](3 in 3rd dice)
                // Again dp[3][2] = dp[2][1] + dp[2][0]
                // so  dp[3][3] = dp[2][2] + dp[3][2]
                dp[d][s] = (dp[d-1][s-1]%mod + dp[d][s-1]%mod)%mod;
            }else{
                // an example when s > fn
                // dp[3][8] : 8 sum from 3 dices
                // here dp[3][8] = dp[2][7](1 in 3rd dice) + d[2][6] (2 in 3rd dice) + dp[2][5](3 in 3rd dice)
                // again dp[3][7] = dp[2][6] + dp[2][5] + dp[2][4]
                // so dp[3][8] = dp[2][7] + dp[3][7] - dp[2][4]
                dp[d][s] = (dp[d-1][s-1]%mod + dp[d][s-1]%mod)%mod - dp[d-1][s-faces[d-1]-1]%mod;;
            }
            //cout<< dp[d][s]<<" ";
        }
       // cout<<endl;
        
    }
    return dp[dices][sum];
}



int main(int argc, char const *argv[]){
    freopen("in.txt", "r", stdin);

    int numberOfDices, sum;
    cin>> numberOfDices >> sum;

    int faces[numberOfDices];
    for (int i = 0; i < numberOfDices; i++)
        cin>> faces[i];

    cout<< ways(sum, numberOfDices, faces)<<endl;
   
    return 0;
}

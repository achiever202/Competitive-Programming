/*****************************************************************************************/
/*																		     			 */
/*  					Adarsh Pugalia 										 			 */
/*																			 			 */
/*****************************************************************************************/

#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <set>
#include <queue>
#include <algorithm>
#include <stack>
#include <cmath>
#include <cassert>
#include <map>
#include <limits>
#include <cassert>
 
#define ll long long int
#define vi vector <int>
#define vl vector <ll> 
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vpii vector <pii >
#define vpll vector <pll >
 
 
#define f first
#define s second
 
#define sd(n) scanf("%d", &n)
#define sl(n) scanf("%lld", &n)
#define slf(n) scanf("%lf", &n)

#define pd(n) printf("%d", n);
#define pl(n) printf("%lld", n);
#define ps printf(" ")
#define pe printf("\n")

#define rep(i,j,k) for(int i=j; i<=k; i++)
#define repd(i,j,k) for(int i=j; i>=k; i--)

#define sz(n) (int)n.size()-1 
#define pb push_back
#define pob pop_back
#define mp make_pair
 
#define max_size 1005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_log 17
#define max_sieve_size 1005

#define INF 10000000
#define MOD 1000000007
 
using namespace std;

class LongestCommonSubstring {
	public:
		string word1, word2;
		int dp[max_size][max_size];

		int calc_longest_common_substring(string w1, string w2) {
			word1 = w1;
			word2 = w2;

			int ret = 0;

			rep(i,0,word1.length())
				rep(j,0,word2.length())
					dp[i][j] = 0;

			rep(i,1,word1.length()){
				rep(j,1,word2.length()) {
					if(word1[i-1]==word2[j-1]) {
						dp[i][j] = dp[i-1][j-1]+1;

						if(ret<dp[i][j])
							ret = dp[i][j];
					}
				}
			}

			return ret;
		}
}lcs;

int dp[max_size][max_size];

int main() {
	int n;
	sd(n);
	while(n) {
		string a, b;
		cin>>a>>b;

		lcs.calc_longest_common_substring(a,b);

		rep(i,1,a.length()) {
			rep(j,1,b.length()) {
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

				if(lcs.dp[i][j]>=n) {
					repd(k,lcs.dp[i][j], n) {
						dp[i][j] = max(dp[i][j], k+dp[i-k][j-k]);
					}
				}
			}
		}

		pd(dp[a.length()][b.length()]); pe;
		sd(n);
	}
}
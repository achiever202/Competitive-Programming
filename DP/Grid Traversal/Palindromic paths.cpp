/*
 * Author: Adarsh Pugalia
 * Algorithm: Number of palindromic paths in a grid.
 * Time: O(n^2), Space: O(n^2)
 * Problem: http://codeforces.com/contest/570/problem/E
 */

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
 
#define ll int
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
#define rep(i,j,k) for(int i=j; i<=k; i++)
#define repd(i,j,k) for(int i=j; i>=k; i--)
 
#define pb push_back
#define pob pop_back
#define mp make_pair
 
#define max_size 505
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_sieve_size 1300005
#define max_log 17
#define MOD 1000000007L
 
using namespace std;

ll dp[2][max_size][max_size];
char board[max_size][max_size];

int main() {
	ll n, m;
	cin>>n>>m;

	rep(i,0,n-1){
		scanf("%s", board[i]);
	}

	if(board[0][0]==board[n-1][m-1])
		dp[0][0][n-1] = 1;

	rep(len,2,(n+m)/2) {

		rep(i,0,n-1){
			rep(j,0,n-1)
				dp[1][i][j] = 0;
		}

		ll left_len = n+m-len-1;
		rep(i,0,n-1){
			ll j = len-i-1;
			rep(p,i,n-1){
				ll q = (m-1) - (len - (n-1-p)) + 1;

				if(j<0 || j>=m || q<0 || q>=m || j>q)
					continue;

				if(board[i][j]!=board[p][q]){
					continue;
				}

				if(j>0){
					dp[1][i][p] = (dp[1][i][p] + dp[0][i][p+1])%MOD;

					if(q<m-1)
						dp[1][i][p] = (dp[1][i][p] + dp[0][i][p])%MOD;
				}

				if(i>0){
					dp[1][i][p] = (dp[1][i][p] + dp[0][i-1][p+1])%MOD;

					if(q<m-1)
						dp[1][i][p] = (dp[1][i][p] + dp[0][i-1][p])%MOD;
				}
			}
		}

		rep(i,0,n-1){
			rep(j,0,n-1){
				dp[0][i][j] = dp[1][i][j];
			}
		}
	}

	ll ans = 0;
	rep(i,0,n-1){
		rep(j,i,n-1){
			ans = (ans+dp[1][i][j])%MOD;
		}
	}

	cout<<ans<<endl;
	return 0;
}
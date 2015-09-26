/*
 * Author: Adarsh Pugalia
 * Problem: Number of binary search tree with nodes n and height h.
 * Problem Link: http://codeforces.com/problemset/problem/9/D
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
#define all(n) n.begin(), n.end()
#define pb push_back
#define pob pop_back
#define mp make_pair
 
#define max_size 100005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_log 17
#define max_sieve_size 1005

#define INF 100000000000L
#define MOD 1000000007
 
using namespace std;

long long unsigned dp[50][50];

int main() {
	int n, h;
	sd(n); sd(h);

	dp[0][0] = 1;
	dp[1][1] = 1;

	/* iterating over number of nodes in the binary search tree. */
	rep(i,2,n) {

		/* iterating over height of the tree for a given number of nodes. */
		rep(j,1,i) {

			/* iterating over the number on the root. */
			rep(k,1,i) {

				/* 
				 * let the height of the left subtree be j-1.
				 * iterating over the height of right subtree.
				 */
				rep(l,0,j-1) {
					dp[i][j] += dp[k-1][j-1]*dp[i-k][l];
				}

				/*
				 * let the height of the right subtree be j-1.
				 * iterating over the height of left subtree.
				 */
				rep(l,0,j-2) {
					dp[i][j] += dp[k-1][l]*dp[i-k][j-1];
				}

			}

		}
	}

	long long unsigned ans = 0;
	rep(j,h,n)
		ans += dp[n][j];

	cout<<ans<<endl;	

	return 0;
}
/* 
 * Author: Adarsh Pugalia
 * Algorithm: Number of k paths in a tree.
 * Problem Link: http://codeforces.com/contest/161/problem/D
 * Time: O(n*k)
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
#define pb push_back
#define pob pop_back
#define mp make_pair
 
#define max_size 50005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_log 17
#define max_sieve_size 1005

#define INF 10000000
#define MOD 1000000007
 
using namespace std;

string tolower(string w) {
	rep(i,0,w.length()) {
		if(w[i]>='A' && w[i]<='Z')
			w[i] = 'a' + w[i] - 'A';
	}

	return w;
}

int dp[max_size][505], final[max_size][505];
vi nodes[max_size];
int parent[max_size];

/* variables */

void preprocess(){
}



void init(){
	
}

int dfs(int node, int p, int k) {
	parent[node] = p;
	dp[node][0] = 1;

	rep(i,0,sz(nodes[node])) {
		if(nodes[node][i]!=p) {
			dfs(nodes[node][i], node, k);

			rep(j,1,k) {
				dp[node][j] += dp[nodes[node][i]][j-1];
			}
		}
	}
}

void update_parent(int node, int k) {
	if(parent[node]!=-1) {
		repd(j,k,1) {
			dp[node][j] += dp[parent[node]][j-1];
			if(j-2>=0)
				dp[node][j] -= dp[node][j-2];
		}
	}

	rep(i,0,sz(nodes[node]))
		if(nodes[node][i]!=parent[node])
			update_parent(nodes[node][i], k);
}

void solve(int test_case){
	init();

	int n, k;
	sd(n), sd(k);

	rep(i,1,n-1) {
		int a, b;
		sd(a), sd(b);

		nodes[a].pb(b);
		nodes[b].pb(a);
	}

	dfs(1, -1, k);
	update_parent(1, k);

	ll ans = 0;
	rep(i,1,n)
		ans += dp[i][k];

	ans /= 2;
	pl(ans); pe;
}

int main(){
	preprocess();

	int t=1;
	//cin>>t;
	rep(i,1,t)
		solve(i);
	return 0;
}
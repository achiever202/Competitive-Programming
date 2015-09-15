/*
 * Author: Adarsh Pugalia
 * Algorithm: Minimum edge inversions to reach all edges from an edge.
 * Problem link: http://codeforces.com/contest/219/problem/D
 *
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
 
#define max_size 200005
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

int dp[max_size];
vpii nodes[max_size];
int parent[max_size];
int orient[max_size];
vi ans;

/* variables */

void preprocess(){
}



void init(){
	
}

int dfs(int node, int p) {
	parent[node] = p;

	rep(i,0,sz(nodes[node])) {
		if(nodes[node][i].f!=p) {
			dp[node] += dfs(nodes[node][i].f, node);

			if(nodes[node][i].s==0) {
				orient[nodes[node][i].f] = 1;
			}
			else
				dp[node]++;
		}
	}

	return dp[node];
}

void update_parent(int node) {
	if(parent[node]!=-1) {
		dp[node] = dp[parent[node]];
		if(orient[node]) {
			dp[node]++;
		}
		else {
			dp[node]--;
		}
	}

	rep(i,0,sz(nodes[node]))
		if(nodes[node][i].f!=parent[node])
			update_parent(nodes[node][i].f);
}

void solve(int test_case){
	init();

	int n;
	sd(n);

	rep(i,1,n-1) {
		int a, b;
		sd(a), sd(b);

		nodes[a].pb(mp(b,0));
		nodes[b].pb(mp(a,1));
	}

	dfs(1,-1);
	update_parent(1);

	int min = n;
	rep(i,1,n) {
		if(dp[i]<min)
			min = dp[i];
	}

	rep(i,1,n) {
		if(dp[i]==min)
			ans.pb(i);
	}

	sort(ans.begin(), ans.end());
	pd(min); pe;
	rep(i,0,sz(ans)) {
		pd(ans[i]); ps;
	}

	pe;
}

int main(){
	preprocess();

	int t=1;
	//cin>>t;
	rep(i,1,t)
		solve(i);
	return 0;
}
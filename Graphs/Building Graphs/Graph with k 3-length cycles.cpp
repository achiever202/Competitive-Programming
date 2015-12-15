/*
 * Author: Adarsh Pugalia
 * Problem: Construct a graph with k 3 length cycles.
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
#include <string.h>
#include <sstream>
 
#define ll long long int
#define llu long long int unsigned
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
#define max_sieve_size 100005
#define max_log 17
 
#define INF 1000000000000000000
#define MOD 1000000007
// #define ESP 0.0000001
 
#define mod(a) ((a)%MOD)
#define swap(a, b) a += b, b = a-b, a -= b
 
using namespace std;

void preprocess() {
}


void init() {
}

vi edges[105];
int mat[105][105];

void solve(int test_case) {
	init();
	
	int k;
	sd(k);

	int cur_cycles = 0;
	edges[1].pb(2);
	edges[2].pb(1);

	int next_node = 3, next_added_node = 1;
	while(cur_cycles<k) {
		if(next_added_node<next_node && cur_cycles+next_added_node-1<=k) {
			edges[next_node].pb(next_added_node);
			edges[next_added_node].pb(next_node);

			cur_cycles += next_added_node-1;
			next_added_node++;
		}
		else {
			next_node++;
			next_added_node = 1;
		}
	}

	for(int i=1; i<=next_node; i++) {
		rep(j,0,sz(edges[i])) {
			mat[i][edges[i][j]] = 1;
		}
	}

	pd(next_node); pe;
	rep(i,1,next_node) {
		rep(j,1,next_node) {
			pd(mat[i][j]);
		}

		pe;
	}
}

int main() {
	preprocess();
	int t = 1;
	//sd(t);

	rep(i,1,t) {
		solve(i);
	}

	return 0;
}
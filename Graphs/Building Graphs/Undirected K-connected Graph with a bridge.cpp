/*
 * Author: Adarsh Pugalia
 * Problem: Building an undirected, k-regular graph with at least one bridge.
 * Link: http://codeforces.com/contest/550/problem/D
 * 
 * Solution: Solution exists only if k is odd. Make k k-regular components and
 *			 connect each of them to a central node to form the bridge. In each
 *			 of the connected components the root has k-1 child, which in turn
 *			 each have 1 child. connect all the leaves to level 1, and then
 *			 connect the leaves in pairs of two.
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
#define ESP 0.0000001
 
#define mod(a) ((a)%MOD)
#define swap(a, b) a += b, b = a-b, a -= b
 
using namespace std;

void init() {
}

vector<int> bridge_child;
vector<pii > ans;

void solve(int test_case) {
	init();

	int k;
	sd(k);

	if(k%2==0) {
		cout<<"NO\n";
		return;
	}

	cout<<"YES\n";

	int bridge_node = 1;
	int next_node = 2;
	int num_bridges = 0;

	while(num_bridges<k) {
		ans.pb(mp(1, next_node));
		int bridge_parent = next_node;
		num_bridges++;
		next_node++;

		for(int i=1; i<k; i++) {
			ans.pb(mp(bridge_parent, next_node));
			next_node++;
		}

		for(int i=1; i<k; i++) {
			bridge_child.pb(next_node);
			ans.pb(mp(bridge_parent+i, next_node));
			next_node++;
		}

		for(int i=1; i<k; i++) {
			for(int j=1; j<k; j++) {
				if(i!=j) {
					ans.pb(mp(bridge_parent+j, bridge_child[i-1]));
				}
			}
		}

		for(int i=0; i<sz(bridge_child); i+=2) {
			ans.pb(mp(bridge_child[i], bridge_child[i+1]));
		}

		bridge_child.clear();
	}

	pd(next_node-1); ps; pd((int)ans.size()); pe;
	rep(i,0,sz(ans)) {
		pd(ans[i].f); ps; pd(ans[i].s); pe;
	}
}

int main() {
	int t = 1;
	//sd(t);

	rep(i,1,t) {
		solve(i);
	}

	return 0;
}
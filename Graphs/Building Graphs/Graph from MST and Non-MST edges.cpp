/*
 * Author: Adarsh Pugalia
 * Problem: Given the number of nodes, and edges, and the edges that belong to
 *			the MST, reconstruct a possible graph without loops and multiple
 *			edges.
 *
 * Problem Link: http://codeforces.com/contest/606/problem/D
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

vector<pair<pii, int> > v;
vector<pii > ans;

bool comp(pair<pii, int> i, pair<pii, int> j) {
	if(i.f.f==j.f.f) {
		return i.f.s>j.f.s;
	}

	return i.f.f<j.f.f;
}

void solve(int test_case) {
	init();

	int n, m;
	sd(n); sd(m);

	rep(i,0,m-1) {
		ans.pb(mp(0,0));
	}

	rep(i,0,m-1) {
		int a, b;
		sd(a); sd(b);

		v.pb(mp(mp(a, b), i));
	}

	sort(all(v), comp);
	int last_in_node = 1, cur_start_node = 1, cur_end_node = 1;
	for(int i=0; i<=sz(v); i++) {
		if(v[i].f.s==1) {
			last_in_node++;
			ans[v[i].s] = mp(last_in_node-1, last_in_node);
		}
		else {
			while(1) {
				if(cur_end_node>last_in_node) {
					cout<<"-1\n";
					return;
				}

				if(cur_end_node-cur_start_node<=1) {
					cur_start_node = 1;
					cur_end_node++;
					continue;
				}
				else {
					ans[v[i].s] = mp(cur_start_node, cur_end_node);
					cur_start_node++;
					break;
				}
			}
		}
	}

	rep(i,0,sz(ans)) {
		pd(ans[i].f); ps; pd(ans[i].s); pe;
	}
}

int main() {
	int t = 1;

	rep(i,1,t) {
		solve(i);
	}

	return 0;
}
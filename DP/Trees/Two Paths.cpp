/*
 * Author: Adarsh Pugalia
 * Problem: Two exclusive paths in a tree such that their product is maximum.
 * Problem Link: http://codeforces.com/contest/14/problem/D
 *
 * Time: O(n^3)
 * There is an O(n^2) algorithm, by removal of each edge one by one, and then
 * checking the maximum length path in each of the connected components.
 * See tutorial for clarification.
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

#define INF 100000000000L
#define MOD 1000000007
 
using namespace std;

pii dia[max_size];

class Node {
	public:
		int index;
		int parent;
		vector<pair<int, ll> >edges;
};

int ans = 0;

class Tree {
	public:
		Node nodes[max_size];
		int node_size;

		void init(int sz) {
			node_size = sz;

			rep(i,1,sz) {
				nodes[i].index = i;
				nodes[i].parent = -1;
				nodes[i].edges.clear();
			}
		}

		void add_edge(int i, int j, ll cost) {
			nodes[i].edges.pb(mp(j,cost));
			nodes[j].edges.pb(mp(i,cost));
		}


		void add_edge(int i, int j) {
			add_edge(i,j,1);
		}

		pair<int, int> get_diameter(int node, int parent) {
			nodes[node].parent = parent;

			pair<int, int> ret;
			ret.f = ret.s = 0;

			rep(i,0,sz(nodes[node].edges)) {
				if(nodes[node].edges[i].f!=parent) {
					pair<int, int> temp = get_diameter(nodes[node].edges[i].f, node);
					ret.f = max(ret.f, max(temp.f, ret.s+temp.s+1));
					ret.s = max(ret.s, temp.s+1);
				}
			}

			dia[node] = ret;
			return ret;
		}


		void dfs(int node, int parent, int prev_dia, int cur_path) {
			nodes[node].parent = parent;

			int temp = 0;
			rep(i,0,sz(nodes[node].edges)) {
				if(nodes[node].edges[i].f!=parent) {
					temp = max(temp, dia[nodes[node].edges[i].f].f);
				}
			}
			ans = max(ans, cur_path*max(temp, prev_dia));

			rep(i,0,sz(nodes[node].edges)) {
				if(nodes[node].edges[i].f!=parent) {
					int temp = prev_dia;
					rep(j,0,sz(nodes[node].edges)) {
						if(nodes[node].edges[j].f!=parent && nodes[node].edges[j].f!=nodes[node].edges[i].f) {
							temp = max(temp, dia[nodes[node].edges[j].f].f);
						}
					}

					dfs(nodes[node].edges[i].f, node, temp, cur_path+1);
				}
			}

			
		}
}tree;

int main() {
	int n;
	sd(n);

	tree.init(n);

	rep(i,1,n-1) {
		int a, b;
		sd(a); sd(b);

		tree.add_edge(a, b);
	}

	rep(i,1,n) {
		tree.get_diameter(i, -1);
		tree.dfs(i,-1, 0, 0);
	}

	pd(ans); pe;
	
	return 0;
}
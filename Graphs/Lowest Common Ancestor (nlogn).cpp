/*
 * Author: Adarsh Pugalia
 * Algorithm: Lowest Common Ancestor in a tree.
 * 			  Preprocessing: O(n)
 			  Query: O(sqrt(n))
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
#include <unordered_set>
 
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
#define max_sieve_size 100005
#define max_log 17
 
#define INF 1000000000
#define MOD 1000000007
 
#define mod(a) ((a)%MOD)
 
using namespace std;

class Node {
	public:
		int index;
		int parent;
		vector<pair<int, ll> >edges;
};

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
}tree;

class LCA {
	public:
		Tree tree;
		int level[max_size];
		int level_parent[max_log][max_size];
		int power2[max_log];

		LCA() {
			power2[0] = 1;
			rep(i,1,max_log-1)
				power2[i] = power2[i-1]*2;
		}

		void init(Tree t) {
			tree = t;
			preprocess_lca(1, -1, 0);
		}


		void preprocess_lca(int node, int parent, int l) {
			level[node] = l;

			level_parent[0][node] = parent;
			rep(i,1,max_log-1) {
				if(parent==-1)
					level_parent[i][node] = parent;
				else
					level_parent[i][node] = level_parent[i-1][level_parent[i-1][node]];
			}

			rep(i,0,sz(tree.nodes[node].edges)) {
				if(tree.nodes[node].edges[i].f!=parent)
					preprocess_lca(tree.nodes[node].edges[i].f, node, l+1);
			}
		}


		int get_lca(int x, int y) {
			if(level[x]<level[y]) {
				int temp = x;
				x = y;
				y = temp;
			}

			repd(i,max_log-1,0) {
				if(level[x]-power2[i]>=level[y]) {
					x = level_parent[i][x];
				}
			}

			if(x==y)
				return x;

			repd(i,max_log-1,0) {
				if(level_parent[i][x]!=level_parent[i][y]) {
					x = level_parent[i][x];
					y = level_parent[i][y];
				}
			}

			return level_parent[0][x];
		}


		int get_ancestor_at_level(int a, int lvl) {
            repd(i,max_log-1, 0) {
                if(level[a]-power2[i]>=lvl)
                    a = level_parent[i][a];
            }

            return a;
        }

}lca;

int main() {
	return 0;
}
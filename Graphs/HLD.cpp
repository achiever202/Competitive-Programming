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
 
#define max_size 10005
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
		int subtree_size;
		vector<pair<int, ll> >edges;
};


class Tree {
	public:
		Node nodes[max_size];
		int node_size, visited[max_size];

		void init(int sz) {
			node_size = sz;

			rep(i,1,sz) {
				nodes[i].index = i;
				nodes[i].parent = -1;
				nodes[i].edges.clear();
				nodes[i].subtree_size = 1;
			}
		}

		void add_edge(int i, int j, ll cost) {
			nodes[i].edges.pb(mp(j,cost));
			nodes[j].edges.pb(mp(i,cost));
		}


		void add_edge(int i, int j) {
			add_edge(i,j,1);
		}


		/*
		 * This function removes the edge between nodes i and j.

		 * NOTE: The removal changes the vector states, so do not remove
		 * the edge while iterating over the vector.
		 */
		void remove_edge(int a, int b) {
			ll cost;
			rep(i,0,sz(nodes[a].edges)) {
				if(nodes[a].edges[i].f==b) {
					cost = nodes[a].edges[i].s;
					break;
				}
			}

			nodes[a].edges.erase(remove(nodes[a].edges.begin(), nodes[a].edges.end(), mp(b,cost)), nodes[a].edges.end());
			nodes[b].edges.erase(remove(nodes[b].edges.begin(), nodes[b].edges.end(), mp(a,cost)), nodes[b].edges.end());
		}

		void dfs(int node, int parent) {
			nodes[node].parent = parent;

			rep(i,0,sz(nodes[node].edges)) {
				if(nodes[node].edges[i].f!=parent) {
					dfs(nodes[node].edges[i].f, node);
					nodes[node].subtree_size += nodes[nodes[node].edges[i].f].subtree_size;
				}
			}
		}
}tree;

class HLD {
	public:
		/*
		 * @data tree: the tree for HLD.
		 * @data chain_number: the total number of chains.
		 * @data chain_head: head node for the chain at index i.
		 * @data chain_length: length of the ith chain.
		 * @data chain_index: the chain to which the ith node in the tree belongs.
		 * @data chain_position: position of the ith node in its respective chain.
		 *
		 * NOTE: The tree is 1 indexed, but the chain index and the chain positions are 0 indexed.
		 */
		Tree tree;
		int chain_number;
		int chain_head[max_size];
		int chain_length[max_size];
		int chain_index[max_size];
		int chain_position[max_size];

		void init(Tree t) {
			tree = t;
			chain_number = 0;

			rep(i,0,tree.node_size) {
				chain_head[i] = -1;
				chain_length[i] = 0;
			}

			decompose_tree(1, -1);
		}


		void decompose_tree(int node, int parent) {
			if(chain_head[chain_number]==-1) {
				chain_head[chain_number] = node;
			}

			chain_index[node] = chain_number;
			chain_position[node] = chain_length[chain_number];
			chain_length[chain_number]++;

			int special_child = -1, special_child_subtree_size = 0;
			rep(i,0,sz(tree.nodes[node].edges)) {
				if(tree.nodes[node].edges[i].f!=parent && tree.nodes[tree.nodes[node].edges[i].f].subtree_size>special_child_subtree_size) {
					special_child = tree.nodes[node].edges[i].f;
					special_child_subtree_size = tree.nodes[tree.nodes[node].edges[i].f].subtree_size;
				}
			}

			if(special_child!=-1) {
				decompose_tree(special_child, node);
			}

			rep(i,0,sz(tree.nodes[node].edges)) {
				if(tree.nodes[node].edges[i].f!=parent && tree.nodes[node].edges[i].f!=special_child) {
					chain_number++;
					decompose_tree(tree.nodes[node].edges[i].f, node);
				}
			}
		}
}hld;

int main() {
	return 0;
}
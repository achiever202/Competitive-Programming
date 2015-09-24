/*
 * Author: Adarsh Pugalia
 *
 * Problem link: http://codeforces.com/problemset/problem/519/E
 * Problem: Number of nodes equidistant from two nodes in a tree.
 * 
 * Preprocessing: O(nsqrt(n))
 * Query: O(sqrt(n))
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
 
#define max_size 100005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_log 17
#define max_sieve_size 1005

#define INF 1000000000
#define MOD 1000000007
 
using namespace std;

/* This stores the number of nodes in the subtree rooted at the node. */
int dp[max_size];

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

		int dfs(int node, int parent) {
			nodes[node].parent = parent;
			dp[node] = 1;

			rep(i,0,sz(nodes[node].edges)) {
				if(nodes[node].edges[i].f!=parent) {
					dp[node] += dfs(nodes[node].edges[i].f, node);
				}
			}

			return dp[node];
		}
}tree;

class LCA {
	public:
		Tree tree;
		int level[max_size];
		int level_parent[max_size];

		void init(Tree t) {
			tree = t;
		}


		void preprocess_lca(int node, int parent, int block_size, int l) {
			level[node] = l;
			tree.nodes[node].parent = parent;

			/* if the node belongs to the first level. */
			if(l<block_size)
					level_parent[node] = 1;
			else
			{
				/* if the node is the on the first level in a block. */
				if(!(l%block_size))
					level_parent[node] = parent;
				else
					level_parent[node] = level_parent[parent];					
			}

			rep(i,0,sz(tree.nodes[node].edges))
				if(tree.nodes[node].edges[i].f!=parent)
					preprocess_lca(tree.nodes[node].edges[i].f, node, block_size, l+1);
		}


		int get_lca(int x, int y)
		{
			/* if the parent in the above section is not same. */
			while(level_parent[x]!=level_parent[y])
			{
				if(level_parent[x]>level[y])
					x = level_parent[x];
				else
					y = level_parent[y];
			}

			/* if they are on the same level block. */
			while(x!=y)
			{
				if(level[x]>level[y])
					x = tree.nodes[x].parent;
				else
					y = tree.nodes[y].parent;
			}

			return x;
		}


		int get_ancestor_at_level(int a, int lvl) {
			while(level[level_parent[a]]>=lvl)
				a = level_parent[a];

			while(level[a]>lvl)
				a = tree.nodes[a].parent;

			return a;
		}

}lca;

int main() {
	int n;
	sd(n);

	tree.init(n);

	rep(i,1,n-1){
		int a, b;
		sd(a); sd(b);
		tree.add_edge(a, b);
	}

	tree.dfs(1, -1);

	lca.init(tree);
	lca.preprocess_lca(1, -1, pow(n, 0.5), 1);

	int q;
	sd(q);
	while(q--) {
		/*
		 * Find the number of nodes equidistant from a and b.
		 */
		int a, b;
		sd(a); sd(b);

		/* if a and b are same, all the nodes are equidistant. */
		if(a==b) {
			pd(n); pe;
			continue;
		}

		int ancestor = lca.get_lca(a, b);

		/*
		 * If the lowest common ancestor is equidistant, all the nodes
		 * except the nodes in the subtree containing a and b rooted at
		 * the lca is equidistant.
		 */
		if(lca.level[a]==lca.level[b]) {
			int ans = n;
			int temp = lca.get_ancestor_at_level(a, lca.level[ancestor]+1);
			ans -= dp[temp];

			temp = lca.get_ancestor_at_level(b, lca.level[ancestor]+1);
			ans -= dp[temp];

			pd(ans); pe;
		}

		/*
		 * if one of the nodes is the lca, check the middle node in the path
		 * ans its subtree, except the one containing the node other than the
		 * lca.
		 */
		else if(ancestor==a || ancestor==b) {
			if(ancestor==b) {
				int temp = b;
				b = a;
				a = temp;
			}

			if(!((lca.level[b]-lca.level[a])&1)) {
				int temp = (lca.level[b]-lca.level[a])/2;

				temp = lca.get_ancestor_at_level(b, lca.level[b]-temp);
				int ans = dp[temp];

				temp = lca.get_ancestor_at_level(b, lca.level[temp]+1);
				ans -= dp[temp];

				pd(ans); pe;
			}
			else {
				pd(0); pe;
			}
		}

		/*
		 * if the path between a and b has even edges, the middle node and its subtree
		 * is equiditant, except the subtree containig a and b.
		 */
		else if(!((lca.level[a] - lca.level[ancestor] + lca.level[b] - lca.level[ancestor])&1)) {
			int temp = (lca.level[a] - lca.level[ancestor] + lca.level[b] - lca.level[ancestor])/2;
			if(lca.level[a]>lca.level[b]) {
				int ans = dp[lca.get_ancestor_at_level(a, lca.level[a]-temp)];
				ans -= dp[lca.get_ancestor_at_level(a, lca.level[a]-temp+1)];
				pd(ans); pe;
			}
			else {
				int ans = dp[lca.get_ancestor_at_level(b, lca.level[b]-temp)];
				ans -= dp[lca.get_ancestor_at_level(b, lca.level[b]-temp+1)];
				pd(ans); pe;
			}
		}
		else {
			pd(0); pe;
		}
	}

	return 0;
}

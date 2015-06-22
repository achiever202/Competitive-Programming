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
#include <stack>
#include <queue>
#include <algorithm>
#include <cassert>

#define ll long long int
#define vi vector <int>
#define vl vector <ll>
#define vpii vector <pair<int, int> >
#define vpll vector <pair<ll, ll> >
#define pll pair<ll, ll>

#define f first
#define s second

#define sd(n) scanf("%d", &n)
#define sl(n) scanf("%lld", &n)

#define pb push_back
#define pob pop_back

#define max_size 100007
#define max_node_size 100007

using namespace std;

ll INF = 1e17;

class Edge
{
	public:
		ll node;
		ll cost;
		ll index;

		Edge(ll i, ll j)
		{
			node = i;
			cost = j;
		}

		Edge(ll i, ll j, ll k)
		{
			node = i;
			cost = j;
			index = k;
		}
};

bool edge_comp(Edge i, Edge j)
{
	return i.node<j.node;
}

class Node
{
	public:
		ll index;
		ll parent;
		ll cost; // here cost is used as level for the node.
		ll colour;
		vector <Edge> edges;

		Node()
		{

		}

		Node(ll i)
		{
			index = i;
			parent = -1;
		}

		void add_edge(ll node, ll cost)
		{
			edges.pb(Edge(node, cost));
		}

		void add_edge(ll node, ll cost, ll index)
		{
			edges.pb(Edge(node, cost, index));
		}
};

bool node_comp(Node i, Node j)
{
	return i.index<j.index;
}

vector <pll > group;

class Graph
{
	public:
		ll node_size;
		ll edge_size;
		Node nodes[max_node_size];
		ll visited[max_node_size];
		ll level_parent[max_node_size];

		Graph()
		{

		}

		void init(ll n, ll m)
		{
			node_size = n;
			edge_size = m;
			for(ll i=0; i<=n; i++)
			{
				nodes[i].index = i;
				nodes[i].parent = -1;
				nodes[i].edges.clear();
				nodes[i].colour = -1;
			}
		}

		void add_edge(ll i, ll j, ll k)
		{
			nodes[i].add_edge(j, k);
		}


		void add_bidirectional_edge(ll i, ll j, ll k)
		{
			nodes[i].add_edge(j, k);
			nodes[j].add_edge(i, k);
		}

		void add_edge(ll i, ll j, ll k, ll m)
		{
			nodes[i].add_edge(j, k, m);
		}

		void preprocess_lca(ll node, ll block_size, ll level)
		{
			nodes[node].cost = level;

			/* if the node belongs to the first level. */
			if(nodes[node].cost<block_size)
				level_parent[node] = 1;
			else
			{
				/* if the node is the on the first level in a block. */
				if(!(nodes[node].cost%block_size))
					level_parent[node] = nodes[node].parent;
				else
					level_parent[node] = level_parent[nodes[node].parent];					
			}

			for(ll i=0; i<nodes[node].edges.size(); i++)
				if(nodes[node].edges[i].node!=nodes[node].parent)
					preprocess_lca(nodes[node].edges[i].node, block_size, nodes[node].cost+1);
		}


		ll lca(ll x, ll y)
		{
			/* if the parent in the above section is not same. */
			while(level_parent[x]!=level_parent[y])
			{
				if(nodes[x].cost>nodes[y].cost)
					x = level_parent[x];
				else
					y = level_parent[y];
			}

			/* if they are on the same level block. */
			while(x!=y)
			{
				if(nodes[x].cost>nodes[y].cost)
					x = nodes[x].parent;
				else
					y = nodes[y].parent;
			}

			return x;
		}

		void clear_graph()
		{
			for(ll i=0; i<max_node_size; i++)
			{
				nodes[i].parent = -1;
				nodes[i].edges.clear();
			}
		}
}graph;

int main()
{
	return 0;
}
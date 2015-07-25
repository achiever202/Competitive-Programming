/*
 * Author: Adarsh Pugalia
 * Algorithm: K nodes in a path in a tree.
 * Problem Statement: https://www.codechef.com/problems/KNODES
 * Editorial: http://discuss.codechef.com/problems/KNODES
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

ll tick_time = 0;

class Graph
{
	public:
		ll node_size;
		ll edge_size;
		Node nodes[max_node_size];
		ll visited[max_node_size];
		ll level_parent[max_node_size];
		pair<ll, ll> dfs_times[max_node_size];

		Graph()
		{

		}

		void init()
		{
			for(ll i=0; i<=node_size; i++)
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
			dfs_times[node].f = tick_time++;

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

			for(ll i=0; i<nodes[node].edges.size(); i++){
				if(nodes[node].edges[i].node!=nodes[node].parent){
					nodes[nodes[node].edges[i].node].parent = node;
					preprocess_lca(nodes[node].edges[i].node, block_size, nodes[node].cost+1);
				}
			}

			dfs_times[node].s = tick_time++;
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
			for(ll i=0; i<=node_size; i++)
			{
				nodes[i].parent = -1;
				nodes[i].edges.clear();
			}
		}
}graph;

vector <ll> query_nodes, a, b, c, d, temp;

int main()
{
	ll t;
	cin>>t;

	while(t--){
		cin>>graph.node_size;
		graph.init();

		for(int i=0; i<graph.node_size-1; i++){
			ll a, b;
			cin>>a>>b;

			graph.add_bidirectional_edge(a, b, 1);
		}

		graph.preprocess_lca(1, (ll)pow(graph.node_size, 0.5), 0);

		ll q, rd, s;
		cin>>q;
		while(q--){

			a.clear(), b.clear(), c.clear(), d.clear();
			query_nodes.clear();

			ll min_node, max_node, min_cost=graph.node_size+1, max_cost = -1;

			ll k;
			cin>>k;

			while(k--){
				ll a;
				cin>>a;
				query_nodes.push_back(a);

				if(graph.nodes[a].cost>max_cost){
					max_cost = graph.nodes[a].cost;
					max_node = a;
				}

				if(graph.nodes[a].cost<min_cost){
					min_cost = graph.nodes[a].cost;
					min_node = a;
				}
			}

			for(int i=0; i<query_nodes.size(); i++){
				if(query_nodes[i]!=max_node){
					if(graph.dfs_times[query_nodes[i]].f<graph.dfs_times[max_node].f && graph.dfs_times[query_nodes[i]].s>graph.dfs_times[max_node].s)
						a.push_back(query_nodes[i]);
					else
						b.push_back(query_nodes[i]);
				}
			}

			if(b.size()==0){
				cout<<"Yes\n";
				continue;
			}

			rd = max_node, s = min_node;

			min_cost = graph.node_size+1, max_cost = -1;
			for(int i=0; i<b.size(); i++){
				if(graph.nodes[b[i]].cost>max_cost){
					max_cost = graph.nodes[b[i]].cost;
					max_node = b[i];
				}

				if(graph.nodes[b[i]].cost<min_cost){
					min_cost = graph.nodes[b[i]].cost;
					min_node = b[i];
				}
			}

			for(int i=0; i<b.size(); i++){
				if(b[i]!=max_node){
					if(graph.dfs_times[b[i]].f<graph.dfs_times[max_node].f && graph.dfs_times[b[i]].s>graph.dfs_times[max_node].s)
						c.push_back(b[i]);
					else
						d.push_back(b[i]);
				}
			}

			if(d.size()>0){
				cout<<"No\n";
				continue;
			}

			ll lca = graph.lca(max_node, rd);

			if(graph.nodes[s].cost>=graph.nodes[lca].cost)
				cout<<"Yes\n";
			else
				cout<<"No\n";
		}
	}

	return 0;
}
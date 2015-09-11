/*
 * Author: Adarsh Pugalia
 * Algorithm: Number of strongly connected components.
 * Time: O(V+E)
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
 
#define ll int
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
#define max_node_size 50005
#define max_power 26
#define max_sieve_size 105
#define max_log 17

#define INF 10000000
#define MOD 1000000007
 
using namespace std;

class Edge
{
	public:
		int node;
		ll cost;
		int index;

		Edge(int i, ll j)
		{
			node = i;
			cost = j;
		}

		Edge(int i, ll j, int k)
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
		int index;
		int parent;
		ll cost;
		int colour;
		vector <Edge> edges;

		Node()
		{

		}

		Node(int i)
		{
			index = i;
			parent = -1;
		}

		void add_edge(int node, ll cost)
		{
			edges.pb(Edge(node, cost));
		}

		void add_edge(int node, ll cost, int index)
		{
			edges.pb(Edge(node, cost, index));
		}
};

bool node_comp(Node i, Node j)
{
	return i.index<j.index;
}

class Graph
{
	public:
		int node_size;
		int edge_size;
		Node nodes[max_node_size];
		int visited[max_node_size];

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

		void add_edge(ll i, ll j, ll k, ll m)
		{
			nodes[i].add_edge(j, k, m);
		}

		void add_bidirectional_edge(ll i, ll j, ll k)
		{
			nodes[i].add_edge(j, k);
			nodes[j].add_edge(i, k);
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

class StronglyConnectedComponents {
	
	public:
		Graph graph, reversed_graph;
		stack <int> nodes;
		int visited[max_size];

		void init(int n, int m) {
			graph.init(n,m);
		}

		void reverse_graph() {
			reversed_graph.init(graph.node_size, graph.edge_size);
			rep(i,1,graph.node_size) {
				rep(j,0,sz(graph.nodes[i].edges)) {
					reversed_graph.add_edge(graph.nodes[i].edges[j].node, i, 1);
				}
			}
		}

		void recursive_dfs(int node, int parent, int flag)
		{
			visited[node] = 1;

			if(flag) {
				rep(i,0,sz(graph.nodes[node].edges)) {
					if(!visited[graph.nodes[node].edges[i].node])
						recursive_dfs(graph.nodes[node].edges[i].node, node, 1);
				}

				nodes.push(node);
			}
			else {
				rep(i,0,sz(reversed_graph.nodes[node].edges)) {
					if(!visited[reversed_graph.nodes[node].edges[i].node])
						recursive_dfs(reversed_graph.nodes[node].edges[i].node, node, 0);
				}
			}
		}

		int get_scc_count() {
			int ret = 0;
			fill(visited, visited+graph.node_size+1, 0);

			rep(i,1,graph.node_size) {
				if(!visited[i])
					recursive_dfs(i, -1, 1);
			}

			fill(visited, visited+graph.node_size+1, 0);
			while(!nodes.empty()) {
				int cur = nodes.top();
				nodes.pop();

				if(!visited[cur]) {
					ret++;
					recursive_dfs(cur, -1, 0);
				}
			}

			return ret;
		}
}scc;

int main() {

	return 0;
}
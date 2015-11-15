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
 
#define INF 1000000000
#define MOD 1000000007
 
#define mod(a) ((a)%MOD)
 
using namespace std;
 
using namespace std;

class Node
{
	public:
		int index;
		int parent;
		vector <pair<int, ll> > edges;

		Node()
		{

		}
};

class Graph {
	public:
		Node nodes[max_size];
		int node_size, edge_size;
		int visited[max_size];

		void init(int node_sz, int edge_sz) {
			node_size = node_sz, edge_size = edge_size;

			rep(i,1,node_size) {
				nodes[i].index = i;
				nodes[i].parent = -1;
				nodes[i].edges.clear();
				visited[i] = 0;
			}
		}

		void add_edge(int i, int j) {
			nodes[i].edges.pb(mp(j,1));
		}

		void add_edge(int i, int j, ll cost) {
			nodes[i].edges.pb(mp(j,cost));
		}

		void add_bidirectional_edge(int i, int j) {
			add_edge(i,j);
			add_edge(j,i);
		}

		void add_bidirectional_edge(int i, int j, ll cost) {
			add_edge(i, j, cost);
			add_edge(j,i,cost);
		}

		void dfs(int cur_node, int parent) {
			visited[cur_node] = 1;

			rep(i,0,sz(nodes[cur_node].edges)) {
				int next_node = nodes[cur_node].edges[i].f;
				if(!visited[next_node])
					dfs(next_node, cur_node);
			}
		}
}graph;

class StronglyConnectedComponents {
	
	public:
		Graph graph, reversed_graph;
		stack <int> nodes;
		int visited[max_size];
		vector<vector<int> > scc;
		int cur_scc_count;

		void init(Graph g) {
			graph = g;
			reverse_graph();
			cur_scc_count = 0;
		}

		void reverse_graph() {
			reversed_graph.init(graph.node_size, graph.edge_size);
			rep(i,1,graph.node_size) {
				rep(j,0,sz(graph.nodes[i].edges)) {
					reversed_graph.add_edge(graph.nodes[i].edges[j].f, i, graph.nodes[i].edges[j].s);
				}
			}
		}

		void recursive_dfs(int node, int parent, int flag)
		{
			visited[node] = 1;

			if(flag) {
				rep(i,0,sz(graph.nodes[node].edges)) {
					if(!visited[graph.nodes[node].edges[i].f])
						recursive_dfs(graph.nodes[node].edges[i].f, node, 1);
				}

				nodes.push(node);
			}
			else {
				scc[cur_scc_count].pb(node);
				rep(i,0,sz(reversed_graph.nodes[node].edges)) {
					if(!visited[reversed_graph.nodes[node].edges[i].f])
						recursive_dfs(reversed_graph.nodes[node].edges[i].f, node, 0);
				}
			}
		}

		void compute_scc() {
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
					vector<int> v;
					scc.pb(v);

					recursive_dfs(cur, -1, 0);
					cur_scc_count++;
				}
			}
		}
}scc;

int main() {
	return 0;
}
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
 
#define max_size 200005
#define max_sieve_size 100005
#define max_log 19
 
#define INF 10000000000000L
#define MOD 1000000007
 
#define mod(a) ((a)%MOD)
 
using namespace std;

class Node
{
	public:
		int index;
		int parent;
		vector<pair<int, ll> > edges;
};

class Graph
{
	public:
		int node_size;
		int edge_size;
		Node nodes[max_size];

		void init(int n, int m) {
			node_size = n;
			edge_size = m;

			rep(i,1,n) {
				nodes[i].index = i;
				nodes[i].parent = -1;
				nodes[i].edges.clear();
			}
		}

		void add_edge(int a, int b, ll c) {
			nodes[a].edges.pb(mp(b, c));
		}


		void add_edge(int a, int b) {
			add_edge(a, b, 1);
		}

		void add_edge_bidirectional(int a, int b, ll c) {
			add_edge(a, b, c);
			add_edge(b, a, c);
		}

		void add_edge_bidirectional(int a, int b) {
			add_edge_bidirectional(a, b, 1);
		}
};


/*
 * This class implements dijkstra shortest path.
 *
 * NOTE: 
 *    1. Dijkstra works for non-negative edges.
 *    2. Priority queue stores max priority queue here.
 */
class Dijkstra {
	public:
		Graph graph;
		ll distance[max_size];
		int visited[max_size];
		priority_queue<pair<ll, int> > pq;

		void init(int n, int m) {
			graph.init(n, m);
			rep(i,1,n) {
				distance[i] = INF;
				visited[i] = 0;
				
				while(!pq.empty())
					pq.pop();
			}
		}

		void compute_shortest_paths(int source) {

			distance[source] = 0;
			pq.push(mp(0, source));
			while(!pq.empty()) {
				pair<ll, int> cur = pq.top();
				pq.pop();

				if(!visited[cur.s]) {
					visited[cur.s] = 1;
					
					rep(i,0,sz(graph.nodes[cur.s].edges)) {
						int next_node = graph.nodes[cur.s].edges[i].f;
						ll edge_cost = graph.nodes[cur.s].edges[i].s;
						

						if(!visited[next_node] && distance[next_node]>distance[cur.s]+edge_cost) {
							distance[next_node] = distance[cur.s] + edge_cost;
							graph.nodes[next_node].parent = cur.s;
							pq.push(mp(-distance[next_node], next_node));
						}
					}

				}
			}
		}

		ll get_distance(int node) {
			return distance[node];
		}
}dijkstra;
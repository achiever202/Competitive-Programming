/*
 * Author: Adarsh Pugalia
 * Algorithm: Detecting cycle in an undirected graph.
 * Complexity: O(V+E)
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
#define max_node_size 50005
#define max_power 26
#define max_sieve_size 105
#define max_log 17

#define INF 10000000
#define MOD 1000000007
 
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

bool is_cycle_found = false;

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

    /*
     * This method detects cycle in the graph.
     */
    void dfs(int cur_node, int parent, int depth) {
    	visited[cur_node] = depth;

      	for(int i=0; i<nodes[cur_node].edges.size() && (!is_cycle_found); i++) {
        	int next_node = nodes[cur_node].edges[i].f;
          	if(visited[next_node]) {
            	is_cycle_found = true;

            	/*
            	 * The length of the cycle found is, depth - visited[next_node]+1.
            	 */

            	/* printing the cycle. */
              	int cur = cur_node;
              	while(cur!=next_node) {
                	pd(cur); ps;
                	cur = nodes[cur].parent;
              	}
              	pd(next_node); pe;
            }  
          	else {
            	nodes[next_node].parent = cur_node;
            	dfs(next_node, cur_node, depth+1);
          	}
        }
      	
      	visited[cur_node] = 1;
    }
}graph;

int main() {
	int n, m;
  	sd(n); sd(m);

	graph.init(n,m);
	rep(i,1,m) {
    	int a, b;
    	sd(a); sd(b);

    	graph.add_bidirectional_edge(a, b);
  	}

  	graph.dfs(1, -1, 1);
  	return 0;
}
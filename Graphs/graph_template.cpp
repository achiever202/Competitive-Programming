#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>

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

#define max_size 100005
#define max_capacity 100007
#define max_node_size 100005
#define INF 100000

using namespace std;

class Edge
{
	public:
		ll node;
		ll cost;

		Edge(ll i, ll j)
		{
			node = i;
			cost = j;
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

		void sort_edges()
		{
			sort(edges.begin(), edges.end(), edge_comp);
		}

		ll search_index(ll node, ll start, ll end)
		{
			if(end<start)
				return -1;

			if(end-start<=1)
			{
				if(edges[end].node==node)
					return end;

				if(edges[start].node==node)
					return start;

				return -1;
			}

			ll mid = (start+end)/2;
			if(edges[mid].node<node)
				return search_index(node, mid+1, end);

			return search_index(node, start, mid);
		}


		ll find_edge_index(ll node)
		{
			return search_index(node, 0, edges.size()-1);
		}

		ll find_edge_cost(ll node)
		{
			return edges[find_edge_index(node)].cost;
		}
};

class Graph
{
	public:
		ll node_size;
		ll edge_size;
		Node nodes[max_node_size];
		bool visited[max_node_size];
		ll cost[max_node_size];

		Graph()
		{

		}

		void init(ll n)
		{
			node_size = n;
			for(ll i=0; i<=n; i++)
			{
				nodes[i].index = i;
				nodes[i].parent = -1;
				nodes[i].edges.clear();
			}
		}

		void add_edge(ll i, ll j, ll k)
		{
			nodes[i].add_edge(j, k);
		}

		void dfs(ll source)
		{
			for(ll i=0; i<=node_size; i++)
				visited[i] = 0;

			stack <ll> dfs;
			dfs.push(source);
			nodes[source].parent = -1;
			cost[source] = 0;
			visited[source] = 1;

			while(!dfs.empty())
			{
				ll cur = dfs.top();
				dfs.pop();

				for(ll i=0; i<nodes[cur].edges.size(); i++)
				{
					if(!visited[nodes[cur].edges[i].node] && nodes[cur].edges[i].cost>0)
					{
						visited[nodes[cur].edges[i].node] = 1;
						nodes[nodes[cur].edges[i].node].parent = cur;
						cost[nodes[cur].edges[i].node] = cost[cur] + nodes[cur].edges[i].cost;
						dfs.push(nodes[cur].edges[i].node);
					}
				}
			}
		}

		void sort_edges()
		{
			for(ll i=0; i<node_size; i++)
				nodes[i].sort_edges();
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
	graph.init(5);
	graph.add_edge(1, 2, -1);
	graph.add_edge(1, 3, 4);
	graph.add_edge(2, 3, 3);
	graph.add_edge(2, 4, 2);
	graph.add_edge(2, 5, 2);
	graph.add_edge(4, 3, 5);
	graph.add_edge(4, 2, 2);
	graph.add_edge(5, 4, -3);

	bellman_ford.init(1);
	for(ll i=1; i<=graph.node_size; i++)
		cout<<bellman_ford.get_cost(i)<<endl;
	return 0;
}
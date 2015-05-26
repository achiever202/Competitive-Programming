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
#define max_node_size 300005

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
		ll cost;
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

bool node_comp(Node i, Node j)
{
	return i.index<j.index;
}

class Graph
{
	public:
		ll node_size;
		ll edge_size;
		Node nodes[max_node_size];
		bool visited[max_node_size];

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

		ll find_edge_index(ll i, ll j)
		{
			return nodes[i].find_edge_index(j);
		}

		ll find_edge_cost(ll i, ll j)
		{
			return nodes[i].find_edge_cost(j);
		}

		void dfs(ll source)
		{
			for(ll i=0; i<=node_size; i++)
				visited[i] = 0;

			stack <ll> dfs;
			dfs.push(source);
			nodes[source].parent = -1;
			nodes[source].cost = 0;
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
						nodes[nodes[cur].edges[i].node].cost = nodes[cur].cost + nodes[cur].edges[i].cost;
						dfs.push(nodes[cur].edges[i].node);
					}
				}
			}
		}

		void recursive_dfs(ll node, ll parent)
		{
			visited[node] = 1;

			for(ll i=0; i<nodes[node].edges.size(); i++)
			{
				if(!visited[nodes[node].edges[i].node])
				{
					recursive_dfs(nodes[node].edges[i].node, node);
				}
			}
		}

		void sort_edges()
		{
			for(ll i=0; i<=node_size; i++)
				nodes[i].sort_edges();
		}

		void sort_nodes()
		{
			sort(nodes+1, nodes+node_size+1, node_comp);
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

ll ans = 0;
vl final_edges;

class Dijkstra
{
	public:
		ll places[max_node_size];
		ll n;

		void init(ll source)
		{
			n = graph.node_size;

			for(ll i=1; i<=graph.node_size; i++)
			{
				places[i] = i;
				graph.nodes[i].cost = INF;
				graph.visited[i] = false;
			}

			graph.nodes[source].cost = 0;
			heapify(source);
		}

		ll calc_shortest_path(ll destination)
		{
			while(n)
			{
				ll cur = extract_min();
				graph.visited[cur] = true;
				ll index = places[cur];
				
				for(ll i=0; i<graph.nodes[index].edges.size(); i++)
				{
					ll next_node = graph.nodes[index].edges[i].node;
					ll next_cost = graph.nodes[index].edges[i].cost;

					if(!graph.visited[next_node] && graph.nodes[places[next_node]].cost>graph.nodes[index].cost+next_cost)
					{
						graph.nodes[places[next_node]].cost = graph.nodes[places[cur]].cost+next_cost;
						graph.nodes[places[next_node]].parent = cur;
						heapify(places[next_node]);
					}
				}
			}

			return graph.nodes[places[destination]].cost;
		}

		void heapify(ll i)
		{
			if(i>1)
			{
				ll j = i/2;
				if(graph.nodes[i].cost<graph.nodes[j].cost)
				{
					places[graph.nodes[i].index] = j;
					places[graph.nodes[j].index] = i;

					Node temp = graph.nodes[i];
					graph.nodes[i] = graph.nodes[j];
					graph.nodes[j] = temp;

					heapify(j);
				}
			}
		}

		ll extract_min()
		{
			ll ret = graph.nodes[1].index;

			places[graph.nodes[1].index] = n;
			places[graph.nodes[n].index] = 1;

			Node temp = graph.nodes[1];
			graph.nodes[1] = graph.nodes[n];
			graph.nodes[n] = temp;

			n--;
			heapify_down(1);

			return ret;
		}

		void heapify_down(ll i)
		{
			if(2*i<=n)
			{
				ll j = 2*i;
				if(j<n && graph.nodes[j].cost>graph.nodes[j+1].cost)
					j++;

				if(graph.nodes[j].cost<graph.nodes[i].cost)
				{
					places[graph.nodes[i].index] = j;
					places[graph.nodes[j].index] = i;

					Node temp = graph.nodes[i];
					graph.nodes[i] = graph.nodes[j];
					graph.nodes[j] = temp;

					heapify_down(j);
				}
			}
		}

}dijkstra;

int main()
{	
	return 0;
}
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <set>
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
#define max_capacity INT_MAX
#define max_node_size 100005

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
			if(end-start<=1)
			{
				if(edges[end].node==node)
					return end;

				return start;
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

		Graph()
		{

		}

		void input_graph(bool is_tree, bool is_directed, bool is_cost)
		{
			cin>>node_size;
			for(ll i=0; i<node_size; i++)
			{
				nodes[i].index = i;
				nodes[i].parent = -1;
				nodes[i].edges.clear();
			}

			if(!is_tree)
				cin>>edge_size;
			else
				edge_size = node_size-1;


			for(ll i=0; i<edge_size; i++)
			{
				ll a, b, c=1;
				cin>>a>>b;

				if(is_cost)
					cin>>c;

				nodes[a].add_edge(b, c);
				if(!is_directed)
					nodes[b].add_edge(a, c);
			}
		}

		void sort_edges()
		{
			for(ll i=0; i<node_size; i++)
				nodes[i].sort_edges();
		}
};

int main()
{
	return 0;
}
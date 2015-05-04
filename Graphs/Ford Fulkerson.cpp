/*
 * Author: Adarsh Pugalia
 * Algorithm: Ford Fulkerson (for maximum flow) using bfs as a subroutine.
 * Time Complexity: O(VE^2log(V))
 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <set>
#include <queue>
#include <algorithm>
#include <limits.h>

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
#define max_node_size 650

using namespace std;

/* Graph template begins here. */
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

		Graph()
		{
			for(ll i=0; i<max_node_size; i++)
			{
				nodes[i].index = i;
				nodes[i].parent = -1;
				nodes[i].edges.clear();
			}
		}

		void input_graph(bool is_tree, bool is_directed, bool is_cost)
		{
			cin>>node_size;

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
			for(ll i=0; i<=node_size; i++)
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

/* Graph template ends here. */


/* 
 * This class implements the ford fulkerson algorithm.
 * @member residual_graph: the residual graph for the original graph.
 * @member max_flow: maximum flow for a given source destination.
 */
class Ford_Fulkerson
{
	public:
		Graph residual_graph;
		ll max_flow;

		Ford_Fulkerson()
		{
		}

		/* This function initializes the residual graph for a given graph. */
		void init(Graph graph)
		{
			residual_graph.node_size = graph.node_size;
			for(ll i=0; i<=residual_graph.node_size; i++)
			{
				residual_graph.nodes[i].index = i;
				residual_graph.nodes[i].parent = graph.nodes[i].parent;

				for(ll j=0; j<graph.nodes[i].edges.size(); j++)
				{
					residual_graph.nodes[i].add_edge(graph.nodes[i].edges[j].node, graph.nodes[i].edges[j].cost);
					ll index = graph.nodes[graph.nodes[i].edges[j].node].find_edge_index(i);
					if(index==-1)
						residual_graph.nodes[graph.nodes[i].edges[j].node].add_edge(i, 0);
				}
			}

			residual_graph.sort_edges();
		}

		/* This function performs bfs given a source and a destination. */
		bool bfs(ll source, ll destination)
		{
			for(ll i=0; i<=residual_graph.node_size; i++)
			{
				residual_graph.visited[i] = false;
				residual_graph.nodes[i].parent = -1;
			}

			queue <ll> bfs;
			residual_graph.visited[source] = true;
			bfs.push(source);

			while(!bfs.empty())
			{
				ll cur = bfs.front();
				bfs.pop();

				if(cur==destination)
					return true;

				for(ll i=0; i<residual_graph.nodes[cur].edges.size(); i++)
				{
					ll next_node = residual_graph.nodes[cur].edges[i].node;
					ll cost = residual_graph.nodes[cur].edges[i].cost;

					if(!residual_graph.visited[next_node] && cost>0)
					{
						residual_graph.visited[next_node] = true;
						residual_graph.nodes[next_node].parent = cur;
						bfs.push(next_node);
					}
				}
			}

			return false;
		}

		/* This function calculates the maximum flow given a source and a destination. */
		ll calc_flow(ll source, ll destination)
		{
			max_flow = 0;
			while(bfs(source, destination))
			{
				ll temp_flow = INT_MAX;
				ll cur = destination;
				while(cur!=source)
				{
					temp_flow = min(temp_flow, residual_graph.nodes[residual_graph.nodes[cur].parent].find_edge_cost(cur));
					cur = residual_graph.nodes[cur].parent;
				}

				max_flow += temp_flow;

				cur = destination;
				while(cur!=source)
				{
					ll cur_parent = residual_graph.nodes[cur].parent;
					
					ll index = residual_graph.nodes[cur].find_edge_index(cur_parent);
					residual_graph.nodes[cur].edges[index].cost += temp_flow;

					index = residual_graph.nodes[cur_parent].find_edge_index(cur);
					residual_graph.nodes[cur_parent].edges[index].cost -= temp_flow;

					cur = residual_graph.nodes[cur].parent;
				}
			}

			return max_flow;
		}

		/* This function clears the resudual graph. */
		void clear_graph()
		{
			residual_graph.clear_graph();
		}
}ford_fulkerson;
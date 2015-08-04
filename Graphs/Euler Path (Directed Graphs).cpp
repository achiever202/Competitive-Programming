/*
 * Author: Adarsh Pugalia
 * Algorithm: Euler Path for directed graphs.
 * Credits: http://www.graph-magics.com/articles/euler.php
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
#define rep(i,j,k) for(int i=j; i<=k; i++)
#define repd(i,j,k) for(int i=j; i>=k; i--)
 
#define pb push_back
#define pob pop_back
#define mp make_pair
 
#define max_size 100005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 10007
#define max_power 26
#define max_sieve_size 105
#define max_log 17
 
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
		ll in_degree, out_degree;
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

class Graph
{
	public:
		ll node_size;
		ll edge_size;
		Node nodes[max_node_size];
		ll visited[max_node_size];

		void init(ll n, ll m)
		{
			node_size = n;
			edge_size = m;
			for(ll i=0; i<=n; i++)
			{
				nodes[i].index = i;
				nodes[i].parent = -1;
				nodes[i].edges.clear();
				nodes[i].in_degree = nodes[i].out_degree = 0;
			}
		}

		void add_edge(ll i, ll j, ll k)
		{
			nodes[i].add_edge(j, k);
			nodes[i].out_degree++;
			nodes[j].in_degree++;
		}

		void add_edge(ll i, ll j, ll k, ll m)
		{
			nodes[i].add_edge(j, k, m);
			nodes[i].out_degree++;
			nodes[j].in_degree++;
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

class EulerPath{
	public:
		Graph graph;

		int start_node, end_node, vis[max_node_size], pos[max_node_size];
		stack <ll> s;
		vector <ll> path;

		void init(Graph g){
			graph = g;
		}

		void dfs(ll node){
			vis[node] = 1;

			rep(i,0,(ll)graph.nodes[node].edges.size()-1){
				if(!vis[graph.nodes[node].edges[i].node])
					dfs(graph.nodes[node].edges[i].node);
			}			
		}


		bool is_connected(ll start_node){
			rep(i,1,graph.node_size)
				vis[i] = 0;

			if(start_node!=-1){
				dfs(start_node);

				rep(i,1,graph.node_size){
					if(graph.nodes[i].edges.size()>0 && !vis[i])
						return false;
				}
			}

			return true;
		}


		bool is_eulerian(){
			ll equal = 0, greater = 0, smaller = 0;

			rep(i,1,graph.node_size){
				if(graph.nodes[i].in_degree==graph.nodes[i].out_degree)
					equal++;
				else if(graph.nodes[i].in_degree>graph.nodes[i].out_degree){
					if(graph.nodes[i].in_degree-graph.nodes[i].out_degree>1)
						return false;
					else{
						greater++;
						end_node = i;
					}
				}
				else{
					if(graph.nodes[i].out_degree-graph.nodes[i].in_degree>1)
						return false;
					else{
						smaller++;
						start_node = i;
					}
				}
			}

			if(greater>1 || smaller>1)
				return false;

			if(smaller==0)
				start_node = 1;

			if(!is_connected(start_node))
				return false;

			return true;
		}


		void print_euler_path(){
			if(!is_eulerian()){
				cout<<"Graph does not have an euler path.\n";
				return;
			}

			cout<<"Path: \n";

			while(!s.empty())
				s.pop();

			path.clear();

			rep(i,1,graph.node_size)
				pos[i] = 0;

			ll cur_node = start_node;
			while(1){
				if(pos[cur_node]==graph.nodes[cur_node].edges.size()){
					path.pb(cur_node);
					
					if(s.empty())
						break;

					cur_node = s.top();
					s.pop();
				}
				else{
					s.push(cur_node);
					int temp = cur_node;
					cur_node = graph.nodes[cur_node].edges[pos[cur_node]].node;
					pos[temp]++;
				}
			}

			repd(i,path.size()-1,0)
				cout<<path[i]<<"->";
			cout<<endl;
		}

}euler_path;

int main(){
	return 0;
}
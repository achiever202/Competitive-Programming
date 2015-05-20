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
 
#define max_size 505
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_edge_size 10
#define max_power 26
 
#define MOD 1000000007
 
using namespace std;

class BipartiteMatching
{
	public:
		ll first_set_size, second_set_size, edges;
		ll last[max_node_size], used[max_node_size], visited[max_node_size], matching[max_node_size], distance[max_node_size], bfs_q[max_node_size];
		ll previous[max_edge_size], head[max_edge_size];

		void init(ll a, ll b)
		{
			first_set_size = a;
			second_set_size = b;
			edges = 0;
			fill(last, last+first_set_size, -1);
		}

		void add_edge(ll a, ll b)
		{
			head[edges] = b;
			previous[edges] = last[a];
			last[a] = edges++;
		}

		void bfs()
		{
			fill(distance, distance+first_set_size, -1);
			ll size = 0;
			for(ll i=0; i<first_set_size; i++)
			{
				if(!used[i])
				{
					bfs_q[size++] = i;
					distance[i] = 0;
				}
			}

			for(ll i=0; i<size; i++)
			{
				ll start = bfs_q[i];
				for(ll e=last[start]; e>=0; e=previous[e])
				{
					ll mid = matching[head[e]];
					if(mid>=0 && distance[mid]<0)
					{
						bfs_q[size++] = mid;
						distance[mid] = distance[start]+1;
					}
				}
			}
		}

		bool dfs(ll node)
		{
			visited[node] = 1;
			for(ll e=last[node]; e>=0; e=previous[e])
			{
				ll v = head[e];
				ll u = matching[v];

				if(u<0 || !visited[u] && distance[u]==distance[node]+1 && dfs(u))
				{
					matching[v] = node;
					used[u] = 1;
					return true;
				}
			}

			return false;
		}

		ll get_max_matching()
		{
			fill(used, used+first_set_size, 0);
			fill(matching, matching+second_set_size, -1);
			for(ll res=0; ; )
			{
				bfs();
				fill(visited, visited+first_set_size, 0);
				ll f = 0;
				for(ll i=0; i<first_set_size; i++)
				{
					if(!used[i] && dfs(i))
						f++;
				}

				if(!f)
					return res;

				res += f;
			}
		}
}bipartite_matching;

int main()
{
	bipartite_matching.init(2, 2);
	bipartite_matching.add_edge(0, 0);
	bipartite_matching.add_edge(0, 1);
	bipartite_matching.add_edge(1, 1);
	cout<<bipartite_matching.get_max_matching()<<endl;
	return 0;
}
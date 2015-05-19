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
#define max_power 26
 
#define MOD 1000000007
#define INF 1000000007

 
using namespace std;

class FloydWarshall
{
	public:
		ll node_size;
		ll all_pair_shortest_paths[max_node_size][max_node_size];

		void init(ll n)
		{
			node_size = n;

			for(ll i=0; i<node_size; i++)
				for(ll j=0; j<node_size; j++)
					if(i==j)
						all_pair_shortest_paths[i][j] = 0;
					else
						all_pair_shortest_paths[i][j] = INF;
		}

		void add_edge(ll node_a, ll node_b, ll cost, bool is_directed)
		{
			all_pair_shortest_paths[node_a][node_b] = cost;
			if(!is_directed)
				all_pair_shortest_paths[node_b][node_a] = cost;
		}

		void calc_all_pair_shortest_paths()
		{
			for(ll k=0; k<node_size; k++)
				for(ll i=0; i<node_size; i++)
					for(ll j=0; j<node_size; j++)
						if(all_pair_shortest_paths[i][k]+all_pair_shortest_paths[k][j]<all_pair_shortest_paths[i][j])
							all_pair_shortest_paths[i][j] = all_pair_shortest_paths[i][k] + all_pair_shortest_paths[k][j];
		}

		ll get_path_length(ll node_a, ll node_b)
		{
			return all_pair_shortest_paths[node_a][node_b];
		}
}floyd_warshall;

int main()
{
	floyd_warshall.init(4);

	floyd_warshall.add_edge(0, 1, 5, true);
	floyd_warshall.add_edge(0, 3, 10, true);
	floyd_warshall.add_edge(1, 2, 3, true);
	floyd_warshall.add_edge(2, 3, 1, true);

	floyd_warshall.calc_all_pair_shortest_paths();
	for(ll i=0; i<4; i++)
	{
		for(ll j=0; j<4; j++)
			cout<<floyd_warshall.get_path_length(i, j)<<" ";
		cout<<endl;
	}
}
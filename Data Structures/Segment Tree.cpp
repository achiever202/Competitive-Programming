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
 
#define max_size 100005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_sieve_size 5000003
 
#define MOD 100000000
 
using namespace std;

class SegmentTree
{
	public:
		ll n;
		ll ar[max_size];
		ll seg_tree[4*max_size];

		void init()
		{
			scanf("%d %d", &n, &q);
			for(ll i=1; i<=n; i++)
				scanf("%d", &ar[i]);
		}

		ll build_segment_tree(ll node, ll start, ll end)
		{
			if(start==end)
			{
				seg_tree[node] = 0;
				return seg_tree[node];
			}

			ll mid = (start+end)/2;
			ll left = build_segment_tree(2*node, start, mid);
			ll right = build_segment_tree(2*node+1, mid+1, end);

			/* Logic for combining left and right nodes. */

			return seg_tree[node];
		}

		ll query(ll node, ll start, ll end, ll x, ll y)
		{
			if(end==start && end==x && end==y)
			{
				return seg_tree[node];
			}

			ll mid = (start+end)/2;

			if(mid>=y)
				return query(2*node, start, mid, x, y);

			if(mid+1<=x)
				return query(2*node+1, mid+1, end, x, y);

			ll left = query(2*node, start, mid, x, mid);
			ll right = query(2*node+1, mid+1, end, mid+1, y);

			/* Logic for merging left and right queries. */

			return seg_tree[node];
		}

		void print_segment_tree(ll node, ll start, ll end)
		{
			if(start==end)
			{
				cout<<node<<" "<<start<<" "<<end<<" "<<seg_tree[node]<<endl;
				return;
			}

			ll mid = (start+end)/2;
			print_segment_tree(2*node, start, mid);
			print_segment_tree(2*node+1, mid+1, end);

			cout<<node<<" "<<start<<" "<<end<<" "<<seg_tree[node]<<endl;
		}
}segment_tree;
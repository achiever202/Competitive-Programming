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
 
#define max_size 100005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_log 17
#define max_sieve_size 1005

#define INF 100000000000L
#define MOD 1000000007
 
using namespace std;

class SegmentTree
{
	public:
		int n;
		ll ar[max_size];
		ll seg_tree[4*max_size];

		void init(int num)
		{
			n = num;
			rep(i,1,n)
				sd(ar[i]);
		}

		ll build_segment_tree(int node, int start, int end)
		{
			if(start==end)
			{
				seg_tree[node] = 0;
				return seg_tree[node];
			}

			int mid = (start+end)/2;
			ll left = build_segment_tree(2*node, start, mid);
			ll right = build_segment_tree(2*node+1, mid+1, end);

			/* Logic for combining left and right nodes. */

			return seg_tree[node];
		}

		ll query(int node, int start, int end, int x, int y)
		{
			if(start==x && end==y)
			{
				return seg_tree[node];
			}

			int mid = (start+end)/2;

			if(mid>=y)
				return query(2*node, start, mid, x, y);

			if(mid+1<=x)
				return query(2*node+1, mid+1, end, x, y);

			ll left = query(2*node, start, mid, x, mid);
			ll right = query(2*node+1, mid+1, end, mid+1, y);

			/* Logic for merging left and right queries. */

			return seg_tree[node];
		}

		void print_segment_tree(int node, int start, int end)
		{
			if(start==end)
			{
				cout<<node<<" "<<start<<" "<<end<<" "<<seg_tree[node]<<endl;
				return;
			}

			int mid = (start+end)/2;
			print_segment_tree(2*node, start, mid);
			print_segment_tree(2*node+1, mid+1, end);

			cout<<node<<" "<<start<<" "<<end<<" "<<seg_tree[node]<<endl;
		}
}segment_tree;
/*
 * Algorithm: Segment Tree with Lazy Propagation.
 * 
 * Problem: lazy_update a value to an interval and query an index for value.
 * Problem: http://codeforces.com/problemset/problem/276/C
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

#define INF 1000000000
#define MOD 1000000007
 
using namespace std;

class SegmentTreeNode
{
	public:
		ll lazy_update;
		ll max_value;
};


class SegmentTree
{
	public:
		int n;
		ll ar[max_size];
		SegmentTreeNode seg_tree[4*max_size];

		void init(int num, ll a[])
		{
			n = num;
			rep(i,1,num)
				ar[i] = a[i];

			build_segment_tree(1, 1, n);
		}

		void build_segment_tree(int node, int start, int end)
		{
			if(start==end)
			{
				seg_tree[node].max_value = ar[start];
				seg_tree[node].lazy_update = 0;
				return;
			}

			int mid = (start+end)/2;
			build_segment_tree(2*node, start, mid);
			build_segment_tree(2*node+1, mid+1, end);


			seg_tree[node].max_value = max(seg_tree[2*node].max_value, seg_tree[2*node+1].max_value);
			seg_tree[node].lazy_update = 0;
		}

		void update(int node, int start, int end, int x, int y, ll value)
		{
			if(start==x && end==y) {
				seg_tree[node].lazy_update = value;
				return;
			}

			if(seg_tree[node].lazy_update>0) {
				seg_tree[node].max_value = seg_tree[node].lazy_update;
				seg_tree[2*node].lazy_update = seg_tree[node].lazy_update;
				seg_tree[2*node+1].lazy_update = seg_tree[node].lazy_update;
				seg_tree[node].lazy_update = 0;
			}

			int mid = (start+end)/2;
			if(mid>=y) {
				update(2*node, start, mid, x, y, value);
			}
			else if(mid+1<=x) {
				update(2*node+1, mid+1, end, x, y, value);
			}
			else {
				update(2*node, start, mid, x, mid, value);
				update(2*node+1, mid+1, end, mid+1, y, value);
			}

			seg_tree[node].max_value = max(max(seg_tree[2*node].max_value, seg_tree[2*node].lazy_update), max(seg_tree[2*node+1].max_value, seg_tree[2*node+1].lazy_update));
		}

		ll query(int node, int start, int end, int x, int y)
		{
			if(seg_tree[node].lazy_update>0) {
				seg_tree[node].max_value = seg_tree[node].lazy_update;
				seg_tree[2*node].lazy_update = seg_tree[node].lazy_update;
				seg_tree[2*node+1].lazy_update = seg_tree[node].lazy_update;
				seg_tree[node].lazy_update = 0;
			}

			if(start==x && end==y)
			{
				return seg_tree[node].max_value;
			}

			int mid = (start+end)/2;

			if(mid>=y)
				return query(2*node, start, mid, x, y);

			if(mid+1<=x)
				return query(2*node+1, mid+1, end, x, y);

			ll left = query(2*node, start, mid, x, mid);
			ll right = query(2*node+1, mid+1, end, mid+1, y);
			
			return max(left, right);
		}
}segment_tree;

int main() {
	return 0;
}
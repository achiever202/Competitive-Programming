/*
 * Author: Adarsh Pugalia
 * Algorithm: Implementation of BIT.
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
 
#define max_size 500005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_log 17
#define max_sieve_size 1005

#define INF 1000000000
#define MOD 1000000007
 
using namespace std;
 
using namespace std;

class BIT {
	public:
		int n;
		ll tree[max_size];

		void init(int num)
		{
			n = num;
			rep(i,0,n)
				tree[i] = 0;
		}

		ll get_cumulative_frequency(ll index)
		{
			ll ret = 0;
			while(index>0)
			{
				ret += tree[index];
				index -= (index & (-index));
			}

			return ret;
		}


		void update_frequency(int index, ll value)
		{
			while(index<=n)
			{
				tree[index] += value;
				index += (index &(-index));
			}
		}
}bit;
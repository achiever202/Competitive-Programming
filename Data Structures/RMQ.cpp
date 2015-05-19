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
 
#define max_size 10000005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
 
#define MOD 1000000007
 
using namespace std;

class RMQ
{
	public:
		ll num_of_elements;
		ll power_of_two[max_power];
		ll sparse_table[max_power][max_size];

		RMQ()
		{
			power_of_two[0] = 1;
			for(ll i=0; i<max_power; i++)
				power_of_two[i] = power_of_two[i-1]*2;
		}

		void init(ll n, ll ar[], ll flag)
		{
			num_of_elements = n;
			for(ll i=0; i<num_of_elements; i++)
				sparse_table[0][i] = ar[i];

			if(flag)
			{
				for(ll j=1; j<max_power; j++)
					for(ll i=0; i<n; i++)
						sparse_table[j][i] = max(sparse_table[j-1][i], sparse_table[j-1][i+power_of_two[j-1]]);
			}
			else
			{
				for(ll j=1; j<max_power; j++)
					for(ll i=0; i<n; i++)
						sparse_table[j][i] = min(sparse_table[j-1][i], sparse_table[j-1][i+power_of_two[j-1]]);
			}
		}

		ll compute_index(ll length)
		{
			ll index = 0;
			while(power_of_two[index]<=length)
				index++;

			index--;

			return index;
		}

		ll query(ll x, ll y, ll flag)
		{
			if(x>y)
			{
				ll temp = x;
				x = y;
				y = temp;
			}

			ll length = y-x+1;
			ll index = compute_index(y-x+1);
			
			if(flag)
				return max(sparse_table[index][x], sparse_table[index][y-power_of_two[index]+1]);
			else
				return min(sparse_table[index][x], sparse_table[index][y-power_of_two[index]+1]);			
		}

		ll query_index(ll x, ll y, ll flag, ll index)
		{
			if(x>y)
			{
				ll temp = x;
				x = y;
				y = temp;
			}

			ll length = y-x+1;
			if(flag)
				return max(sparse_table[index][x], sparse_table[index][y-power_of_two[index]+1]);
			else
				return min(sparse_table[index][x], sparse_table[index][y-power_of_two[index]+1]);	
		}
}rmq;

int main()
{
	return 0;
}
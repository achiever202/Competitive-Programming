/*
 * Author: Adarsh Pugalia
 * Algorithm: KMP for numbers.
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
 
#define max_size 1000005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
 
#define MOD 100000000
 
using namespace std;

ll horse[max_size], bear[max_size];

class KMP
{
	public:
		ll num[max_size];
		ll len;
		ll failure_function[max_size];

		void init(ll n)
		{
			len = n;
			for(ll i=0; i<n; i++)
				cin>>num[i];

			failure_function[0] = 0;
			ll pos = 1, next = 0;
			while(pos<len)
			{
				if(num[pos]==num[next])
				{
					next++;
					failure_function[pos] = next;
					pos++;
				}
				else if(next>0)
				{
					next = failure_function[next-1];
				}
				else
				{
					failure_function[pos] = 0;
					pos++;
				}
			}
		}

		vl search(ll n, ll ar[], ll start)
		{
			vector <ll> ret;

			ll i=start, j=0;
			while(i<n)
			{
				if(ar[i]==num[j])
				{
					i++;
					j++;

					if(j==len)
					{
						ret.pb(i-j);
						j = failure_function[j-1];
					}
				}
				else
				{
					if(j>0)
						j = failure_function[j-1];
					else
						i++;
				}			
			}

			return ret;
		}

		void print_failure_function()
		{
			for(ll i=0; i<len; i++)
				cout<<failure_function[i]<<" ";
			cout<<endl;
		}
}kmp;

int main()
{
	return 0;
}
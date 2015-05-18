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
 
#define MOD 1000000007
 
using namespace std;

class Knapsack
{
	public:
		ll max_weight;
		ll num_of_elements;
		vector <ll> weights;
		vector <ll> values;
		ll ar[max_size];

		void init(ll n, ll w, ll input_mode)
		{
			num_of_elements = n;
			max_weight = w;

			if(input_mode)
			{
				for(ll i=0; i<num_of_elements; i++)
					cin>>weights[i];
				for(ll i=0; i<num_of_elements; i++)
					cin>>values[i];
			}
			else
			{
				for(ll i=0; i<num_of_elements; i++)
					cin>>weights[i]>>values[i];
			}
		}

		ll calc_knapsack()
		{
			for(ll i=0; i<=max_weight; i++)
				ar[i] = -1;

			ar[0] = 0;

			for(ll i=0; i<num_of_elements; i++)
				for(ll j=max_weight; j>=0; j--)
					if(ar[j]>-1 && j+weights[i]<=max_weight && ar[j+weights[i]]>ar[j]+values[i])
						ar[j+weights[i]] = ar[j]+weights[i];

			ll ret = ar[0];
			for(ll i=1; i<=max_weight; i++)
				if(ar[i]>ret)
					ret = ar[i];

			return ret;
		}
}knapsack;

int main()
{
	return 0;
}
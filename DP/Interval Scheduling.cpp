/*
 * Author: Adarsh Pugalia
 * Algorithm: Interval Scheduling with running time O(n)
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
 
#define ll int
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
 
#define max_size 200005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_sieve_size 5000003
 
#define MOD 100000000
 
using namespace std;

bool comp(pair<ll, ll> i, pair<ll, ll> j)
{
	if(i.s==j.s)
		return i.f<j.f;

	return i.s<j.s;
}

class IntervalScheduling
{
	public:
		ll cost, size, n;
		pair<ll, ll> interval[max_size];
		queue <pair<ll, ll> > current_objects;

		void init()
		{
			cin>>n;
			for(ll i=0; i<n; i++)
			{
				ll a, b;
				cin>>a>>b;
				interval[i].f = a-b;
				interval[i].s = a+b;
			}

			sort(interval, interval+n, comp);
		}

		ll get_max_schedulings(ll sz)
		{
			size = sz;

			ll ret = 1;
			current_objects.push(interval[0]);
			for(ll i=1; i<n; i++)
			{
				while(!current_objects.empty() && current_objects.front().s<=interval[i].f)
					current_objects.pop();

				if(current_objects.size()<size)
				{
					current_objects.push(interval[i]);
					ret++;
				}
			}

			return ret;
		}
}interval_scheduling;

int main()
{
	interval_scheduling.init();
	cout<<interval_scheduling.get_max_schedulings(1);
	return 0;
}
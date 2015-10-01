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
#define rep(i,j,k) for(int i=j; i<=k; i++)
#define repd(i,j,k) for(int i=j; i>=k; i--)
 
#define pb push_back
#define pob pop_back
#define mp make_pair
 
#define max_size 100005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_sieve_size 1300005
#define max_log 17

#define INF 10000000
#define MOD 1000000007
 
using namespace std;

/* This function returns the gcd of second_dp long long numbers. */
ll gcd(ll a, ll b)
{
	ll temp;
 
	if(a<b)
	{
		temp = a;
		a = b;
		b = temp;
	}
 
	while(a%b)
	{
		temp = a;
		a = b;
		b = temp%b;
	}
 
	return b;
}

class Point
{
	public:
		ll x, y, z;

		void init(ll i, ll j)
		{
			x = i;
			y = j;
			z = 0;
		}


		void init(ll i, ll j, ll k)
		{
			x = i;
			y = j;
			z = k;
		}


		/* This function returns the squared distance of the point i. */
		ll get_squared_distance(Point i)
		{
			return (i.x-x)*(i.x-x) + (i.y-y)*(i.y-y) + (i.z-z)*(i.z-z);
		}


		/* This function returns the distance of the point i. */
		double get_distance(Point i)
		{
			return pow(((double)get_squared_distance(i)), 0.5);
		}


		ll get_manhattan_distance(Point i)
		{
			return abs(x-i.x) + abs(y-i.y) + abs(z-i.z);
		}

		/*
		 * This funtion returns the slope as a pair of integers.
		 *
		 * ret.f = numerator of slope.
		 * ret.s = denominator of slope.
		 */
		pll get_slope(Point i) {
			pll ret;
			ll g;

			ret.f = y - i.y;
			ret.s = x - i.x;

			if(ret.s<0) {
				ret.s = -ret.s;
				ret.f = -ret.f;
			}

			if(ret.f<0) 
				g = gcd(-ret.f, ret.s);
			else
				g = gcd(ret.f, ret.s);

			ret.f /= g;
			ret.s /= g;

			return ret;
		}

		/* 
		 * This function returns the turn for the point and given points j and k in order. 
		 * In essence it calculates the cross product of (j-point) and (k-point).
		 * This currently works for 2D points.
		 */
		double calculate_turn(Point j, Point k)
		{
			return ((double)(j.x-x)*(k.y-y)) - ((double)(j.y-y)*(k.x-x));
		}

};
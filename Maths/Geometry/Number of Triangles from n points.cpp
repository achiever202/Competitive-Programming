/*
 * Algorithm: Number of triangles formed from n points.
 *
 * For each point we calculate the numebr of points with a given slope and
 * subtract them from the total triangles.
 *
 * NOTE: It works when the cordinates of the points are in a given range.
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
 
#define max_size 1000005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_log 17
#define max_sieve_size 1005

#define INF 1000000000
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

			if(!(ret.f==0 || ret.s==0)) {
				if(ret.f<0) 
					g = gcd(-ret.f, ret.s);
				else
					g = gcd(ret.f, ret.s);

				ret.f /= g;
				ret.s /= g;
			}

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

Point points[max_size];
int dp[410][210];
int offset = 202;

int main() {
	ll n;
	sl(n);

	rep(i,1,n) {
		ll x, y;
		sl(x); sl(y);
		points[i].init(x, y);
	}

	ll ans = (n*(n-1)*(n-2))/6;
	rep(i,1,n) {

		rep(j,0,409)
			rep(k,0,209)
				dp[j][k] = 0;

		rep(j,i+1,n) {
			pll ret = points[i].get_slope(points[j]);

			if(ret.f==0)
				ret.s = 1;
			else if(ret.s==0)
				ret.f = 1;

			ans -= dp[ret.f+offset][ret.s];

			dp[ret.f+offset][ret.s]++;
		}
	}

	pl(ans); pe;
	return 0;
}
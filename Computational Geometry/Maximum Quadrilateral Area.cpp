/* 
 * Author: Adarsh Pugalia
 * Algorithm: Maximum Quadrilateral Area in O(n^3).
 *
 * Explanation: For maximum area, the quadrilateral should be non-self
 		intersecting as a self intersecting quadrilateral can be transformed
 		to a non-self intersecting quadrilateral with a greater area. Now, we
 		choose a diagonal(O(n^2)) and compute the maximum area of traingles
 		that can be formed with the diagonal on both the sides (signed area).
 		Then we take the maximum of them, and compute the maximum for all pairs
 		of diagonals.
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
 
#define max_size 500
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_sieve_size 105
 
#define MOD 1000000007
 
using namespace std;

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

int main()
{
	ll n;
	cin>>n;

	for(ll i=0; i<n; i++)
	{
		ll a, b;
		cin>>a>>b;

		points[i].init(a, b);
	}

	double ans = 0;

	for(ll i=0; i<n; i++)
	{
		for(ll j=i+1; j<n; j++)
		{
			double positive = 0, negative = 0;
			for(ll k=0; k<n; k++)
			{
				if(k!=i && k!=j)
				{
					double temp = points[i].calculate_turn(points[j], points[k]);
					if(temp>0)
						positive = max(positive, temp);
					else
						negative = max(negative, -temp);
				}
			}

			if(positive>0 && negative>0)
				ans = max(ans, positive+negative);
		}
	}

	printf("%0.6lf\n", ans/2);
	return 0;
}
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


class Circle
{
	public:

		/* circle definition with centre and radius. */
		ll radius;
		Point centre;
		double area, circumference, PI;

		void init(ll i, ll j, ll k)
		{
			centre.init(i, j);
			radius = k;
			PI = 3.14159265358979323846;
			area = PI*radius*radius;
			circumference = 2.0*PI*radius;
		}


		/*
		 * This function checks if a Point is strictly inside a circle.
		 */
		bool is_inside(Point i)
		{
			cout<<((centre.x-i.x)*(centre.x-i.x) + (centre.x-i.y)*(centre.x-i.y) - radius*radius)<<endl;
			return (((centre.x-i.x)*(centre.x-i.x) + (centre.x-i.y)*(centre.x-i.y) - radius*radius) < 0);
		}


		/*
		 * This function checks if the circle i is strictly inside the circle.
		 */
		bool is_inside(Circle i)
		{
			ll distance = centre.get_squared_distance(i.centre);
			if(distance<(radius-i.radius)*(radius-i.radius))
				return true;
			return false;
		}


		/*
		 * This function checks if the two circles strictly intersect.
		 */
		bool is_intersecting(Circle i)
		{
			ll distance = centre.get_squared_distance(i.centre);
			if((radius+i.radius)*(radius+i.radius)>distance && (radius-i.radius)*(radius-i.radius)<distance)
				return true;

			return false;
		}
};
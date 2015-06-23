/*
 * Author: Adarsh Pugalia
 * Algorithm: Smallest Enclosing Circle (O(Number_of_iterations*n))
 *			  The algoirthm is similar to linear regression, where it tries to reduce the farthest distance in each iteration.
 *			  Larger the number of iterations, greater the accuracy.
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
 
#define max_size 1005
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
		double x, y, z;

		void init(double i, double j, double k)
		{
			x = i;
			y = j;
			z = k;
		}


		/* This function returns the squared distance of the point i. */
		double get_squared_distance(Point i)
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

}points[max_size];

int main()
{
	ll n;
	double a, b, c;
	cin>>n;

	for(ll i=0; i<n; i++)
	{
		cin>>a>>b>>c;
		points[i].init(a, b, c);
	}

	double mul=1;

	/* starting with origin as the centre of the smallest circle. */
	Point centre;
	centre.init(0, 0, 0);

	for(ll step=0; step<100000; step++)
	{
		ll cur_index = -1;
		double cur_radius = -1;

		/* iterating over each point to find the farthest point. */
		for(ll i=0; i<n; i++)
		{	
			if(cur_radius<centre.get_squared_distance(points[i]))
			{
				cur_radius = centre.get_squared_distance(points[i]);
				cur_index = i;
			}
		}

		/* moving the centre towards the farthest point. */
		centre.x += mul*(points[cur_index].x-centre.x);
		centre.y += mul*(points[cur_index].y-centre.y);
		centre.z += mul*(points[cur_index].z-centre.z);
		mul = mul*0.999;
	}

	printf("%0.8lf %0.8lf %0.8lf\n", centre.x, centre.y, centre.z);
	return 0;
}
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
 
#define max_size 4005
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
		ll x, y;

		void init(ll i, ll j)
		{
			x = i;
			j = y;
		}


		/* This function returns the squared distance of the point i. */
		ll get_squared_distance(Point i)
		{
			return (i.x-x)*(i.x-x) + (i.y-y)*(i.y-y);
		}


		/* This function returns the distance of the point i. */
		double get_distance(Point i)
		{
			return pow(((double)get_squared_distance(i)), 0.5);
		}


		/* 
		 * This function returns the turn for the point and given points j and k in order. 
		 * In essence it calculates the cross product of (j-point) and (k-point)
		 */
		double calculate_turn(Point j, Point k)
		{
			return ((double)(j.x-x)*(k.y-y)) - ((double)(j.y-y)*(k.x-x));
		}

};


class Line
{
	public:
		/* a and b are any two points on the line. */
		Point a, b;

		/* A, B, C are constants that can define the line in the form Ax+By+C. */
		ll A, B, C;


		/* This function initializes the line from two points. */
		void init(Point i, Point j)
		{
			a = i;
			b = j;

			/* generating the Ax+By+C form. */
			A = b.y-a.y;
			B = b.x-a.x;
			C = A*a.x + B*a.y;
		}


		/*
		 * This function returns the distance of point i from the given line.
		 * NOTE: the distance is the signed distance because of calculate turn used.
		 */
		double get_distance_point(Point i)
		{
			double dist = a.calculate_turn(b, i);
			double base = a.get_distance(b);
			return dist/base;
		}


		/*
		 * This function returns the intersection of the line with line i.
		 * It returns a piar of bool and a pair of cordinates.
		 * The bool value is set to false if the lines are parallel.
		 * Else the bool value is true, and the pair of cordinates is the intersection points.
		 */
		pair<bool, pair<double, double> > get_line_intersection(Line i)
		{
			ll det = A*i.B - i.A*B;
			if(det==0)
				return make_pair(false, make_pair(0, 0));

			double x = ((double)(i.B*C - B*i.C))/det;
			double y = ((double)(A*i.C - i.A*C))/det;

			return make_pair(true, make_pair(x, y));
		}
};


class Polygon
{
	public:
		ll sides;
		vector <Point> vertices;

		void init()
		{
			cin>>sides;
			for(ll i=0; i<sides; i++)
			{
				Point temp;
				cin>>temp.x>>temp.y;
			}
		}


		double get_area()
		{
			double area = 0;
			for(ll i=1; i+1<sides; i++)
				area += vertices[0].calculate_turn(vertices[i], vertices[i+1]);

			return abs(area/2);
		}
};


/* 
 * This function computes the turn for three points in order.
 * The method returns a positive number if the points are in anticlockwise order.
 * The method returns 0, if the points are collinear.
 * The method returns a negative number if the points are in clockwise order.
 */
ll calculate_turn(Point i, Point j, Point k)
{
	return (j.x - i.x)*(k.y - i.y) - (j.y - i.y)*(k.x - i.x);	
}

int main()
{
	return 0;
}

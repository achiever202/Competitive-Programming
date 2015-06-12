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
		ll x, y, z;

		void init(ll i, ll j)
		{
			x = i;
			j = y;
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


/* Geometry template ends here. */

Point lowest_point;


/* Comparator function for sorting points on the basis of polar angle. */
bool graham_comp(Point i, Point j)
{
	ll turn = calculate_turn(lowest_point, i, j);
	if(turn==0)
	{
		ll dis1 = lowest_point.get_squared_distance(i);
		ll dis2 = lowest_point.get_squared_distance(j);

		return dis1<dis2;
	}

	if(turn>0)
		return true;

	return false;
}



class GrahamScan
{
	public:
		ll n;
		Point points[max_size];
		vector <Point> hull;

		void init()
		{
			cin>>n;
			for(ll i=0; i<n; i++)
			{
				ll x, y;
				cin>>points[i].x>>points[i].y;
			}

			hull.clear();
		}

		void calc_lowest_point()
		{
			lowest_point = points[0];

			for(ll i=1; i<n; i++)
				if(points[i].y<lowest_point.y || (points[i].y==lowest_point.y && points[i].x<lowest_point.x))
					lowest_point = points[i];

		}

		void compute_convex_hull()
		{
			calc_lowest_point();
			sort(points, points+n, graham_comp);

			hull.push_back(points[0]);
			hull.push_back(points[1]);

			for(ll i=2; i<n; i++)
			{
				while(hull.size()>1)
				{
					Point last = hull[hull.size()-1];

					/* 
					 * if the points are same, keeping the previous point.
					 */
					if(points[i].x==last.x && points[i].y==last.y)
						break;

					hull.pop_back();

					ll turn = calculate_turn(hull[hull.size()-1], last, points[i]);

					/*
					 * This excludes multiples points on the same segment of the hull.
					 * To include collinear points, change the condition to >=.
					 */
					if(turn>0)
					{
						hull.push_back(last);
						hull.push_back(points[i]);
						break;
					}
				}

				if(hull.size()==1)
					hull.push_back(points[i]);
			}
		}


		double get_hull_length()
		{
			double fence = 0;
			for(ll i=1; i<hull.size(); i++)
				fence += hull[i-1].get_distance(hull[i]);

			fence += hull[hull.size()-1].get_distance(hull[0]);

			return fence;
		}


		void print_hull_points()
		{
			for(ll i=0; i<hull.size(); i++)
				cout<<hull[i].x<<" "<<hull[i].y<<endl;
		}
}graham_scan;

int main()
{	
	graham_scan.init();
	graham_scan.compute_convex_hull();
	graham_scan.print_hull_points();
	return 0;
}
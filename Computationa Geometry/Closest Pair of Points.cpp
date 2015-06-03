/*
 * Author: Adarsh Pugalia
 * Algorithm: Closest pair of points using sweep line method in O(nlogn).
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
 
#define max_size 4005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_sieve_size 105

#define eps 0.00000001
#define INF 1e15
 
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


		/* This function returns the manhattan distance of the point from point i. */
		ll get_manhattan_distance(Point i)
		{
			return abs(x-i.x) + abs(y-i.y);
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


/* This is used as a comparator for the set to compare points on the basis of y cordinate. */
class PointComparator
{
	public:
		bool operator()(const Point& i, const Point&j)
		{
			return i.y<j.y;
		}
};


/* This is a comparator for sorting points on the basis of x cordinate. */
bool point_x_comparator(Point i, Point j)
{
	if(i.x==j.x)
		return i.y<j.y;

	return i.x<j.x;
}


class ClosestPairofPoints
{
	public:
		ll num_of_points;
		Point points[max_size];
		set <Point, PointComparator> box;
		set <Point, PointComparator>::iterator it;
		ll closest_distance;


		/* This function takes the points as input and sorts them. */
		void init()
		{
			cin>>num_of_points;
			for(ll i=0; i<num_of_points; i++)
				cin>>points[i].x>>points[i].y;

			sort(points, points+num_of_points, point_x_comparator);
			closest_distance = INF;
		}


		/*
		 * This function calculates the closest pair of points.
		 * @return pair of closest distance and the pair of closest points.
		 */
		pair<double, pair<Point, Point> > get_closest_pair()
		{
			pair<Point, Point> closest_pair;

			box.insert(points[0]);
			ll left = 0;

			for(ll i=1; i<num_of_points; i++)
			{
				/* remove points that are farther than the closest distance in x. */
				while(left<i && (points[i].x-points[left].x)*(points[i].x-points[left].x)>closest_distance)
				{
					box.erase(points[left]);
					left++;
				}

				Point temp;
				temp.x = points[i].x-pow(closest_distance, 0.5);
				temp.y = points[i].y-pow(closest_distance, 0.5);

				/* check only points that are closer than the closest distance in y. */
				for(it=box.lower_bound(temp); it!=box.end() && (points[i].y-it->y)*(points[i].y-it->y)<=closest_distance; it++)
				{
					ll distance = points[i].get_squared_distance(*it);
					if(distance<closest_distance)
					{
						closest_distance = distance;
						closest_pair = make_pair(*it, points[i]);
					}
				}

				box.insert(points[i]);
			}

			return make_pair(pow((double)closest_distance, 0.5)+eps, closest_pair);
		}
}closest_pair_of_points;

int main()
{
	closest_pair_of_points.init();
	pair<double, pair<Point, Point> > ans = closest_pair_of_points.get_closest_pair()
	return 0;
}
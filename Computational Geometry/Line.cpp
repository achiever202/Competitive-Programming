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

double eps = 0.000000001;

class Point
{
	public:
		double x, y, z;

		void init(double i, double j)
		{
			x = i;
			y = j;
			z = 0;
		}


		void init(double i, double j, double k)
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
			return pow((get_squared_distance(i)), 0.5);
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
			return ((j.x-x)*(k.y-y)) - ((j.y-y)*(k.x-x));
		}

};


/*
 * This class creates a Line object.
 * It currently handles lines in 2D.
 */
class Line
{
	public:
		/* a and b are any two points on the line. */
		Point a, b;

		/* A, B, C are constants that can define the line in the form Ax+By+C. */
		double A, B, C;


		/* This function initializes the line from two points. */
		void init(Point i, Point j)
		{
			a = i;
			b = j;

			/* generating the Ax+By+C form. */
			A = a.y-b.y;
			B = -(a.x-b.x);
			C = -b.x*A + b.y*(-B);
		}


		/* This function initalizes the line from the constants. */
		void init(ll a, ll b, ll c)
		{
			A = a;
			B = b;
			C = c;
		}


		double get_x_cordinate(double y)
		{
			return (-C-B*y)/A;
		}


		double get_y_cordinate(double x)
		{
			return (-C-A*x)/B;
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
			double det = A*i.B - i.A*B;
			if(det==0)
				return make_pair(false, make_pair(0, 0));

			double x = ((double)(i.B*C - B*i.C))/det;
			double y = ((double)(A*i.C - i.A*C))/det;

			return make_pair(true, make_pair(x, y));
		}


		/* 
		 * This function tests if a point is on the line.
		 */
		bool is_on_line(Point i)
		{
			return (A*i.x + B*i.y + C == 0);
		}

		bool is_on_line(double i, double j)
		{
			return (A*i + B*j + C == 0);
		}


		/*
		 * This function tests whether two points are on the same side of the line.
		 * The points should not be on the line. In that case, it returns false.
		 */
		bool is_same_side(Point i, Point j)
		{
			double value1 = A*i.x + B*i.y + C;
			double value2 = A*j.x + B*j.y + C;

			if(value1>0 && value2>0)
				return true;

			if(value1<0 && value2<0)
				return true;

			return false;
		}
};

int main()
{
	return 0;
}
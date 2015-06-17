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
#define fi(i,n) for(int i=0; i<n; i++)
#define fie(i,n) for(int i=0; i<=n; i++)
#define fd(i,n) for(int i=n; i>0; i--)
#define fde(i,n) for(int i=n; i>=0; i--)

 
#define pb push_back
#define pob pop_back
 
#define max_size 100005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_sieve_size 105
#define max_log 17
 
#define MOD 1000000007L
 
using namespace std;

double INF = 1000000000000.0;

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
		ll A, B, C;

		/*
		 * y = mx+c, where:
		 * m = slope
		 * c = y-intercept.
		 */
		ll m, c;

		bool is_vertical;


		/* This function initializes the line from two points. */
		void init(Point i, Point j)
		{
			a = i;
			b = j;

			/* generating the Ax+By+C form. */
			A = b.y-a.y;
			B = b.x-a.x;
			C = A*a.x + B*a.y;

			if(B!=0)
			{
				m = (A/-B);
				c = (C/-B);
				is_vertical = false;
			}
			else
				is_vertical = true;
		}


		/* This function initalizes the line from the constants. */
		void init(ll a, ll b, ll c)
		{
			A = a;
			B = b;
			C = c;

			if(B!=0)
			{
				m = (A/-B);
				c = (C/-B);
				is_vertical = false;
			}
			else
				is_vertical = true;
		}


		/* This function initializes the line of the for y = mx+c. */
		void init(ll slope, ll intercept)
		{
			m = slope;
			c = intercept;

			A = m;
			B = -1;
			C = c;

			is_vertical = false;
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
			det = -det;
			if(det==0)
				return make_pair(false, make_pair(0, 0));

			double x = ((double)(i.B*C - B*i.C))/det;
			double y = ((double)(A*i.C - i.A*C))/det;

			return make_pair(true, make_pair(x, y));
		}


		/*
		 * This function tests whether two points are on the same side of the line.
		 * The points should not be on the line. In that case, it returns false.
		 */
		bool is_same_side(Point i, Point j)
		{
			ll value1 = A*i.x + B*i.y + C;
			ll value2 = A*j.x + B*j.y + C;

			if(value1>0 && value2>0)
				return true;

			if(value1<0 && value2<0)
				return true;

			return false;
		}
};

/* for minima. */
class LineComparator
{
	public:
		bool operator()(const Line& i, const Line&j)
		{
			if(i.m==j.m)
				return i.c<j.c;

			return i.m>j.m;
		}
};

/* for maxima. */
/*class LineComparator
{
	public:
		bool operator()(const Line& i, const Line&j)
		{
			if(i.m==j.m)
				return i.c>j.c;

			return i.m<j.m;
		}
};*/

class ConvexHullTrick
{
	public:
		bool is_minima;
		set <Line, LineComparator> lines;
		map <Line, double, LineComparator> x_point;
		map <double, Line> query_set;

		/*
		 * This function initializes the convex hull for maximum or minimum.
		 * For minimum: flag = false
		 * For maximum: flag = true
		 */
		void init(bool flag)
		{
			is_minima = flag;
		}


		/* This function tests if a line is valid in the set. */
		bool is_bad(Line a)
		{
			Line right, left;
			set <Line, LineComparator>::iterator it;

			it = lines.find(a);

			if(it==lines.begin())
			{
				it++;

				/* for minimua */
				if(is_minima && it!=lines.end())
					return (a.m==it->m && a.c>=it->c);

				/* for maxima */
				if(!is_minima && it!=lines.end())
					return (a.m==it->m && a.c<=it->c);
				
				return false;
			}

			it--;
			left = *it;

			it++; it++;

			/* for minimua */
			if(is_minima && it==lines.end())
				return a.m==left.m && a.c>=left.c;

			if(is_minima && (a.m==left.m && a.c>=left.c)||(a.m==right.m && a.c>=right.c))
				return true;

			/* for maxima */
			if(!is_minima && it==lines.end())
				return a.m==left.m && a.c<=left.c;

			if(!is_minima && (a.m==left.m && a.c<=left.c)||(a.m==right.m && a.c<=right.c))
				return true;

			right = *it;

			pair<bool, pair<double, double> > first_point = left.get_line_intersection(a);
			pair<bool, pair<double, double> > second_point = left.get_line_intersection(right);

			if(first_point.s.f>=second_point.s.f)
				return true;

			return false;
		}

		/* This function adds a line to the set. */
		void add_line(Line a)
		{
			lines.insert(a);

			if(is_bad(a))
			{
				lines.erase(a);
				return;
			}

			set <Line, LineComparator>::iterator it, next, prev;
			it = lines.find(a);

			next = it;
			next++;

			while(next!=lines.end() && is_bad(*next))
			{
				lines.erase(*next);
				double x = x_point.find(*next)->s;
				x_point.erase(*next);
				query_set.erase(x);

				next = it;
				next++;
			}

			prev = it;
			prev--;

			while(it!=lines.begin() && is_bad(*prev))
			{
				lines.erase(*prev);
				double x = x_point.find(*prev)->s;
				x_point.erase(*prev);
				query_set.erase(x);

				prev = it;
				prev--;
			}

			if(it==lines.begin())
			{
				x_point.insert(make_pair(a, -INF));
				query_set.insert(make_pair(-INF, a));
			}
			else
			{
				it--;
				pair<bool, pair<double, double> > intersection = a.get_line_intersection(*it);
				x_point.insert(make_pair(a, intersection.s.f));
				query_set.insert(make_pair(intersection.s.f, a));
			}

			it = lines.find(a);
			it++;
			if(it!=lines.end())
			{
				pair<bool, pair<double, double> > intersection = a.get_line_intersection(*it);
				query_set.erase(x_point.find(*it)->s);
				query_set.insert(make_pair(intersection.s.f, *it));
				x_point.find(*it)->s = intersection.s.f;
			}
		}


		/* This function returns the minimum/maximum value at x. */
		double get_value(double x)
		{	
			map<double, Line>::iterator it = query_set.upper_bound(x);
			it--;

			return x*it->s.m + it->s.c;
		}

		/* This function prints the current lines in the set. */
		void print_lines()
		{
			cout<<"printing lines:\n";
			set <Line, LineComparator>::iterator it;
			for(it=lines.begin(); it!=lines.end(); it++)
			{
				cout<<it->m<<" "<<it->c;
				double x = x_point.find(*it)->s;
				cout<<" starting at point: "<<x<<endl;
			}
		}
}convex_hull_trick;

int main()
{
	
	return 0;
}
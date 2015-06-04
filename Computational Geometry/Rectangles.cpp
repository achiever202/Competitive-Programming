/*
 * Author: Adarsh Pugalia
 * Algorithm: Implementation of rectangle class.
 *			  Area of union of rectangles (paralled to axes) in O(n^2).
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

class Rectangle
{
	/* 
	 * A rectangle can be defined by two points.
	 * We are using bottom left and top right points.
	 */
	public:
		pll bottom_left;
		pll top_right;
		ll length;
		ll breadth;

		/*
		 * If flag = 1, the points to initialize are bottom left and top right.
		 * Else, the points are bottom right and top left.
		 * In the second case, the points are converted to first and then stored.
		 */
		void init(pll i, pll j, ll flag)
		{
			if(flag)
			{
				bottom_left = i;
				top_right = j;
				length = (top_right.f - bottom_left.f);
				breadth = (top_right.s - bottom_left.s);
			}
			else
			{
				bottom_left = make_pair(j.f, i.s);
				top_right = make_pair(i.f, j.s);
				length = (top_right.f - bottom_left.f);
				breadth = (top_right.s - bottom_left.s);
			}
		}


		ll get_area()
		{
			return length*breadth;
		}


		ll get_perimeter()
		{
			return 2*(length+breadth);
		}
};


class VerticalComparator
{
	public:
		bool operator()(const pair<ll, pll >& i, const pair<ll, pll >&j)
		{
			if(i.s.s==j.s.s)
				return i.f<j.f;

			return i.s.s<j.s.s;	
		}
};

class HorizontalComparator
{
	public:
		bool operator()(const pll& i, const pll&j)
		{
			if(i.s==j.s)
				return i.f<j.f;

			return i.s>j.s;	
		}
};

class Rectangles
{
	public:
		ll num_of_rectangles;
		Rectangle rectangles[max_size];
		set <pair<ll, pll >, VerticalComparator> vertical_events;
		set <pair<ll, pll >, VerticalComparator>::iterator vertical_it;

		set<pll, HorizontalComparator> horizontal_events;
		set<pll, HorizontalComparator>::iterator horizontal_it;


		void init()
		{
			cin>>num_of_rectangles;
			for(ll i=0; i<num_of_rectangles; i++)
			{
				pll temp, temp2;
				cin>>temp.f>>temp.s>>temp2.f>>temp2.s;
				rectangles[i].init(temp, temp2, 1);
			}
		}	


		ll get_area_of_union()
		{
			ll area = 0;

			/* 
			 * Adding the vertical events for breadth edges. 
			 * 0 means start edge, 1 means end edge.
		  	 */
			for(ll i=0; i<num_of_rectangles; i++)
			{
				vertical_events.insert(make_pair(0, make_pair(i, rectangles[i].bottom_left.f)));
				vertical_events.insert(make_pair(1, make_pair(i, rectangles[i].top_right.f)));
			}

			/* adding the horizontal events for the first rectangle. */
			vertical_it = vertical_events.begin();
			horizontal_events.insert(make_pair(0, rectangles[vertical_it->s.f].top_right.s));
			horizontal_events.insert(make_pair(1, rectangles[vertical_it->s.f].bottom_left.s));
			ll last_x = vertical_it->s.s;

			vertical_it++;

			for(; vertical_it!=vertical_events.end(); vertical_it++)
			{
				ll swept_distance = vertical_it->s.s - last_x;
				last_x = vertical_it->s.s;

				/* for each vertical sweep, calculating the horizontal sweep of active rectangles. */
				ll overlapping_rectangles = 0;
				ll begin_y, last_y;
				for(horizontal_it = horizontal_events.begin(); horizontal_it!=horizontal_events.end(); horizontal_it++)
				{					if(horizontal_it->f==0)
					{
						if(overlapping_rectangles==0)
						{
							overlapping_rectangles = 1;
							begin_y = horizontal_it->s;
						}
						else
							overlapping_rectangles++;
					}
					else
					{
						overlapping_rectangles--;
						if(overlapping_rectangles==0)
							area += swept_distance*abs(horizontal_it->s-begin_y);
					}

					last_y = horizontal_it->s;
				}

				if(vertical_it->f==0)
				{
					horizontal_events.insert(make_pair(0, rectangles[vertical_it->s.f].top_right.s));
					horizontal_events.insert(make_pair(1, rectangles[vertical_it->s.f].bottom_left.s));
				}
				else
				{
					horizontal_events.erase(make_pair(0, rectangles[vertical_it->s.f].top_right.s));
					horizontal_events.erase(make_pair(1, rectangles[vertical_it->s.f].bottom_left.s));
				}
			}

			return area;

		}
}rects;

int main()
{	
	rects.init();
	cout<<rects.get_area_of_union();
}
/*
 * Author: Adarsh Pugalia
 * Algorithm: Fully dynamic variant of convex hull trick for optimizing DP.
 *
 * NOTE: This implementation is for minima for curves (x-a)^2 + c. (a>=0)
 *
 * Hint: http://wcipeg.com/wiki/Convex_hull_trick
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
 
#define max_size 5000005
#define max_sieve_size 5000005
#define max_power 26
#define max_log 17
 
#define MOD 1000000007
#define mod(a) ((a)%MOD)
 
using namespace std;
 
double INF = 10000000000000000.0;

/*
 * Types for caluclating lower bound and sorting the set.
 *
 * Initialize with CURVE for storing in the set.
 * Initialize with QUERY for finding the lowest value at a point.
 */ 
int CURVE = 0, QUERY = 1; 

class Curve {
	public:
		int x;
		ll c;
		double start_point;
		int type;
 
		bool operator<(const Curve& curve) const
        {
            if (curve.type == CURVE)
                return this->x < curve.x;
 
            return this->start_point < curve.x;
        }
 
		void init(int a, ll b) {
			x = a;
			c = b;
			start_point = -INF;
			type = CURVE;
		}
 
		void init(int a, ll b, int t){
			x = a;
			c = b;
			type = t;
		}
 
		double get_intersection(Curve i) {
			double ret = 1.0*i.x*i.x - 1.0*x*x;
			ret += i.c - c;
			ret /= 2*(i.x-x);
			return ret;
		}
};
 
 
class ConvexHullTrick
{
	public:
		set <Curve> curves;
 
		/* This function tests if a curve is valid in the set. */
		bool is_bad(set<Curve>::iterator it)
		{
			Curve right, left;
 
			if(it==curves.begin()) {
				return false;
			}
 
			it--;
			left = *it;
 
			it++; it++;
			right = *it;
			if(it==curves.end()) {
				return false;
			}
 
			double first_point = left.get_intersection(*it);
			double second_point = left.get_intersection(right);
 
			if(first_point>=second_point) {
				return true;
			}
 
			return false;
		}
 
		/* This function adds a curve to the set. */
		void add_curve(Curve a)
		{
			int flag = 1;
 
			auto it = curves.lower_bound(a);
			if(it!=curves.end() && it->x==a.x) {
				if(it->c<=a.c)
					return;
 
				curves.erase(it);
			}
 
			auto it2 = curves.insert(a);
			if(is_bad(it2)) {
				curves.erase(it2);
				return;
			}
			
			it = curves.find(a);
			auto next = it;
			next++;
 
			while(next!=curves.end() && is_bad(*next))
			{
				curves.erase(*next);
 
				next = it;
				next++;
			}
 
			auto prev = it;
			prev--;
 
			while(it!=curves.begin() && is_bad(*prev))
			{
				curves.erase(*prev);
 
				prev = it;
				prev--;
			}
 
			if(it!=curves.begin()) {
				prev = it;
				prev--;
				double intersection = a.get_intersection(*prev);
				a.start_point = intersection;
 
				curves.erase(it);
				curves.insert(a);
				it = curves.find(a);
			}
 
			next = it;
			next++;
			if(next!=curves.end())
			{
				double intersection = a.get_intersection(*next);
				Curve curve = *next;
				curve.start_point = intersection;
 
				curves.erase(next);
				curves.insert(curve);
			}
		}
 
 
		/* This function returns the minimum/maximum value at x. */
		ll get_value(int x)
		{	
			if(curves.size()==0)
				return INF;
 
			Curve curve;
			curve.init(x, 0, QUERY);
 
			auto it = curves.lower_bound(curve);
			it--;
 
			return ((ll)it->x-x)*(it->x-x) + it->c;
		};
};

int main() {
	return 0;
}
/*****************************************************************************************/
/*																		     			 */
/*  					Adarsh Pugalia 										 			 */
/*																			 			 */
/*****************************************************************************************/

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
#include <string.h>
 
#define ll long long int
#define llu long long int unsigned
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
 
#define max_size 500005
#define max_sieve_size 100005
#define max_log 17
 
#define INF 1000000000000000000
#define MOD 1000000007
#define ESP 0.0000001
 
#define mod(a) ((a)%MOD)
#define swap(a, b) a += b, b = a-b, a -= b
 
using namespace std;

bool interval_comp(pii i, pii j) {
	if(i.f==j.f) {
		return i.s<j.s;
	}

	return i.f<j.f;
}


class IntervalScheduling {
	public:
		int n;
		vector<pii > intervals;
		vector<pii > v;

		int START, END;

		IntervalScheduling() : START(1), END(0) {

		}

		void init(int n_) {
			n = n_;
			intervals.clear();
			v.clear();
		}


		void add_interval(int start, int end) {
			intervals.pb(mp(start, end));
		}


		int get_maximum_intersection() {
			rep(i,0,sz(intervals)) {
				v.pb(mp(intervals[i].f, START));
				v.pb(mp(intervals[i].s, END));
			}

			sort(all(v), interval_comp);

			int ret = 0, cur_intersection = 0;
			rep(i,0,sz(v)) {
				if(v[i].s==START) {
					cur_intersection++;
					ret = max(ret, cur_intersection);
				}
				else {
					cur_intersection--;
				}
			}

			return ret;
		}
};

int main() {
	return 0;
}
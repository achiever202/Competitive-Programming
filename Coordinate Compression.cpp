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
 
#define max_size 100005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_log 17
#define max_sieve_size 1005

#define INF 100000000000L
#define MOD 1000000007
 
using namespace std;

class CoordinateCompression {
	public:
		static const int EXACT_VALUE=0, LESS_THAN_EQUAL=1, GREATER_THAN_EQUAL=2;
		vector <ll> v;
		map<ll, int> mapping;

		void init(vector<ll> original) {
			v.clear();
			mapping.clear();

			set<ll> s;
			rep(i,0,sz(original))
				s.insert(original[i]);

			v.assign(all(s));

			rep(i,0,sz(v))
				mapping.insert(mp(v[i], i));
		}

		int binary_search(int start, int end, ll value, int flag) {
			if(end-start<=1) {
				if(flag==LESS_THAN_EQUAL) {
					if(v[end]<=value){
						return end;
					}

					if(v[start]<=value) {
						return start;
					}

					return -1;
				}
				else {
					if(v[start]>=value)
						return start;

					if(v[end]>=value)
						return end; 

					return -1;
				}
			}

			int mid = (start+end)/2;

			if(flag==LESS_THAN_EQUAL) {
				if(v[mid+1]<=value)
					return binary_search(mid+1, end, value, flag);

				return binary_search(start, mid, value, flag);
			}
			else {
				if(v[mid]>=value)
					return binary_search(start, mid, value, flag);
				return binary_search(mid+1, end, value, flag);
			}
		}

		int get_index(ll value) {
			map<ll, int>::iterator it = mapping.find(value);
			if(it==mapping.end())
				return -1;

			return it->s;
		}
}cc;
/*
 * Author: Adarsh Pugalia
 * Problem: Given n numbers, find the number of subsets whose xor equals p.
 * Constraints: n <= 10^5, A[i] < 2^10
 * 
 * Solution: DP (similar to knapsack)
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
 
#define max_size 105
#define max_sieve_size 100005
#define max_log 17
 
#define INF 1000000000000000000
#define MOD 1000000007
#define ESP 0.0000001
 
#define mod(a) ((a)%MOD)
#define swap(a, b) a += b, b = a-b, a -= b
 
using namespace std;

class Long {
	public:
		ll val;

		Long() {
			val = 0;
		}

		Long(ll v) {
			val = v;
		}

		void set(ll v) {
			val = v;
		}

		Long operator+(const Long& i) {
			Long ret = Long(val);
			ret.val += i.val;
			ret.val %= MOD;
			return ret;
		}

		Long operator-(const Long& i) {
			Long ret(val);
			ret.val += (MOD-i.val);
			ret.val %= MOD;
			return ret;
		}

		Long operator*(const Long& i) {
			Long ret(val);
			ret.val *= i.val;
			ret.val %= MOD;
			return ret;
		}

		bool operator<(const Long& i) {
			return val<i.val;
		}

		bool operator>(const Long& i) {
			return val>i.val;
		}

		bool operator==(const Long& i) {
			return val==i.val;
		}
};

/* stores the powers of 2. */
Long pow2[100005];

void preprocess() {
	pow2[0].set(1);
	for(int i=1; i<100005; i++)
		pow2[i] = (pow2[i-1]*Long(2));
}

Long total[1030], temp[1030];
ll num[1025];

void init() {
	rep(i,0,1024) {
		total[i].set(0);
		temp[i].set(0);
		num[i] = 0;
	}
}

string word;
void solve(int test_case) {
	init();
	
	int p;
	sd(p);

	int n;
	sd(n);

	total[0].set(1);

	rep(j,1,n) {
		int a;
		sd(a);
		num[a]++;
	}

	/*
	 * updating xors for subsets with number i.
	 * using a^a = 0, 0^a = a.
	 * nC0 + nC2 + .. = nC1 + nC3.. = 2^n - 1
	 */
	for(int i=0; i<1024; i++) {
		if(num[i]>0) {
			rep(j,0,1023) {
				temp[i^j] = (temp[i^j] + (pow2[num[i]-1]*total[j]));
				temp[j] = (temp[j] + ((pow2[num[i]-1]-Long(1))*total[j]));
			}

			rep(j,0,1023) {
				total[j] = total[j] + temp[j];
				temp[j].set(0);
			}
		}
	}

	pl(total[p].val); pe;
} 

int main() {
	preprocess();
	int t = 1;
	sd(t);

	rep(i,1,t) {
		solve(i);
	}
}
/*
 * Author: 		Adarsh Pugalia
 *
 * Algorithm: 	Z Algorithm: For a given string s, it calculates the longest
 *				subbstring starting from each index, such that the substring
 *				is a prefix of the string.
 *
 * Complexity:	O(n)
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
#define rep(i,j,k) for(int i=j; i<=k; i++)
#define repd(i,j,k) for(int i=j; i>=k; i--)
 
#define pb push_back
#define pob pop_back
#define mp make_pair
 
#define max_size 100005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_sieve_size 1300005
#define max_log 17

#define INF 10000000
#define MOD 1000000007
 
using namespace std;

class Z{
	public:
		int z[max_size];

		void init(string w){
			int l=0, r = 0;
			rep(i,1,(int)w.length()-1) {
				if(i>r) {
					l = r = i;
					while(r<w.length() && w[r]==w[r-l])
						r++;

					z[i] = r-l;
					r--;
				}
				else {
					int k = i-l;
					if(z[k]<r-i+1) {
						z[i] = z[k];
					}
					else {
						l = i;
						while(r<w.length() && w[r]==w[r-l])
							r++;
						z[i] = r-l;
						r--;
					}
				}
			}
		}
};

int main(){

	return 0;
}
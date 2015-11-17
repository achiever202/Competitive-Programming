/*
 * Author: Adarsh Pugalia
 * Algorithm: Kth laregst number in a multiplication grid.
 * Complexity: O(nlog(nm))
 * Problem: http://codeforces.com/contest/448/problem/D
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
#define slf(n) scanf("%lf", &n)

#define pd(n) printf("%d", n);
#define pl(n) printf("%lld", n);
#define ps printf(" ")
#define pe printf("\n")

#define rep(i,j,k) for(int i=j; i<=k; i++)
#define repd(i,j,k) for(int i=j; i>=k; i--)

#define sz(n) (int)n.size()-1 
#define pb push_back
#define pob pop_back
#define mp make_pair
 
#define max_size 1005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 50005
#define max_power 26
#define max_sieve_size 105
#define max_log 17

#define INF 10000000
#define MOD 1000000007
 
using namespace std;

class BinarySearch {
    public:
        ll ar[max_size];

        bool check(ll index, ll value) {
            return false;
        }

        int is_present(int start, int end, ll value) {
            if(start>end)
                return false;

            if(end-start<=1) {
                if(ar[start]==value)
                    return start;

                if(ar[end]==value)
                    return end;

                return -1;
            }

            int mid = (start+end)/2;
            if(ar[mid]>=value)
                return is_present(start, mid, value);

            return is_present(mid+1, end, value);
        }


        ll b_search_left(ll start, ll end, ll value) {
            if(end<start)
                return -1;

            if(end-start<=1) {
                if(check(start, value))
                    return start;

                if(check(end, value))
                    return end;

                return -1;
            }

            ll mid = (start+end)/2;
            if(check(mid, value))
                return b_search_left(start, mid, value);

            return b_search_left(mid+1, end, value);
        }
}b_search;

int main() {
    return 0;
}  
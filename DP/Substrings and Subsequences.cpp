/*
 * Author: Adarsh Pugalia
 * Problem: Number of substrings of one string as subsequences of other string.
 * 			http://codeforces.com/problemset/problem/163/A
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
#define max_sieve_size 105
#define max_log 17
#define MOD 1000000007L
 
using namespace std;

ll dp[5005][5005];
string s, t;

int main(){

	cin>>s>>t;
	ll lens = s.length(), lent = t.length();

	repd(i,lens-1,0){
		if(s[i]==t[lent-1])
			dp[i][lent-1] = 1;
		else
			dp[i][lent-1] = 0;

		repd(j,lent-2,0){
			dp[i][j] = dp[i][j+1];
			if(s[i]==t[j])
				dp[i][j] = (dp[i][j]+dp[i+1][j+1]+1)%MOD;
		}
	}

	ll ans = 0;
	rep(i,0,lens-1)
		ans = (ans+dp[i][0])%MOD;

	cout<<ans<<endl;
	return 0;
}
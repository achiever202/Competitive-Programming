/*
 * Author: Adarsh Pugalia
 * Problem: Find the number of unordered pairs in an undirected graph such that
 *			the neibhour sets are equal. 
 *			http://codeforces.com/contest/154/problem/C
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
 
#define max_size 1000005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_sieve_size 105
#define max_log 17
 
using namespace std;

map<ll,ll> friends_hash;
map<ll,ll>::iterator it;

ll size = 101;
pair<ll,ll> powers[max_size];
pair<ll,ll> friends[max_size];
pair<int,int> edges[max_size];

int main(){

	ll n, m;
	sl(n), sl(m);

	powers[0].f = powers[0].s = 1;
	rep(i,1,n){
		powers[i].f = (powers[i-1].f*size);
	}

	rep(i,1,m){
		sd(edges[i].f); sd(edges[i].s);

		friends[edges[i].f].f = (friends[edges[i].f].f + powers[edges[i].s].f);
		friends[edges[i].s].f = (friends[edges[i].s].f + powers[edges[i].f].f);		
	}

	rep(i,1,n){
		it = friends_hash.find(friends[i].f);
		if(it==friends_hash.end())
			friends_hash.insert(make_pair(friends[i].f, 1));
		else
			it->s++;
	}


	ll ans = 0;
	for(it=friends_hash.begin(); it!=friends_hash.end(); it++){
		ans += (it->s*(it->s-1))/2;
	}

	rep(i,1,m){
		pll temp1 = friends[edges[i].f], temp2 = friends[edges[i].s];

		temp1.f = (temp1.f - powers[edges[i].s].f);
		temp2.f = (temp2.f - powers[edges[i].f].f);

		if(temp1.f==temp2.f)
			ans++;
	}

	printf("%lld\n", ans);
	return 0;
}
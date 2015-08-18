/* 
 * Author: Adarsh Pugalia
 * Algorithm: Number of ways to reach a point in a grid without visiting some of the cells.
 * Problem : http://codeforces.com/contest/559/problem/C
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
 
#define max_size 5005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_sieve_size 105
#define max_log 17
 
#define MOD 1000000007L
 
using namespace std;

ll fact[200005];

 
/* Template ends here. */

/* This function calcluates the pth power of a number n modula given mod. */
ll mod_pow(ll n, ll p, ll mod)
{
	ll res = 1;
	while(p)
	{
		if(p&1)
			res = (res*n)%mod;
 
		n = (n*n)%mod;
 
		p /= 2;
	}
 
	return res;
}
 
 
/* This function calculates the modular inverse of the given number n. */
ll mod_inv(ll n, ll mod)
{
	return mod_pow(n, mod-2, mod);
}
 
 
 
/* This function performs the division modulo prime. */
ll mod_divison(ll dividend, ll divisor, ll mod)
{
	return (dividend*mod_inv(divisor, mod))%mod;
}
 

/* This function returns nCk mod prime. */
ll get_nCr(ll n, ll k, ll mod)
{
	//cout<<fact[n]<<" "<<fact[k]*fact[n-k]<<" "<<mod_divison(fact[n], (fact[k]*fact[n-k])%mod, mod)<<endl;
	return mod_divison(fact[n], (fact[k]*fact[n-k])%mod, mod);
}

void generate_factorials(ll n){
	fact[0] = fact[1] = 1;

	rep(i,2,n){
		fact[i] = (fact[i-1]*i)%MOD;
	}
}

bool comp(pair<pair<ll, ll>, ll> i, pair<pair<ll, ll>, ll> j){
	if(i.f==j.f)
		return i.s<j.s;

	return i.f<j.f;
}

int main(){

	ll h, w, n;
	cin>>h>>w>>n;

	generate_factorials(h+w+5);

	vector<pair<pair<ll, ll>, ll> > black_cells;

	rep(i,1,n){
		ll a, b;
		cin>>a>>b;

		black_cells.push_back(make_pair(make_pair(a, b), 0));
	} 

	black_cells.push_back(make_pair(make_pair(h, w), 0));

	sort(black_cells.begin(), black_cells.end(), comp);

	rep(i,0,black_cells.size()-1){
		black_cells[i].s = get_nCr(black_cells[i].f.f-1+black_cells[i].f.s-1, black_cells[i].f.f-1, MOD);

		rep(j,0,i-1){
			if(black_cells[j].f.s<=black_cells[i].f.s)
				black_cells[i].s = ((black_cells[i].s - (black_cells[j].s*get_nCr(black_cells[i].f.f - black_cells[j].f.f + black_cells[i].f.s - black_cells[j].f.s, black_cells[i].f.f - black_cells[j].f.f, MOD))%MOD)%MOD+MOD)%MOD;
		}
	}

	cout<<black_cells[n].s<<endl;
	return 0;
}
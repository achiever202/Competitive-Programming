#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <set>
#include <queue>
#include <algorithm>
#include <stack>

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

#define max_size 100005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340

#define mod 1000000007

using namespace std;

/* This function calcluates the pth power of a number n modula given mod. */
ll mod_pow(ll n, ll p)
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
ll mod_inv(ll n)
{
	return mod_pow(n, mod-2);
}



/* This function performs the division modulo prime. */
ll mod_divison(ll dividend, ll divisor)
{
	return (dividend*mod_inv(divisor))%mod;
}
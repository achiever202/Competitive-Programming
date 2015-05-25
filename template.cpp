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
 
#define ll int
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
#define max_power 26
#define max_sieve_size 5000003
 
#define MOD 100000000
 
using namespace std;
 
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
 
 
/* This function returns the gcd of two long long numbers. */
ll gcd(ll a, ll b)
{
	ll temp;
 
	if(a<b)
	{
		temp = a;
		a = b;
		b = temp;
	}
 
	while(a%b)
	{
		temp = a;
		a = b;
		b = temp%b;
	}
 
	return b;
}
 
 
ll pow_ar[max_power];
/* This function generates the first p powers of a number n. */
void generate_power(ll n, ll p)
{
	pow_ar[0] = 1;
	for(ll i=1; i<p; i++)
		pow_ar[i] = pow_ar[i-1]*n;
}


vector <ll> primes;
/*ll sieve[max_sieve_size];
*/

/* This function calculates primes upto the given max_sieve_size. */
void calc_sieve()
{
	for(ll i=0; i<max_sieve_size; i++)
		sieve[i] = 0;

	sieve[0] = sieve[1] = -1;

	for(ll i=2; i<max_sieve_size; i++)
	{
		if(sieve[i]==0)
		{
			primes.pb(i);
			for(ll j=i; j<max_sieve_size; j=j+i)
			{
				sieve[j]++;
			}
		}
	}
}

int main()
{
	return 0;
}
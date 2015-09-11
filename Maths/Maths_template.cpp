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

/* Maths definitions */
#define max_sieve_size 105
#define max_log 17
 
#define MOD 1000000007L
 
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
 

/* This function returns nCk mod prime. */
ll get_nCr(ll n, ll k, ll mod)
{
	return mod_divison(fact[n], (fact[k]*fact[n-k])%mod, mod);
}

ll get_mulmod_constant(ll a, ll b, ll mod) {
	double c = a;
    c*=b;
    c/=k;
    
    ll x = c;
    
    ll ans = a*b;
    ans -= (x*k);
    ans%=k;
    
    if(ans<0)
    	ans+=k;
    
    return ans;
}


ll get_mulmod_log(ll a, ll b, ll mod) {
	ll ret = 0;
    while(b) {
        if(b&1) {
            ret += a;
            ret %= k;
        }
          
        a *= 2;
        a %= k;
        b /= 2;
    }

    return ret;
}


/*
 * This function generates factorials given a mod.
 */
void generate_factorials(ll n){
	fact[0] = fact[1] = 1;

	rep(i,2,n){
		fact[i] = (fact[i-1]*i)%MOD;
	}
}

 
/* This function returns the gcd of second_dp long long numbers. */
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
 
 
/* This function generates the first p powers of a number n. */
void generate_power(ll n, ll p)
{
	pow_ar[0] = 1;
	for(ll i=1; i<p; i++)
		pow_ar[i] = pow_ar[i-1]*n;
}
 
 
/* This function calculates primes upto the given max_sieve_size. */
int sieve[max_sieve_size];
vector <int> primes;
void calc_sieve()
{
	for(int i=0; i<max_sieve_size; i++)
		sieve[i] = 0;
 
	sieve[0] = sieve[1] = -1;
 
	for(int i=2; i<max_sieve_size; i++)
	{
		if(sieve[i]==0)
		{
			primes.pb(i);
			for(int j=i; j<max_sieve_size; j=j+i)
			{
				sieve[j]++;
			}
		}
	}
}
 
 
/*This function generates the pascal's triangle. */
ll pascal_triangle[max_size][max_size];
void generate_pascal_triangle(ll n)
{
	pascal_triangle[0][0] = 1;
	for(int i=1; i<=n; i++)
	{
		pascal_triangle[i][0] = 1;
		for(int j=1; j<i; j++)
			pascal_triangle[i][j] = (pascal_triangle[i-1][j-1]+pascal_triangle[i-1][j])%MOD;
 
		pascal_triangle[i][i] = 1;
	}
}


/* 
 * This function returns the euler's totient function phi(n).
 * phi(n) = number of positive integers<n such that gcd(n, a) = 1.
 * 1. If m and n are coprime, phi(mn) = phi(m)*phi(n)
 * 2. phi(p) = p-1, if p is prime.
 * 3. phi(n) = n*(1 - (1/p1))*..(1 - (1/pk)) where p1,..pk are prime factors of n.
 * 4. if a and m are coprime, a^(phi(m)) = 1 (mod m), a^(phi(m)-1) = a^(-1) (mod m)
 */
int phi(int n)
{
	int ret = n;
	for(int i=2; i*i<=n; i++)
	{
		if(n%i==0)
		{
			ret -= ret/i;
			while(n%i==0)
				n /= i;
		}
	}

	if(n>1)
		ret -= ret/n;

	return ret;
}


/*
 * Miller Rabin primality testing.
 * @param iterations: number of iterations.
 */
bool is_prime_miller(ll prime, int iterations)
{
	if(prime<2)
		return false;

	if(p==2 || p==3 || p==5)
		return true;

	if(p%2==0)
		return false;


	ll s = p-1;
	while(s%2==0)
		s /= 2;

	for(int i=0; i<iterations, i++)
	{
		ll a = rand()%(prime-1)+1;
		ll temp = s;

		ll m = mod_pow(a, temp, prime);
		while(temp!=prime-1 && m!=1 && m!=prime-1)
		{
			m = (m%prime)*(m%prime)%prime;
			temp *= 2;
		}

		if(m!=prime-1 && temp%2==0)
			return false;
	}

	return true;
}
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

class RabinKarp
{
	public:
		/*
		 * Use these primes in case primes not given, prime1 = 9999991, prime2 = 1000000007 
		 */
		ll prime1, prime2;
		ll alphabet_size;
		pll pre[max_size], suf[max_size], mul[max_size];

		void init(ll i, ll j, ll k)
		{
			prime1 = i;
			prime2 = j;
			alphabet_size = k;
		}

		void init(ll k)
		{
			alphabet_size = k;
			prime1 = 9999991;
			prime2 = 1000000007;
		}

		void generate_prefix_hash(string word)
		{
			pre[0] = make_pair(0, 0);
			mul[0] = make_pair(1, 1);

			for(ll i=1; i<=word.length(); i++)
			{
				pre[i].f = ((pre[i-1].f*alphabet_size)%prime1 + word[i-1])%prime1;
				pre[i].s = ((pre[i-1].s*alphabet_size)%prime2 + word[i-1])%prime2;

				mul[i].f = (mul[i-1].f*alphabet_size)%prime1;
				mul[i].s = (mul[i-1].s*alphabet_size)%prime2;
			}
		}


		void generate_suffix_hash(string word)
		{
			suf[word.length()+1] = make_pair(0, 0);
			for(ll i=word.length(); i>0; i--)
			{
				suf[i].f = ((suf[i+1].f*alphabet_size)%prime1 + (word[i-1]))%prime1;
				suf[i].s = ((suf[i+1].s*alphabet_size)%prime2 + (word[i-1]))%prime2;
			}	
		}


		pll get_hash(ll i, ll j)
		{
			ll hash1 = ((pre[j].f - pre[i-1].f*mul[j-i+1].f)%prime1+prime1)%prime1;
			ll hash2 = ((pre[j].s - pre[i-1].s*mul[j-i+1].s)%prime2+prime2)%prime2;

			return make_pair(hash1, hash2);
		}

		vl search(string text, string pattern)
		{
			vl ret;

			ll pattern_hash1=0, pattern_hash2=0;
			ll text_hash1=0, text_hash2=0;
			ll mul1=1, mul2=1;

			for(ll i=0; i<pattern.length(); i++)
			{
				pattern_hash1 = ((pattern_hash1*alphabet_size)%prime1 + pattern[i])%prime1;
				pattern_hash2 = ((pattern_hash2*alphabet_size)%prime2 + pattern[i])%prime2;

				text_hash1 = ((text_hash1*alphabet_size)%prime1 + text[i])%prime1;
				text_hash2 = ((text_hash2*alphabet_size)%prime2 + text[i])%prime2;

				mul1 = (mul1*alphabet_size)%prime1;
				mul2 = (mul2*alphabet_size)%prime2;
			}

			mul1 = mod_divison(mul1, alphabet_size, prime1);
			mul2 = mod_divison(mul2, alphabet_size, prime2);

			if(pattern_hash1==text_hash1 && pattern_hash2==text_hash2)
				ret.pb(0);

			for(ll i=pattern.length(); i<text.size(); i++)
			{
				text_hash1 = (text_hash1 - (text[i-pattern.length()]*mul1)%prime1 + prime1)%prime1;
				text_hash1 = (text_hash1*alphabet_size)%prime1;
				text_hash1 = (text_hash1 + text[i])%prime1;

				text_hash2 = (text_hash2 - (text[i-pattern.length()]*mul2)%prime2 + prime2)%prime2;
				text_hash2 = (text_hash2*alphabet_size)%prime2;
				text_hash2 = (text_hash2 + text[i])%prime2;

				if(pattern_hash1==text_hash1 && pattern_hash2==text_hash2)
					ret.pb(i-pattern.length()+1);
			}

			return ret;
		}
}rabin_karp;

int main()
{
	rabin_karp.init(101, 41, 26);
	vl ret = rabin_karp.search("GEEKS FOR GEEKS", "GEEK");
	for(ll i=0; i<ret.size(); i++)
		cout<<ret[i]<<" ";
	return 0;
}
/*
 * Auhtor: Adarsh Pugalia
 * Algorithm: Suffix Array construction in O(n*log^2(n))
 *			  LCP calculation for suffixes in O(log(n))
 * Implementation Credits: http://web.stanford.edu/class/cs97si/suffix-array.pdf
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
 
#define max_size 1005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_sieve_size 5000003
#define max_log 17
 
#define MOD 100000000
 
using namespace std;

/* This is the comparator function for sorting suffixes. */
bool comp(pair<ll, pair<ll, ll> > i, pair<ll, pair<ll, ll> > j)
{
	if(i.s.f==j.s.f)
		return i.s.s<j.s.s;

	return i.s.f<j.s.f;
}

class SuffixArrays
{
	public:
		/*
		 * word stores the word for suffix array construction.
		 * step keeps count of the number of sorting steps needed.
		 * suf_ar[i][j] stores the sorted index of suffix at index j in step i.
		 */ 
		string word;
		ll step, cnt;
		ll suf_ar[max_log][max_size];
		pair<ll, pair<ll, ll> > sorted_sufs[max_size];

		/*
		 * This function does the suffix array construction.
		 * @param string: word for construction
		 * @return void.
		 * O(nlog2(n))
		 */
		void init(string w)
		{
			word = w;
			for(ll i=0; i<w.length(); i++)
				suf_ar[0][i] = w[i]-'a';

			for(step=1, cnt=1; cnt >> 1<w.length(); step++, cnt <<= 1)
			{
				for(ll i=0; i<w.length(); i++)
				{
					sorted_sufs[i].s.f = suf_ar[step-1][i];
					sorted_sufs[i].s.s = (i+cnt<w.length())?suf_ar[step-1][i+cnt]:-1;
					sorted_sufs[i].f = i;
				}

				sort(sorted_sufs, sorted_sufs+w.length(), comp);

				for(ll i=0; i<w.length(); i++)
				{
					if(i>0 && sorted_sufs[i].s.f==sorted_sufs[i-1].s.f && sorted_sufs[i].s.s==sorted_sufs[i-1].s.s)
						suf_ar[step][sorted_sufs[i].f] = suf_ar[step][sorted_sufs[i-1].f];
					else
						suf_ar[step][sorted_sufs[i].f] = i;
				}
			}
		}


		/* This function prints the sorted suffixes. */
		void print_suffixes()
		{
			for(ll i=0; i<word.length(); i++)
			{
				for(ll j=sorted_sufs[i].f; j<word.length(); j++)
					cout<<word[j];
				cout<<endl;
			}
		}

		/* This function returns the longest common prefix for suffixes at index x and y. */
		ll lcp(ll x, ll y)
		{
			if(x==y)
				return word.length()-x;

			ll ret = 0;

			for(ll k=step-1; k>=0 && x<word.length() && y<word.length(); k--)
				if(suf_ar[k][x]==suf_ar[k][y])
					x += 1<<k, y += 1<<k, ret += 1<<k;

			return ret;
		}
}suffix_array;

int main()
{
	suffix_array.init("alabalaalabala");
	suffix_array.print_suffixes();
	return 0;
}
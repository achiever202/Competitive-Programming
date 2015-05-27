/*
 * Auhtor: Adarsh Pugalia
 * Algorithm: Manacher's algorithm for Longest Palindromic Substring in O(n)
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

class Manacher
{
	public:
		string word;
		ll centre, right_bound, len;
		ll palin_ar[2*max_size];

		void init(string w)
		{
			word = "^";

			for(ll i=0; i<w.length(); i++)
				word += "#" + w.substr(i, 1);

			word += "#$";

			right_bound = 0, centre = 0;
			len = word.length();
		}

		ll get_longest_palindrome()
		{
			for(ll i=0; i<len; i++)
			{
				ll mirror = 2*centre - i;
				palin_ar[i] = (right_bound>i)?(min(palin_ar[mirror], right_bound-i)):0;

				while(word[i+palin_ar[i]+1]==word[i-palin_ar[i]-1])
					palin_ar[i]++;

				if(i+palin_ar[i]>right_bound)
				{
					centre = i;
					right_bound = i+palin_ar[i];
				}
			}

			ll ret = palin_ar[0];
			for(ll i=1; i<len; i++)
				ret = max(ret, palin_ar[i]);

			return ret;
		}

		void print_longest_palindrome()
		{
			ll max_len = palin_ar[0];
			ll centre_index = 0;

			for(ll i=1; i<len; i++)
				if(max_len<palin_ar[i])
					max_len = palin_ar[i], centre_index = i;

			for(ll i=centre_index-palin_ar[centre_index]; i<=centre_index+palin_ar[centre_index]; i++)
				if(word[i]!='#')
					cout<<word[i];

			cout<<endl;
		}
}manacher;

int main()
{
	manacher.init("babcbabcbaccba");
	cout<<manacher.get_longest_palindrome()<<endl;
	manacher.print_longest_palindrome();
	return 0;
}


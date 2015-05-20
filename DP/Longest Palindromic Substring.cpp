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
 
#define max_size 105
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
 
#define MOD 1000000007
 
using namespace std;

class LongestPalindromicSubstring
{
	public:
		string word;
		ll len;
		ll dp[max_size];

		void init(string w)
		{
			word = w;
			len = word.length();
		}

		ll calc_lps()
		{
			for(ll i=0; i<len; i++)
			{
				dp[i] = 1;
				for(ll j=0; j<i; j++)
				{
					if(j==i-1)
					{
						if(word[i]==word[j])
							dp[i] = max(dp[i], (ll)2);
					}
					else if(word[i]==word[j] && dp[i-1]==i-j-1)
						dp[i] = max(dp[i], i-j+1);
				}
			}

			ll ret = dp[0];
			for(ll i=1; i<len; i++)
				ret = max(ret, dp[i]);

			return ret;
		}
}longest_palindromic_subsequence;

int main()
{
	string w = "forgeeksskeegfor";
	longest_palindromic_subsequence.init(w);
	cout<<longest_palindromic_subsequence.calc_lps();
	return 0;
}
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

class PalindromePartitioning
{
	public:
		string word;
		ll len;
		ll dp[max_size][max_size];

		void init(string w)
		{
			word = w;
			len = w.length();
		}

		ll get_palindrome_partitioning()
		{
			for(ll i=0; i<len; i++)
				dp[i][i] = 0;

			for(ll i=len-1; i>=0; i--)
			{
				for(ll j=i+1; j<len; j++)
				{
					dp[i][j] = dp[i][i]+dp[i+1][j]+1;
					for(ll k=i+1; k<j; k++)
						dp[i][j] = min(dp[i][j], dp[i][k]+dp[k+1][j]+1);

					if(word[i]==word[j] && j-i==1)
						dp[i][j] = 0;
					else if(word[i]==word[j] && dp[i+1][j-1]==0)
						dp[i][j] = 0;
				}
			}

			return dp[0][len-1];
		}
}palindrome_partitioning;

int main()
{
	palindrome_partitioning.init("ababbbabbababa");
	cout<<palindrome_partitioning.get_palindrome_partitioning()<<endl;
	return 0;
}
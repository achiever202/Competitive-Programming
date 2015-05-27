/*
 * Author: Adarsh Pugalia
 * Algorithm: Longest Bracket Substring in O(n)
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
 
#define max_size 1000005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_sieve_size 105
 
#define MOD 1000000007
 
using namespace std;

/*
 * brackets stores the indices of starting brackets.
 * word is the input bracket sequence.
 * ar[i] stores the length of the longest regular bracket sequence ending at i.
 */
stack <ll> brackets;
string word;
ll ar[max_size];

int main()
{
	cin>>word;

	for(ll i=0; i<word.length(); i++)
	{
		if(word[i]=='(')
		{
			brackets.push(i);
			ar[i] = 0;
		}
		else
		{
			if(brackets.size()==0)
			{
				ar[i] = 0;
			}
			else
			{
				ar[i] = i-brackets.top()+1;
				ll cur = i-ar[i], flag=1;
				while(cur>0 && flag && ar[cur]>0)
				{
					ar[i] += ar[cur];
					cur -= ar[cur];

					if(cur==0)
						flag = 0;
				}
				
				brackets.pop();

			}
		}
	}

	/*
	 * maxi stores the length of the longest regular substring.
	 * count stores the number of such substrings.
	 */
	ll maxi = ar[0], count = 1;
	for(ll i=1; i<word.length(); i++)
	{
		if(ar[i]==maxi)
		{
			count++;
		}
		else if(ar[i]>maxi)
		{
			maxi = ar[i];
			count = 1;
		}
	}

	if(maxi>0)
		cout<<maxi<<" "<<count<<endl;
	else
		cout<<"0 1";

	return 0;
}
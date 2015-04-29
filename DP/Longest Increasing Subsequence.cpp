/*
 * Author: Adarsh Pugalia
 * Algorithm: Longest Increasing Subsequence using dynamic programming.
 * Space Complexity: O(n)
 * Time Complexity: O(n^2)
 *
 * The input array is stored in ar[].
 * The function longest_increasing_subsequence computes the longest increasing subsequence of the given array.
 * vector lis stores the longest increasing subsequence obtained in reverse order.
 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <set>

#define ll long long int
#define vi vector <int>
#define vl vector <ll>
#define vpii vector <pair<int, int> >
#define vpll vector <pair<ll, ll> >

#define f first
#define s second

#define sd(n) scanf("%d", &n)
#define sl(n) scanf("%lld", &n)

#define pb push_back
#define pob pop_back

#define max_size 100005

using namespace std;

/* The input array. */
ll ar[max_size];

/* 
 * dp[i].first stores the longest increasing subsequence ending at index i.
 * dp[i].second stores the predecessor of longest increasing subsequence ending at index i.
 * lis stores the longest increasing subsequence in reverse order.
 */
pair<ll, ll> dp[max_size];
vector <ll> lis;


/* 
 * This function computes the longest increasing subsequence.
 * @param ar[]: the input array.
 * @param n: the size of array.
 * @return ret: the value of longest increasing subsequence.
 */
ll  longest_increasing_subsequence(ll ar[], ll n)
{
	ll ret = 1;

	for(ll i=0; i<n; i++)
	{
		dp[i].f = 1;
		dp[i].s = -1;
	}

	for(ll i=1; i<n; i++)
	{
		for(ll j=i-1; j>=0; j--)
		{
			if(ar[j]<ar[i] && dp[i].f<dp[j].f+1)
			{
				dp[i].f = dp[j].f+1;
				dp[i].s = j;
			}
		}
	}

	for(ll i=0; i<n; i++)
		ret = max(ret, dp[i].f);

	for(ll i=0; i<n; i++)
	{
		if(dp[i].f==ret)
		{
			while(i!=-1)
			{
				lis.pb(ar[i]);
				i = dp[i].s;
			}
			break;
		}
	}

	return ret;
}

int main()
{
	ll n;
	cin>>n;

	for(ll i=0; i<n; i++)
		cin>>ar[i];

	cout<<longest_increasing_subsequence(ar, n)<<endl;
	for(ll i=lis.size()-1; i>=0; i--)
		cout<<lis[i]<<" ";
	cout<<endl;
}
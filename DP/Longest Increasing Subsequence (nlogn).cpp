/*
 * Author: Adarsh Pugalia
 * Algorithm: Longest Increasing Subsequence using dynamic programming.
 * Space Complexity: O(n)
 * Time Complexity: O(nlog(n))
 * Hint link: http://en.wikipedia.org/wiki/Longest_increasing_subsequence#Efficient_algorithms
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

class LongestIncreasingSubsequence
{
	public:
		/* The input array. */
		ll ar[max_size];
		ll n;
		/* 
		 * lis_length[i] stores the index of the element with the smalles value for a subsequence of length i.
		 * predecessor[i] stores the predecessor of the element at index i in the lis ending at i.
		 * lis stores the longest increasing subsequence in reverse order.
		 */
		vl lis_length;
		ll predecessor[max_size];
		vl lis;

		void init()
		{
			cin>>n;
			for(ll i=0; i<n; i++)
				cin>>ar[i];
		}

		/* This function finds the largest index such that ar[lis_length[index]]<ar[cur]. */
		ll find_index(ll cur, ll start, ll end)
		{
			if(end-start<=1)
			{
				if(ar[lis_length[end]]<ar[cur])
					return end;

				if(ar[lis_length[start]]<ar[cur])
					return start;

				return -1;
			}

			ll mid = (start+end)/2;

			if(ar[lis_length[mid+1]]<ar[cur])
				return find_index(cur, mid+1, end);

			return find_index(cur, start, mid);
		}

		/* 
		 * This function computes the longest increasing subsequence.
		 * @param ar[]: the input array.
		 * @param n: the size of array.
		 * @return: the value of longest increasing subsequence.
		 */
		ll  get_lis()
		{
			lis_length.push_back(0);
			predecessor[0] = -1;

			for(ll i=1; i<n; i++)
			{
				ll index = find_index(i, 0, lis_length.size()-1);

				if(index==-1)
				{
					lis_length[0] = i;
					predecessor[i] = -1;
				}
				else if(index==lis_length.size()-1)
				{
					lis_length.push_back(i);
					predecessor[i] = lis_length[index];
				}
				else
				{
					lis_length[index+1] = i;
					predecessor[i] = lis_length[index];
				}
			}

			ll cur = lis_length[lis_length.size()-1];
			while(cur!=-1)
			{
				lis.push_back(ar[cur]);
				cur = predecessor[cur];
			}

			return lis_length.size();
		}
}longest_increasing_subsequence;

int main()
{
	longest_increasing_subsequence.init();
	cout<<longest_increasing_subsequence.get_lis();
	return 0;
}
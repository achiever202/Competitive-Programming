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
 
#define MOD 100000000
 
using namespace std;

class KMP
{
	public:
		string word;
		ll len;
		ll failure_function[max_size];

		void init(string w)
		{
			word = w;
			len = w.length();

			failure_function[0] = 0;
			ll pos = 1, next = 0;
			while(pos<len)
			{
				if(word[pos]==word[next])
				{
					next++;
					failure_function[pos] = next;
					pos++;
				}
				else if(next>0)
				{
					next = failure_function[next-1];
				}
				else
				{
					failure_function[pos] = 0;
					pos++;
				}
			}
		}

		vl search(string w, ll start)
		{
			vector <ll> ret;

			ll i=start, j=0, temp_len = w.length();
			while(i<temp_len)
			{
				if(w[i]==word[j])
				{
					i++;
					j++;

					if(j==len)
					{
						ret.pb(i-j);
						j = failure_function[j-1];
					}
				}
				else
				{
					if(j>0)
						j = failure_function[j-1];
					else
						i++;
				}			
			}

			return ret;
		}

		void print_failure_function()
		{
			for(ll i=0; i<len; i++)
				cout<<failure_function[i]<<" ";
			cout<<endl;
		}
}kmp;

int main()
{
		
	return 0;
}
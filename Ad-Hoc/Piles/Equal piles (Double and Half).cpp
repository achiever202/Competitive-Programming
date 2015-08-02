/* 
 * Author: Adarsh Pugalia
 * Problem: http://codeforces.com/contest/558/problem/C
 *			Given n piles, make the piles equal by doubling or halfing the piles.
 *			Find the minimum number of operations required.
 *
 * Editorial: http://codeforces.com/blog/entry/19212
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
 
#define max_size 100005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_sieve_size 105
#define max_log 17
 
using namespace std;
 
/* Template ends here. */
ll ar[max_size], vis[max_size];

pair<ll,ll> ans[max_size];

void bfs(ll value, ll max){
	vector <ll> elements;

	vis[value] = 1;
	elements.push_back(value);
	queue<pair<ll, ll> > bfs;
	bfs.push(make_pair(value, 0));
	while(!bfs.empty()){
		pair<ll, ll> cur = bfs.front();
		bfs.pop();

		ans[cur.f].f++;
		ans[cur.f].s += cur.s;

		if(cur.f*2<=max && !vis[cur.f*2]){
			vis[cur.f*2] = 1;
			elements.push_back(cur.f*2);
			bfs.push(make_pair(cur.f*2, cur.s+1));
		}

		if((cur.f/2)>=1 && !vis[cur.f/2]){
			vis[cur.f/2] = 1;
			elements.push_back(cur.f/2);
			bfs.push(make_pair(cur.f/2, cur.s+1));
		}
	}

	rep(i,0,elements.size()-1){
		vis[elements[i]] = 0;
	}
}

int main(){
	ll n, max=0;
	sl(n);

	rep(i,1,n){
		sl(ar[i-1]);
		if(max<ar[i-1])
			max = ar[i-1];
	}

	rep(i,1,max){
		ans[i].f = 0;
		ans[i].s = 0;
	}

	rep(i,0,n-1){
		bfs(ar[i], max);
	}

	ll min = -1;
	rep(i,1,max){
		if(ans[i].f==n && (min==-1 || ans[i].s<min))
			min = ans[i].s;
	}

	cout<<min<<endl;
	return 0;
}
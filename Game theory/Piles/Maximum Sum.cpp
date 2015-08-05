/*
 * Author: Adarsh Pugalia
 * Problem: Given n piles, with numbers on cards in each piles, one draws from
 *			the top and the other from bottom. Maximize each players sum.
 *			http://codeforces.com/contest/388/problem/C
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
#define mp make_pair
 
#define max_size 100005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_sieve_size 105
#define max_log 17
#define MOD 1000000007L
 
using namespace std;

vector <ll> elements;

int main(){
	ll n, first = 0, second = 0;
	cin>>n;
	while(n--){
		ll m;
		cin>>m;
		rep(i,1,m/2){
			ll a;
			cin>>a;
			first += a;
		}

		if(m&1){
			ll a;
			cin>>a;
			elements.pb(a);
		}

		rep(i,1,m/2){
			ll a;
			cin>>a;
			second += a;
		}
	}

	sort(elements.begin(), elements.end());
	ll turn = 1;
	repd(i,(ll)elements.size()-1,0){
		if(turn)
			first += elements[i];
		else
			second += elements[i];

		turn = turn^1;
	}

	cout<<first<<" "<<second<<endl;
	return 0;
}
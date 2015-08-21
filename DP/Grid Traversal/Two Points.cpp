/*
 * Author: Adarsh Pugalia
 * Algorithm: Grid traversal with two points (go from start to a mid point and then to an end point)
 * Problem: https://www.hackerrank.com/contests/101hack28/challenges/grid-maze
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
 
#define ll int
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
 
#define max_size 1005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_sieve_size 1300005
#define max_log 17
#define MOD 1000000007L
#define INF 1000000
 
using namespace std;
int dis[3][max_size][max_size];
char board[max_size][max_size];
int vis[max_size][max_size];
int n, m;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

class Comparator {
	public:
		bool operator()(const pair<int, pii >& i, const pair<int, pii > &j)
		{
			return i.f>j.f;
		}
};

void dijkstra(int x, int y, int index) {
	rep(i,0,n-1){
		rep(j,0,m-1){
			dis[index][i][j] = INF;
			vis[i][j] = 0;
		}
	}

	priority_queue<pair<int, pii >, vector<pair<int, pii > >, Comparator> q;
	if(index==0 || index==1) {
		q.push(mp(0, mp(x,y)));
	}
	else {
		rep(j,0,m-1){
			if(board[0][j]=='#')
				q.push(mp(1, mp(0,j)));
			else
				q.push(mp(0, mp(0,j)));

			if(board[n-1][j]=='#')
				q.push(mp(1, mp(n-1, j)));
			else
				q.push(mp(0, mp(n-1, j)));
		}

		rep(i,0,n-1){
			if(board[i][0]=='#')
				q.push(mp(1, mp(i,0)));
			else
				q.push(mp(0, mp(i,0)));

			if(board[i][m-1]=='#')
				q.push(mp(1, mp(i,m-1)));
			else
				q.push(mp(0, mp(i,m-1)));
		}
	}

	while(!q.empty()) {
		pair<int, pii > cur = q.top();
		q.pop();

		if(vis[cur.s.f][cur.s.s])
			continue;

		dis[index][cur.s.f][cur.s.s] = cur.f;
		vis[cur.s.f][cur.s.s] = 1;
		rep(i,0,3){
			if(cur.s.f+dx[i]>=0 && cur.s.f+dx[i]<n && cur.s.s+dy[i]>=0 && cur.s.s+dy[i]<m){
				int temp_cost = 0;
				if(board[cur.s.f+dx[i]][cur.s.s+dy[i]]=='#')
					temp_cost = 1;

				if(dis[index][cur.s.f+dx[i]][cur.s.s+dy[i]]>dis[index][cur.s.f][cur.s.s]+temp_cost){
					dis[index][cur.s.f+dx[i]][cur.s.s+dy[i]] = dis[index][cur.s.f][cur.s.s]+temp_cost;
					q.push(mp(dis[index][cur.s.f][cur.s.s]+temp_cost, mp(cur.s.f+dx[i], cur.s.s+dy[i])));
				}
			}
		}
	}
}

int main(){
  	sd(n), sd(m);

	rep(i,0,n-1){
		scanf("%s", board[i]);
  	}

  	rep(i,0,n-1){
  		rep(j,0,m-1){
  			if(board[i][j]=='S')
  				dijkstra(i,j,0);

 	 		if(board[i][j]=='P')
  				dijkstra(i,j,1);
  		}
  	}

  	dijkstra(-1,-1,2);

 	int ans = INF;
    rep(i,0,n-1){
  		rep(j,0,m-1){
  			int cost = dis[0][i][j] + dis[1][i][j] + dis[2][i][j];
  			if(board[i][j]=='#')
  				cost -= 2;

	  		ans = min(ans, cost);
  		}

  	}

  	cout<<ans<<endl;
 	return 0; 
}
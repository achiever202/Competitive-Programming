/* Code courtesy: http://stanford.edu/~liszt90/acm/notebook.html#file2 */

// Implementation of min cost max flow algorithm using adjacency
// matrix (Edmonds and Karp 1972).  This implementation keeps track of
// forward and reverse edges separately (so you can set cap[i][j] !=
// cap[j][i]).  For a regular max flow, set all edge costs to 0.
//
// Running time, O(|V|^2) cost per augmentation
//     max flow:           O(|V|^3) augmentations
//     min cost max flow:  O(|V|^4 * MAX_EDGE_COST) augmentations
//     
// INPUT: 
//     - graph, constructed using AddEdge()
//     - source
//     - sink
//
// OUTPUT:
//     - (maximum flow value, minimum cost value)
//     - To obtain the actual flow, look at positive values only.

#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <limits>
#include <queue>

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

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef int L;
typedef vector<L> VL;
typedef vector<VL> VVL;
typedef pair<int, int> PII;
typedef vector<PII> VPII;

const L INF = numeric_limits<L>::max() / 4;

struct MinCostMaxFlow {
  int N;
  VVL cap, flow, cost, edges;
  VI found;
  VL dist, pi, width, parent;
  VPII dad;

   MinCostMaxFlow(int N) : 
     N(N), cap(N, VL(N)), flow(N, VL(N)), cost(N, VL(N)), 
     found(N), dist(N), pi(N), width(N), dad(N), vis(N), edges(N), parent(N) {}    
  
  void AddEdge(int from, int to, L cap, L cost) {
    this->cap[from][to] = cap;
    this->cost[from][to] = cost;
  }

  void AddEdgeList(int from, int to, L cap, L cost) {
    edges[from].pb(to);
    this->cap[from][to] = cap;
    this->cost[from][to] = cost;
  }
  
  void Relax(int s, int k, L cap, L cost, int dir) {
    L val = dist[s] + pi[s] - pi[k] + cost;
    if (cap && val < dist[k]) {
      dist[k] = val;
      dad[k] = make_pair(s, dir);
      width[k] = min(cap, width[s]);
    }
  }

  L Dijkstra(int s, int t) {
    fill(found.begin(), found.end(), false);
    fill(dist.begin(), dist.end(), INF);
    fill(width.begin(), width.end(), 0);
    dist[s] = 0;
    width[s] = INF;
    
    while (s != -1) {
      int best = -1;
      found[s] = true;
      for (int k = 0; k < N; k++) {
        if (found[k]) continue;
        Relax(s, k, cap[s][k] - flow[s][k], cost[s][k], 1);
        Relax(s, k, flow[k][s], -cost[k][s], -1);
        if (best == -1 || dist[k] < dist[best]) best = k;
      }
      s = best;
    }

    for (int k = 0; k < N; k++)
      pi[k] = min(pi[k] + dist[k], INF);
    return width[t];
  }

  L SPFA(int s, int t) {

    rep(i,0,N-1) {
      found[i] = width[i] = 0;
      dist[i] = INF;
    }

    dist[s] = 0;
    width[s] = INF;

    queue<int> q;
    q.push(s);

    while(!q.empty()) {
      int cur = q.front(); q.pop();
      found[cur] = false;

      for(int j=0; j<edges[cur].size(); j++) {
        int i = edges[cur][j];
        ll temp = dist[i];
        if(flow[cur][i]<cap[cur][i] && dist[i]>dist[cur]+cost[cur][i]) {
          dist[i] = dist[cur] + cost[cur][i];
          parent[i] = cur;
          width[i] = min(width[cur], cap[cur][i]-flow[cur][i]);

          if(!found[i]) {
            found[i] = true;
            q.push(i);
          }
        }
      }
    }

    return width[t];
  }

  pair<L,L> GetMaxFlowWithNegativeEdges(int s, int t) {
    L totflow = 0, totcost = 0;

    while (L amt = SPFA(s, t)) {
      totflow += amt;

      for (int x = t; x != s; x = parent[x]) {
        flow[parent[x]][x] += amt;
        flow[x][parent[x]] -= amt;
        totcost += amt * cost[parent[x]][x];
      }
    }
    return make_pair(totflow, totcost);
  }

  pair<L, L> GetMaxFlow(int s, int t) {
    L totflow = 0, totcost = 0;
    while (L amt = Dijkstra(s, t)) {
      totflow += amt;

      for (int x = t; x != s; x = dad[x].first) {
        if (dad[x].second == 1) {
          flow[dad[x].first][x] += amt;
          totcost += amt * cost[dad[x].first][x];
        } 
        else {
          flow[x][dad[x].first] -= amt;
          totcost -= amt * cost[x][dad[x].first];
        }
      }

    }

    return make_pair(totflow, totcost);
  }
};
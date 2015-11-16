/*
 * Author: Adarsh Pugalia
 * Algorithm: Longest Common Subsequences of K sequences.
 * Complexity: O(n^2*k)
 * Problem Link: http://codeforces.com/contest/463/problem/D
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
#include <limits>
#include <cassert>
 
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
#define slf(n) scanf("%lf", &n)

#define pd(n) printf("%d", n);
#define pl(n) printf("%lld", n);
#define ps printf(" ")
#define pe printf("\n")

#define rep(i,j,k) for(int i=j; i<=k; i++)
#define repd(i,j,k) for(int i=j; i>=k; i--)

#define sz(n) (int)n.size()-1 
#define pb push_back
#define pob pop_back
#define mp make_pair
 
#define max_size 1005
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_log 17
#define max_sieve_size 1005

#define INF 100000000000L
#define MOD 1000000007
 
using namespace std;

int ans[max_size];

class Node {
    public:
        int index;
        int parent;
        vector<pair<int, ll> >edges;
};


class Tree {
    public:
        Node nodes[max_size];
        int node_size, visited[max_size];

        void init(int sz) {
            node_size = sz;

            rep(i,1,sz) {
                nodes[i].index = i;
                nodes[i].parent = -1;
                nodes[i].edges.clear();
                visited[i] = 0;
            }
        }

        void add_edge(int i, int j, ll cost) {
            nodes[i].edges.pb(mp(j,cost));
        }


        void add_edge(int i, int j) {
            add_edge(i,j,1);
        }


        pii get_edge(int node, int index) {
            return nodes[node].edges[index];
        }


        pair<int, int> get_diameter(int node, int parent) {
            nodes[node].parent = parent;

            pair<int, int> ret;
            ret.f = ret.s = 0;

            rep(i,0,sz(nodes[node].edges)) {
                if(nodes[node].edges[i].f!=parent) {
                    pair<int, int> temp = get_diameter(nodes[node].edges[i].f, node);
                    ret.f = max(ret.f, max(temp.f, ret.s+temp.s+1));
                    ret.s = max(ret.s, temp.s+1);
                }
            }

            return ret;
        }


        void dfs(int node, int parent) {
           visited[node] = 1;

           rep(i,0,sz(nodes[node].edges)) {
                int next_node = get_edge(node, i).f;
                if(!visited[next_node])
                    dfs(next_node, node);

                ans[node] = max(ans[node], ans[next_node]);
           }

            ans[node]++;              
        }
}tree;

int pos[max_size][6];

int main() {
    int n, k;
    sd(n); sd(k);

    tree.init(n);

    rep(i,1,k) {
        rep(j,1,n) {
            int a;
            sd(a);

            pos[a][i] = j;
        }
    }

    rep(i,1,n) {
        rep(j,1,n) {
            if(i!=j) {
                int flag = 1;
                rep(l,1,k) {
                    if(pos[i][l]>pos[j][l]) {
                        flag = 0;
                        break;
                    }
                }

                if(flag) {
                    tree.add_edge(i,j);
                }
            }
        }
    }

    rep(i,1,n) {
        if(!tree.visited[i])
            tree.dfs(i, -1);
    }

    int temp = ans[1];
    rep(i,2,n)
        temp = max(ans[i], temp);

    cout<<temp<<endl;
    return 0;
}

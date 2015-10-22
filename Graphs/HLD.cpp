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
#include <string.h>
 
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
#define all(n) n.begin(), n.end()
 
#define pb push_back
#define pob pop_back
#define mp make_pair
 
#define max_size 10005
#define max_sieve_size 100005
#define max_log 17
 
#define INF 1000000000
#define MOD 1000000007
 
#define mod(a) ((a)%MOD)
 
using namespace std;

class Node {
    public:
        int index;
        int parent;
        int subtree_size;
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
                nodes[i].subtree_size = 1;
            }
        }

        void add_edge(int i, int j, ll cost) {
            nodes[i].edges.pb(mp(j,cost));
            nodes[j].edges.pb(mp(i,cost));
        }


        void add_edge(int i, int j) {
            add_edge(i,j,1);
        }


        /*
         * This function removes the edge between nodes i and j.

         * NOTE: The removal changes the vector states, so do not remove
         * the edge while iterating over the vector.
         */
        void remove_edge(int a, int b) {
            ll cost;
            rep(i,0,sz(nodes[a].edges)) {
                if(nodes[a].edges[i].f==b) {
                    cost = nodes[a].edges[i].s;
                    break;
                }
            }

            nodes[a].edges.erase(remove(nodes[a].edges.begin(), nodes[a].edges.end(), mp(b,cost)), nodes[a].edges.end());
            nodes[b].edges.erase(remove(nodes[b].edges.begin(), nodes[b].edges.end(), mp(a,cost)), nodes[b].edges.end());
        }

        void dfs(int node, int parent) {
            nodes[node].parent = parent;

            rep(i,0,sz(nodes[node].edges)) {
                if(nodes[node].edges[i].f!=parent) {
                    dfs(nodes[node].edges[i].f, node);
                    nodes[node].subtree_size += nodes[nodes[node].edges[i].f].subtree_size;
                }
            }
        }
}tree;

class LCA {
    public:
        Tree tree;
        int level[max_size];
        int level_parent[max_log][max_size];
        int power2[max_log];

        LCA() {
            power2[0] = 1;
            rep(i,1,max_log-1)
                power2[i] = power2[i-1]*2;
        }

        void init(Tree t) {
            tree = t;
            preprocess_lca(1, -1, 0);
        }


        void preprocess_lca(int node, int parent, int l) {
            level[node] = l;

            level_parent[0][node] = parent;
            rep(i,1,max_log-1) {
                if(parent==-1)
                    level_parent[i][node] = parent;
                else
                    level_parent[i][node] = level_parent[i-1][level_parent[i-1][node]];
            }

            rep(i,0,sz(tree.nodes[node].edges)) {
                if(tree.nodes[node].edges[i].f!=parent)
                    preprocess_lca(tree.nodes[node].edges[i].f, node, l+1);
            }
        }


        int get_lca(int x, int y) {
            if(level[x]<level[y]) {
                int temp = x;
                x = y;
                y = temp;
            }

            repd(i,max_log-1,0) {
                if(level[x]-power2[i]>=level[y]) {
                    x = level_parent[i][x];
                }
            }

            if(x==y)
                return x;

            repd(i,max_log-1,0) {
                if(level_parent[i][x]!=level_parent[i][y]) {
                    x = level_parent[i][x];
                    y = level_parent[i][y];
                }
            }

            return level_parent[0][x];
        }


        int get_ancestor_at_level(int a, int lvl) {
            repd(i,max_log-1, 0) {
                if(level[a]-power2[i]>=lvl)
                    a = level_parent[i][a];
            }

            return a;
        }

}lca;

class SegmentTree
{
    public:
        int n;
        ll ar[max_size];
        ll seg_tree[4*max_size];

        void init(int num, ll a[])
        {
            n = num;
            rep(i,1,n)
                ar[i] = a[i];

            build_segment_tree(1, 1, n);
        }

        void build_segment_tree(int node, int start, int end)
        {
            if(start==end)
            {
                seg_tree[node] = ar[start];
                return;
            }

            int mid = (start+end)/2;
            build_segment_tree(2*node, start, mid);
            build_segment_tree(2*node+1, mid+1, end);

            seg_tree[node] = seg_tree[2*node] + seg_tree[2*node+1];
        }

        ll query(int node, int start, int end, int x, int y)
        {
            if(start==x && end==y)
            {
                return seg_tree[node];
            }

            int mid = (start+end)/2;

            if(mid>=y)
                return query(2*node, start, mid, x, y);

            if(mid+1<=x)
                return query(2*node+1, mid+1, end, x, y);

            ll left = query(2*node, start, mid, x, mid);
            ll right = query(2*node+1, mid+1, end, mid+1, y);

            /* Logic for merging left and right queries. */

            return left+right;
        }
}segment_tree;

class HLD {
    public:
        /*
         * @data tree: the tree for HLD.
         * @data chain_number: the total number of chains.
         * @data chain_head: head node for the chain at index i.
         * @data chain_length: length of the ith chain.
         * @data chain_index: the chain to which the ith node in the tree belongs.
         * @data chain_position: position of the ith node in its respective chain.
         *
         * NOTE: The tree is 1 indexed, but the chain index and the chain positions are 0 indexed.
         */
        Tree tree;
        int chain_number;
        int chain_head[max_size];
        int chain_length[max_size];
        int chain_index[max_size];
        int chain_position[max_size];

        ll base_array[max_size];
        int pos_base_array[max_size], cur_pos, node_base_array[max_size];

        void init(Tree t) {
            tree = t;

            chain_number = 0;
            cur_pos = 1;

            rep(i,0,tree.node_size) {
                chain_head[i] = -1;
                chain_length[i] = 0;
            }

            tree.dfs(1, -1);
            lca.init(tree);

            decompose_tree(1, -1, 0);
            segment_tree.init(cur_pos-1, base_array);
        }


        void decompose_tree(int node, int parent, ll cost) {
            if(chain_head[chain_number]==-1) {
                chain_head[chain_number] = node;
            }

            chain_index[node] = chain_number;
            chain_position[node] = chain_length[chain_number];
            chain_length[chain_number]++;

            base_array[cur_pos] = cost;
            pos_base_array[node] = cur_pos;
            node_base_array[cur_pos] = node;
            cur_pos++;

            int special_child = -1, special_child_subtree_size = 0;
            rep(i,0,sz(tree.nodes[node].edges)) {
                if(tree.nodes[node].edges[i].f!=parent && tree.nodes[tree.nodes[node].edges[i].f].subtree_size>special_child_subtree_size) {
                    special_child = tree.nodes[node].edges[i].f;
                    special_child_subtree_size = tree.nodes[tree.nodes[node].edges[i].f].subtree_size;
                    cost = tree.nodes[node].edges[i].s;
                }
            }

            if(special_child!=-1) {
                decompose_tree(special_child, node, cost);
            }

            rep(i,0,sz(tree.nodes[node].edges)) {
                if(tree.nodes[node].edges[i].f!=parent && tree.nodes[node].edges[i].f!=special_child) {
                    chain_number++;
                    decompose_tree(tree.nodes[node].edges[i].f, node, tree.nodes[node].edges[i].s);
                }
            }
        }

        int get_next_chain_node(int node) {
            return tree.nodes[chain_head[chain_index[node]]].parent;
        }


        int get_chain_head_base_pos(int node) {
            return pos_base_array[chain_head[chain_index[node]]];
        }


        ll query_up(int start, int end) {
            ll ret = 0;
            while(chain_index[start]!=chain_index[end]) {
                ret += segment_tree.query(1, 1, cur_pos-1, get_chain_head_base_pos(start), pos_base_array[start]);
                start = get_next_chain_node(start);
            }

            if(start!=end)
                ret += segment_tree.query(1, 1, cur_pos-1, pos_base_array[end]+1, pos_base_array[start]);

            return ret;
        }


        ll query_path(int a, int b) {
            int ancestor = lca.get_lca(a, b);

            ll ret = 0;
            ret += query_up(a, ancestor);
            ret += query_up(b, ancestor);

            return ret;
        }
}hld;

int main() {
	return 0;
}
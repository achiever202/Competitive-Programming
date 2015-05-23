/* MAXFLOW CODE CREDITS -> Home  Â» Trinity 2014 Â» Modak Automation Â» All Submissions Â» anta [3493805].
	http://www.codechef.com/viewsolution/3493805*
*/

#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <stack>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <math.h>

#define max_nodes_size 100005
#define max_log_size 17
#define ll long long int
#define mod 1000000007

#define each(it,o) for(aut(it, (o).begin()); it != (o).end(); ++ it)
#define INF 0x3f3f3f3f
#if defined(_MSC_VER) || __cplusplus > 199711L
#define aut(r,v) auto r = (v)
#else
#define aut(r,v) typeof(v) r = (v)
#endif
	
using namespace std;

struct MaximumFlow {
    typedef int Index;
	typedef int Flow;
	static const Flow InfCapacity = INF;
	struct Edge {
		Index to;
		Flow capacity;
		Index rev;
	};


	vector<vector<Edge> > g;
	

	void init(Index n) { g.assign(n, vector<Edge>()); }
	

	void add(Index i, Index j, Flow capacity) {
		Edge e, f; e.to = j, f.to = i; e.capacity = capacity, f.capacity = 0;
		g[i].push_back(e); g[j].push_back(f);
		g[i].back().rev = (Index)g[j].size() - 1; g[j].back().rev = (Index)g[i].size() - 1;
	}


	void addB(Index i, Index j, Flow capacity) {
		Edge e, f; e.to = j, f.to = i; e.capacity = capacity, f.capacity = capacity;
		g[i].push_back(e); g[j].push_back(f);
		g[i].back().rev = (Index)g[j].size() - 1; g[j].back().rev = (Index)g[i].size() - 1;
	}


	Flow maximumFlow(int s, int t) {
		int n = g.size();
		vector<Index> level(n);
		Flow total = 0; bool update;
		do {
			update = false;
			fill(level.begin(), level.end(), -1); level[s] = 0;
			queue<Index> q; q.push(s);
			for(Index d = n; !q.empty() && level[q.front()] < d; ) {
				int u = q.front(); q.pop();
				if(u == t) d = level[u];
				each(e, g[u]) if(e->capacity > 0 && level[e->to] == -1)
					q.push(e->to), level[e->to] = level[u] + 1;
			}
			while(1) {
				Flow f = augment(level, s, t, InfCapacity);
				if(f == 0) break;
				total += f; update = true;
			}
		}while(update);
		return total;
	}


	Flow augment(vector<Index> &level, Index u, Index t, Flow f) {
		if(u == t || f == 0) return f;
		Index lv = level[u];
		if(lv == -1) return 0;
		level[u] = -1;
		each(e, g[u]) if(level[e->to] > lv) {
			Flow l = augment(level, e->to, t, min(f, e->capacity));
			if(l == 0) continue;
			e->capacity -= l; g[e->to][e->rev].capacity += l;
			level[u] = lv;
			return l;
		}
		return 0;
	}
};
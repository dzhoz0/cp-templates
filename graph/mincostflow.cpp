struct MinCostFlow {
 
    struct Edge {
        int u, v, w, cap;
        Edge(int u, int v, int w, int cap): u(u), v(v), w(w), cap(cap) {}
    };
 
    vector<Edge> edges;
    void addEdge(int u, int v, int w, int cap) {
        edges.push_back(Edge(u, v, w, cap));
    }
 
    vector<vi> g, cost, cap, ocap;
    void shortest_paths(int n, int source, vi &d, vi &p) {
        d.assign(n, INF);
        p.assign(n, -1);
 
        vector<bool> inQueue(n, false);
        queue<int> q;
        d[source] = 0;
        q.push(source);
 
        while(!q.empty()) {
            int u = q.front(); q.pop();
            inQueue[u] = false;
            for(int v : g[u]) {
                if(cap[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                    d[v] = d[u] + cost[u][v];
                    p[v] = u;
                    if(!inQueue[v]) {
                        inQueue[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }
 
    int get_ans(int n, int K, int source, int target) {
        g.resize(n, vi());
        cost.resize(n, vi(n, 0));
        cap.resize(n, vi(n, 0));
        ocap.resize(n, vi(n, 0));
        for(auto e : edges) {
            g[e.u].push_back(e.v);
            g[e.v].push_back(e.u);
 
            cost[e.u][e.v] = e.w;
            cost[e.v][e.u] = -e.w;
 
            cap[e.u][e.v] = ocap[e.u][e.v] = e.cap;
        }
 
        int flow = 0, total_cost = 0;
        vi d, p;
        while(flow < K) {
            shortest_paths(n, source, d, p);
            if(d[target] == INF) break;
 
            int f = K - flow;
            int cur = target;
            while(cur != source) {
                f = min(f, cap[p[cur]][cur]);
                cur = p[cur];
            }
            
            flow += f;
            total_cost += f * d[target];
            cur = target;
            while(cur != source) {
                cap[p[cur]][cur] -= f;
                cap[cur][p[cur]] += f;
                cur = p[cur];
            }
        }        
        
        if(flow < K) return INF;
        else return total_cost;
    }
};

struct HLD {
    int n;
    vector<vi> g;
    vi p, depth, sz, in, out, nxt, heavy;
    int timer = 0;

    HLD() {}
    HLD(int _n) { init(_n); }

    void init(int _n) {
        n = _n;
        g.assign(n+1, {});
        p.assign(n+1, 0);
        depth.assign(n+1, 0);
        sz.assign(n+1, 0);
        in.assign(n+1, 0);
        out.assign(n+1, 0);
        nxt.assign(n+1, 0);
        heavy.assign(n+1, -1);
        timer = 0;
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs_sz(int u, int par) {
        p[u] = par;
        sz[u] = 1;
        heavy[u] = -1;
        for (int &v : g[u]) {
            if (v == par) continue;
            depth[v] = depth[u] + 1;
            dfs_sz(v, u);
            sz[u] += sz[v];
            if (heavy[u] == -1 || sz[v] > sz[heavy[u]]) heavy[u] = v;
            if (g[u][0] == par || sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
    }

    void dfs_hld(int u, int par, int head) {
        in[u] = ++timer;
        nxt[u] = head;
        for (int v : g[u]) {
            if (v == par) continue;
            if (v == g[u][0]) {
                dfs_hld(v, u, head);
            } else {
                dfs_hld(v, u, v);
            }
        }
        out[u] = timer;
    }

    void build(int root = 1) {
        timer = 0;
        depth[root] = 0;
        dfs_sz(root, 0);
        dfs_hld(root, 0, root);
    }

    // Insert data structures functions here
    void range_upd(int L, int R, int val) {
    }

    int range_query(int L, int R) {
        return 0;
    }

    // subtree add: add val to all nodes in subtree u
    void subtree_add(int u, int val) {
        range_upd(in[u], out[u], val); 
    }

    int point_query(int u) {
        return range_query(in[u], in[u]); 
    }

    void path_add(int a, int b, int val) {
        while (nxt[a] != nxt[b]) {
            if (depth[nxt[a]] < depth[nxt[b]]) swap(a, b);
            int head = nxt[a];
            range_upd(in[head], in[a], val);
            a = p[head];
        }
        if (depth[a] > depth[b]) swap(a, b);
        range_upd(in[a], in[b], val);
    }

    int path_query(int a, int b) {
        int res = 0;
        while (nxt[a] != nxt[b]) {
            if (depth[nxt[a]] < depth[nxt[b]]) swap(a, b);
            int head = nxt[a];
            res += range_query(in[head], in[a]);
            a = p[head];
        }
        if (depth[a] > depth[b]) swap(a, b);
        res += range_query(in[a], in[b]);
        return res;
    }
};



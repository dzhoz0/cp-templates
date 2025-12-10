struct DSU {
    int n;
    vi par;
    vi sz;
    int cmps = 0;
    void make_set(int v) {
        par[v] = v;
        sz[v] = 1;
        cmps++;
    }

    int find_set(int v) {
        if(v == par[v]) return v;
        return par[v] = find_set(par[v]);
    }

    void union_set(int u, int v) {
        u = find_set(u);
        v = find_set(v);
        if(u != v) {
            cmps--;
            if(sz[u] < sz[v]) swap(u, v);
            par[v] = u;
            sz[u] += sz[v];
        }
    }

    void init() {
        for(int i = 1; i <= n; i++) make_set(i);
    }

    DSU(int _n, bool is_init = false) {
        n = _n;
        par.resize(n + 1);
        sz.resize(n + 1);
        if(is_init) init();
    }    
};

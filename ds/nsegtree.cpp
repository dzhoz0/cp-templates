struct SegmentTree {
    int n;
    vector<int> a;
    vector<int> st;

    SegmentTree(int n, vector<int> a): n(n), a(a) {
        st.assign(4 * n + 5, INF);
    }

    void build(int id, int l, int r) {
        if (l == r) {
            st[id] = a[l - 1];
            return;
        }
        int mid = (l + r) >> 1;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        st[id] = min(st[id * 2], st[id * 2 + 1]);
    }

    void update(int id, int l, int r, int i, int val) {
        if (i < l || i > r) return;
        if (l == r) {
            st[id] = val;
            return;
        }
        int mid = (l + r) >> 1;
        update(id * 2, l, mid, i, val);
        update(id * 2 + 1, mid + 1, r, i, val);
        st[id] = min(st[id * 2], st[id * 2 + 1]);
    }

    int get(int id, int l, int r, int u, int v) {
        if (v < l || u > r) return INF;
        if (u <= l && r <= v) return st[id];
        int mid = (l + r) >> 1;
        int left = get(id * 2, l, mid, u, v);
        int right = get(id * 2 + 1, mid + 1, r, u, v);
        return min(left, right);
    }
};

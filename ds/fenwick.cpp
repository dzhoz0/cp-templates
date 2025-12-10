struct FenwickTree {
    int n;
    vi bit;
    FenwickTree(int sz) {
        n = sz;
        bit.resize(n + 1);
    }
    void upd(int id, int v) {
        while(id <= n) {
            bit[id] += v;
            id += id & (-id);
        }
    }
    int query(int id) {
        int res = 0;
        while(id > 0) {
            res += bit[id];
            id -= id & (-id);
        }
        return res;
    }
 
    int queryRange(int l, int r) {
        return query(r) - query(l - 1);
    }
};

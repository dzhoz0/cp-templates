struct OfflineFenwickTree2D {
    int n;
    vector<vi> vals;
    vector<vi> bit;
 
    int id(vector<int> &v, int x) {
        return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
    }
 
    OfflineFenwickTree2D(int n): n(n), vals(n + 1), bit(n + 1) {}
 
    void fakeUse(int x, int y) {
        for(; x <= n; x += x & (-x)) {
            vals[x].push_back(y);
        }
    }
 
    void init() {
        for(int i = 1; i <= n; i++) {
            sort(vals[i].begin(), vals[i].end());
            vals[i].erase(unique(vals[i].begin(), vals[i].end()), vals[i].end());
            bit[i].resize(vals[i].size() + 5);
        }
    }
 
    void upd(int x, int y, int w) {
        for(; x <= n; x += x & (-x)) {
            for(int i = id(vals[x], y); i < bit[x].size(); i += i & (-i)) {
                bit[x][i] = max(bit[x][i], w);
            }
        }
    }
 
    int query(int x, int y) {
        int res = 0;
        for(; x > 0; x -= x & (-x)) {
            for(int i = id(vals[x], y); i > 0; i -= i & (-i)) {
                res = max(res, bit[x][i]);
            }
        }
        return res;
    }
};

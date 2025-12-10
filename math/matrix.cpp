struct Matrix {
    int n, m;
    vector<vi> d;
    void init(vector<vi> v) {
        d = v;
        n = v.size();
        m = v[0].size();
    }
 
    void I(int n) {
        vector<vi> v(n, vi(n, 0));
        for(int i = 0; i < n; i++) v[i][i] = 1; 
        init(v);
    }
 
    Matrix operator*(Matrix &other) {
        Matrix res;
        res.n = n;
        res.m = other.m;
        res.d.resize(n, vi(m, 0));
        for(int i = 0; i < res.n; i++) {
            for(int j = 0; j < res.m; j++) {
                for(int k = 0; k < other.n; k++) {
                    res.d[i][j] += d[i][k] * other.d[k][j];
                    res.d[i][j] %= MOD;
                }
            }
        }
        return res;
    }
 
    Matrix operator^(int k) {
        assert(n == m);
        Matrix res; res.I(n);
        Matrix cur; cur.init(d);
        while(k > 0) {
            if(k & 1) res = res * cur;
            cur = cur * cur;
            k >>= 1; 
        }
        return res;
    }
};

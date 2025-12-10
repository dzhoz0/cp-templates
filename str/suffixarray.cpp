struct SuffixArray {
    vi sort_shifts(string s, bool cyclic, vector<vi> &ck) {
        if (!cyclic) s.push_back('$');
        int n = (int)s.size();
        const int ALPH = 256;
 
        vi p(n), c(n), cnt(max(ALPH, n), 0);
        for (unsigned char ch : s) cnt[ch]++;
        for (int i = 1; i < (int)cnt.size(); i++) cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; --i) p[--cnt[(unsigned char)s[i]]] = i;
 
        c[p[0]] = 0; int classes = 1;
        for (int i = 1; i < n; ++i) {
            if (s[p[i]] != s[p[i-1]]) classes++;
            c[p[i]] = classes - 1;
        }
 
        ck.clear();
        ck.push_back(c);
 
        vi pn(n), cn(n);
        for (int h = 0; (1 << h) < n; h++) {
            int shift = 1 << h;
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - shift;
                if (pn[i] < 0) pn[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < n; i++) ++cnt[c[pn[i]]];
            for (int i = 1; i < classes; i++) cnt[i] += cnt[i-1];
            for (int i = n-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
 
            cn[p[0]] = 0; classes = 1;
            for (int i = 1; i < n; i++) {
                pii cur = {c[p[i]], c[(p[i] + shift) % n]};
                pii prev = {c[p[i-1]], c[(p[i-1] + shift) % n]};
                if (cur != prev) ++classes;
                cn[p[i]] = classes - 1;
            }
            ck.push_back(cn);
            c.swap(cn);
        }
 
        if (!cyclic) p.erase(p.begin());
        return p;
    }
 
    int lcp(int i, int j, vector<vi> &ck) {
        int ans = 0;
        if (ck.empty()) return 0;
        int n = ck[0].size();
        int maxk = (int)ck.size() - 1;
        for (int k = maxk; k >= 0; --k) {
            if (ck[k][i % n] == ck[k][j % n]) {
                ans += (1 << k);
                i += (1 << k);
                j += (1 << k);
            }
        }
        return ans;
    }
 
    vi build_suffix_array(string s) { vector<vi> ck; return sort_shifts(s, false, ck); }
    vi build_cyclic_shifts(string s) { vector<vi> ck; return sort_shifts(s, true, ck); }
};

struct Hash {
    Hash() {}
    const int BASE = 53;
    vi pr = {1'000'000'000 + 7, 998244353, 4518541637, 7385466377};
    int mod;
    int n;
    vi hash, pw;
    Hash(int p, string s) {
        n = s.size();
 
        mod = pr[p];
        s = "@" + s;
 
        pw.resize(n + 1);
        hash.resize(n + 1);
        pw[0] = 1;
        for(int i = 1; i <= n; i++) pw[i] = (pw[i - 1] * BASE) % mod;
        for(int i = 1; i <= n; i++) hash[i] = ((hash[i - 1] * BASE) + (s[i] - 'a' + 1)) % mod;
    }
 
    int get(int l, int r) {
        return (hash[r] - hash[l - 1] * pw[r - l + 1] + mod * mod) % mod;
    }
};

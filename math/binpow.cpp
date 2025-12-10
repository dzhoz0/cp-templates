int binmul(int a, int b, int mod = MOD) {
    int res = 0;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

int binpow(int a, int b, int mod = MOD) {
    int res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = binmul(res, a, mod);
        a = binmul(a, a, mod);
        b >>= 1;
    }
    return res;
}

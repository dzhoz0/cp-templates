/*
    it could have been better :)
    it will next time ;)
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF 1e18
#define f first
#define s second
#define pii pair<int, int>
#define vi vector<int>

const int MOD = 1'000'000'000 + 7;

void setIO(string name = "")
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
#ifdef LOCAL
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
    if (!name.empty())
    {
        freopen((name + ".INP").c_str(), "r", stdin);
        freopen((name + ".OUT").c_str(), "w", stdout);
    }
#endif
}

void solve()
{
    
}

signed main()
{
    setIO();
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}


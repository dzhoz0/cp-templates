struct PersistentSegTree {
    struct Node {
        int val = 0;
        int l = -1, r = -1;

        Node() {}
        Node(int v) : val(v) {}
        Node(int v, int L, int R) : val(v), l(L), r(R) {}

        Node operator+(const Node &a, const Node &b) {
            return Node(a.val + b.val, a.l, b.r);
        }
    };

    vector<Node> st;
    int n, id;

    void init(int _n){
        n = _n; 
        st.resize(20 * _n + 5);
    }

    int add_copy(int root) {
        st.push_back(st[root]);
        return id++;
    }

    int build(int l, int r) {
        int my = id++;
        st.emplace_back();
        if (l == r) return my;

        int mid = (l + r) >> 1;
        int left = build(l, mid);
        int right = build(mid + 1, r);
        st[my] = st[left] + st[right];
        st[my].l = left;
        st[my].r = right;
        return my;
    }

    int update(int cur, int l, int r, int k, int x) {
        if (k < l || k > r) return cur;
        if (l == r) {
            st.emplace_back(x);
            return id++;
        }

        int mid = (l + r) >> 1;
        int newLeft = update(st[cur].l, l, mid, k, x);
        int newRight = updateRec(st[cur].r, mid + 1, r, k, x);
        st.emplace_back(st[newLeft] + st[newRight]);
        st.back().l = newLeft;
        st.back().r = newRight;
        return id++;
    }

    int queryRec(int cur, int l, int r, int L, int R) {
        if (R < l || r < L) return 0;
        if (L <= l && r <= R) return st[cur].val;
        int mid = (l + r) >> 1;
        return queryRec(st[cur].l, l, mid, L, R) +
               queryRec(st[cur].r, mid + 1, r, L, R);
    }
};

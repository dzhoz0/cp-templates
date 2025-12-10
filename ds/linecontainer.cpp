struct Line {
	mutable int k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(int x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	bool is_max; 
	LineContainer(bool fl = true) : is_max(fl) {}
    // LineContainer cht(true): query max
    // LineContainer cht(false): query min

	int div(int a, int b) { 
		return a / b - ((a ^ b) < 0 && a % b);
	}

	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = INF, 0;
		if (x->k == y->k) 
			x->p = (x->m > y->m ? INF : -INF);
		else 
			x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}

	void add(int k, int m) {
		if (!is_max) k = -k, m = -m;

		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}

	int query(int x) const {
		assert(!empty());
		auto l = *lower_bound(x);
		int res = l.k * x + l.m;
		return is_max ? res : -res;
	}
};

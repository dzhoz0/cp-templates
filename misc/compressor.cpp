template <typename T> struct Compressor {
    vector<T> v;

    int sz() { return (int)v.size(); }

    void add(T x) {
        v.push_back(x);
    }
    
    void init() {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }

    int id(T key) {
        return lower_bound(v.begin(), v.end(), key) - v.begin() + 1;
    }
};

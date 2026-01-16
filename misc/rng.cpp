int rng() {
    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(0, INT64_MAX)(gen);
}

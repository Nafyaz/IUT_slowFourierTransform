inline int sgn(int mask) {
    return 1 - 2 * (__builtin_popcount(mask) & 1);
} // returns 1 if set cardinality is even, -1 otherwise

template <typename T, int b> struct Subset {
    static const int N = 1 << b;
    array <T, N> F;
    void Zeta() { // SOS
        for(int i = 0; i < b; i++)
            for(int mask = 0; mask < N; mask++)
                if(mask & 1 << i)
                    F[mask] += F[mask ^ 1 << i];
    }
    void OddEven() {
        for(int mask = 0; mask < N; mask++)
            F[mask] *= sgn(mask);
    }
    void MobiusOld() {
        OddEven();
        Zeta();
        OddEven();
    }
    void Mobius(){
        for(int i = 0; i < b; i++)
            for(int mask = 0; mask < N; mask++)
                if(mask & 1 << i)
                    F[mask] -= F[mask ^ 1 << i];
    }
    void operator *= (Subset &R) {
        auto &G = R.F;
        array < array <int, N>, b> Fh = {0}, Gh = {0}, H = {0};

        for(int mask = 0; mask < N; mask++) 
            Fh[__builtin_popcount(mask)][mask] = F[mask], Gh[__builtin_popcount(mask)][mask] = G[mask];

        for(int i = 0; i < b; i++)
            for(int j = 0; j < b; j++)
                for(int mask = 0; mask < N; mask++)
                    if((mask & (1 << j)) != 0)
                        Fh[i][mask] += Fh[i][mask ^ (1 << j)], Gh[i][mask] += Gh[i][mask ^ (1 << j)];
                    
        for(int mask = 0; mask < N; mask++)
            for(int i = 0; i < b; i++)
                for(int j = 0; j <= i; j++)
                    H[i][mask] += Fh[j][mask] * Gh[i - j][mask];

        for(int i = 0; i < b; i++) 
            for(int j = 0; j < b; j++) 
                for(int mask = 0; mask < N; mask++) 
                    if((mask & (1 << j)) != 0) 
                        H[i][mask] -= H[i][mask ^ (1 << j)];
                
        for(int mask = 0; mask < N; mask++)  
            F[mask] = H[__builtin_popcount(mask)][mask];
    }
    Subset operator * (Subset &R) {
        Subset ans = *this;
        return ans;
    }
};

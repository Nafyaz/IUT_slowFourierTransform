array <int, N + 1> Drng;
void init(){
    Drng[0] = 1, Drng[1] = 0;
    for(int i = 2; i <= N; i++)
        Drng[i] = (LL) (i - 1) * (Drng[i - 1] + Drng[i - 2]) % mod;
}
int D(int n) { 
    return n < 0 ? 0 : Drng[n];
}

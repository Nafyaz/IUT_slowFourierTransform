//stirling number 2nd kind variation(number of ways to place n marbles in k boxes so that each box has at least x marbles)
ll solve(int marble, int box) {
  if (marble < 1ll * box * x) return 0;
  if (box == 1 && marble >= x) return 1;
  if (vis[marble][box] == cs) return dp[marble][box];
  vis[marble][box] = cs;
  ll a = ( 1ll * box * solve(marble - 1, box) ) % MOD;
  ll b = ( 1ll * box * ncr(marble - 1, x - 1) ) % MOD;
  b = (b * solve(marble - x, box - 1)) % MOD;
  ll ret = (a + b) % MOD;
  return dp[marble][box] = ret;
}
//number of ways to place n marbles in k boxes so that no box is empty
ll stir(ll n, ll k) {
  ll ret = 0;
  for (int i = 0; i <= k; i++) {
    ll v = ncr(k, i) * bigmod(i, n) % MOD;
    if ( (k - i) % 2 == 0 ) ret = (ret + v) % MOD;
    else ret = (ret - v + MOD) % MOD;
  }
  return ret;
}

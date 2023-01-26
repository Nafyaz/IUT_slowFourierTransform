bool valid[205][205];
ll dp[205][205];
ll solve(int L, int R) {
  if (L + 1 == R) return 1;
  if (dp[L][R] != -1) return dp[L][R];
  ll ret = 0;
  for (int mid = L + 1; mid < R; mid++) {
    if (valid[L][mid] && valid[mid][R]) {
      ///selecting triangle(P[L], P[mid], P[R])
      ll temp = ( solve(L, mid) * solve(mid, R) ) % MOD;
      ret = (ret + temp) % MOD;
    }
  }
  return dp[L][R] = ret;
}

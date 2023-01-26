int trie[40 * MAX][26];
int XOR[40 * MAX][26];
int valu[40 * MAX];
int node = 1;

int add(string s) {
  int now = 1;
  stack<int>st;
  for (int i = 0; i < s.size(); i++) {
    int c = s[i] - 'a';
    if (!trie[now][c]) trie[now][c] = ++node;
    st.push(now);
    now = trie[now][c];
  }

  int nxt = now;
  int nxt_val = 0;
  for (int i = 0; i < 26; i++) nxt_val ^= XOR[now][i];
  while (!st.empty()) {
    now = st.top();
    st.pop();
    int val = 0;
    for (int i = 0; i < 26; i++) {
      if (trie[now][i] == nxt) {
        XOR[now][i] = nxt_val + 1;
      }
      val ^= XOR[now][i];
    }
    nxt_val = val;
    nxt = now;
  }
  return nxt_val;
}

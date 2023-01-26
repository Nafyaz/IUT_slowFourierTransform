struct dominator {
  int n, d_t;
  vector<vector<int>> g, rg, tree, bucket;
  vector<int> sdom, dom, par, dsu, label, val, rev;
  dominator() {}
  dominator(int n) : 
    n(n), d_t(0), g(n + 1), rg(n + 1),
    tree(n + 1), bucket(n + 1), sdom(n + 1),
    dom(n + 1), par(n + 1), dsu(n + 1),
    label(n + 1), val(n + 1), rev(n + 1)
  { for (int i = 1; i <= n; i++) sdom[i] = dom[i] = dsu[i] = label[i] = i; }

  void add_edge(int u, int v) { g[u].pb(v); }
  int dfs(int u) {
    d_t++;
    val[u] = d_t, rev[d_t] = u;
    label[d_t] = sdom[d_t] = dom[d_t] = d_t;
    for (int v : g[u]) {
      if (!val[v]) {
        dfs(v);
        par[val[v]] = val[u];
      }
      rg[val[v]].pb(val[u]);
    }
  }
  int findpar(int u, int x = 0) {
    if (dsu[u] == u) return x ? -1 : u;
    int v = findpar(dsu[u], x + 1);
    if (v < 0) return u;
    if (sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
    dsu[u] = v;
    return x ? v : label[u];
  }
  void join(int u, int v) { dsu[v] = u; }
  vector<vector<int>> build(int s) {
    dfs(s);
    for (int i = n; i >= 1; i--) {
      for (int j = 0; j < rg[i].size(); j++) {
        sdom[i] = min(sdom[i], sdom[ findpar(rg[i][j]) ]);
      }
      if (i > 1) bucket[sdom[i]].pb(i);
      for (int w : bucket[i]) {
        int v = findpar(w);
        if (sdom[v] == sdom[w]) dom[w] = sdom[w];
        else dom[w] = v;
      }
      if (i > 1) join(par[i], i);
    }
    for (int i = 2; i <= n; i++) {
      if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
      tree[rev[i]].pb(rev[dom[i]]);
      tree[rev[dom[i]]].pb(rev[i]);
    }
    return tree;
  }
};

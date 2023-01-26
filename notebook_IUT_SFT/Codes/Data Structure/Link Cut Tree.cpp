struct SplayTree {
  struct node {
    int ch[2] = {0, 0}, p = 0;
    ll self = 0, path = 0;
    ll sub = 0, extra = 0;
    bool rev = false;
  };
  vector<node> T;
  SplayTree(int n) : T(n + 1) {}
  void push(int x) {
    if (!x) return;
    int l = T[x].ch[0], r = T[x].ch[1];
    if (T[x].rev) {
      T[l].rev ^= true, T[r].rev ^= true;
      swap(T[x].ch[0], T[x].ch[1]);
      T[x].rev = false;
    }
  }
  void pull(int x) {
    int l = T[x].ch[0], r = T[x].ch[1];
    push(l), push(r);
    T[x].path = T[x].self + T[l].path + T[r].path;
    T[x].sub = T[x].self + T[x].extra + T[l].sub + T[r].sub;
  }
  void set(int parent, int child, int d) {
    T[parent].ch[d] = child;
    T[child].p = parent;
    pull(parent);
  }
  int dir(int x) {
    int parent = T[x].p;
    if (!parent) return -1;
    return (T[parent].ch[0] == x) ? 0 : (T[parent].ch[1] == x) ? 1 : -1;
  }
  void rotate(int x) {
    int parent = T[x].p, gparent = T[parent].p;
    int dx = dir(x), dp = dir(parent);
    set(parent, T[x].ch[!dx], dx);
    set(x, parent, !dx);
    if (~dp) set(gparent, x, dp);
    T[x].p = gparent;
  }
  void splay(int x) {
    push(x);
    while (~dir(x)) {
      int parent = T[x].p;
      int gparent = T[parent].p;
      push(gparent), push(parent), push(x);
      int dx = dir(x), dp = dir(parent);
      if (~dp) rotate(dx != dp ? x : parent);
      rotate(x);
    }
  }
};
struct LinkCut : SplayTree {
  LinkCut(int n) : SplayTree(n) {}
  void cut_right(int x) {
    splay(x);
    int r = T[x].ch[1];
    T[x].extra += T[r].sub;
    T[x].ch[1] = 0, pull(x);
  }
  int access(int x) {
    int u = x, v = 0;
    for (; u; v = u, u = T[u].p) {
      cut_right(u);
      T[u].extra -= T[v].sub;
      T[u].ch[1] = v, pull(u);
    }
    return splay(x), v;
  }
  void make_root(int x) {
    access(x);
    T[x].rev ^= true, push(x);
  }
  void link(int u, int v) {
    make_root(v), access(u);
    T[u].extra += T[v].sub;
    T[v].p = u, pull(u);
  }
  void cut(int u) {
    access(u);
    T[u].ch[0] = T[ T[u].ch[0] ].p = 0;
    pull(u);
  }
  void cut(int u, int v) {
    make_root(u), access(v);
    T[v].ch[0] = T[u].p = 0, pull(v);
  }
  int find_root(int u) {
    access(u), push(u);
    while (T[u].ch[0]) {
      u = T[u].ch[0], push(u);
    }
    return splay(u), u;
  }
  int lca(int u, int v) {
    if (u == v) return u;
    access(u);
    int ret = access(v);
    return T[u].p ? ret : 0;
  }
  // subtree query of u if v is the root
  ll subtree(int u, int v) {
    make_root(v), access(u);
    return T[u].self + T[u].extra;
  }
  ll path(int u, int v) {
    make_root(u), access(v);
    return T[v].path;
  }
  // point update
  void update(int u, ll val) {
    access(u);
    T[u].self = val, pull(u);
  }
};

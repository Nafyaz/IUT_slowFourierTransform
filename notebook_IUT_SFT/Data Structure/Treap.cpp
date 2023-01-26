mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef struct node* pnode;
struct node {
  int prior, val, sz;
  ll sum;
  node *lft, *rt;
  node(int val = 0, node *lft = NULL, node *rt = NULL) : 
    lft(lft), rt(rt), prior(rnd()), val(val), sz(1), sum(0) {}
};
struct treap {
  pnode root;
  treap() {
    root = NULL;
  }
  int get_sz(pnode now) {
    return now ? now->sz : 0;
  }
  void update_sz(pnode now) {
    if (!now) return;
    now->sz = 1 + get_sz(now->lft) + get_sz(now->rt);
  }
  ll get(pnode now) {
    return now ? now->sum : 0;
  }
  void push(pnode now) {}
  void combine(pnode now) {
    if (!now) return;
    now->sum = now->val + get(now->lft) + get(now->rt);
  }
  pnode unite(pnode lft, pnode rt) {
    if (!lft || !rt) return lft ? lft : rt;
    // push(lft), push(rt); this not tested
    if (lft->prior < rt->prior) swap(lft, rt);
    pnode l, r;
    split(rt, l, r, lft->val);
    lft->lft = unite(lft->lft, l), update_sz(lft);
    lft->rt = unite(lft->rt, r), update_sz(lft);
    // combine(lft); this not tested
    return lft;
  }
  ///value < val goes to left, value >= val goes to right
  void split(pnode now, pnode &lft, pnode &rt, int val, int add = 0) {
    push(now);
    if (!now) return void(lft = rt = NULL);
    if (now->val < val) split(now->rt, now->rt, rt, val), lft = now;
    else split(now->lft, lft, now->lft, val), rt = now;
    update_sz(now), combine(now);
  }
  void merge(pnode &now, pnode lft, pnode rt) {
    push(lft), push(rt);
    if (!lft || !rt) now = lft ? lft : rt;
    else if (lft->prior > rt->prior) merge(lft->rt, lft->rt, rt), now = lft;
    else merge(rt->lft, lft, rt->lft), now = rt;
    update_sz(now), combine(now);
  }
  void insert(pnode &now, pnode notun) {
    if (!now) return void(now = notun);
    push(now);
    if (notun->prior > now->prior) split(now, notun->lft, notun->rt, notun->val), now = notun;
    else insert(notun->val < now->val ? now->lft : now->rt, notun);
    update_sz(now), combine(now);
  }
  void erase(pnode &now, int val) {
    push(now);
    if (now->val == val) {
      pnode temp = now;
      merge(now, now->lft, now->rt);
      delete(temp);
    } else erase(val < now->val ? now->lft : now->rt, val);
    update_sz(now), combine(now);
  }
  int get_idx(pnode &now, int val) {
    if (!now) return INT_MIN;
    else if (now->val == val) return 1 + get_sz(now->lft);
    else if (val < now->val) return get_idx(now->lft, val);
    else return (1 + get_sz(now->lft) + get_idx(now->rt, val));
  }
  int find_kth(pnode &now, int k) {
    if (k < 1 || k > get_sz(now)) return -1;
    if (get_sz(now->lft) + 1 == k) return now->val;
    if (k <= get_sz(now->lft)) return find_kth(now->lft, k);
    return find_kth(now->rt, k - get_sz(now->lft) - 1);
  }
  ll prefix_sum(pnode &now, int k) {
    if (k < 1 || k > get_sz(now)) return -inf;
    if (get_sz(now->lft) + 1 == k) return get(now->lft) + now->val;
    if (k <= get_sz(now->lft)) return prefix_sum(now->lft, k);
    return get(now->lft) + now->val + prefix_sum(now->rt, k - get_sz(now->lft) - 1);
  }
  pnode get_rng(int l, int r) { ///gets all l <= values <= r
    pnode lft, rt, mid;
    split(root, lft, mid, l);
    split(mid, mid, rt, r + 1);
    merge(root, lft, rt);
    return mid;
  }
  void output(pnode now, vector<int>&v) {
    if (!now) return;
    output(now->lft, v);
    v.pb(now->val);
    output(now->rt, v);
  }
  vector<int>get_arr() {
    vector<int>ret;
    output(root, ret);
    return ret;
  }
};

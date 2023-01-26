mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef struct node* pnode;
struct node {
  int prior, sz;
  ll val, sum, lazy;
  bool rev;
  node *lft, *rt;
  node(int val = 0, node *lft = NULL, node *rt = NULL) : lft(lft), rt(rt), prior(rnd()), sz(1), val(val), rev(false), sum(0), lazy(0) {}
};
struct implicit_treap {
  pnode root;
  implicit_treap() {
    root = NULL;
  }
  int get_sz(pnode now) {
    return now ? now->sz : 0;
  }
  void update_sz(pnode now) {
    if (!now) return;
    now->sz = 1 + get_sz(now->lft) + get_sz(now->rt);
  }
  // lazy sum
  void push(pnode now) {
    if (!now || !now->lazy) return;
    now->val += now->lazy;
    now->sum += get_sz(now) * now->lazy;
    if (now->lft) now->lft->lazy += now->lazy;
    if (now->rt) now->rt->lazy += now->lazy;
    now->lazy = 0;
  }
  void combine(pnode now) {
    if (!now) return;
    now->sum = now->val; // reset the node
    push(now->lft), push(now->rt); // update lft and rt
    now->sum += (now->lft ? now->lft->sum : 0) + (now->rt ? now->rt->sum : 0);
  }
  // reverse substring
  void push(pnode now) {
    if (!now || !now->rev) return;
    now->rev = false;
    swap(now->lft, now->rt);
    if (now->lft) now->lft->rev ^= true;
    if (now->rt) now->rt->rev ^= true;
  }
  sort ascending or descending
  void push(pnode now) {
    if (!now || !now->sort_kor) return;
    if (now->sort_kor == -1) swap(now->lft, now->rt);
    int cnt[26];
    for (int i = 0; i < 26; i++) cnt[i] = now->cnt[i];
    int idx = 0;
    if (now->lft) {
      memset(now->lft->cnt, 0, sizeof now->lft->cnt);
      int lft_sz = get_sz(now->lft);
      while (idx < 26 && lft_sz) {
        int mn = min(cnt[idx], lft_sz);
        now->lft->cnt[idx] = mn;
        cnt[idx] -= mn; lft_sz -= mn;
        if (!cnt[idx]) idx++;
      }
      now->lft->sort_kor = now->sort_kor;
    }
    while (!cnt[idx]) idx++;
    now->val = idx, cnt[idx]--;
    if (!cnt[idx]) idx++;
    if (now->rt) {
      memset(now->rt->cnt, 0, sizeof now->rt->cnt);
      int rt_sz = get_sz(now->rt);
      while (idx < 26 && rt_sz) {
        int mn = min(cnt[idx], rt_sz);
        now->rt->cnt[idx] = mn;
        cnt[idx] -= mn; rt_sz -= mn;
        if (!cnt[idx]) idx++;
      }
      now->rt->sort_kor = now->sort_kor;
    }
    if (now->sort_kor == -1) swap(now->lft, now->rt);
    now->sort_kor = 0;
  }
  void combine(pnode now) {
    if (!now) return;
    memset(now->cnt, 0, sizeof now->cnt);
    for (int i = 0; i < 26; i++) {
      now->cnt[i] = (now->lft ? now->lft->cnt[i] : 0) + (now->rt ? now->rt->cnt[i] : 0);
    }
    now->cnt[now->val]++;
  }
  ///first pos ta elements go to left, others go to right
  void split(pnode now, pnode &lft, pnode &rt, int pos, int add = 0) {
    if (!now) return void(lft = rt = NULL);
    push(now);
    int cur = add + get_sz(now->lft);
    if (cur < pos) split(now->rt, now->rt, rt, pos, cur + 1), lft = now;
    else split(now->lft, lft, now->lft, pos, add), rt = now;
    update_sz(now); combine(now);
  }
  void merge(pnode &now, pnode lft, pnode rt) {
    push(lft);
    push(rt);
    if (!lft || !rt) now = lft ? lft : rt;
    else if (lft->prior > rt->prior) merge(lft->rt, lft->rt, rt), now = lft;
    else merge(rt->lft, lft, rt->lft), now = rt;
    update_sz(now); combine(now);
  }
  void insert(int pos, ll val) {
    if (!root) return void(root = new node(val));
    pnode lft, rt;
    split(root, lft, rt, pos - 1);
    pnode notun = new node(val);
    merge(root, lft, notun);
    merge(root, root, rt);
  }
  void erase(int pos) {
    pnode lft, rt, temp;
    split(root, lft, rt, pos);
    split(lft, lft, temp, pos - 1);
    merge(root, lft, rt);
    delete(temp);
  }
  void reverse(int l, int r) {
    pnode lft, rt, mid;
    split(root, lft, mid, l - 1);
    split(mid, mid, rt, r - l + 1);
    mid->rev ^= true;
    merge(root, lft, mid);
    merge(root, root, rt);
  }
  void right_shift(int l, int r) {
    pnode lft, rt, mid, last;
    split(root, lft, mid, l - 1);
    split(mid, mid, rt, r - l + 1);
    split(mid, mid, last, r - l);
    merge(mid, last, mid);
    merge(root, lft, mid);
    merge(root, root, rt);
  }
  void output(pnode now, vector<int>&v) {
    if (!now) return;
    push(now);
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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ordered_set<pii> bst[MAX << 2];
void init(int n) {
  for (int i = 0; i <= 4 * n; i++) bst[i].clear();
}

void build(int now, int L, int R) {
  if (L == R) {
    bst[now].insert({arr[L], L});
    return;
  }
  for (int i = L; i <= R; i++) bst[now].insert({arr[i], i});

  int mid = (L + R) / 2;
  build(now << 1, L, mid);
  build((now << 1) | 1, mid + 1, R);
}

void update(int now, int L, int R, int idx, int ager_val, int val) {
  if (L == R) {
    bst[now].erase(bst[now].find({ager_val, idx}));
    bst[now].insert({val, idx});
    return;
  }

  int mid = (L + R) / 2;
  if (idx <= mid) update(now << 1, L, mid, idx, ager_val, val);
  else update((now << 1) | 1, mid + 1, R, idx, ager_val, val);
  bst[now].erase(bst[now].find({ager_val, idx}));
  bst[now].insert({val, idx});
}

ll query(int now, int L, int R, int i, int j, int val) {
  if (R < i || L > j) return 0;
  if (L >= i && R <= j) {
    int ret = bst[now].order_of_key({val, INT_MAX});
    return ret;
  }

  int mid = (L + R) / 2;
  return query(now << 1, L, mid, i, j, val) + query((now << 1) | 1, mid + 1, R, i, j, val);
}


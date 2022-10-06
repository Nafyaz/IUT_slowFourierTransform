/*---------------Go Code GO---------------*/ 
#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
#ifdef BUG
#include "bits/error.h"
#else
#define debug(x...)
#define endl '\n'
#endif
#pragma GCC target("sse4.2")
#pragma GCC target("avx2")
#pragma GCC optimization("O3")
#pragma GCC optimization("unroll-loops")
using namespace std;
using namespace __gnu_pbds;
template <typename T>
using Order_Set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
//(order) Set.order_of_key(); (pointer) Set.find_by_order();
int main()
{
#ifdef BUG
    freopen("in.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    debug("HI");
}

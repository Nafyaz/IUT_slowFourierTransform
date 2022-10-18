const int N = 2e5 + 5, LOG = 19;
namespace Tree {
    vector <int> T[N];
    int n;
    int anc[N][LOG], level[N]; // binary ancestors of node
    //binary lifting
    void setupLifting(int node, int par) {
        for (int v : T[node]) if (v != par) {
            anc[v][0] = node, level[v] = level[node] + 1;
            for (int k = 1; k < LOG; k++) anc[v][k] = anc[anc[v][k - 1]][k - 1];
            setupLifting(v, node);
        }
    }
    int lca(int u, int v) {
        if (level[u] > level[v])
            swap(u, v);
        for (int k = LOG - 1; ~k; k--)
            if (level[u] + (1 << k) <= level[v])
                v = anc[v][k];
        if (u == v)
            return u;
        for (int k = LOG - 1; ~k; k--)
            if (anc[u][k] != anc[v][k])
                u = anc[u][k], v = anc[v][k];
        return anc[u][0];
    }
    int getAncestor(int node, int ht) {
        for (int k = 0; k < LOG; k++)
            if (ht & (1 << k))
                node = anc[node][k];
        return node;
    }
    int distance(int u, int v) {
        int g = lca(u, v);
        return level[u] + level[v] - 2 * level[g];
    }
    void initLifting(int root = 0) {
        setupLifting(root, root);
    }
    //binary lifting end
    //euler tour start

    int start[N], finish[N], par[N], time;
    void call(int node, int p = -1) {
        if (p != -1) level[node] = level[p] + 1;
        start[node] = time++;
        for (int e : T[node]) if (e != p) call(e, node);
        par[node] = p, finish[node] = time++;
    }
    bool isAncestor(int node, int par) {
        return start[par] <= start[node] and finish[par] >= finish[node];
    }
    int subtreeSize(int node) {
        return finish[node] - start[node] + 1 >> 1;
    }
    void euler_tour(int root = 0) {
        time = 0;
        call(root);
    }
}

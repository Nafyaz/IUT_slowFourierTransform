int n, m;
bool vis[MAXN];
int tin[MAXN], low[MAXN], timer;
vector<int> adj[MAXN];
set<int> AP;

void dfs(int node, int p = -1)
{
    vis[node] = 1;
    timer++;
    tin[node] = low[node] = timer;

    int child = 0;
    for(auto nxt : adj[node])
    {
        if(nxt == p)
            continue;
        if(!vis[nxt])
        {
            child++;
            dfs(nxt, node);
            low[node] = min(low[node], low[nxt]);
            if(low[nxt] >= tin[node] && p != -1)
                AP.insert(node);
        }
        else
            low[node] = min(low[node], tin[nxt]);
    }

    if(p == -1 && child > 1)
        AP.insert(node);
}

void findAP()
{
    AP.clear();
    timer = 0;
    int i;
    for(i = 1; i <= n; i++)
    {
        vis[i] = 0;
        tin[i] = -1;
        low[i] = -1;
    }

    for(i = 1; i <= n; i++)
    {
        if(!vis[i])
            dfs(i);
    }
}

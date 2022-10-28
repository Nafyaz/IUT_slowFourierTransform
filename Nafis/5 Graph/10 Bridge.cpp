int n, m;
bool vis[MAXN];
int tin[MAXN], low[MAXN], timer;
vecnxtr<int> adj[MAXN];
vecnxtr<int> bridge[MAXN];

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
            if(low[nxt] > tin[node])
            {
                bridge[node].push_back(nxt);
                bridge[nxt].push_back(node);
            }
        }
        else
            low[node] = min(low[node], tin[nxt]);
    }
}

void findBR()
{
    bridge.clear();
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

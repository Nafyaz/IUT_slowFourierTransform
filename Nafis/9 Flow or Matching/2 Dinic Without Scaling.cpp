// Complexity O(V^2E)

struct edge
{
    LL node, nxt, cap, flow = 0;

    edge(LL u, LL v, LL c) : node(u), nxt(v), cap(c) {}
};

struct Dinic
{
    vector<edge> edges;
    vector<vector<LL>> adj;
    vector<LL> level, ptr;

    LL n, m, s, t;

    Dinic(LL n, LL s, LL t) : n(n), s(s), t(t)
    {
        m = 0;
        adj.resize(n+1);
        level.resize(n+1);
        ptr.resize(n+1);
    }

    void add_edges(LL u, LL v, LL c)
    {
        edges.push_back(edge(u, v, c));
        adj[u].push_back(m);
        m++;

        edges.push_back(edge(v, u, c));
        adj[v].push_back(m);
        m++;
    }

    bool bfs(LL s)
    {
        queue<LL> q;

        level[s] = 0;
        q.push(s);

        while(!q.empty())
        {
            LL node = q.front();
            q.pop();

            for(auto id : adj[node])
            {
                LL nxt = edges[id].nxt;
                if(edges[id].cap == edges[id].flow || level[nxt] != -1)
                    continue;

                level[nxt] = level[node] + 1;
                q.push(nxt);
            }
        }

        return (level[t] != -1);
    }

    LL dfs(LL node, LL currFlow)
    {
        if(currFlow == 0)
            return 0;

        if(node == t)
            return currFlow;

        for(LL &cid = ptr[node]; cid < adj[node].size(); cid++)
        {
            LL id = adj[node][cid];
            LL nxt = edges[id].nxt;

            if(level[nxt] != level[node] + 1 || edges[id].cap == edges[id].flow)
                continue;

            LL newFlow = dfs(nxt, min(currFlow, edges[id].cap - edges[id].flow));

            if(newFlow == 0)
                continue;

            edges[id].flow += newFlow;
            edges[id ^ 1].flow -= newFlow;

            return newFlow;
        }

        return 0;
    }

    LL getFlow()
    {
        LL flow = 0;

        while(1)
        {
            fill(level.begin(), level.end(), -1);
            if(!bfs(s))
                break;

            fill(ptr.begin(), ptr.end(), 0);
            while(LL newFlow = dfs(s, INF))
                flow += newFlow;
        }

        return flow;
    }
};
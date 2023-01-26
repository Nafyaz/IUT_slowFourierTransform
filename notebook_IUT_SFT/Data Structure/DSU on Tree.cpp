///Query: Number of distinct names among all the k'th son of a node.
const int N = 100005;
string name[N];
vector<int>G[N];
vector<pii>Q[N];
int L[N],ans[N];

void dfs(int v,int d){
    L[v]=d;
    for(int i:G[v]) dfs(i,d+1);
    return;
}

void dsu(int v,map<int,set<string>>&mp){
    for(int i:G[v]){
        map<int,set<string>>s;
        dsu(i,s);
        if(s.size()>mp.size()) swap(mp,s);
        for(auto it:s) mp[it.ff].insert(all(it.ss));
    }
    if(v!=0) mp[L[v]].insert(name[v]); //Here zero is not a actual node
    for(pii p:Q[v]) ans[p.ss] = mp[p.ff].size();
    return;
}

int main(){
    int n;
    cin >> n;
    FOR(i,1,n){
        int u;
        cin >> name[i] >> u;
        G[u].pb(i);
    }
    dfs(0,0);
    int q;
    cin >>q;
    FOR(i,1,q){
        int v,k;
        cin >> v >> k;
        Q[v].pb(pii(k+L[v],i)); //Actual level
    }
    map<int,set<string>>mp;
    dsu(0,mp);
    FOR(i,1,q) cout << ans[i] << '\n';
    return 0;
}

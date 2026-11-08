class Solution {
    int _revcnt = 0;
    struct edge { int dst; bool reversed; };
    vector<vector<edge>> _adj;

public:
    int minReorder(int n, vector<vector<int>>& connections) 
    {
        _adj.resize(n);
        for (const auto& e : connections)
        {
            _adj[e[0]].push_back(edge{e[1], false});
            _adj[e[1]].push_back(edge{e[0], true});
        }
        dfs(0, -1);
        return _revcnt;
    }

    void dfs(int node, int parent)
    {
        for (const auto& e : _adj[node])
        {
            if (e.dst != parent)
            {
                if (!e.reversed)
                {
                    ++_revcnt; 
                }
                dfs(e.dst, node);
            }
        }
    }
};

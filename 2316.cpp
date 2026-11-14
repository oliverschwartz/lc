class Solution {
    unordered_set<int> _visited; 
    unordered_map<int, vector<int>> _adj;
    vector<int> _cmp_sizes; 

public:
    long long countPairs(int n, vector<vector<int>>& edges) 
    {
        for (const auto& e : edges)
        {
            _adj[e[0]].push_back(e[1]);
            _adj[e[1]].push_back(e[0]);
        }

        long long pair_count = 0; 
        for (int i = 0; i < n; ++i)
        {
            if (!_visited.contains(i))
            {
                const long long cmp_size = dfs(i);
                pair_count += cmp_size * (n - cmp_size);
            }
        }

        return pair_count / 2;
    }

    int dfs(int node)
    {
        int visit_count = 1;
        _visited.insert(node);

        if (_adj.find(node) == _adj.end())
        {
            return visit_count;
        }

        for (auto nbor : _adj[node])
        {
            if (!_visited.contains(nbor))
            {
                visit_count += dfs(nbor);
            }
        }
        return visit_count;
    }
};

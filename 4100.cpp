class Solution {
    long long _min_even_cost = LLONG_MAX;
    struct edge { int dst; long long cost; };

public:
    int minActivationCost(vector<vector<int>>& edges, vector<int>& values)
    {
        const int n = values.size();
        vector<vector<edge>> adj(n);
        for (auto& e : edges)
        {
            adj[e[0]].push_back(edge{e[1], e[2]});
            adj[e[1]].push_back(edge{e[0], e[2]});
        }

        min_odd_even_cost(0, -1, adj, values);

        return _min_even_cost == LLONG_MAX ? -1 : _min_even_cost;
    }

    bool is_bitwise_even(int x) const
    {
        bool even = true;
        while (x)
        {
            x = x & (x-1);
            even = !even;
        }
        return even;
    }

    pair<long long, long long> min_odd_even_cost(
        int node, int parent,
        const vector<vector<edge>>& adj,
        const vector<int>& values)
    {
        cout << "dfs for node=" << node << endl;

        const bool is_even = is_bitwise_even(values[node]);
        constexpr long long INF = LLONG_MAX;

        // even, odd := minimum-cost downward paths beginning at node
        long long even = is_even ? 0LL : INF;
        long long odd = !is_even ? 0LL : INF;

        for (const edge& child : adj[node])
        {
            if (child.dst == parent) { continue; }

            auto [odd_child, even_child] =
                min_odd_even_cost(child.dst, node, adj, values);

            if (even_child != INF)
            {
                even_child += child.cost;
            }
            if (odd_child != INF)
            {
                odd_child += child.cost;
            }

            // Combine paths BEFORE incorporating this child.
            if (even != INF && even_child != INF)
                _min_even_cost = min(_min_even_cost, even + even_child);

            if (odd != INF && odd_child != INF)
                _min_even_cost = min(_min_even_cost, odd + odd_child);

            // Update the costs of paths beginning at this node.
            if (is_even)
            {
                even = min(even, even_child);
                odd = min(odd, odd_child);
            }
            else
            {
                even = min(even, odd_child);
                odd = min(odd, even_child);
            }
        }

        return make_pair(odd, even);
    }
};

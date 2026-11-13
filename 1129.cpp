class Solution {

    static constexpr auto MAX_N = 100;
    array<array<bool,MAX_N>,MAX_N> _badj{};
    array<array<bool,MAX_N>,MAX_N> _radj{};

public:

    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) 
    {
        for (const auto& re : redEdges)
        {
            _radj[re[0]][re[1]] = true;
        }
        for (const auto& be : blueEdges)
        {
            _badj[be[0]][be[1]] = true;
        }

        deque<int> queue { 0 }; 
        unordered_set<int> visited; 
        vector<int> answer(n, -1);
        int dist = 0;

        while (queue.size())
        {
            const int sz = queue.size();

            for (int i = 0; i < sz; ++i)
            {
                const int node = queue.front();
                const int abs_node = std::abs(node);
                if (answer[abs_node] == -1)
                {
                    answer[abs_node] = dist;
                }

                // We took blue edge to node, so take red edge from node.
                if (node >= 0)
                {
                    for (int nbor = 0; nbor < n; ++nbor)
                    {
                        if (_radj[node][nbor] && !visited.contains(-nbor))
                        {
                            visited.insert(-nbor);
                            queue.push_back(-nbor);
                        }
                    }
                }

                // We took red edge to node, so take blue edge from node
                if (node <= 0) 
                {
                    for (int nbor = 0; nbor < n; ++nbor)
                    {
                        if (_badj[abs_node][nbor] && !visited.contains(nbor))
                        {
                            visited.insert(nbor);
                            queue.push_back(nbor);
                        }
                    }
                }

                queue.pop_front();
            }
            ++dist;
        }

        return answer;
    }
};

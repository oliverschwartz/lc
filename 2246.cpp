class Solution 
{
    int _max_path = 1; 

public:

    int longestPath(vector<int>& parent, string s) 
    {
        const int n = parent.size();
        vector<vector<int>> children(n);
        for (int node = 1; node < n; ++node)
        {
            children[parent[node]].push_back(node);
        }
        max_path(0, children, s);
        return _max_path;
    }

    
    int max_path(int node, const vector<vector<int>>& children, const string& s)
    {
        int max_child_path = 0;
        for (const int child : children[node])
        {
            const int child_path = max_path(child, children, s);
            if (s[node] != s[child])
            {
                _max_path = std::max(_max_path, max_child_path + child_path + 1);
                max_child_path = std::max(max_child_path, child_path);
            }
        }
        if (max_child_path == 0)
        {
            return 1;
        }
        else
        {
            return max_child_path + 1;
        }
    }
};

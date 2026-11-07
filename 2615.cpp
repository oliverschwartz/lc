class Solution {
public:
vector<long long> distance(const vector<int>& v)
{
    vector<long long> ret(v.size(), 0);

    struct elem { int last_idx; long long dist_sum; int count; };
    unordered_map<int, elem> m; 

    for (int i = 0; i < v.size(); ++i)
    {
        auto it = m.find(v[i]);
        if (it == m.end())
        {
            m[v[i]] = elem { i, 0, 1 };
        }
        else 
        {
            elem& e = it->second;
            ret[i] = e.dist_sum + (e.count) * static_cast<long long>(i - e.last_idx);
            ++e.count;
            e.last_idx = i; 
            e.dist_sum = ret[i];
        }
    }
    
    m.clear();
    for (int i = v.size() - 1; i >= 0; --i)
    {
        auto it = m.find(v[i]);
        if (it == m.end())
        {
            m[v[i]] = elem { i, 0, 1 };
        }
        else 
        {
            elem& e = it->second;
            const long long dist = e.dist_sum + (e.count) * static_cast<long long>(e.last_idx - i);
            ret[i] += dist;
            ++e.count;
            e.last_idx = i; 
            e.dist_sum = dist;
        }
    }

    return ret;
}
};

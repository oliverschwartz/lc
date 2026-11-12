class Solution {
    using adj_t = std::array<std::array<int, 26>,26>;
    adj_t _adj {};
    std::array<std::array<long long, 26>,26> _sps {};

public:

    long long sp_len(char src, char dst) // Dijkstra to compute SP tree from src
    {
        struct elem { char c; long long dist; };
        array<long long, 26> dist_to; 
        std::fill(dist_to.begin(), dist_to.end(), std::numeric_limits<long long>::max());
        dist_to[src-'a'] = 0;
        
        auto cmp = [](const elem& left, const elem& right) { 
            return left.dist > right.dist;
        };
        priority_queue<elem, vector<elem>, decltype(cmp)> heap(cmp);
        heap.push(elem{src, 0});

        while (!heap.empty())
        {
            elem top = heap.top();
            heap.pop();

            if (top.dist > dist_to[top.c-'a']) { continue; }
            else if (top.c == dst) { return top.dist; }

            for (char nbor = 0; nbor < 26; ++nbor)
            {
                if (_adj[top.c-'a'][nbor] > 0 && dist_to[nbor] > dist_to[top.c-'a'] + _adj[top.c-'a'][nbor])
                {
                    heap.push(elem{.c=static_cast<char>(nbor+'a'), .dist=dist_to[top.c-'a'] + _adj[top.c-'a'][nbor]});
                    dist_to[nbor] = dist_to[top.c-'a'] + _adj[top.c-'a'][nbor];
                }
            }
        }

        return -1;
    }

    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        for (auto i = 0; i < original.size(); ++i)
        {
            int& elem = _adj[original[i]-'a'][changed[i]-'a']; 
            elem = (elem == 0) ? cost[i] : std::min(elem, cost[i]);
        }

        // Precompute SP matrix.
        for (char src = 'a'; src <= 'z'; ++src)
        {
            for (char dst = 'a'; dst <= 'z'; ++dst)
            {
                if (src == dst) { continue; }
                _sps[src-'a'][dst-'a'] = sp_len(src, dst);
            }
        }

        long long acc = 0;
        for (auto i = 0; i < source.size(); ++i)
        {
            if (source[i] == target[i]) { continue; }

            const long long len = _sps[source[i]-'a'][target[i]-'a'];
            if (len == -1)
            {
                return -1;
            }
            else
            {
                acc += len;
            }
        }

        return acc;
    }
};

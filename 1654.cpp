class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        
        unordered_set<int> fbd;
        int M = x;
        for (auto f : forbidden)
        {
            fbd.insert(f);
            M = std::max(M, f);
        }

        struct state 
        { 
            int pos; 
            bool prev_was_back; 
            bool operator==(const state& other) const = default;
        };
        struct hasher
        {
            size_t operator()(const state& st) const
            {
                size_t hash = (st.pos << 1) | static_cast<unsigned>(st.prev_was_back);
                return hash;
            }
        };

        unordered_set<state, hasher> visited;
        deque<state> queue; 
        queue.push_back(state{0, false});
        visited.insert(queue.front());
        int jumps = 0;

        while (!queue.empty())
        {
            const int sz = queue.size();
            for (int i = 0; i < sz; ++i)
            {
                state s = queue.front();
                queue.pop_front();
                if (s.pos == x)
                {
                    return jumps;
                }
                else if (s.pos > M + b + a)
                {
                    continue;
                }

                int back = s.pos - b;
                int fwd = s.pos + a;

                if (!s.prev_was_back && back >= 0 && !visited.contains({back, true}) && !fbd.contains(back))
                {
                    visited.insert({back, true});
                    queue.push_back(state{back, true});
                }
                if (!fbd.contains(fwd) && !visited.contains({fwd, false}))
                {
                    visited.insert({fwd, false});
                    queue.push_back(state{s.pos + a, false});
                }
            }
            ++jumps;
        }

        return -1;
    }
};

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        
        // Sort intervals by smallest left endpoint first.
        std::sort(intervals.begin(), intervals.end(), [](const auto& i0, const auto& i1) { 
            return i0[0] < i1[0];
        }); 
        
        // Sort queries from smallest to largest.
        vector<int> indices(queries.size());
        std::iota(indices.begin(), indices.end(), 0);
        std::stable_sort(indices.begin(), indices.end(), 
            [&queries](int i, int j) { return queries[i] < queries[j]; });
        std::sort(queries.begin(), queries.end());

        // Heap with shortest interval at the top.
        auto cmp = [](const auto& i0, const auto& i1) {
            return i0[1] - i0[0] > i1[1] - i1[0];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> heap;

        vector<int> ret; 
        ret.resize(queries.size(), -1);

        int next_ival = 0;
        
        for (int i = 0; i < queries.size(); ++i)
        {
            const int q = queries[i];

            // Clear heap of intervals that don't overlap.
            while (heap.size() && heap.top()[1] < q)
            {
                heap.pop();
            }

            // Add overlapping intervals to heap.
            while (next_ival < intervals.size())
            {
                if (intervals[next_ival][0] > q)
                {
                    break;
                }
                if (intervals[next_ival][0] <= q && q <= intervals[next_ival][1])
                {
                    heap.push(intervals[next_ival]);
                }
                ++next_ival;
            }

            if (!heap.empty())
            {
                ret[indices[i]] = heap.top()[1] - heap.top()[0] + 1;
            }
        }

        return ret;
    }
};

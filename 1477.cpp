class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        const int n = arr.size();
        vector<int> pref(n); 
        vector<int> suff(n); 
        pref[0] = arr[0];
        suff[n-1] = arr[n-1];
        for (auto i = 1; i < n; ++i)
        {
            pref[i] = pref[i-1] + arr[i];
            suff[n-i-1] = suff[n-i] + arr[n-i-1];
        }
        
        vector<int> l_mins(n, INT_MAX); // l_mins[i] := min len of subarray in [0...i] that sums to target
        unordered_map<int,int> pref_to_index; 
        pref_to_index[0] = -1;
        for (int i = 0; i < n; ++i)
        {
            if (i > 0)
            {
                l_mins[i] = l_mins[i-1];
            }

            int other_pref = pref[i] - target;
            if (auto it = pref_to_index.find(other_pref); it != pref_to_index.end())
            {
                l_mins[i] = std::min(l_mins[i], i - it->second); 
            }
            pref_to_index[pref[i]] = i;
        }

        vector<int> r_mins(n, INT_MAX); // r_mins[i] := min len of subarray in [i...n-1] that sums to target
        unordered_map<int,int> suff_to_index; 
        suff_to_index[0] = n;
        for (int i = n-1; i >= 0; --i)
        {
            if (i < n-1)
            {
                r_mins[i] = r_mins[i + 1];
            }

            int other_suff = suff[i] - target;
            if (auto it = suff_to_index.find(other_suff); it != suff_to_index.end())
            {
                r_mins[i] = std::min(r_mins[i], it->second - i); 
            }
            suff_to_index[suff[i]] = i;
        }

        // Consider each possible split point in the array [L | R]. 
        // For each split, ask "what is the shortest subarray in each half that sums
        // to target?".
        int min_len_sum = INT_MAX;
        for (int i = 0; i < n-1; ++i)
        {
            int l_len = l_mins[i];
            int r_len = r_mins[i+1];
            if (l_len != INT_MAX && r_len != INT_MAX)
            {
                min_len_sum = std::min(min_len_sum, l_len + r_len);
            }
        }

        return min_len_sum == INT_MAX ? -1 : min_len_sum;
    }
};

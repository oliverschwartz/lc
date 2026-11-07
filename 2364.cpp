class Solution {
public:
    long long countBadPairs(vector<int>& nums) {
        const long long n = nums.size();
        unordered_map<int,int> offset_to_cnt; 
        long long good_pairs = 0;
        
        for (int i = 0; i < n; ++i)
        {
            int offset = i - nums[i];
            auto it = offset_to_cnt.find(offset);
            if (it == offset_to_cnt.end())
            {
                offset_to_cnt[offset] = 1;
            }
            else 
            {
                good_pairs += it->second; 
                ++it->second;
            }
        }

        return n * (n-1) / 2 - good_pairs;
    }
};

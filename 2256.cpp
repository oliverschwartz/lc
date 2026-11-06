class Solution {
public:
    int minimumAverageDifference(vector<int>& nums) {
        const int n = nums.size();
        vector<long long> pref(n); 
        pref[0] = nums[0];
        for (auto i = 1; i < n; ++i)
        {
            pref[i] = pref[i-1] + nums[i];
        }

        int best_idx = 0; 
        long long min_diff = INT_MAX;
        const long long total = pref.back();

        for (int i = 0; i < n; ++i)
        {
            long long lavg = pref[i] / (i+1); 
            long long ravg = (i + 1 == n) ? 0 : (total - pref[i]) / (n - (i + 1));
            long long diff = std::abs(lavg - ravg);
            if (diff < min_diff)
            {
                min_diff = diff; 
                best_idx = i;
            }
        }
        return best_idx;
    }
};

class Solution 
{
public:
    int maxSumMinProduct(vector<int>& nums) 
    {
        vector<long long> pref(nums.size(), 0);
        pref[0] = nums[0];
        for (size_t i = 1; i < nums.size(); ++i)
        {
            pref[i] = pref[i-1] + nums[i];
        }

        long long max_mprod = nums.front();
        struct elem { int index; int left_ext; };
        vector<elem> stack;

        auto process_elem = [&](int right_ext) {
            int left_ext = stack.back().left_ext;
            long long subarr_sum = pref[right_ext] - (left_ext == 0 ? 0 : pref[left_ext - 1]);
            max_mprod = std::max(max_mprod, static_cast<long long>(subarr_sum) * nums[stack.back().index]);
            stack.pop_back();
        };

        for (int i = 0; i < nums.size(); ++i)
        {
            const int val = nums[i];
            while (stack.size() && nums[stack.back().index] > val)
            {
                int right_ext = i - 1; 
                process_elem(right_ext);
            }

            if (stack.empty())
            {
                stack.push_back(elem{i, 0});
            }
            else if (nums[stack.back().index] == val)
            {
                stack.push_back(elem{i, stack.back().left_ext});
            }
            else
            {
                stack.push_back(elem{i, stack.back().index + 1});
            }
        }

        int right_ext = nums.size() - 1; 
        while (stack.size())
        {
            process_elem(right_ext);
        }

        return max_mprod % 1'000'000'007;
    }
};

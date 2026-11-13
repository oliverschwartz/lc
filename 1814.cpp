class Solution {
public:
    int reverse(int x)
    {
        int rev = 0; 
        while (x)
        {
            rev = rev * 10; 
            rev += x % 10; 
            x = x / 10;
        }
        return rev;
    }

    static constexpr int MOD = 1'000'000'007;

    int countNicePairs(vector<int>& nums) 
    {
        // Key insight: a + rev(b) = b + rev(a) can be rearranged as: a - rev(a) = b - rev(b)
        // Implicitly, what we are doing is: 
        // given input array [a,b,c,d,...], make an array of [a-rev(a),b-rev(b),...], 
        // count occurences of equal values. 
        unordered_map<int, int> cnts; 
        for (auto& n : nums)
        {
            const int revd = reverse(n);
            ++cnts[n - revd];
        }

        long long pairs = 0; 
        for (const auto& [_, count] : cnts)
        {
            pairs += (static_cast<long long>(count) * (count - 1) / 2) % MOD;
            pairs = pairs % MOD;
        }

        return pairs;
    }
};

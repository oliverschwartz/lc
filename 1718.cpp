class Solution 
{
    static constexpr int EMPTY = -1;
public:
    vector<int> constructDistancedSequence(int n) 
    {
        vector<int> v(2 * n - 1, EMPTY);
        uint32_t mask = 0; // ith bit == 1 means i has been placed
        fill(v, mask, n);
        return v;
    }

    bool fill(vector<int>& v, uint32_t mask, int n)
    {
        auto it = std::find(v.begin(), v.end(), EMPTY); 
        if (it == v.end())
        {
            return true;
        }

        for (int value = n; value >= 1; --value)
        {
            const uint32_t bit = 0x1 << value;
            if (bit & mask)
            {
                continue; // already placed
            }
            else if (value == 1)
            {
                *it = 1; 
                if (fill(v, mask | bit, n))
                {
                    return true;
                }
                *it = EMPTY;
            }
            else
            {
                int dist_to_end = std::distance(it, v.end());
                if (value < dist_to_end && *(it + value) == EMPTY)
                {
                    *it = value; 
                    *(it + value) = value;
                    if (fill(v, mask | bit, n))
                    {
                        return true;
                    }
                    *it = EMPTY; 
                    *(it + value) = EMPTY;
                }
            }
        }
        return false;
    }
};

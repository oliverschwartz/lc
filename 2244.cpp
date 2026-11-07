class Solution {
public:
    
    int num_rounds(int count)
    {
        if (count == 1)
        {
            return -1;
        }
        else if (count % 3 == 0)
        {
            return count / 3;
        }
        else
        {
            return count / 3 + 1;
        }
    }

    int minimumRounds(vector<int>& tasks) {
        unordered_map<int,int> fq; 
        for (int t : tasks)
        {
            ++fq[t];
        }

        int rounds = 0;
        for (const auto [_, freq] : fq)
        {
            int reqd = num_rounds(freq);
            if (reqd == -1)
            {
                return -1; 
            }
            rounds += reqd;
        }
        return rounds;
    }
};

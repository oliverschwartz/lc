class Solution {
public:
    int findMinimumTime(vector<vector<int>>& tasks) {
        constexpr int MAX_T = 2000;
        std::array<bool, MAX_T + 1> on {};

        // Sort by right endpoint. Break ties by putting task with longer duration first.
        std::sort(tasks.begin(), tasks.end(), [](const auto& t0, const auto& t1) { 
            if (t0[1] != t1[1]) { return t0[1] < t1[1]; }
            else { return t0[2] > t1[2]; }
        });

        int runtime = 0;
        for (const auto& task : tasks)
        {
            const int start = task[0];
            const int end = task[1];
            int dur = task[2];

            // See how much we have left to run.
            for (int t = start; t <= end && dur > 0; ++t)
            {
                if (on[t])
                {
                    --dur;
                }
            }

            // Greedily schedule remaining runtime at end of the interval.
            for (int t = end; t >= start && dur > 0; --t)
            {
                if (!on[t])
                {
                    on[t] = true;
                    --dur;
                    ++runtime;
                }
            }
        }

        return runtime;
    }
};

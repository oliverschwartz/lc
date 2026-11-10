class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        long long day = 1; 
        unordered_map<int, long long> task_starts; 
        for (int task : tasks)
        {
            auto it = task_starts.find(task); 
            if (it == task_starts.end())
            {
                task_starts[task] = day;
                ++day;
            }
            else
            {
                long long start = it->second; 
                if (day < start + space + 1)
                {
                    day = start + space + 1;
                }

                it->second = day; 
                ++day;
            }
        }
        return day-1; // subtract 1 as we advance the day to the next day after completion.
    }
};

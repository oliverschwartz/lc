class Solution {
public:
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {

        std::sort(buses.begin(), buses.end());
        std::sort(passengers.begin(), passengers.end());

        int waiting = 0; 
        int next_pidx = 0; 
        int latest = 1;
        int on_board = 0;

        for (const int dep_time : buses)
        {
            on_board = 0;

            // Load everyone on board.
            while (next_pidx < passengers.size() && on_board < capacity && passengers[next_pidx] <= dep_time)
            {
                ++next_pidx;
                ++on_board;
            }
        }

        // Once this loop terminates, passengers[next_pidx-1] is the arrival time of the last person to board.
        // If next_pidx == 0, no one boarded, so our candi
        if (next_pidx == 0)
        {
            return buses.back();
        }

        int pidx = next_pidx - 1;
        int arrival_time = on_board < capacity ? buses.back() : passengers[pidx];
        
        while (pidx >= 0 && arrival_time == passengers[pidx])
        {
            --arrival_time; 
            --pidx; 
        }

        return arrival_time;
    }
};

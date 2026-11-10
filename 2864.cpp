class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) {
        const int m = grid.size();
        const int n = grid.front().size();
        for (int i = 0; i < m; ++i)
        {
            grid[i][0] *= -1;
        }

        int col = 1; 
        while (true)
        {
            int cnt = 0;

            // See if we can reach col.
            for (int row = 0; row < m; ++row)
            {
                if (row - 1 >= 0 && grid[row-1][col-1] < 0 && std::abs(grid[row-1][col-1]) < grid[row][col])
                {
                    grid[row][col] *= -1;
                }
                else if (grid[row][col-1] < 0 && std::abs(grid[row][col-1]) < grid[row][col])
                {
                    grid[row][col] *= -1;
                }
                else if (row + 1 < m && grid[row+1][col-1] < 0 && std::abs(grid[row+1][col-1]) < grid[row][col])
                {
                    grid[row][col] *= -1;
                }
                cnt += static_cast<int>(grid[row][col] < 0);
            }

            if (cnt == 0)
            {
                return col - 1;
            }
            else if (col == n - 1)
            {
                return col;
            }
            ++col;
        }
    }
};

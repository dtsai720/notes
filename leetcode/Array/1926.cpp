#include <vector>
#include <queue>
#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    const vector<pair<int, int>> cursor{{0,1},{0,-1},{1,0},{-1,0}};
    
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        const int m = maze.size(), n = maze[0].size();

        int count = 0;
        queue<pair<int, int>> q;
        q.push({entrance[0], entrance[1]});
        maze[entrance[0]][entrance[1]] = '+';

        while (!q.empty()) {
            int size = q.size();

            while (size-- > 0) {
                pair<int, int> point = q.front(); q.pop();

                if ((point.first != entrance[0] || point.second != entrance[1]) &&
                    (point.first == 0 || point.first == m-1 || point.second == 0 || point.second == n-1)
                ) return count;

                for (auto& cur: cursor) {
                    int x = point.first + cur.first;
                    int y = point.second + cur.second;
                    if (x == -1 || x == m || y == -1 || y == n || maze[x][y] == '+') continue;
                    maze[x][y] = '+';
                    q.push({x, y});
                }
            }

            count++;
        }
        return -1;
    }
};

TEST(TestNearestExit, TestNearestExit1) {
    Solution solution = Solution();
    vector<vector<char>> maze{
        {'+','+','.','+'},
        {'.','.','.','+'},
        {'+','+','+','.'},
    };
    vector<int> entrance{1,2};
    ASSERT_EQ(1, solution.nearestExit(maze, entrance));
}

TEST(TestNearestExit, TestNearestExit2) {
    Solution solution = Solution();
    vector<vector<char>> maze{
        {'+','+','+'},
        {'.','.','.'},
        {'+','+','+'},
    };
    vector<int> entrance{1,0};
    ASSERT_EQ(2, solution.nearestExit(maze, entrance));
}

TEST(TestNearestExit, TestNearestExit3) {
    Solution solution = Solution();
    vector<vector<char>> maze{{'.','+'}};
    vector<int> entrance{0,0};
    ASSERT_EQ(-1, solution.nearestExit(maze, entrance));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
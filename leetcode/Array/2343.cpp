#include <string>
#include <vector>
#include <unordered_map>
#include <gtest/gtest.h>

class Solution {
public:
    std::vector<int> smallestTrimmedNumbers(std::vector<std::string> nums, std::vector<std::vector<int>> queries);
};

std::vector<int> Solution::smallestTrimmedNumbers(std::vector<std::string> nums, std::vector<std::vector<int>> queries) {
    const int m = nums.size();
    const int n = nums[0].length();
    std::vector<int> result;
    std::unordered_map<int, std::vector<std::pair<std::string, int>>> mymap;
    for (std::vector<int>& query: queries) {
        const int rank = query[0];
        const int size = query[1];
        if (mymap.count(size) > 0) {
            result.push_back(mymap[size][rank-1].second);
            continue;
        }
        std::vector<std::pair<std::string, int>> array(m);
        for (int i = 0; i < nums.size(); i++) {
            const std::string str = nums[i];
            array[i] = std::make_pair(str, i);
            if (n > size) array[i].first = str.substr(n-size);
        }
        sort(array.begin(), array.end(), [&](auto& a, auto& b) {
            if (a.first > b.first) return false;
            return a.first < b.first || a.second < b.second;
        });
        mymap[size] = array;
        result.push_back(mymap[size][rank-1].second);
    }
    return result;
}

TEST(TestSmallestTrimmedNumbers, example1) {
    Solution solution = Solution();
    std::vector<int> actual = solution.smallestTrimmedNumbers({"102","473","251","814"}, {{1,1},{2,3},{4,2},{1,2}});
    std::vector<int> want {2,2,1,0};
    ASSERT_EQ(want, actual);
}

TEST(TestSmallestTrimmedNumbers, example2) {
    Solution solution = Solution();
    std::vector<int> actual = solution.smallestTrimmedNumbers({"24","37","96","04"}, {{2,1},{2,2}});
    std::vector<int> want {3,0};
    ASSERT_EQ(want, actual);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
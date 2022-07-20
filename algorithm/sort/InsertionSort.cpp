#include <vector>
#include <gtest/gtest.h>

void InsertionSort(std::vector<int> &array) {
    for (int i = 1; i < array.size(); i++) {
        const int key = array[i];
        int j = i-1;
        while (j > -1 && key < array[j]) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = key;
    }
}

TEST(InsertionSortSuite, InsertionSort) {
    std::vector<int> array{5,4,3,1,2};
    InsertionSort(array);
    std::vector<int> want{1,2,3,4,5};
    ASSERT_EQ(array, want);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include <gtest/gtest.h>
#include "../src/Grid.cpp"

// Test for adding a random number
TEST(GridTest, AddRandomNumber) {
    Grid grid(4); // Initialize a 4x4 grid

    // Before adding a random number, there should be two non-zero cells
    int initialNonZeroCount = 0;
    for (const auto& row : grid.getGridData()) {
        for (int value : row) {
            if (value != 0) ++initialNonZeroCount;
        }
    }

    // Add a random number
    grid.addRandomNumber();

    // After adding a random number, there should be one more non-zero cell
    int finalNonZeroCount = 0;
    for (const auto& row : grid.getGridData()) {
        for (int value : row) {
            if (value != 0) ++finalNonZeroCount;
        }
    }

    EXPECT_EQ(finalNonZeroCount, initialNonZeroCount + 1);
}

// Test for checking if the grid is full
TEST(GridTest, IsGridFull) {
    Grid grid(4);

    // Fill the grid manually
    vector<vector<int>> fullGrid(4, vector<int>(4, 2)); // Fill with non-zero values
    grid.setGridData(fullGrid);

    EXPECT_TRUE(grid.isGridFull()); // Grid should be full now
}

// Test for movement and merging
TEST(GridTest, MoveAndMerge) {
    Grid grid(4);

    // Manually set up the grid with tiles that can be merged
    vector<vector<int>> testGrid = {
        {2, 2, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    grid.setGridData(testGrid);

    grid.move(0, 1); // Move right

    // After moving right, the merged tile should be at (0,3)
    EXPECT_EQ(grid.getTileValue(0, 3), 4);
    EXPECT_EQ(grid.getTileValue(0, 0), 0);
    EXPECT_EQ(grid.getTileValue(0, 1), 0);
    EXPECT_EQ(grid.getTileValue(0, 2), 0);
}

// Entry point for Google Test
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

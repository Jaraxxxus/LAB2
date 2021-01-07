#include "pch.h"
#include "gtest/gtest.h"
#include "\Users\RuIrina\source\repos\lab2\HeadLab2.h"
#include <fstream>



namespace {
    class GTest : public ::testing::Test {
    public:
        
        Command Game;
        
        
        std::string output1 = "output1.txt";
        std::string output2 = "output2.txt";
        std::string output3 = "output3.txt";
    };
}

bool compareTestFiles(std::string& fileName1, std::string& fileName2) {
    std::ifstream file1, file2;
    file1.open(fileName1);
    file2.open(fileName2);
    return std::equal(std::istreambuf_iterator<char>(file1.rdbuf()),
        std::istreambuf_iterator<char>(),
        std::istreambuf_iterator<char>(file2.rdbuf()));


}

void runSimpleTest(std::istringstream& input, Command& Game) {
    std::streambuf* backup1, * backup2;
    std::ofstream output;
    output.open("testOutput.txt");
    backup1 = std::cin.rdbuf();
    backup2 = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());
    std::cin.rdbuf(input.rdbuf());
    
    Game.playTest();
    


    std::cin.rdbuf(backup1);
    std::cout.rdbuf(backup2);
}








TEST_F(GTest, set) {
    std::istringstream input("setA0\n"
        "save" + output1 + "\n"
        "reset\n"
        "save" + output2 + "\n"
        "end\n");

    runSimpleTest(input, Game);
    ASSERT_FALSE(compareTestFiles(output1, output2));
}

TEST_F(GTest, clear) {
    std::istringstream input("setG7\n"
        "save" + output1 + "\n"
        "clearG7\n"
        "save" + output2 + "\n"
        "reset\n"
        "save" + output3 + "\n"
        "end\n");

    runSimpleTest(input, Game);
    EXPECT_FALSE(compareTestFiles(output1, output2));
    ASSERT_TRUE(compareTestFiles(output2, output3));
}

TEST_F(GTest, save_load) {
    std::istringstream input("setA0\n"
        "save" + output1 + "\n"
        "reset\n"
        "load" + output1 + "\n"
        "save" + output2 + "\n"
        "end\n");

    runSimpleTest(input, Game);
    ASSERT_TRUE(compareTestFiles(output1, output2));
}

TEST_F(GTest, back) {
    std::istringstream input("setB3\n"
        "setB4\n"
        "setB5\n"
        "save" + output1 + "\n"
        "step1\n"
        "save" + output2 + "\n"
        "back\n"
        "save" + output3 + "\n"
        "end\n");

    runSimpleTest(input, Game);
    EXPECT_FALSE(compareTestFiles(output1, output2));
    ASSERT_TRUE(compareTestFiles(output1, output3));
}

TEST_F(GTest, single_step) {
    std::istringstream input("setA0\n"
        "setA1\n"
        "setB1\n"
        "setC1\n"
        "save" + output1 + "\n"
        "step\n"
        "save" + output2 + "\n"
        "load" + output1 + "\n"
        "step1\n"
        "save" + output3 + "\n"
        "end\n");

    runSimpleTest(input, Game);
    ASSERT_FALSE(compareTestFiles(output1, output2));
    ASSERT_TRUE(compareTestFiles(output2, output3));
}



TEST_F(GTest, Optimal) {
    std::istringstream input("setD4\n"
        "setE3\n"
        "setE5\n"
        "setF4\n"
        "save" + output1 + "\n"
        "step1000\n"
        "save" + output2 + "\n"
        "step1\n"
        "save" + output3 + "\n"
        "end\n");

    runSimpleTest(input, Game);
    EXPECT_FALSE(compareTestFiles(output1, output2));
    ASSERT_FALSE(compareTestFiles(output1, output3));
}







int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    //testing::FLAGS_gtest_break_on_failure = "";
    return RUN_ALL_TESTS();
}
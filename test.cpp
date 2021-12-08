#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<
                "10 10\n"
                "1 61 126 217 2876 6127 39162 98126 712687 1000000000 \n"
                "100 6127 1 61 200 -10000 1 217 10000 1000000000 "
            ;
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();

    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    INFO(buffer.str());
    REQUIRE(buffer.str() ==
            "NO\n"
            "YES\n"
            "YES\n"
            "YES\n"
            "NO\n"
            "NO\n"
            "YES\n"
            "YES\n"
            "NO\n"
            "YES\n"
    );
}

TEST_CASE("test 2", ""){
    std::stringstream input(
            "10 10\n"
            "-8 -6 -4 -4 -2 -1 0 2 3 3 \n"
            "8 3 -3 -2 2 -1 2 9 -8 0 "
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
            "NO\n"
            "YES\n"
            "NO\n"
            "YES\n"
            "YES\n"
            "YES\n"
            "YES\n"
            "NO\n"
            "YES\n"
            "YES\n"
    );
}

TEST_CASE("test 3", ""){
    std::stringstream input(
            "10 5\n"
            "1 2 3 4 5 6 7 8 9 10 \n"
            "-2 0 4 9 12 "
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
            "NO\n"
            "NO\n"
            "YES\n"
            "YES\n"
            "NO\n"
    );
}

TEST_CASE("one element", ""){
    std::stringstream input(
            "1 5\n"
            "1\n"
            "-100 -1 0 1 200 "
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
            "NO\n"
            "NO\n"
            "NO\n"
            "YES\n"
            "NO\n"
    );
}

TEST_CASE("all same elements", ""){
    std::stringstream input(
            "5 5\n"
            "1 1 1 1 1\n"
            "-100 -1 0 1 200 "
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
            "NO\n"
            "NO\n"
            "NO\n"
            "YES\n"
            "NO\n"
    );
}

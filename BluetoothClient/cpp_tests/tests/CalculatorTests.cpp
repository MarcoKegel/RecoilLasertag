#define CATCH_CONFIG_MAIN
#include </usr/include/catch2/catch_all.hpp>
#include "../include/Calculator.h"

TEST_CASE("Calculator tests", "[calculator]") {
    Calculator calc;
    
    SECTION("addition") {
        REQUIRE(calc.add(2, 2) == 4);
        REQUIRE(calc.add(-1, 1) == 0);
    }
    
    SECTION("subtraction") {
        REQUIRE(calc.subtract(4, 2) == 2);
        REQUIRE(calc.subtract(1, 1) == 0);
    }
}
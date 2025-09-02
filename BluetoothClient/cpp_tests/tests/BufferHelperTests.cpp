#define CATCH_CONFIG_MAIN
#include </usr/include/catch2/catch_all.hpp>
#include "../include/BufferHelper.h"

TEST_CASE("BufferHelper tests", "[get]")
{

    uint8_t data[] = {
        0b00000100, // 4
        0b00001000, // 8
        0b00001111, // 15
        0b11111110  // 254
    };

    SECTION("read_8bit")
    {

        REQUIRE(BufferHelper::read_8bit(data, 0) == 4);
        REQUIRE(BufferHelper::read_8bit(data, 1) == 8);
        REQUIRE(BufferHelper::read_8bit(data, 2) == 15);
        REQUIRE(BufferHelper::read_8bit(data, 3) == 254);
    }

    // SECTION("subtraction") {
    //     REQUIRE(calc.subtract(4, 2) == 2);
    //     REQUIRE(calc.subtract(1, 1) == 0);
    // }
}
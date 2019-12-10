#include "flag_set.hpp"

#include "gtest/gtest.h"

#include <cstdint>

enum class Options : uint8_t {
    FULLSCREEN,
    INVERT_MOUSE,
    FLASH,
    RED_BACKGROUND,
    RED_FOREGROUND,
    _
};

TEST(flag_set, test_and)
{
    flag_set<Options> red(Options::RED_FOREGROUND | Options::RED_BACKGROUND);

    auto result = red & Options::RED_BACKGROUND;
    EXPECT_TRUE(result);
    EXPECT_EQ(result.count(), 1);

    result = red & Options::RED_FOREGROUND;
    EXPECT_TRUE(result);
    EXPECT_EQ(result.count(), 1);

    result = red & (Options::RED_FOREGROUND | Options::RED_BACKGROUND);
    EXPECT_TRUE(result);
    EXPECT_EQ(result.count(), 2);

    result = ~red & Options::RED_BACKGROUND;
    EXPECT_FALSE(result);
    EXPECT_EQ(result.count(), 0);

    flag_set<Options> red_foreground(Options::RED_FOREGROUND);
    red &= Options::RED_FOREGROUND;
    EXPECT_TRUE(red == red_foreground);
}

TEST(flag_set, test_or)
{
    flag_set<Options> red;
    red |= Options::RED_FOREGROUND | Options::RED_BACKGROUND;
    EXPECT_TRUE(red);
    EXPECT_EQ(red.count(), 2);

    flag_set<Options> options;
    options |= (Options::FULLSCREEN | Options::FLASH);

    auto result = options & (Options::FULLSCREEN | Options::FLASH | Options::RED_FOREGROUND);
    EXPECT_TRUE(result);

    flag_set<Options> expected;
    expected |= Options::FULLSCREEN;
    EXPECT_EQ(options & expected, expected);

    result = options & (Options::RED_FOREGROUND | Options::RED_BACKGROUND);
    EXPECT_FALSE(result);

    EXPECT_FALSE(options & red);

    EXPECT_TRUE(!(options & Options::INVERT_MOUSE));

    options |= ~red;

    EXPECT_TRUE(options & Options::INVERT_MOUSE);
}

TEST(flag_set, test_set_reset)
{
    flag_set<Options> options;
    EXPECT_EQ(options.count(), 0);

    options.set();
    EXPECT_EQ(options.count(), 5);
    EXPECT_EQ(options.size(), 5);
    EXPECT_EQ(options.to_string(), "11111");

    options.reset();
    EXPECT_EQ(options.count(), 0);

    options.set(Options::FLASH);
    EXPECT_EQ(options.count(), 1);
    EXPECT_TRUE(options[Options::FLASH]);

    options.set(Options::FLASH, false);
    EXPECT_EQ(options.count(), 0);

    options.set(Options::FLASH);
    options.set(Options::INVERT_MOUSE);
    EXPECT_EQ(options.count(), 2);
}

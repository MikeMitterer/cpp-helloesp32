//
// Created by Mike Mitterer on 02.11.15.
//

#include <regex>
#include <gtest/gtest.h>


TEST(basic_check_ma, split_url_test) {
    const std::string url = "https://google/2yC6KX";

    EXPECT_EQ(url[8],'g');
    EXPECT_EQ(url[8],0x67);

    EXPECT_EQ(url.length(),21);

    std::regex scheme("([^:]*)://(.*)", std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::smatch match;
    std::regex_search(url, match, scheme);

    EXPECT_EQ(match.size(),3);
    EXPECT_EQ("https",match.str(1));
    EXPECT_EQ("google/2yC6KX",match.str(2));
}


//
// 56
// 06
// 64
// 2e
// 46
// 41
// 50
// ec
// 02
// 65

// 00
// 00
// 00
// 00
// 00
// 01
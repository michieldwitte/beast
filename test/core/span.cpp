//
// Copyright (c) 2013-2017 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Test that header file is self-contained.
#include <beast/core/span.hpp>

#include <beast/unit_test/suite.hpp>

namespace beast {

class span_test : public beast::unit_test::suite
{
public:
    struct base {};
    struct derived : base {};

    BOOST_STATIC_ASSERT(detail::is_contiguous_container<
        std::vector<char>, char>::value);
    
    BOOST_STATIC_ASSERT(detail::is_contiguous_container<
        std::vector<char>, char const>::value);

    BOOST_STATIC_ASSERT(! detail::is_contiguous_container<
        std::vector<derived>, base>::value);

    BOOST_STATIC_ASSERT(! detail::is_contiguous_container<
        std::vector<derived>, base const>::value);

    void
    testSpan()
    {
        span<char const> sp{"hello", 5};
        BEAST_EXPECT(sp.size() == 5);
        std::string s("world");
        sp = s;
    }

    void
    run() override
    {
        testSpan();
    }
};

BEAST_DEFINE_TESTSUITE(span,core,beast);

} // beast
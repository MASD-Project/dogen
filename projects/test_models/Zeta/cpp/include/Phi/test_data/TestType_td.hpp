#ifndef PHI_TEST_DATA_TESTTYPE_TD_HPP
#define PHI_TEST_DATA_TESTTYPE_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "Phi/types/TestType.hpp"

namespace Phi {

class TestType_generator {
public:
    TestType_generator();

public:
    typedef Phi::TestType result_type;

public:
    static void populate(const unsigned int position, result_type& v);
    static result_type create(const unsigned int position);
    result_type operator()();

private:
    unsigned int position_;
public:
    static result_type* create_ptr(const unsigned int position);
};

}

#endif

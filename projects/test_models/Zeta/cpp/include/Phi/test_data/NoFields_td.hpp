#ifndef PHI_TEST_DATA_NOFIELDS_TD_HPP
#define PHI_TEST_DATA_NOFIELDS_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "Phi/types/NoFields.hpp"

namespace Phi {

class NoFields_generator {
public:
    NoFields_generator();

public:
    typedef Phi::NoFields result_type;

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

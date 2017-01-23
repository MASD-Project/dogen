#ifndef PHI_TEST_DATA_SOMEENUM_TD_HPP
#define PHI_TEST_DATA_SOMEENUM_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "Phi/types/SomeEnum.hpp"

namespace Phi {

class SomeEnum_generator {
public:
    SomeEnum_generator();

public:
    typedef Phi::SomeEnum result_type;

public:
    static void populate(const unsigned int position, result_type& v);
    static result_type create(const unsigned int position);
    result_type operator()();

private:
    unsigned int position_;
};

}

#endif

#ifndef ZETA_TEST_DATA_EXTERNALMODELTEST_TD_HPP
#define ZETA_TEST_DATA_EXTERNALMODELTEST_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "Zeta/types/ExternalModelTest.hpp"

namespace Zeta {

class ExternalModelTest_generator {
public:
    ExternalModelTest_generator();

public:
    typedef Zeta::ExternalModelTest result_type;

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

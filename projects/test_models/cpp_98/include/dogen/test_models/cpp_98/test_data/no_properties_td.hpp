#ifndef DOGEN_TEST_MODELS_CPP_98_TEST_DATA_NO_PROPERTIES_TD_HPP
#define DOGEN_TEST_MODELS_CPP_98_TEST_DATA_NO_PROPERTIES_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/cpp_98/types/no_properties.hpp"

namespace dogen {
namespace test_models {
namespace cpp_98 {

class no_properties_generator {
public:
    no_properties_generator();

public:
    typedef dogen::test_models::cpp_98::no_properties result_type;

public:
    static void populate(const unsigned int position, result_type& v);
    static result_type create(const unsigned int position);
    result_type operator()();

private:
    unsigned int position_;
public:
    static result_type* create_ptr(const unsigned int position);
};

} } }

#endif

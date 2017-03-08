#ifndef DOGEN_TEST_MODELS_SPLIT_PROJECT_TEST_DATA_PACKAGE1_FIRST_CLASS_TD_HPP
#define DOGEN_TEST_MODELS_SPLIT_PROJECT_TEST_DATA_PACKAGE1_FIRST_CLASS_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/split_project/types/package1/first_class.hpp"

namespace dogen {
namespace test_models {
namespace split_project {
namespace package1 {

class first_class_generator {
public:
    first_class_generator();

public:
    typedef dogen::test_models::split_project::package1::first_class result_type;

public:
    static void populate(const unsigned int position, result_type& v);
    static result_type create(const unsigned int position);
    result_type operator()();

private:
    unsigned int position_;
public:
    static result_type* create_ptr(const unsigned int position);
};

} } } }

#endif

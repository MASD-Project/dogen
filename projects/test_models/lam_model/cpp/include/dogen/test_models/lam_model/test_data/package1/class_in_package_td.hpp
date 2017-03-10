#ifndef DOGEN_TEST_MODELS_LAM_MODEL_TEST_DATA_PACKAGE1_CLASS_IN_PACKAGE_TD_HPP
#define DOGEN_TEST_MODELS_LAM_MODEL_TEST_DATA_PACKAGE1_CLASS_IN_PACKAGE_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/lam_model/types/package1/class_in_package.hpp"

namespace dogen {
namespace test_models {
namespace lam_model {
namespace package1 {

class class_in_package_generator {
public:
    class_in_package_generator();

public:
    typedef dogen::test_models::lam_model::package1::class_in_package result_type;

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

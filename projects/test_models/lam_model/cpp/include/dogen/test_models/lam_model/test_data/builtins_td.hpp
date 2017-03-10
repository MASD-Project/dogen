#ifndef DOGEN_TEST_MODELS_LAM_MODEL_TEST_DATA_BUILTINS_TD_HPP
#define DOGEN_TEST_MODELS_LAM_MODEL_TEST_DATA_BUILTINS_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/lam_model/types/builtins.hpp"

namespace dogen {
namespace test_models {
namespace lam_model {

class builtins_generator {
public:
    builtins_generator();

public:
    typedef dogen::test_models::lam_model::builtins result_type;

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

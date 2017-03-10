#ifndef DOGEN_TEST_MODELS_LAM_MODEL_HASH_PACKAGE1_CLASS_IN_PACKAGE_HASH_HPP
#define DOGEN_TEST_MODELS_LAM_MODEL_HASH_PACKAGE1_CLASS_IN_PACKAGE_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/test_models/lam_model/types/package1/class_in_package.hpp"

namespace dogen {
namespace test_models {
namespace lam_model {
namespace package1 {

struct class_in_package_hasher {
public:
    static std::size_t hash(const class_in_package& v);
};

} } } }

namespace std {

template<>
struct hash<dogen::test_models::lam_model::package1::class_in_package> {
public:
    size_t operator()(const dogen::test_models::lam_model::package1::class_in_package& v) const {
        return dogen::test_models::lam_model::package1::class_in_package_hasher::hash(v);
    }
};

}
#endif

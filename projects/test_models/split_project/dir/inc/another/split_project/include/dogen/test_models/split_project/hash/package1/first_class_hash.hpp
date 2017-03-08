#ifndef DOGEN_TEST_MODELS_SPLIT_PROJECT_HASH_PACKAGE1_FIRST_CLASS_HASH_HPP
#define DOGEN_TEST_MODELS_SPLIT_PROJECT_HASH_PACKAGE1_FIRST_CLASS_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/test_models/split_project/types/package1/first_class.hpp"

namespace dogen {
namespace test_models {
namespace split_project {
namespace package1 {

struct first_class_hasher {
public:
    static std::size_t hash(const first_class& v);
};

} } } }

namespace std {

template<>
struct hash<dogen::test_models::split_project::package1::first_class> {
public:
    size_t operator()(const dogen::test_models::split_project::package1::first_class& v) const {
        return dogen::test_models::split_project::package1::first_class_hasher::hash(v);
    }
};

}
#endif

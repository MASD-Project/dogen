#ifndef DOGEN_TEST_MODELS_LAM_MODEL_HASH_BUILTINS_HASH_HPP
#define DOGEN_TEST_MODELS_LAM_MODEL_HASH_BUILTINS_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/test_models/lam_model/types/builtins.hpp"

namespace dogen {
namespace test_models {
namespace lam_model {

struct builtins_hasher {
public:
    static std::size_t hash(const builtins& v);
};

} } }

namespace std {

template<>
struct hash<dogen::test_models::lam_model::builtins> {
public:
    size_t operator()(const dogen::test_models::lam_model::builtins& v) const {
        return dogen::test_models::lam_model::builtins_hasher::hash(v);
    }
};

}
#endif

#ifndef DOGEN_TEST_MODELS_LAM_MODEL_SERIALIZATION_BUILTINS_SER_HPP
#define DOGEN_TEST_MODELS_LAM_MODEL_SERIALIZATION_BUILTINS_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/split_free.hpp>
#include "dogen/test_models/lam_model/types/builtins.hpp"

BOOST_SERIALIZATION_SPLIT_FREE(dogen::test_models::lam_model::builtins)
namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar, const dogen::test_models::lam_model::builtins& v, unsigned int version);

template<typename Archive>
void load(Archive& ar, dogen::test_models::lam_model::builtins& v, unsigned int version);

} }

#endif

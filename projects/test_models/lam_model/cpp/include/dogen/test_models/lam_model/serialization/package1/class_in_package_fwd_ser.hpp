#ifndef DOGEN_TEST_MODELS_LAM_MODEL_SERIALIZATION_PACKAGE1_CLASS_IN_PACKAGE_FWD_SER_HPP
#define DOGEN_TEST_MODELS_LAM_MODEL_SERIALIZATION_PACKAGE1_CLASS_IN_PACKAGE_FWD_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/lam_model/types/package1/class_in_package_fwd.hpp"

namespace boost {
namespace serialization {

template<class Archive>
void save(Archive& ar, const dogen::test_models::lam_model::package1::class_in_package& v, unsigned int version);

template<class Archive>
void load(Archive& ar, dogen::test_models::lam_model::package1::class_in_package& v, unsigned int version);

} }

#endif

#ifndef DOGEN_TEST_MODELS_SPLIT_PROJECT_SERIALIZATION_PACKAGE1_FIRST_CLASS_FWD_SER_HPP
#define DOGEN_TEST_MODELS_SPLIT_PROJECT_SERIALIZATION_PACKAGE1_FIRST_CLASS_FWD_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/split_project/types/package1/first_class_fwd.hpp"

namespace boost {
namespace serialization {

template<class Archive>
void save(Archive& ar, const dogen::test_models::split_project::package1::first_class& v, unsigned int version);

template<class Archive>
void load(Archive& ar, dogen::test_models::split_project::package1::first_class& v, unsigned int version);

} }

#endif

#ifndef DOGEN_TEST_MODELS_CPP_98_SERIALIZATION_NO_PROPERTIES_FWD_SER_HPP
#define DOGEN_TEST_MODELS_CPP_98_SERIALIZATION_NO_PROPERTIES_FWD_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/cpp_98/types/no_properties_fwd.hpp"

namespace boost {
namespace serialization {

template<class Archive>
void save(Archive& ar, const dogen::test_models::cpp_98::no_properties& v, unsigned int version);

template<class Archive>
void load(Archive& ar, dogen::test_models::cpp_98::no_properties& v, unsigned int version);

} }

#endif

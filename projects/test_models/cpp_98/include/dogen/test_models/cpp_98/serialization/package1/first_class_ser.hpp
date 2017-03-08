#ifndef DOGEN_TEST_MODELS_CPP_98_SERIALIZATION_PACKAGE1_FIRST_CLASS_SER_HPP
#define DOGEN_TEST_MODELS_CPP_98_SERIALIZATION_PACKAGE1_FIRST_CLASS_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/split_free.hpp>
#include "dogen/test_models/cpp_98/types/package1/first_class.hpp"

BOOST_SERIALIZATION_SPLIT_FREE(dogen::test_models::cpp_98::package1::first_class)
namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar, const dogen::test_models::cpp_98::package1::first_class& v, unsigned int version);

template<typename Archive>
void load(Archive& ar, dogen::test_models::cpp_98::package1::first_class& v, unsigned int version);

} }

#endif

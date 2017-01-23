#ifndef ZETA_SERIALIZATION_EXTERNALMODELTEST_SER_HPP
#define ZETA_SERIALIZATION_EXTERNALMODELTEST_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/split_free.hpp>
#include "Zeta/types/ExternalModelTest.hpp"

BOOST_SERIALIZATION_SPLIT_FREE(Zeta::ExternalModelTest)
namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar, const Zeta::ExternalModelTest& v, unsigned int version);

template<typename Archive>
void load(Archive& ar, Zeta::ExternalModelTest& v, unsigned int version);

} }

#endif

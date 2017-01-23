#ifndef PHI_SERIALIZATION_COLLECTIONTESTTYPE_SER_HPP
#define PHI_SERIALIZATION_COLLECTIONTESTTYPE_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/split_free.hpp>
#include "Phi/types/CollectionTestType.hpp"

BOOST_SERIALIZATION_SPLIT_FREE(Phi::CollectionTestType)
namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar, const Phi::CollectionTestType& v, unsigned int version);

template<typename Archive>
void load(Archive& ar, Phi::CollectionTestType& v, unsigned int version);

} }

#endif

#ifndef PHI_SERIALIZATION_TESTTYPE_FWD_SER_HPP
#define PHI_SERIALIZATION_TESTTYPE_FWD_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "Phi/types/TestType_fwd.hpp"

namespace boost {
namespace serialization {

template<class Archive>
void save(Archive& ar, const Phi::TestType& v, unsigned int version);

template<class Archive>
void load(Archive& ar, Phi::TestType& v, unsigned int version);

} }

#endif

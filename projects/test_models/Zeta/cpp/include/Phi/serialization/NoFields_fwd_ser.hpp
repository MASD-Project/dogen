#ifndef PHI_SERIALIZATION_NOFIELDS_FWD_SER_HPP
#define PHI_SERIALIZATION_NOFIELDS_FWD_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "Phi/types/NoFields_fwd.hpp"

namespace boost {
namespace serialization {

template<class Archive>
void save(Archive& ar, const Phi::NoFields& v, unsigned int version);

template<class Archive>
void load(Archive& ar, Phi::NoFields& v, unsigned int version);

} }

#endif

#ifndef ZETA_SERIALIZATION_EXTERNALMODELTEST_FWD_SER_HPP
#define ZETA_SERIALIZATION_EXTERNALMODELTEST_FWD_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "Zeta/types/ExternalModelTest_fwd.hpp"

namespace boost {
namespace serialization {

template<class Archive>
void save(Archive& ar, const Zeta::ExternalModelTest& v, unsigned int version);

template<class Archive>
void load(Archive& ar, Zeta::ExternalModelTest& v, unsigned int version);

} }

#endif

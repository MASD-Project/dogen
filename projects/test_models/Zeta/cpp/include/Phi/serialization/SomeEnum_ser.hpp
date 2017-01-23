#ifndef PHI_SERIALIZATION_SOMEENUM_SER_HPP
#define PHI_SERIALIZATION_SOMEENUM_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/nvp.hpp>
#include "Phi/types/SomeEnum.hpp"

template<class Archive>
void serialize(Archive& ar, Phi::SomeEnum& v, unsigned int /*version*/){
    using boost::serialization::make_nvp;
    ar & make_nvp("SomeEnum", v);
}

#endif

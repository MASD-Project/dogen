#ifndef DOGEN_TEST_MODELS_CPP_98_SERIALIZATION_AN_ENUMERATION_SER_HPP
#define DOGEN_TEST_MODELS_CPP_98_SERIALIZATION_AN_ENUMERATION_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/nvp.hpp>
#include "dogen/test_models/cpp_98/types/an_enumeration.hpp"

template<class Archive>
void serialize(Archive& ar, dogen::test_models::cpp_98::an_enumeration& v, unsigned int /*version*/){
    using boost::serialization::make_nvp;
    ar & make_nvp("an_enumeration", v);
}

#endif

#ifndef DOGEN_TEST_MODELS_CPP_98_SERIALIZATION_CHILD_SER_HPP
#define DOGEN_TEST_MODELS_CPP_98_SERIALIZATION_CHILD_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/split_free.hpp>
#include <boost/type_traits/is_virtual_base_of.hpp>
#include "dogen/test_models/cpp_98/types/child.hpp"

namespace boost {

template<>struct
is_virtual_base_of<
    dogen::test_models::cpp_98::parent,
    dogen::test_models::cpp_98::child
> : public mpl::true_ {};

}

BOOST_SERIALIZATION_SPLIT_FREE(dogen::test_models::cpp_98::child)
namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar, const dogen::test_models::cpp_98::child& v, unsigned int version);

template<typename Archive>
void load(Archive& ar, dogen::test_models::cpp_98::child& v, unsigned int version);

} }

#endif

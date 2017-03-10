#ifndef DOGEN_TEST_MODELS_CPP_98_TYPES_NO_PROPERTIES_HPP
#define DOGEN_TEST_MODELS_CPP_98_TYPES_NO_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/cpp_98/serialization/no_properties_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_98 {

class no_properties {
public:
    no_properties();

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_98::no_properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_98::no_properties& v, unsigned int version);

public:
    bool operator==(const no_properties& rhs) const;
    bool operator!=(const no_properties& rhs) const {
        return !this->operator==(rhs);
    }

};

} } }

#endif

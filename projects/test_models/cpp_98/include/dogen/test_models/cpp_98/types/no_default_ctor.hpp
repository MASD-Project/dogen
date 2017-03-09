#ifndef DOGEN_TEST_MODELS_CPP_98_TYPES_NO_DEFAULT_CTOR_HPP
#define DOGEN_TEST_MODELS_CPP_98_TYPES_NO_DEFAULT_CTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/test_models/cpp_98/serialization/no_default_ctor_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_98 {

/**
 * @brief This class does not require a default constructor due to using simple types.
 */
class no_default_ctor {
public:
    no_default_ctor();

public:
    explicit no_default_ctor(const std::string& prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_98::no_default_ctor& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_98::no_default_ctor& v, unsigned int version);

public:
    const std::string& prop_0() const;
    std::string& prop_0();
    void prop_0(const std::string& v);

public:
    bool operator==(const no_default_ctor& rhs) const;
    bool operator!=(const no_default_ctor& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(no_default_ctor& other);
    no_default_ctor& operator=(no_default_ctor other);

private:
    std::string prop_0_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::cpp_98::no_default_ctor& lhs,
    dogen::test_models::cpp_98::no_default_ctor& rhs) {
    lhs.swap(rhs);
}

}

#endif

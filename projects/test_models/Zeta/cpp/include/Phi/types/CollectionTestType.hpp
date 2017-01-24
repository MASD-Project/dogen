#ifndef PHI_TYPES_COLLECTIONTESTTYPE_HPP
#define PHI_TYPES_COLLECTIONTESTTYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include "Phi/serialization/CollectionTestType_fwd_ser.hpp"

namespace Phi {

/**
 * @brief Test type
 */
class CollectionTestType final {
public:
    CollectionTestType() = default;
    CollectionTestType(const CollectionTestType&) = default;
    CollectionTestType(CollectionTestType&&) = default;
    ~CollectionTestType() = default;

public:
    explicit CollectionTestType(const std::vector<std::string>& BinariesTest);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const Phi::CollectionTestType& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, Phi::CollectionTestType& v, unsigned int version);

public:
    /**
     * @brief Some comment
     */
    /**@{*/
    const std::vector<std::string>& BinariesTest() const;
    std::vector<std::string>& BinariesTest();
    void BinariesTest(const std::vector<std::string>& v);
    void BinariesTest(const std::vector<std::string>&& v);
    /**@}*/

public:
    bool operator==(const CollectionTestType& rhs) const;
    bool operator!=(const CollectionTestType& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(CollectionTestType& other) noexcept;
    CollectionTestType& operator=(CollectionTestType other);

private:
    std::vector<std::string> BinariesTest_;
};

}

namespace std {

template<>
inline void swap(
    Phi::CollectionTestType& lhs,
    Phi::CollectionTestType& rhs) {
    lhs.swap(rhs);
}

}

#endif

#ifndef ZETA_TYPES_EXTERNALMODELTEST_HPP
#define ZETA_TYPES_EXTERNALMODELTEST_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "Phi/types/Date.hpp"
#include "Zeta/serialization/ExternalModelTest_fwd_ser.hpp"

namespace Zeta {

/**
 * @brief Test type
 */
class ExternalModelTest final {
public:
    ExternalModelTest(const ExternalModelTest&) = default;
    ExternalModelTest(ExternalModelTest&&) = default;
    ~ExternalModelTest() = default;

public:
    ExternalModelTest();

public:
    ExternalModelTest(
        const Phi::Date DateTest,
        const std::list<std::string>& BinariesTest,
        const std::list<std::list<std::string> >& CollectionOfCollectionTest,
        const std::list<std::list<std::list<std::string> > >& CollectionOfCollectionOfCollectionTest);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const Zeta::ExternalModelTest& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, Zeta::ExternalModelTest& v, unsigned int version);

public:
    /**
     * @brief Some comment
     */
    /**@{*/
    Phi::Date DateTest() const;
    void DateTest(const Phi::Date v);
    /**@}*/

    /**
     * @brief Some comment
     */
    /**@{*/
    const std::list<std::string>& BinariesTest() const;
    std::list<std::string>& BinariesTest();
    void BinariesTest(const std::list<std::string>& v);
    void BinariesTest(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Some comment
     */
    /**@{*/
    const std::list<std::list<std::string> >& CollectionOfCollectionTest() const;
    std::list<std::list<std::string> >& CollectionOfCollectionTest();
    void CollectionOfCollectionTest(const std::list<std::list<std::string> >& v);
    void CollectionOfCollectionTest(const std::list<std::list<std::string> >&& v);
    /**@}*/

    /**
     * @brief Some comment
     */
    /**@{*/
    const std::list<std::list<std::list<std::string> > >& CollectionOfCollectionOfCollectionTest() const;
    std::list<std::list<std::list<std::string> > >& CollectionOfCollectionOfCollectionTest();
    void CollectionOfCollectionOfCollectionTest(const std::list<std::list<std::list<std::string> > >& v);
    void CollectionOfCollectionOfCollectionTest(const std::list<std::list<std::list<std::string> > >&& v);
    /**@}*/

public:
    bool operator==(const ExternalModelTest& rhs) const;
    bool operator!=(const ExternalModelTest& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(ExternalModelTest& other) noexcept;
    ExternalModelTest& operator=(ExternalModelTest other);

private:
    Phi::Date DateTest_;
    std::list<std::string> BinariesTest_;
    std::list<std::list<std::string> > CollectionOfCollectionTest_;
    std::list<std::list<std::list<std::string> > > CollectionOfCollectionOfCollectionTest_;
};

}

namespace std {

template<>
inline void swap(
    Zeta::ExternalModelTest& lhs,
    Zeta::ExternalModelTest& rhs) {
    lhs.swap(rhs);
}

}

#endif

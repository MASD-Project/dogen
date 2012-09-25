/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_CLASS_WITHOUT_PACKAGE_DOMAIN_CLASS_1_HPP
#define DOGEN_CLASS_WITHOUT_PACKAGE_DOMAIN_CLASS_1_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/class_without_package/domain/versioned_key.hpp"

namespace dogen {
namespace class_without_package {

class class_1_serializer;

class class_1 {
public:
    class_1(const class_1&) = default;
    ~class_1() = default;
    class_1(class_1&&) = default;

public:
    class_1();

public:
    class_1(
        int an_attribute,
        dogen::class_without_package::versioned_key versioned_key);

public:
    friend class dogen::class_without_package::class_1_serializer;

public:
    void to_stream(std::ostream& stream) const;

public:
    int an_attribute() const {
        return an_attribute_;
    }

    void an_attribute(int value) {
        an_attribute_ = value;
    }

    dogen::class_without_package::versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(dogen::class_without_package::versioned_key value) {
        versioned_key_ = value;
    }

public:
    bool operator==(const class_1& rhs) const {
        return an_attribute_ == rhs.an_attribute_ &&
            versioned_key_ == rhs.versioned_key_;
    }

    bool operator!=(const class_1 rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_1& other);
    class_1& operator=(class_1 other);

private:
    int an_attribute_;
    dogen::class_without_package::versioned_key versioned_key_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::class_without_package::class_1& lhs,
    dogen::class_without_package::class_1& rhs) {
    lhs.swap(rhs);
}

}

#endif

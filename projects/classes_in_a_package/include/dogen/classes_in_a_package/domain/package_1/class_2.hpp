/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_CLASSES_IN_A_PACKAGE_DOMAIN_PACKAGE_1_CLASS_2_HPP
#define DOGEN_CLASSES_IN_A_PACKAGE_DOMAIN_PACKAGE_1_CLASS_2_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/classes_in_a_package/domain/versioned_key.hpp"

namespace dogen {
namespace classes_in_a_package {
namespace package_1 {

class class_2_serializer;

class class_2 {
public:
    class_2() = default;
    class_2(const class_2&) = default;
    ~class_2() = default;
    class_2(class_2&&) = default;

public:
    explicit class_2(dogen::classes_in_a_package::versioned_key versioned_key);

public:
    friend class dogen::classes_in_a_package::package_1::class_2_serializer;

public:
    void to_stream(std::ostream& stream) const;

public:
    dogen::classes_in_a_package::versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(dogen::classes_in_a_package::versioned_key value) {
        versioned_key_ = value;
    }

public:
    bool operator==(const class_2& rhs) const {
        return versioned_key_ == rhs.versioned_key_;
    }

    bool operator!=(const class_2 rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_2& other);
    class_2& operator=(class_2 other);

private:
    dogen::classes_in_a_package::versioned_key versioned_key_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::classes_in_a_package::package_1::class_2& lhs,
    dogen::classes_in_a_package::package_1::class_2& rhs) {
    lhs.swap(rhs);
}

}

#endif

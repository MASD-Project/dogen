/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_CLASSES_IN_A_PACKAGE_DOMAIN_PACKAGE_1_CLASS_4_HPP
#define DOGEN_CLASSES_IN_A_PACKAGE_DOMAIN_PACKAGE_1_CLASS_4_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/classes_in_a_package/domain/versioned_key.hpp"

namespace dogen {
namespace classes_in_a_package {
namespace package_1 {

class class_4_serializer;

class class_4 {
public:
    class_4() = default;
    class_4(const class_4&) = default;
    ~class_4() = default;
    class_4(class_4&&) = default;

public:
    explicit class_4(dogen::classes_in_a_package::versioned_key versioned_key);

public:
    friend class dogen::classes_in_a_package::package_1::class_4_serializer;

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
    bool operator==(const class_4& rhs) const {
        return versioned_key_ == rhs.versioned_key_;
    }

    bool operator!=(const class_4 rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_4& other);
    class_4& operator=(class_4 other);

private:
    dogen::classes_in_a_package::versioned_key versioned_key_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::classes_in_a_package::package_1::class_4& lhs,
    dogen::classes_in_a_package::package_1::class_4& rhs) {
    lhs.swap(rhs);
}

}

#endif

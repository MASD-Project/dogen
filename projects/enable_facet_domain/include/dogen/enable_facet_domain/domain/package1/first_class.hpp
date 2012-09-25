/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_ENABLE_FACET_DOMAIN_DOMAIN_PACKAGE1_FIRST_CLASS_HPP
#define DOGEN_ENABLE_FACET_DOMAIN_DOMAIN_PACKAGE1_FIRST_CLASS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/enable_facet_domain/domain/versioned_key.hpp"

namespace dogen {
namespace enable_facet_domain {
namespace package1 {

class first_class_serializer;

class first_class {
public:
    first_class(const first_class&) = default;
    ~first_class() = default;
    first_class(first_class&&) = default;

public:
    first_class();

public:
    first_class(
        int public_attribute,
        int private_attribute,
        dogen::enable_facet_domain::versioned_key versioned_key);

public:
    friend class dogen::enable_facet_domain::package1::first_class_serializer;

public:
    int public_attribute() const {
        return public_attribute_;
    }

    void public_attribute(int value) {
        public_attribute_ = value;
    }

    int private_attribute() const {
        return private_attribute_;
    }

    void private_attribute(int value) {
        private_attribute_ = value;
    }

    dogen::enable_facet_domain::versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(dogen::enable_facet_domain::versioned_key value) {
        versioned_key_ = value;
    }

public:
    bool operator==(const first_class& rhs) const {
        return public_attribute_ == rhs.public_attribute_ &&
            private_attribute_ == rhs.private_attribute_ &&
            versioned_key_ == rhs.versioned_key_;
    }

    bool operator!=(const first_class rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(first_class& other);
    first_class& operator=(first_class other);

private:
    int public_attribute_;
    int private_attribute_;
    dogen::enable_facet_domain::versioned_key versioned_key_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::enable_facet_domain::package1::first_class& lhs,
    dogen::enable_facet_domain::package1::first_class& rhs) {
    lhs.swap(rhs);
}

}

#endif

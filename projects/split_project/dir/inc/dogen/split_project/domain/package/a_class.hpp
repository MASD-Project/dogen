/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SPLIT_PROJECT_DOMAIN_PACKAGE_A_CLASS_HPP
#define DOGEN_SPLIT_PROJECT_DOMAIN_PACKAGE_A_CLASS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/split_project/domain/versioned_key.hpp"

namespace dogen {
namespace split_project {
namespace package {

class a_class_serializer;

class a_class {
public:
    a_class() = default;
    a_class(const a_class&) = default;
    ~a_class() = default;
    a_class(a_class&&) = default;

public:
    explicit a_class(dogen::split_project::versioned_key versioned_key);

public:
    friend class dogen::split_project::package::a_class_serializer;

public:
    void to_stream(std::ostream& stream) const;

public:
    dogen::split_project::versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(dogen::split_project::versioned_key value) {
        versioned_key_ = value;
    }

public:
    bool operator==(const a_class& rhs) const {
        return versioned_key_ == rhs.versioned_key_;
    }

    bool operator!=(const a_class rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(a_class& other);
    a_class& operator=(a_class other);

private:
    dogen::split_project::versioned_key versioned_key_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::split_project::package::a_class& lhs,
    dogen::split_project::package::a_class& rhs) {
    lhs.swap(rhs);
}

}

#endif

/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_DISABLE_COMPLETE_CONSTRUCTOR_DOMAIN_VERSIONED_KEY_HPP
#define DOGEN_DISABLE_COMPLETE_CONSTRUCTOR_DOMAIN_VERSIONED_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/disable_complete_constructor/domain/unversioned_key.hpp"

namespace dogen {
namespace disable_complete_constructor {

class versioned_key_serializer;

class versioned_key {
public:
    versioned_key(const versioned_key&) = default;
    ~versioned_key() = default;
    versioned_key(versioned_key&&) = default;

public:
    versioned_key();

public:
    friend class dogen::disable_complete_constructor::versioned_key_serializer;

public:
    void to_stream(std::ostream& stream) const;

public:
    unversioned_key to_unversioned() const;

public:
    unsigned int id() const {
        return id_;
    }

    void id(unsigned int value) {
        id_ = value;
    }

    unsigned int version() const {
        return version_;
    }

    void version(unsigned int value) {
        version_ = value;
    }

public:
    bool operator==(const versioned_key& rhs) const {
        return id_ == rhs.id_ &&
            version_ == rhs.version_;
    }

    bool operator!=(const versioned_key rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(versioned_key& other);
    versioned_key& operator=(versioned_key other);

private:
    unsigned int id_;
    unsigned int version_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::disable_complete_constructor::versioned_key& lhs,
    dogen::disable_complete_constructor::versioned_key& rhs) {
    lhs.swap(rhs);
}

}

#endif

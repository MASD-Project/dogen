/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_CPP_TYPES_CLASS_HEAD_HPP
#define DOGEN_CPP_TYPES_CLASS_HEAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include "dogen/cpp/serialization/class_head_fwd_ser.hpp"
#include "dogen/cpp/types/base_specifier.hpp"
#include "dogen/cpp/types/class_key_types.hpp"
#include "dogen/cpp/types/qualified_id.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Header of a class specifier.
 */
class class_head final {
public:
    class_head(const class_head&) = default;
    class_head(class_head&&) = default;
    ~class_head() = default;

public:
    class_head();

public:
    class_head(
        const dogen::cpp::class_key_types& key,
        const dogen::cpp::qualified_id& name,
        const std::list<dogen::cpp::base_specifier>& base_specifier_list,
        const bool is_final);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_head& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_head& v, unsigned int version);

public:
    dogen::cpp::class_key_types key() const;
    void key(const dogen::cpp::class_key_types& v);

    const dogen::cpp::qualified_id& name() const;
    dogen::cpp::qualified_id& name();
    void name(const dogen::cpp::qualified_id& v);
    void name(const dogen::cpp::qualified_id&& v);

    const std::list<dogen::cpp::base_specifier>& base_specifier_list() const;
    std::list<dogen::cpp::base_specifier>& base_specifier_list();
    void base_specifier_list(const std::list<dogen::cpp::base_specifier>& v);
    void base_specifier_list(const std::list<dogen::cpp::base_specifier>&& v);

    bool is_final() const;
    void is_final(const bool v);

public:
    bool operator==(const class_head& rhs) const;
    bool operator!=(const class_head& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_head& other) noexcept;
    class_head& operator=(class_head other);

private:
    dogen::cpp::class_key_types key_;
    dogen::cpp::qualified_id name_;
    std::list<dogen::cpp::base_specifier> base_specifier_list_;
    bool is_final_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::class_head& lhs,
    dogen::cpp::class_head& rhs) {
    lhs.swap(rhs);
}

}

#endif

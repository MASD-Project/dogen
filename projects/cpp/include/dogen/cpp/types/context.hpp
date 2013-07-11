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
#ifndef DOGEN_CPP_TYPES_CONTEXT_HPP
#define DOGEN_CPP_TYPES_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <unordered_map>
#include "dogen/cpp/serialization/context_fwd_ser.hpp"
#include "dogen/cpp/types/class_info.hpp"
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Provides a context for the transformation to take place.
 */
class context final {
public:
    context() = default;
    context(const context&) = default;
    context(context&&) = default;
    ~context() = default;

public:
    explicit context(const std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>& qname_to_class_info);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const context& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, context& v, unsigned int version);

public:
    /**
     * @brief Maps the processed class info to the source's qname.
     */
    /**@{*/
    const std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>& qname_to_class_info() const;
    std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>& qname_to_class_info();
    void qname_to_class_info(const std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>& v);
    void qname_to_class_info(const std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>&& v);
    /**@}*/

public:
    bool operator==(const context& rhs) const;
    bool operator!=(const context& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(context& other) noexcept;
    context& operator=(context other);

private:
    std::unordered_map<dogen::sml::qname, dogen::cpp::class_info> qname_to_class_info_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::context& lhs,
    dogen::cpp::context& rhs) {
    lhs.swap(rhs);
}

}

#endif

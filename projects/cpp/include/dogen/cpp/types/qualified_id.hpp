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
#ifndef DOGEN_CPP_TYPES_QUALIFIED_ID_HPP
#define DOGEN_CPP_TYPES_QUALIFIED_ID_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/cpp/serialization/qualified_id_fwd_ser.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Represents an identifier that is qualifiable.
 */
class qualified_id final {
public:
    qualified_id(const qualified_id&) = default;
    qualified_id(qualified_id&&) = default;
    ~qualified_id() = default;

public:
    qualified_id();

public:
    qualified_id(
        const std::string& unqualified_id,
        const std::list<std::string>& nested_name_specifier,
        const bool start_at_global_scope);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const qualified_id& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, qualified_id& v, unsigned int version);

public:
    /**
     * @brief Identifier that is not qualified.
     */
    /**@{*/
    const std::string& unqualified_id() const;
    std::string& unqualified_id();
    void unqualified_id(const std::string& v);
    void unqualified_id(const std::string&& v);
    /**@}*/

    const std::list<std::string>& nested_name_specifier() const;
    std::list<std::string>& nested_name_specifier();
    void nested_name_specifier(const std::list<std::string>& v);
    void nested_name_specifier(const std::list<std::string>&& v);

    bool start_at_global_scope() const;
    void start_at_global_scope(const bool v);

public:
    bool operator==(const qualified_id& rhs) const;
    bool operator!=(const qualified_id& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(qualified_id& other) noexcept;
    qualified_id& operator=(qualified_id other);

private:
    std::string unqualified_id_;
    std::list<std::string> nested_name_specifier_;
    bool start_at_global_scope_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::qualified_id& lhs,
    dogen::cpp::qualified_id& rhs) {
    lhs.swap(rhs);
}

}

#endif

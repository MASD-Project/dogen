/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_VISITED_TYPE_INFO_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_VISITED_TYPE_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/cpp/serialization/formattables/visited_type_info_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

class visited_type_info final {
public:
    visited_type_info() = default;
    visited_type_info(const visited_type_info&) = default;
    visited_type_info(visited_type_info&&) = default;
    ~visited_type_info() = default;

public:
    visited_type_info(
        const std::string& name,
        const std::string& qualified_name,
        const std::string& documentation);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const visited_type_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, visited_type_info& v, unsigned int version);

public:
    /**
     * @brief Name of the entity.
     *
     * Must be valid according to the rules for C++ names.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Fully qualified name of the entity.
     */
    /**@{*/
    const std::string& qualified_name() const;
    std::string& qualified_name();
    void qualified_name(const std::string& v);
    void qualified_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the programming language in question, e.g. Doxygen for C++, JavaDoc
     * for Java, etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

public:
    bool operator==(const visited_type_info& rhs) const;
    bool operator!=(const visited_type_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(visited_type_info& other) noexcept;
    visited_type_info& operator=(visited_type_info other);

private:
    std::string name_;
    std::string qualified_name_;
    std::string documentation_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::visited_type_info& lhs,
    dogen::cpp::formattables::visited_type_info& rhs) {
    lhs.swap(rhs);
}

}

#endif

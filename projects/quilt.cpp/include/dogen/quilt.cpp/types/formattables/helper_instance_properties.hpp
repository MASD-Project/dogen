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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_HELPER_INSTANCE_PROPERTIES_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_HELPER_INSTANCE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/quilt.cpp/serialization/formattables/helper_instance_properties_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class helper_instance_properties final {
public:
    helper_instance_properties() = default;
    helper_instance_properties(const helper_instance_properties&) = default;
    helper_instance_properties(helper_instance_properties&&) = default;
    ~helper_instance_properties() = default;

public:
    helper_instance_properties(
        const std::string& identifiable_name,
        const std::string& complete_name,
        const std::string& complete_name_identifiable_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const helper_instance_properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, helper_instance_properties& v, unsigned int version);

public:
    /**
     * @brief Representation of the nested tree that is usable as an identifier.
     *
     * Example: std_map_std_string_std_string.
     */
    /**@{*/
    const std::string& identifiable_name() const;
    std::string& identifiable_name();
    void identifiable_name(const std::string& v);
    void identifiable_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Qualified name of the helping target, using a C++ syntax.
     *
     * Example: std::map.
     */
    /**@{*/
    const std::string& complete_name() const;
    std::string& complete_name();
    void complete_name(const std::string& v);
    void complete_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Qualified name of the helping target, usable as an identifier.
     *
     * Example: std_map.
     */
    /**@{*/
    const std::string& complete_name_identifiable_name() const;
    std::string& complete_name_identifiable_name();
    void complete_name_identifiable_name(const std::string& v);
    void complete_name_identifiable_name(const std::string&& v);
    /**@}*/

public:
    bool operator==(const helper_instance_properties& rhs) const;
    bool operator!=(const helper_instance_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(helper_instance_properties& other) noexcept;
    helper_instance_properties& operator=(helper_instance_properties other);

private:
    std::string identifiable_name_;
    std::string complete_name_;
    std::string complete_name_identifiable_name_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::helper_instance_properties& lhs,
    dogen::quilt::cpp::formattables::helper_instance_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif

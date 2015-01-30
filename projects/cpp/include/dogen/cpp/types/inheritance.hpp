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
#ifndef DOGEN_CPP_TYPES_INHERITANCE_HPP
#define DOGEN_CPP_TYPES_INHERITANCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/cpp/serialization/inheritance_fwd_ser.hpp"
#include "dogen/cpp/types/parent_info.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Represents a C++ class.
 */
class inheritance final {
public:
    inheritance(const inheritance&) = default;
    inheritance(inheritance&&) = default;
    ~inheritance() = default;

public:
    inheritance();

public:
    inheritance(
        const std::list<dogen::cpp::parent_info>& parents,
        const bool is_parent,
        const std::string& original_parent_name,
        const std::string& original_parent_name_qualified,
        const std::list<std::string>& leaves,
        const bool is_final);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const inheritance& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, inheritance& v, unsigned int version);

public:
    /**
     * @brief Parents for this class.
     */
    /**@{*/
    const std::list<dogen::cpp::parent_info>& parents() const;
    std::list<dogen::cpp::parent_info>& parents();
    void parents(const std::list<dogen::cpp::parent_info>& v);
    void parents(const std::list<dogen::cpp::parent_info>&& v);
    /**@}*/

    /**
     * @brief True if this class is the parent of one or more classes,
     * false otherwise.
     */
    /**@{*/
    bool is_parent() const;
    void is_parent(const bool v);
    /**@}*/

    /**
     * @brief Parent at the root of a class hierarchy, if any.
     */
    /**@{*/
    const std::string& original_parent_name() const;
    std::string& original_parent_name();
    void original_parent_name(const std::string& v);
    void original_parent_name(const std::string&& v);
    /**@}*/

    /**
     * @brief Original parent name as a fully qualified name.
     */
    /**@{*/
    const std::string& original_parent_name_qualified() const;
    std::string& original_parent_name_qualified();
    void original_parent_name_qualified(const std::string& v);
    void original_parent_name_qualified(const std::string&& v);
    /**@}*/

    /**
     * @brief If the class is abstract, list of concrete types that
     * descend from it. Names are in identifiable name format.
     */
    /**@{*/
    const std::list<std::string>& leaves() const;
    std::list<std::string>& leaves();
    void leaves(const std::list<std::string>& v);
    void leaves(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief If true, the class cannot be inherited from.
     */
    /**@{*/
    bool is_final() const;
    void is_final(const bool v);
    /**@}*/

public:
    bool operator==(const inheritance& rhs) const;
    bool operator!=(const inheritance& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(inheritance& other) noexcept;
    inheritance& operator=(inheritance other);

private:
    std::list<dogen::cpp::parent_info> parents_;
    bool is_parent_;
    std::string original_parent_name_;
    std::string original_parent_name_qualified_;
    std::list<std::string> leaves_;
    bool is_final_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::inheritance& lhs,
    dogen::cpp::inheritance& rhs) {
    lhs.swap(rhs);
}

}

#endif

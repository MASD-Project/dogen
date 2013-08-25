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
#ifndef DOGEN_OM_TYPES_CPP_INSTANCE_TYPEREF_HPP
#define DOGEN_OM_TYPES_CPP_INSTANCE_TYPEREF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/om/serialization/cpp_instance_typeref_fwd_ser.hpp"
#include "dogen/om/types/cpp_memory_types.hpp"
#include "dogen/om/types/cpp_typeref.hpp"

namespace dogen {
namespace om {

/**
 * @brief Represents a "reference" to a C++ type for a variable or argument.
 */
class cpp_instance_typeref final {
public:
    cpp_instance_typeref(const cpp_instance_typeref&) = default;
    cpp_instance_typeref(cpp_instance_typeref&&) = default;
    ~cpp_instance_typeref() = default;

public:
    cpp_instance_typeref();

public:
    cpp_instance_typeref(
        const bool is_const,
        const bool start_at_global_scope,
        const std::list<std::string>& namespaces,
        const std::string& name,
        const std::list<dogen::om::cpp_typeref>& type_arguments,
        const dogen::om::cpp_memory_types& memory_type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_instance_typeref& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_instance_typeref& v, unsigned int version);

public:
    bool is_const() const;
    void is_const(const bool v);

    /**
     * @brief If true, the "reference" will start with the global scope qualifier.
     */
    /**@{*/
    bool start_at_global_scope() const;
    void start_at_global_scope(const bool v);
    /**@}*/

    const std::list<std::string>& namespaces() const;
    std::list<std::string>& namespaces();
    void namespaces(const std::list<std::string>& v);
    void namespaces(const std::list<std::string>&& v);

    /**
     * @brief Name of the type.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief If the referenced type is a template, a number of template arguments.
     */
    /**@{*/
    const std::list<dogen::om::cpp_typeref>& type_arguments() const;
    std::list<dogen::om::cpp_typeref>& type_arguments();
    void type_arguments(const std::list<dogen::om::cpp_typeref>& v);
    void type_arguments(const std::list<dogen::om::cpp_typeref>&& v);
    /**@}*/

    dogen::om::cpp_memory_types memory_type() const;
    void memory_type(const dogen::om::cpp_memory_types& v);

public:
    bool operator==(const cpp_instance_typeref& rhs) const;
    bool operator!=(const cpp_instance_typeref& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(cpp_instance_typeref& other) noexcept;
    cpp_instance_typeref& operator=(cpp_instance_typeref other);

private:
    bool is_const_;
    bool start_at_global_scope_;
    std::list<std::string> namespaces_;
    std::string name_;
    std::list<dogen::om::cpp_typeref> type_arguments_;
    dogen::om::cpp_memory_types memory_type_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cpp_instance_typeref& lhs,
    dogen::om::cpp_instance_typeref& rhs) {
    lhs.swap(rhs);
}

}

#endif

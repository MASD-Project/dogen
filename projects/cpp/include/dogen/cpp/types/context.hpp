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
#include "dogen/cpp/types/enum_info.hpp"
#include "dogen/cpp/types/exception_info.hpp"
#include "dogen/cpp/types/namespace_info.hpp"
#include "dogen/cpp/types/registrar_info.hpp"
#include "dogen/cpp/types/relationships.hpp"
#include "dogen/cpp/types/string_table_info.hpp"
#include "dogen/cpp/types/visitor_info.hpp"
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
    context(
        const std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>& classes,
        const std::unordered_map<dogen::sml::qname, dogen::cpp::relationships>& relationships,
        const std::unordered_map<dogen::sml::qname, dogen::cpp::exception_info>& exceptions,
        const std::unordered_map<dogen::sml::qname, dogen::cpp::enum_info>& enumerations,
        const std::unordered_map<dogen::sml::qname, dogen::cpp::registrar_info>& registrars,
        const std::unordered_map<dogen::sml::qname, dogen::cpp::namespace_info>& namespaces,
        const std::unordered_map<dogen::sml::qname, dogen::cpp::visitor_info>& visitors,
        const std::unordered_map<dogen::sml::qname, dogen::cpp::string_table_info>& string_tables);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const context& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, context& v, unsigned int version);

public:
    /**
     * @brief All the C++ classes, by qname.
     */
    /**@{*/
    const std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>& classes() const;
    std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>& classes();
    void classes(const std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>& v);
    void classes(const std::unordered_map<dogen::sml::qname, dogen::cpp::class_info>&& v);
    /**@}*/

    /**
     * @brief All the relationships, by qname.
     */
    /**@{*/
    const std::unordered_map<dogen::sml::qname, dogen::cpp::relationships>& relationships() const;
    std::unordered_map<dogen::sml::qname, dogen::cpp::relationships>& relationships();
    void relationships(const std::unordered_map<dogen::sml::qname, dogen::cpp::relationships>& v);
    void relationships(const std::unordered_map<dogen::sml::qname, dogen::cpp::relationships>&& v);
    /**@}*/

    /**
     * @brief All C++ exceptions.
     */
    /**@{*/
    const std::unordered_map<dogen::sml::qname, dogen::cpp::exception_info>& exceptions() const;
    std::unordered_map<dogen::sml::qname, dogen::cpp::exception_info>& exceptions();
    void exceptions(const std::unordered_map<dogen::sml::qname, dogen::cpp::exception_info>& v);
    void exceptions(const std::unordered_map<dogen::sml::qname, dogen::cpp::exception_info>&& v);
    /**@}*/

    /**
     * @brief All C++ enumerations.
     */
    /**@{*/
    const std::unordered_map<dogen::sml::qname, dogen::cpp::enum_info>& enumerations() const;
    std::unordered_map<dogen::sml::qname, dogen::cpp::enum_info>& enumerations();
    void enumerations(const std::unordered_map<dogen::sml::qname, dogen::cpp::enum_info>& v);
    void enumerations(const std::unordered_map<dogen::sml::qname, dogen::cpp::enum_info>&& v);
    /**@}*/

    /**
     * @brief The C++ registrar, if available.
     */
    /**@{*/
    const std::unordered_map<dogen::sml::qname, dogen::cpp::registrar_info>& registrars() const;
    std::unordered_map<dogen::sml::qname, dogen::cpp::registrar_info>& registrars();
    void registrars(const std::unordered_map<dogen::sml::qname, dogen::cpp::registrar_info>& v);
    void registrars(const std::unordered_map<dogen::sml::qname, dogen::cpp::registrar_info>&& v);
    /**@}*/

    /**
     * @brief All C++ namespaces.
     */
    /**@{*/
    const std::unordered_map<dogen::sml::qname, dogen::cpp::namespace_info>& namespaces() const;
    std::unordered_map<dogen::sml::qname, dogen::cpp::namespace_info>& namespaces();
    void namespaces(const std::unordered_map<dogen::sml::qname, dogen::cpp::namespace_info>& v);
    void namespaces(const std::unordered_map<dogen::sml::qname, dogen::cpp::namespace_info>&& v);
    /**@}*/

    /**
     * @brief All C++ visitors.
     */
    /**@{*/
    const std::unordered_map<dogen::sml::qname, dogen::cpp::visitor_info>& visitors() const;
    std::unordered_map<dogen::sml::qname, dogen::cpp::visitor_info>& visitors();
    void visitors(const std::unordered_map<dogen::sml::qname, dogen::cpp::visitor_info>& v);
    void visitors(const std::unordered_map<dogen::sml::qname, dogen::cpp::visitor_info>&& v);
    /**@}*/

    /**
     * @brief All C++ string tables.
     */
    /**@{*/
    const std::unordered_map<dogen::sml::qname, dogen::cpp::string_table_info>& string_tables() const;
    std::unordered_map<dogen::sml::qname, dogen::cpp::string_table_info>& string_tables();
    void string_tables(const std::unordered_map<dogen::sml::qname, dogen::cpp::string_table_info>& v);
    void string_tables(const std::unordered_map<dogen::sml::qname, dogen::cpp::string_table_info>&& v);
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
    std::unordered_map<dogen::sml::qname, dogen::cpp::class_info> classes_;
    std::unordered_map<dogen::sml::qname, dogen::cpp::relationships> relationships_;
    std::unordered_map<dogen::sml::qname, dogen::cpp::exception_info> exceptions_;
    std::unordered_map<dogen::sml::qname, dogen::cpp::enum_info> enumerations_;
    std::unordered_map<dogen::sml::qname, dogen::cpp::registrar_info> registrars_;
    std::unordered_map<dogen::sml::qname, dogen::cpp::namespace_info> namespaces_;
    std::unordered_map<dogen::sml::qname, dogen::cpp::visitor_info> visitors_;
    std::unordered_map<dogen::sml::qname, dogen::cpp::string_table_info> string_tables_;
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

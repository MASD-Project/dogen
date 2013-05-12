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
#ifndef DOGEN_CPP_TYPES_NAMESPACE_INFO_HPP
#define DOGEN_CPP_TYPES_NAMESPACE_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/cpp/serialization/namespace_info_fwd_ser.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Represents a C++ namespace.
 */
class namespace_info final {
public:
    namespace_info() = default;
    namespace_info(const namespace_info&) = default;
    namespace_info(namespace_info&&) = default;
    ~namespace_info() = default;

public:
    namespace_info(
        const std::list<std::string>& namespaces,
        const std::string& documentation);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const namespace_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, namespace_info& v, unsigned int version);

public:
    /**
     * @brief List of all namespaces. Last namespace is the target.
     */
    /**@{*/
    const std::list<std::string>& namespaces() const;
    std::list<std::string>& namespaces();
    void namespaces(const std::list<std::string>& v);
    void namespaces(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Documentation for the target namespace.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

public:
    bool operator==(const namespace_info& rhs) const;
    bool operator!=(const namespace_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(namespace_info& other) noexcept;
    namespace_info& operator=(namespace_info other);

private:
    std::list<std::string> namespaces_;
    std::string documentation_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::namespace_info& lhs,
    dogen::cpp::namespace_info& rhs) {
    lhs.swap(rhs);
}

}

#endif

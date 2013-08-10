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
#ifndef DOGEN_CPP_TYPES_ENUM_INFO_HPP
#define DOGEN_CPP_TYPES_ENUM_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <list>
#include <string>
#include "dogen/cpp/serialization/enum_info_fwd_ser.hpp"
#include "dogen/cpp/types/element_info.hpp"
#include "dogen/cpp/types/enumerator_info.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Represents a C++ enum.
 */
class enum_info final : public dogen::cpp::element_info {
public:
    enum_info() = default;
    enum_info(const enum_info&) = default;
    enum_info(enum_info&&) = default;

    virtual ~enum_info() noexcept { }

public:
    enum_info(
        const std::string& documentation,
        const std::string& name,
        const std::list<std::string>& namespaces,
        const std::list<dogen::cpp::enumerator_info>& enumerators,
        const std::string& type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const enum_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, enum_info& v, unsigned int version);

public:
    virtual void accept(const element_info_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(element_info_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const element_info_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(element_info_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

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
     * @brief Namespaces containing the type.
     */
    /**@{*/
    const std::list<std::string>& namespaces() const;
    std::list<std::string>& namespaces();
    void namespaces(const std::list<std::string>& v);
    void namespaces(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Valid values for the enumeration.
     */
    /**@{*/
    const std::list<dogen::cpp::enumerator_info>& enumerators() const;
    std::list<dogen::cpp::enumerator_info>& enumerators();
    void enumerators(const std::list<dogen::cpp::enumerator_info>& v);
    void enumerators(const std::list<dogen::cpp::enumerator_info>&& v);
    /**@}*/

    /**
     * @brief Underlying primitive type.
     */
    /**@{*/
    const std::string& type() const;
    std::string& type();
    void type(const std::string& v);
    void type(const std::string&& v);
    /**@}*/

public:
    bool operator==(const enum_info& rhs) const;
    bool operator!=(const enum_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::cpp::element_info& other) const override;

public:
    void swap(enum_info& other) noexcept;
    enum_info& operator=(enum_info other);

private:
    std::string name_;
    std::list<std::string> namespaces_;
    std::list<dogen::cpp::enumerator_info> enumerators_;
    std::string type_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::enum_info& lhs,
    dogen::cpp::enum_info& rhs) {
    lhs.swap(rhs);
}

}

#endif

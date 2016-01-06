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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_ENUM_INFO_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_ENUM_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen/cpp/types/formattables/entity.hpp"
#include "dogen/cpp/types/formattables/enumerator_info.hpp"
#include "dogen/cpp/serialization/formattables/enum_info_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Represents a C++ enum.
 */
class enum_info final : public dogen::cpp::formattables::entity {
public:
    enum_info() = default;
    enum_info(const enum_info&) = default;
    enum_info(enum_info&&) = default;

    virtual ~enum_info() noexcept { }

public:
    enum_info(
        const std::string& identity,
        const dogen::cpp::formattables::origin_types origin_type,
        const std::string& id,
        const std::string& name,
        const std::string& qualified_name,
        const std::string& documentation,
        const std::list<std::string>& namespaces,
        const std::list<dogen::cpp::formattables::enumerator_info>& enumerators,
        const std::string& type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const enum_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, enum_info& v, unsigned int version);

public:
    virtual void accept(const formattable_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(formattable_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const formattable_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(formattable_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Valid values for the enumeration.
     */
    /**@{*/
    const std::list<dogen::cpp::formattables::enumerator_info>& enumerators() const;
    std::list<dogen::cpp::formattables::enumerator_info>& enumerators();
    void enumerators(const std::list<dogen::cpp::formattables::enumerator_info>& v);
    void enumerators(const std::list<dogen::cpp::formattables::enumerator_info>&& v);
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
    bool equals(const dogen::cpp::formattables::formattable& other) const override;

public:
    void swap(enum_info& other) noexcept;
    enum_info& operator=(enum_info other);

private:
    std::list<dogen::cpp::formattables::enumerator_info> enumerators_;
    std::string type_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::enum_info& lhs,
    dogen::cpp::formattables::enum_info& rhs) {
    lhs.swap(rhs);
}

}

#endif

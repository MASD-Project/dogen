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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_FORWARD_DECLARATIONS_INFO_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_FORWARD_DECLARATIONS_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen/cpp/types/formattables/entity.hpp"
#include "dogen/cpp/serialization/formattables/forward_declarations_info_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

class forward_declarations_info final : public dogen::cpp::formattables::entity {
public:
    forward_declarations_info(const forward_declarations_info&) = default;
    forward_declarations_info(forward_declarations_info&&) = default;

public:
    forward_declarations_info();

    virtual ~forward_declarations_info() noexcept { }

public:
    forward_declarations_info(
        const std::string& identity,
        const dogen::cpp::formattables::origin_types origin_type,
        const std::string& name,
        const std::string& qualified_name,
        const std::string& documentation,
        const std::list<std::string>& namespaces,
        const dogen::cpp::settings::bundle& settings,
        const std::unordered_map<std::string, dogen::cpp::formattables::formatter_properties>& formatter_properties,
        const bool is_enum,
        const std::string& enum_type,
        const bool is_exception);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const forward_declarations_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, forward_declarations_info& v, unsigned int version);

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
     * @brief Returns true if the type for which we are creating a forward declaration is
     * an enumeration, false otherwise.
     */
    /**@{*/
    bool is_enum() const;
    void is_enum(const bool v);
    /**@}*/

    /**
     * @brief The underlying type of the enumeration, if we are an enum forward declaration.
     */
    /**@{*/
    const std::string& enum_type() const;
    std::string& enum_type();
    void enum_type(const std::string& v);
    void enum_type(const std::string&& v);
    /**@}*/

    bool is_exception() const;
    void is_exception(const bool v);

public:
    bool operator==(const forward_declarations_info& rhs) const;
    bool operator!=(const forward_declarations_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::cpp::formattables::formattable& other) const override;

public:
    void swap(forward_declarations_info& other) noexcept;
    forward_declarations_info& operator=(forward_declarations_info other);

private:
    bool is_enum_;
    std::string enum_type_;
    bool is_exception_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::forward_declarations_info& lhs,
    dogen::cpp::formattables::forward_declarations_info& rhs) {
    lhs.swap(rhs);
}

}

#endif

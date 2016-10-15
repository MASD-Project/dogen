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
#ifndef DOGEN_QUILT_CPP_TYPES_FABRIC_FORWARD_DECLARATIONS_HPP
#define DOGEN_QUILT_CPP_TYPES_FABRIC_FORWARD_DECLARATIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/quilt.cpp/serialization/fabric/forward_declarations_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

class forward_declarations final : public dogen::yarn::element {
public:
    forward_declarations(const forward_declarations&) = default;
    forward_declarations(forward_declarations&&) = default;

public:
    forward_declarations();

    virtual ~forward_declarations() noexcept { }

public:
    forward_declarations(
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::yarn::name& name,
        const dogen::yarn::origin_types origin_type,
        const boost::optional<dogen::yarn::name>& contained_by,
        const bool in_global_module,
        const std::vector<std::string>& stereotypes,
        const bool is_element_extension,
        const bool is_enum,
        const dogen::yarn::name& underlying_type,
        const bool is_exception);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::fabric::forward_declarations& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::fabric::forward_declarations& v, unsigned int version);

public:
    using dogen::yarn::element::accept;

    virtual void accept(const dogen::yarn::element_visitor& v) const override;
    virtual void accept(dogen::yarn::element_visitor& v) const override;
    virtual void accept(const dogen::yarn::element_visitor& v) override;
    virtual void accept(dogen::yarn::element_visitor& v) override;
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
    const dogen::yarn::name& underlying_type() const;
    dogen::yarn::name& underlying_type();
    void underlying_type(const dogen::yarn::name& v);
    void underlying_type(const dogen::yarn::name&& v);
    /**@}*/

    bool is_exception() const;
    void is_exception(const bool v);

public:
    bool operator==(const forward_declarations& rhs) const;
    bool operator!=(const forward_declarations& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::yarn::element& other) const override;

public:
    void swap(forward_declarations& other) noexcept;
    forward_declarations& operator=(forward_declarations other);

private:
    bool is_enum_;
    dogen::yarn::name underlying_type_;
    bool is_exception_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::fabric::forward_declarations& lhs,
    dogen::quilt::cpp::fabric::forward_declarations& rhs) {
    lhs.swap(rhs);
}

}

#endif

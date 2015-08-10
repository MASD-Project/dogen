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
#ifndef DOGEN_TACK_TYPES_ENUMERATION_HPP
#define DOGEN_TACK_TYPES_ENUMERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <vector>
#include <algorithm>
#include "dogen/tack/types/name.hpp"
#include "dogen/tack/types/type.hpp"
#include "dogen/tack/types/enumerator.hpp"
#include "dogen/tack/serialization/enumeration_fwd_ser.hpp"

namespace dogen {
namespace tack {

/**
 * @brief Defines a bounded set of logically related values for a primitive type or a string.
 */
class enumeration final : public dogen::tack::type {
public:
    enumeration() = default;
    enumeration(const enumeration&) = default;
    enumeration(enumeration&&) = default;

    virtual ~enumeration() noexcept { }

public:
    enumeration(
        const std::string& documentation,
        const dogen::dynamic::object& extensions,
        const dogen::tack::name& name,
        const dogen::tack::generation_types generation_type,
        const dogen::tack::origin_types origin_type,
        const boost::optional<dogen::tack::name>& containing_module,
        const dogen::tack::name& underlying_type,
        const std::vector<dogen::tack::enumerator>& enumerators);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const enumeration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, enumeration& v, unsigned int version);

public:
    virtual void accept(const type_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(type_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const type_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(type_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Underlying type of each instance of the enumeration.
     */
    /**@{*/
    const dogen::tack::name& underlying_type() const;
    dogen::tack::name& underlying_type();
    void underlying_type(const dogen::tack::name& v);
    void underlying_type(const dogen::tack::name&& v);
    /**@}*/

    /**
     * @brief Enumerators for this enumeration.
     */
    /**@{*/
    const std::vector<dogen::tack::enumerator>& enumerators() const;
    std::vector<dogen::tack::enumerator>& enumerators();
    void enumerators(const std::vector<dogen::tack::enumerator>& v);
    void enumerators(const std::vector<dogen::tack::enumerator>&& v);
    /**@}*/

public:
    bool operator==(const enumeration& rhs) const;
    bool operator!=(const enumeration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::tack::type& other) const override;

public:
    void swap(enumeration& other) noexcept;
    enumeration& operator=(enumeration other);

private:
    dogen::tack::name underlying_type_;
    std::vector<dogen::tack::enumerator> enumerators_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::tack::enumeration& lhs,
    dogen::tack::enumeration& rhs) {
    lhs.swap(rhs);
}

}

#endif

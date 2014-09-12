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
#ifndef DOGEN_SML_TYPES_ENUMERATION_HPP
#define DOGEN_SML_TYPES_ENUMERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <vector>
#include "dogen/sml/serialization/enumeration_fwd_ser.hpp"
#include "dogen/sml/types/enumerator.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/type.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Defines a bounded set of logically related values for a primitive type or a string.
 */
class enumeration final : public dogen::sml::type {
public:
    enumeration() = default;
    enumeration(const enumeration&) = default;
    enumeration(enumeration&&) = default;

    virtual ~enumeration() noexcept { }

public:
    enumeration(
        const std::string& documentation,
        const boost::property_tree::ptree& meta_data,
        const dogen::sml::qname& name,
        const dogen::sml::generation_types& generation_type,
        const dogen::sml::origin_types& origin_type,
        const dogen::sml::qname& parent_module,
        const dogen::sml::qname& underlying_type,
        const std::vector<dogen::sml::enumerator>& enumerators);

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
    const dogen::sml::qname& underlying_type() const;
    dogen::sml::qname& underlying_type();
    void underlying_type(const dogen::sml::qname& v);
    void underlying_type(const dogen::sml::qname&& v);
    /**@}*/

    /**
     * @brief Enumerators for this enumeration.
     */
    /**@{*/
    const std::vector<dogen::sml::enumerator>& enumerators() const;
    std::vector<dogen::sml::enumerator>& enumerators();
    void enumerators(const std::vector<dogen::sml::enumerator>& v);
    void enumerators(const std::vector<dogen::sml::enumerator>&& v);
    /**@}*/

public:
    bool operator==(const enumeration& rhs) const;
    bool operator!=(const enumeration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::sml::type& other) const override;

public:
    void swap(enumeration& other) noexcept;
    enumeration& operator=(enumeration other);

private:
    dogen::sml::qname underlying_type_;
    std::vector<dogen::sml::enumerator> enumerators_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::enumeration& lhs,
    dogen::sml::enumeration& rhs) {
    lhs.swap(rhs);
}

}

#endif

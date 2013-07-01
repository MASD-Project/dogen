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
#ifndef DOGEN_SML_TYPES_VALUE_OBJECT_HPP
#define DOGEN_SML_TYPES_VALUE_OBJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/sml/serialization/value_object_fwd_ser.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/type_visitor.hpp"
#include "dogen/sml/types/value_object_types.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Represents a descriptive aspect of the domain.
 *
 * A value (or value object) does not have an identity, but instead are used
 * to describe some aspect of the domain. For example colour is a value
 * object.
 */
class value_object final : public dogen::sml::abstract_object {
public:
    value_object(const value_object&) = default;
    value_object(value_object&&) = default;

public:
    value_object();

    virtual ~value_object() noexcept { }

public:
    value_object(
        const std::string& documentation,
        const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
        const dogen::sml::qname& name,
        const dogen::sml::generation_types& generation_type,
        const dogen::sml::origin_types& origin_type,
        const std::list<dogen::sml::property>& properties,
        const std::list<dogen::sml::operation>& operations,
        const boost::optional<dogen::sml::qname>& parent_name,
        const boost::optional<dogen::sml::qname>& original_parent_name,
        const std::list<dogen::sml::qname>& leaves,
        const bool is_parent,
        const unsigned int number_of_type_arguments,
        const bool is_visitable,
        const bool is_immutable,
        const bool is_versioned,
        const bool is_comparable,
        const bool is_fluent,
        const std::list<dogen::sml::qname>& modeled_concepts,
        const dogen::sml::value_object_types& type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const value_object& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, value_object& v, unsigned int version);

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
     * @brief Type of this value object.
     */
    /**@{*/
    dogen::sml::value_object_types type() const;
    void type(const dogen::sml::value_object_types& v);
    /**@}*/

public:
    bool operator==(const value_object& rhs) const;
    bool operator!=(const value_object& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::sml::type& other) const override;

public:
    void swap(value_object& other) noexcept;
    value_object& operator=(value_object other);

private:
    dogen::sml::value_object_types type_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::value_object& lhs,
    dogen::sml::value_object& rhs) {
    lhs.swap(rhs);
}

}

#endif

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
#ifndef DOGEN_SML_TYPES_ENTITY_HPP
#define DOGEN_SML_TYPES_ENTITY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/sml/serialization/entity_fwd_ser.hpp"
#include "dogen/sml/types/abstract_entity.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Concrete (instantiable) representation of an entity.
 */
class entity final : public dogen::sml::abstract_entity {
public:
    entity() = default;
    entity(const entity&) = default;
    entity(entity&&) = default;

    virtual ~entity() noexcept { }

public:
    entity(
        const dogen::sml::origin_types& origin_type,
        const std::string& documentation,
        const boost::property_tree::ptree& meta_data,
        const dogen::sml::qname& name,
        const dogen::sml::generation_types& generation_type,
        const std::list<dogen::sml::property>& all_properties,
        const std::list<dogen::sml::property>& local_properties,
        const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >& inherited_properties,
        const std::list<dogen::sml::operation>& operations,
        const bool is_parent,
        const unsigned int number_of_type_arguments,
        const bool is_visitable,
        const bool is_immutable,
        const bool is_versioned,
        const bool is_comparable,
        const bool is_fluent,
        const bool is_child,
        const std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> >& relationships,
        const bool is_inheritance_root,
        const bool is_aggregate_root,
        const std::list<dogen::sml::property>& identity);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const entity& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, entity& v, unsigned int version);

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
    bool operator==(const entity& rhs) const;
    bool operator!=(const entity& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::sml::type& other) const override;

public:
    void swap(entity& other) noexcept;
    entity& operator=(entity other);

};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::entity& lhs,
    dogen::sml::entity& rhs) {
    lhs.swap(rhs);
}

}

#endif

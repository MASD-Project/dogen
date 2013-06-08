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
#include <boost/optional.hpp>
#include <iosfwd>
#include "dogen/sml/serialization/entity_fwd_ser.hpp"
#include "dogen/sml/types/model_element_visitor.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/typed_element.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Represents a type in the domain which has identity.
 *
 * Identity here is understood in the strong sense, not just of the basic identity
 * provided by the programming language (e.g. unique memory address for the
 * object) but in a domain sense, such that this identity could be perserved
 * regardless of how the object was stored (e.g. persisted in a database).
 *
 * All entities have keys associated with them which are implementations of  the
 * identity function; they key could be a regular domain type such as a value, or it
 * could be a system generated type for this purpose. As with any typed element,
 * keys can be versioned or unversioned, depending on the versioning
 * requirements of the underlying typed element.
 */
class entity final : public dogen::sml::typed_element {
public:
    entity(const entity&) = default;

public:
    entity();

    virtual ~entity() noexcept { }

public:
    entity(entity&& rhs);

public:
    entity(
        const dogen::sml::qname& name,
        const std::string& documentation,
        const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
        const dogen::sml::generation_types& generation_type,
        const std::vector<dogen::sml::property>& properties,
        const boost::optional<dogen::sml::qname>& parent_name,
        const boost::optional<dogen::sml::qname>& original_parent_name,
        const std::list<dogen::sml::qname>& leaves,
        const unsigned int number_of_type_arguments,
        const bool is_parent,
        const bool is_visitable,
        const bool is_immutable,
        const bool is_versioned,
        const bool is_comparable,
        const bool is_fluent,
        const std::list<dogen::sml::qname>& modeled_concepts,
        const bool is_aggregate_root,
        const dogen::sml::qname& unversioned_key,
        const boost::optional<dogen::sml::qname>& versioned_key);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const entity& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, entity& v, unsigned int version);

public:
    virtual void accept(const model_element_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(model_element_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const model_element_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(model_element_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief If true, this type is a root of an aggregate.
     */
    /**@{*/
    bool is_aggregate_root() const;
    void is_aggregate_root(const bool v);
    /**@}*/

    /**
     * @brief Identity operation for the entity, without taking version into account.
     */
    /**@{*/
    const dogen::sml::qname& unversioned_key() const;
    dogen::sml::qname& unversioned_key();
    void unversioned_key(const dogen::sml::qname& v);
    void unversioned_key(const dogen::sml::qname&& v);
    /**@}*/

    /**
     * @brief If the type is a versioned keyed entity, its versioned key.
     */
    /**@{*/
    const boost::optional<dogen::sml::qname>& versioned_key() const;
    boost::optional<dogen::sml::qname>& versioned_key();
    void versioned_key(const boost::optional<dogen::sml::qname>& v);
    void versioned_key(const boost::optional<dogen::sml::qname>&& v);
    /**@}*/

public:
    bool operator==(const entity& rhs) const;
    bool operator!=(const entity& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::sml::model_element& other) const override;

public:
    void swap(entity& other) noexcept;
    entity& operator=(entity other);

private:
    bool is_aggregate_root_;
    dogen::sml::qname unversioned_key_;
    boost::optional<dogen::sml::qname> versioned_key_;
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

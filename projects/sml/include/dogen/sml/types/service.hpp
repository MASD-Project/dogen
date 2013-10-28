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
#ifndef DOGEN_SML_TYPES_SERVICE_HPP
#define DOGEN_SML_TYPES_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/sml/serialization/service_fwd_ser.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/service_types.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Type of model element that has behaviour but not necessarily other object properties.
 *
 * In traditional Domain Driven Design, a service is a set of operations that
 * conceptually do not belong to any specific object. In dogen, due to code
 * generation constraints, services tend to be where all the behaviour sits.
 */
class service final : public dogen::sml::abstract_object {
public:
    service(const service&) = default;
    service(service&&) = default;

public:
    service();

    virtual ~service() noexcept { }

public:
    service(
        const std::string& documentation,
        const boost::property_tree::ptree& meta_data,
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
        const dogen::sml::service_types& type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const service& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, service& v, unsigned int version);

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
     * @brief Type of the service.
     */
    /**@{*/
    dogen::sml::service_types type() const;
    void type(const dogen::sml::service_types& v);
    /**@}*/

public:
    bool operator==(const service& rhs) const;
    bool operator!=(const service& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::sml::type& other) const override;

public:
    void swap(service& other) noexcept;
    service& operator=(service other);

private:
    dogen::sml::service_types type_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::service& lhs,
    dogen::sml::service& rhs) {
    lhs.swap(rhs);
}

}

#endif

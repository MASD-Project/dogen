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
#ifndef DOGEN_SML_TYPES_FACTORY_HPP
#define DOGEN_SML_TYPES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/sml/serialization/factory_fwd_ser.hpp"
#include "dogen/sml/types/model_element_visitor.hpp"
#include "dogen/sml/types/typed_element.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Type whose responsibility is to create other types.
 */
class factory final : public dogen::sml::typed_element {
public:
    factory() = default;
    factory(const factory&) = default;
    factory(factory&&) = default;

    virtual ~factory() noexcept { }

public:
    factory(
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
        const std::list<dogen::sml::qname>& modeled_concepts);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const factory& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, factory& v, unsigned int version);

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
    bool operator==(const factory& rhs) const;
    bool operator!=(const factory& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::sml::model_element& other) const override;

public:
    void swap(factory& other) noexcept;
    factory& operator=(factory other);

};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::factory& lhs,
    dogen::sml::factory& rhs) {
    lhs.swap(rhs);
}

}

#endif

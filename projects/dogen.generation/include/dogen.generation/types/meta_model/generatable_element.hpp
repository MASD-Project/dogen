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
#ifndef DOGEN_GENERATION_TYPES_META_MODEL_GENERATABLE_ELEMENT_HPP
#define DOGEN_GENERATION_TYPES_META_MODEL_GENERATABLE_ELEMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.modeling/types/meta_model/element_fwd.hpp"
#include "dogen.formatting/types/decoration_properties.hpp"
#include "dogen.generation/types/meta_model/artefact_properties.hpp"
#include "dogen.generation/serialization/meta_model/generatable_element_fwd_ser.hpp"
#include "dogen.generation/types/meta_model/local_archetype_location_properties.hpp"

namespace dogen {
namespace generation {
namespace meta_model {

class generatable_element final {
public:
    generatable_element() = default;
    generatable_element(const generatable_element&) = default;
    generatable_element(generatable_element&&) = default;
    ~generatable_element() = default;

public:
    generatable_element(
        const boost::shared_ptr<dogen::modeling::meta_model::element>& modeling_element,
        const dogen::formatting::decoration_properties& decoration_properties,
        const std::unordered_map<std::string, dogen::generation::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::generation::meta_model::local_archetype_location_properties>& archetype_location_properties);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::generation::meta_model::generatable_element& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::generation::meta_model::generatable_element& v, unsigned int version);

public:
    const boost::shared_ptr<dogen::modeling::meta_model::element>& modeling_element() const;
    boost::shared_ptr<dogen::modeling::meta_model::element>& modeling_element();
    void modeling_element(const boost::shared_ptr<dogen::modeling::meta_model::element>& v);
    void modeling_element(const boost::shared_ptr<dogen::modeling::meta_model::element>&& v);

    const dogen::formatting::decoration_properties& decoration_properties() const;
    dogen::formatting::decoration_properties& decoration_properties();
    void decoration_properties(const dogen::formatting::decoration_properties& v);
    void decoration_properties(const dogen::formatting::decoration_properties&& v);

    const std::unordered_map<std::string, dogen::generation::meta_model::artefact_properties>& artefact_properties() const;
    std::unordered_map<std::string, dogen::generation::meta_model::artefact_properties>& artefact_properties();
    void artefact_properties(const std::unordered_map<std::string, dogen::generation::meta_model::artefact_properties>& v);
    void artefact_properties(const std::unordered_map<std::string, dogen::generation::meta_model::artefact_properties>&& v);

    const std::unordered_map<std::string, dogen::generation::meta_model::local_archetype_location_properties>& archetype_location_properties() const;
    std::unordered_map<std::string, dogen::generation::meta_model::local_archetype_location_properties>& archetype_location_properties();
    void archetype_location_properties(const std::unordered_map<std::string, dogen::generation::meta_model::local_archetype_location_properties>& v);
    void archetype_location_properties(const std::unordered_map<std::string, dogen::generation::meta_model::local_archetype_location_properties>&& v);

public:
    bool operator==(const generatable_element& rhs) const;
    bool operator!=(const generatable_element& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(generatable_element& other) noexcept;
    generatable_element& operator=(generatable_element other);

private:
    boost::shared_ptr<dogen::modeling::meta_model::element> modeling_element_;
    dogen::formatting::decoration_properties decoration_properties_;
    std::unordered_map<std::string, dogen::generation::meta_model::artefact_properties> artefact_properties_;
    std::unordered_map<std::string, dogen::generation::meta_model::local_archetype_location_properties> archetype_location_properties_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::generation::meta_model::generatable_element& lhs,
    dogen::generation::meta_model::generatable_element& rhs) {
    lhs.swap(rhs);
}

}

#endif

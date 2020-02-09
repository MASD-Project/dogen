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
#ifndef DOGEN_GENERATION_CSHARP_TYPES_FABRIC_ASSISTANT_HPP
#define DOGEN_GENERATION_CSHARP_TYPES_FABRIC_ASSISTANT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen.assets/types/meta_model/element.hpp"

namespace dogen::generation::csharp::fabric {

class assistant final : public dogen::assets::meta_model::element {
public:
    assistant() = default;
    assistant(const assistant&) = default;
    assistant(assistant&&) = default;

    virtual ~assistant() noexcept { }

public:
    assistant(
        const dogen::assets::meta_model::name& name,
        const std::string& documentation,
        const dogen::assets::meta_model::origin_types origin_type,
        const std::string& origin_sha1_hash,
        const std::string& origin_element_id,
        const std::string& contained_by,
        const bool in_global_module,
        const std::list<dogen::assets::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const dogen::assets::meta_model::name& meta_name,
        const dogen::assets::meta_model::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
        const bool is_element_extension,
        const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const std::unordered_map<dogen::assets::meta_model::technical_space, boost::optional<dogen::assets::meta_model::decoration::element_properties> >& decoration);

public:
    using dogen::assets::meta_model::element::accept;

    virtual void accept(const dogen::assets::meta_model::element_visitor& v) const override;
    virtual void accept(dogen::assets::meta_model::element_visitor& v) const override;
    virtual void accept(const dogen::assets::meta_model::element_visitor& v) override;
    virtual void accept(dogen::assets::meta_model::element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const assistant& rhs) const;
    bool operator!=(const assistant& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::assets::meta_model::element& other) const override;

public:
    void swap(assistant& other) noexcept;
    assistant& operator=(assistant other);

};

}

namespace std {

template<>
inline void swap(
    dogen::generation::csharp::fabric::assistant& lhs,
    dogen::generation::csharp::fabric::assistant& rhs) {
    lhs.swap(rhs);
}

}

#endif

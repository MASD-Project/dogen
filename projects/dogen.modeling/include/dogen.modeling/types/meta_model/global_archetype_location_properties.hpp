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
#ifndef DOGEN_YARN_TYPES_META_MODEL_GLOBAL_ARCHETYPE_LOCATION_PROPERTIES_HPP
#define DOGEN_YARN_TYPES_META_MODEL_GLOBAL_ARCHETYPE_LOCATION_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.modeling/types/meta_model/facet_properties.hpp"
#include "dogen.modeling/types/meta_model/backend_properties.hpp"
#include "dogen.modeling/types/meta_model/archetype_properties.hpp"
#include "dogen.modeling/types/meta_model/denormalised_archetype_properties.hpp"
#include "dogen.modeling/serialization/meta_model/global_archetype_location_properties_fwd_ser.hpp"

namespace dogen {
namespace modeling {
namespace meta_model {

class global_archetype_location_properties final {
public:
    global_archetype_location_properties() = default;
    global_archetype_location_properties(const global_archetype_location_properties&) = default;
    global_archetype_location_properties(global_archetype_location_properties&&) = default;
    ~global_archetype_location_properties() = default;

public:
    global_archetype_location_properties(
        const std::unordered_map<std::string, dogen::modeling::meta_model::backend_properties>& backend_properties,
        const std::unordered_map<std::string, dogen::modeling::meta_model::facet_properties>& facet_properties,
        const std::unordered_map<std::string, dogen::modeling::meta_model::archetype_properties>& archetype_properties,
        const std::unordered_map<std::string, dogen::modeling::meta_model::denormalised_archetype_properties>& denormalised_archetype_properties);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::modeling::meta_model::global_archetype_location_properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::modeling::meta_model::global_archetype_location_properties& v, unsigned int version);

public:
    const std::unordered_map<std::string, dogen::modeling::meta_model::backend_properties>& backend_properties() const;
    std::unordered_map<std::string, dogen::modeling::meta_model::backend_properties>& backend_properties();
    void backend_properties(const std::unordered_map<std::string, dogen::modeling::meta_model::backend_properties>& v);
    void backend_properties(const std::unordered_map<std::string, dogen::modeling::meta_model::backend_properties>&& v);

    const std::unordered_map<std::string, dogen::modeling::meta_model::facet_properties>& facet_properties() const;
    std::unordered_map<std::string, dogen::modeling::meta_model::facet_properties>& facet_properties();
    void facet_properties(const std::unordered_map<std::string, dogen::modeling::meta_model::facet_properties>& v);
    void facet_properties(const std::unordered_map<std::string, dogen::modeling::meta_model::facet_properties>&& v);

    const std::unordered_map<std::string, dogen::modeling::meta_model::archetype_properties>& archetype_properties() const;
    std::unordered_map<std::string, dogen::modeling::meta_model::archetype_properties>& archetype_properties();
    void archetype_properties(const std::unordered_map<std::string, dogen::modeling::meta_model::archetype_properties>& v);
    void archetype_properties(const std::unordered_map<std::string, dogen::modeling::meta_model::archetype_properties>&& v);

    const std::unordered_map<std::string, dogen::modeling::meta_model::denormalised_archetype_properties>& denormalised_archetype_properties() const;
    std::unordered_map<std::string, dogen::modeling::meta_model::denormalised_archetype_properties>& denormalised_archetype_properties();
    void denormalised_archetype_properties(const std::unordered_map<std::string, dogen::modeling::meta_model::denormalised_archetype_properties>& v);
    void denormalised_archetype_properties(const std::unordered_map<std::string, dogen::modeling::meta_model::denormalised_archetype_properties>&& v);

public:
    bool operator==(const global_archetype_location_properties& rhs) const;
    bool operator!=(const global_archetype_location_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(global_archetype_location_properties& other) noexcept;
    global_archetype_location_properties& operator=(global_archetype_location_properties other);

private:
    std::unordered_map<std::string, dogen::modeling::meta_model::backend_properties> backend_properties_;
    std::unordered_map<std::string, dogen::modeling::meta_model::facet_properties> facet_properties_;
    std::unordered_map<std::string, dogen::modeling::meta_model::archetype_properties> archetype_properties_;
    std::unordered_map<std::string, dogen::modeling::meta_model::denormalised_archetype_properties> denormalised_archetype_properties_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::modeling::meta_model::global_archetype_location_properties& lhs,
    dogen::modeling::meta_model::global_archetype_location_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif

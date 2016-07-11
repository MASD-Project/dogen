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
#ifndef DOGEN_QUILT_CPP_TYPES_PROPERTIES_HELPER_PROPERTIES_FACTORY_HPP
#define DOGEN_QUILT_CPP_TYPES_PROPERTIES_HELPER_PROPERTIES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include <boost/optional.hpp>
#include "dogen/yarn/types/attribute.hpp"
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/quilt.cpp/types/properties/helper_properties.hpp"
#include "dogen/quilt.cpp/types/settings/helper_settings_repository.hpp"
#include "dogen/quilt.cpp/types/settings/streaming_settings_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

class helper_properties_factory {
public:
    helper_properties_factory(
        const std::unordered_set<std::string>& primitive_ids,
        const settings::helper_settings_repository& hsrp,
        const settings::streaming_settings_repository& ssrp);

private:
    boost::optional<settings::helper_settings>
    helper_settings_for_id(const std::string& id) const;

    bool is_primitive(const std::string& id) const;

    boost::optional<settings::streaming_settings>
    streaming_settings_for_id(const std::string& id) const;

private:
    boost::optional<helper_descriptor>
    make(const yarn::name_tree& nt, const bool is_top_level,
        std::list<helper_properties>& properties) const;

public:
    std::list<helper_properties>
    make(const std::list<yarn::attribute>& attributes) const;

private:
    const std::unordered_set<std::string>& primitive_ids_;
    const settings::helper_settings_repository& helper_settings_;
    const settings::streaming_settings_repository& streaming_settings_;
};

} } } }

#endif

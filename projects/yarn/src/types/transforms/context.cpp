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
#include "dogen/yarn/types/transforms/context.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

context::context(
        const std::vector<boost::filesystem::path>& data_directories,
        const options::knitting_options& options,
        const std::unordered_map<
        std::type_index, std::list<annotations::archetype_location>>&
        als_by_type,
        const annotations::archetype_location_repository& alrp,
        const annotations::type_repository& atrp,
        const helpers::mapping_set_repository& msrp,
        const dogen::formatters::repository& frp) :
    data_directories_(data_directories), options_(options),
    archetype_locations_by_element_type_index_(als_by_type),
    archetype_location_repository_(alrp), type_repository_(atrp),
    groups_factory_(data_directories, archetype_location_repository_,
        type_repository_),
    mapping_repository_(msrp), formatters_repository_(frp) {}

const std::vector<boost::filesystem::path>& context::data_directories() const {
    return data_directories_;
}

const options::knitting_options& context::options() const {
    return options_;
}

const annotations::archetype_location_repository&
context::archetype_location_repository() const {
    return archetype_location_repository_;
}

const std::unordered_map<std::type_index,
                         std::list<annotations::archetype_location>>&
context::archetype_locations_by_element_type_index() const {
    return archetype_locations_by_element_type_index_;
}

const annotations::type_repository& context::type_repository() const {
    return type_repository_;
}

const annotations::annotation_groups_factory& context::groups_factory() const {
    return groups_factory_;
}

const helpers::mapping_set_repository& context::mapping_repository() const {
    return mapping_repository_;
}

const dogen::formatters::repository& context::formatters_repository() const {
    return formatters_repository_;
}

} } }

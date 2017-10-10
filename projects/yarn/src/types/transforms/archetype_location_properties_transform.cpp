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
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/io/meta_model/model_io.hpp"
#include "dogen/yarn/types/helpers/scoped_transform_probing.hpp"
#include "dogen/yarn/types/transforms/archetype_location_properties_transform.hpp"

namespace {

const std::string transform_id(
    "yarn.transforms.archetype_location_properties_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen {
namespace yarn {
namespace transforms {

inline std::ostream& operator<<(std::ostream& s,
    const archetype_location_properties_transform::backend_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"yarn::transform::"
      << "archetype_location_properties_transform::backend_type_group\"" << ", "
      << "\"enabled\": " << v.enabled << ", "
      << "\"directory\": " << v.directory << ", "
      << "\"force_backend_directory\": " << v.force_backend_directory
      << " }";

    return s;
}

inline std::ostream& operator<<(std::ostream& s,
    const archetype_location_properties_transform::facet_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"yarn::transform::"
      << "archetype_location_properties_transform::facet_type_group\"" << ", "
      << "\"enabled\": " << v.enabled << ", "
      << "\"overwrite\": " << v.overwrite << ", "
      << "\"directory\": " << v.directory << ", "
      << "\"postfix\": " << v.postfix
      << " }";

    return s;
}

inline std::ostream& operator<<(std::ostream& s,
    const archetype_location_properties_transform::archetype_type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"yarn::transform::"
      << "archetype_location_properties_transform::archetype_type_group\""
      << ", "
      << "\"enabled\": " << v.enabled << ", "
      << "\"overwrite\": " << v.overwrite << ", "
      << "\"postfix\": " << v.postfix
      << " }";

    return s;
}

std::unordered_map<std::string,
                   archetype_location_properties_transform::backend_type_group>
archetype_location_properties_transform::
make_backend_type_group(const annotations::type_repository& /*atrp*/,
    const annotations::archetype_location_repository& /*alrp*/) {
    std::unordered_map<std::string, backend_type_group> r;
    return r;
}

std::unordered_map<std::string,
                   archetype_location_properties_transform::backend_type_group>
archetype_location_properties_transform::
make_facet_type_group(const annotations::type_repository& /*atrp*/,
    const annotations::archetype_location_repository& /*alrp*/) {
    std::unordered_map<std::string, backend_type_group> r;
    return r;
}

std::unordered_map<std::string,
                   archetype_location_properties_transform::backend_type_group>
archetype_location_properties_transform::
make_archetype_type_group(const annotations::type_repository& /*atrp*/,
    const annotations::archetype_location_repository& /*alrp*/) {
    std::unordered_map<std::string, backend_type_group> r;
    return r;
}

void archetype_location_properties_transform::
transform(const context& ctx, meta_model::model& m) {
    helpers::scoped_transform_probing stp(lg,
        "archetype location properties transform",
        transform_id, m.name().id(), ctx.prober(), m);
}

} } }

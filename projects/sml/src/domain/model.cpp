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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <ostream>
#include "dogen/sml/domain/model.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/sml/io/qualified_name_io.hpp"
#include "dogen/sml/io/package_io.hpp"
#include "dogen/sml/io/pod_io.hpp"
#include "dogen/sml/io/primitive_io.hpp"

namespace dogen {
namespace sml {

bool model::operator==(const model& rhs) const {
    return
        name_ == rhs.name_ &&
        packages_ == rhs.packages_ &&
        pods_ == rhs.pods_ &&
        primitives_ == rhs.primitives_ &&
        external_package_path_ == rhs.external_package_path_ &&
        schema_name_ == rhs.schema_name_;
}

void model::to_stream(std::ostream& stream) const {
    stream << "\"model\": {"
           << "\"name\": \"" << name_ << "\","
           << "\"packages\":" << packages_ << ","
           << "\"pods\":" << pods_ << ","
           << "\"primitives\":" << primitives_
           << "\"external_package_path:" << external_package_path_
           << "\"schema_name:\"" << schema_name_
           << " }";
}

} }

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
#include <ostream>
#include "dogen/utility/io/list_io.hpp"
#include "dogen/sml/domain/qualified_name.hpp"
#include "dogen/sml/io/meta_types_io.hpp"

namespace dogen {
namespace sml {

bool qualified_name::operator==(const qualified_name& rhs) const {
    return
        model_name_ == rhs.model_name_ &&
        external_package_path_ == rhs.external_package_path_ &&
        package_path_ == rhs.package_path_ &&
        type_name_ == rhs.type_name_ &&
        meta_type_ == rhs.meta_type_;
}

void qualified_name::to_stream(std::ostream& stream) const {
    stream << "\"qualified_name\": {"
           << "\"model_name\":\"" << model_name_ << "\", "
           << "\"external_package_path\":" << external_package_path_ << ", "
           << "\"package_path\":" << package_path_ << ", "
           << "\"type_name\":\"" << type_name_ << "\", "
           << "\"meta_type\":" << "\"" << meta_type_ << "\""
           << " }";
}

} }

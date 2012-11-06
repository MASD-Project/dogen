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
#include <boost/io/ios_state.hpp>
#include "dogen/utility/io/optional_io.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/sml/io/category_types_io.hpp"
#include "dogen/sml/io/property_io.hpp"
#include "dogen/sml/io/qualified_name_io.hpp"
#include "dogen/sml/domain/pod.hpp"

namespace dogen {
namespace sml {

bool pod::operator==(const pod& rhs) const {
    return
        name_ == rhs.name_ &&
        properties_ == rhs.properties_ &&
        parent_name_ == rhs.parent_name_ &&
        original_parent_name_ == rhs.original_parent_name_ &&
        leaves_ == rhs.leaves_ &&
        generate_ == rhs.generate_ &&
        is_parent_ == rhs.is_parent_ &&
        category_type_ == rhs.category_type_ &&
        documentation_ == rhs.documentation_ &&
        number_of_type_arguments_ == rhs.number_of_type_arguments_ &&
        is_sequence_container_ == rhs.is_sequence_container_ &&
        is_associative_container_ == rhs.is_associative_container_ &&
        is_smart_pointer_ == rhs.is_smart_pointer_ &&
        is_cacheable_ == rhs.is_cacheable_;
}

void pod::to_stream(std::ostream& stream) const {
    boost::io::ios_flags_saver ifs(stream);

    stream << std::boolalpha
           << "\"pod\": {"
           << name() << ", "
           << "\"properties\":" << properties() << ", "
           << parent_name() << ", "
           << original_parent_name() << ", "
           << "\"leaves\":" << leaves() << ", "
           << "\"generate\": " << generate_ << ", "
           << "\"is_parent\": " << is_parent_ << ", "
           << "\"category_type\":" << "\"" << category_type_ << "\", "
           << "\"documentation\":" << "\"" << documentation_ << "\", "
           << "\"number_of_type_arguments\":" << number_of_type_arguments_
           << ", "
           << "\"is_sequence_container\":" << is_sequence_container_ << ", "
           << "\"is_associative_container\":" << is_associative_container_
           << ", "
           << "\"is_smart_pointer\":" << is_smart_pointer_ << ", "
           << "\"is_cacheable\":" << is_cacheable_
           << " }";
}

} }

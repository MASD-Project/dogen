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
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_facet_includer.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_domain_header.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_domain_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_facet_includer.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_hash_header.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_hash_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_io_header.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_io_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_generator_header.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_generator_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_serialization_header.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_serialization_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_database_header.hpp"
#include "dogen/generator/backends/cpp/formatters/cpp_database_implementation.hpp"
#include "dogen/generator/backends/cpp/formatters/factory.hpp"

namespace {

const std::string invalid_facet_types_enum("Invalid value for cpp_facet_types");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

factory::production_type
factory::create(std::ostream& stream, cpp_facet_types facet_type) const {
    return facet_includer::create(stream, facet_type);
}

factory::production_type factory::
create(std::ostream& stream, cpp_facet_types facet_type,
    cpp_file_types file_type) const {
    switch (facet_type) {
    case cpp_facet_types::domain:
        if (file_type == cpp_file_types::header)
            return domain_header::create(stream,
                settings_.disable_complete_constructor(),
                settings_.use_integrated_io(),
                disable_io_);
        else
            return domain_implementation::create(stream,
                settings_.disable_complete_constructor(),
                settings_.use_integrated_io(),
                disable_io_);
        break;
    case cpp_facet_types::io:
        if (file_type == cpp_file_types::header)
            return io_header::create(stream);
        else
            return io_implementation::create(stream);
        break;
    case cpp_facet_types::hash:
        if (file_type == cpp_file_types::header)
            return hash_header::create(stream);
        else
            return hash_implementation::create(stream);
        break;
    case cpp_facet_types::serialization:
        if (file_type == cpp_file_types::header)
            return serialization_header::create(stream,
                settings_.disable_xml_serialization());
        else
            return serialization_implementation::create(stream);
        break;
    case cpp_facet_types::test_data:
        if (file_type == cpp_file_types::header)
            return generator_header::create(stream);
        else
            return generator_implementation::create(stream);
        break;
    case cpp_facet_types::database:
        if (file_type == cpp_file_types::header)
            return database_header::create(stream);
        else
            return database_implementation::create(stream);
        break;

    default:
        using utility::exception::invalid_enum_value;
        throw invalid_enum_value(invalid_facet_types_enum);
    }
}

} } } } }

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
#ifndef DOGEN_UTILITY_TYPES_ALL_HPP
#define DOGEN_UTILITY_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.utility/types/utility.hpp"
#include "dogen.utility/types/io/map_io.hpp"
#include "dogen.utility/types/io/set_io.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/pair_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/array_io.hpp"
#include "dogen.utility/types/test/macros.hpp"
#include "dogen.utility/types/hash/combine.hpp"
#include "dogen.utility/types/io/memory_io.hpp"
#include "dogen.utility/types/io/vector_io.hpp"
#include "dogen.utility/types/test/fixture.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/io/jsonify_io.hpp"
#include "dogen.utility/types/string/differ.hpp"
#include "dogen.utility/types/test/asserter.hpp"
#include "dogen.utility/types/xml/exception.hpp"
#include "dogen.utility/types/hash/list_hash.hpp"
#include "dogen.utility/types/io/optional_io.hpp"
#include "dogen.utility/types/xml/node_types.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.utility/types/filesystem/path.hpp"
#include "dogen.utility/types/io/typeindex_io.hpp"
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.utility/types/xml/text_reader.hpp"
#include "dogen.utility/types/io/shared_ptr_io.hpp"
#include "dogen.utility/types/xml/node_types_io.hpp"
#include "dogen.utility/types/io/forward_list_io.hpp"
#include "dogen.utility/types/log/severity_level.hpp"
#include "dogen.utility/types/serialization/path.hpp"
#include "dogen.utility/types/test/file_asserter.hpp"
#include "dogen.utility/types/test_data/resolver.hpp"
#include "dogen.utility/types/test_data/sequence.hpp"
#include "dogen.utility/types/xml/text_reader_io.hpp"
#include "dogen.utility/types/filesystem/io_error.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.utility/types/test_data/generator.hpp"
#include "dogen.utility/types/test_data/northwind.hpp"
#include "dogen.utility/types/test_data/test_data.hpp"
#include "dogen.utility/types/test_data/xml_reader.hpp"
#include "dogen.utility/types/formatters/quote_type.hpp"
#include "dogen.utility/types/log/lifecycle_manager.hpp"
#include "dogen.utility/types/formatters/spacing_type.hpp"
#include "dogen.utility/types/test/exception_checkers.hpp"
#include "dogen.utility/types/test_data/tds_test_good.hpp"
#include "dogen.utility/types/serialization/xml_helper.hpp"
#include "dogen.utility/types/filesystem/file_not_found.hpp"
#include "dogen.utility/types/log/logging_configuration.hpp"
#include "dogen.utility/types/test_data/dogen_generation.hpp"
#include "dogen.utility/types/test_data/filesystem_tests.hpp"
#include "dogen.utility/types/environment/variable_reader.hpp"
#include "dogen.utility/types/exception/utility_exception.hpp"
#include "dogen.utility/types/formatters/formatting_error.hpp"
#include "dogen.utility/types/serialization/archive_types.hpp"
#include "dogen.utility/types/test/bytewise_file_asserter.hpp"
#include "dogen.utility/types/exception/invalid_enum_value.hpp"
#include "dogen.utility/types/formatters/utility_formatter.hpp"
#include "dogen.utility/types/log/scoped_lifecycle_manager.hpp"
#include "dogen.utility/types/test_data/generate_container.hpp"
#include "dogen.utility/types/test/xml_serialization_helper.hpp"
#include "dogen.utility/types/test_data/test_data_exception.hpp"
#include "dogen.utility/types/test_data/validating_resolver.hpp"
#include "dogen.utility/types/environment/environment_exception.hpp"
#include "dogen.utility/types/log/invalid_logging_configuration.hpp"
#include "dogen.utility/types/test_data/cpp_ref_impl_generation.hpp"
#include "dogen.utility/types/log/logging_configuration_validator.hpp"
#include "dogen.utility/types/test_data/csharp_ref_impl_generation.hpp"

#endif

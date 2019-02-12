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
#ifndef MASD_DOGEN_UTILITY_TYPES_ALL_HPP
#define MASD_DOGEN_UTILITY_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.utility/types/utility.hpp"
#include "masd.dogen.utility/types/io/map_io.hpp"
#include "masd.dogen.utility/types/io/set_io.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.utility/types/io/pair_io.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/array_io.hpp"
#include "masd.dogen.utility/types/test/macros.hpp"
#include "masd.dogen.utility/types/hash/combine.hpp"
#include "masd.dogen.utility/types/io/memory_io.hpp"
#include "masd.dogen.utility/types/io/vector_io.hpp"
#include "masd.dogen.utility/types/test/fixture.hpp"
#include "masd.dogen.utility/types/test/logging.hpp"
#include "masd.dogen.utility/types/io/jsonify_io.hpp"
#include "masd.dogen.utility/types/test/asserter.hpp"
#include "masd.dogen.utility/types/xml/exception.hpp"
#include "masd.dogen.utility/types/hash/list_hash.hpp"
#include "masd.dogen.utility/types/io/optional_io.hpp"
#include "masd.dogen.utility/types/test/io_tester.hpp"
#include "masd.dogen.utility/types/test_data/seam.hpp"
#include "masd.dogen.utility/types/xml/node_types.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.utility/types/filesystem/path.hpp"
#include "masd.dogen.utility/types/io/typeindex_io.hpp"
#include "masd.dogen.utility/types/string/splitter.hpp"
#include "masd.dogen.utility/types/xml/text_reader.hpp"
#include "masd.dogen.utility/types/io/shared_ptr_io.hpp"
#include "masd.dogen.utility/types/test/hash_tester.hpp"
#include "masd.dogen.utility/types/test_data/stitch.hpp"
#include "masd.dogen.utility/types/test/canned_tests.hpp"
#include "masd.dogen.utility/types/xml/node_types_io.hpp"
#include "masd.dogen.utility/types/io/forward_list_io.hpp"
#include "masd.dogen.utility/types/log/severity_level.hpp"
#include "masd.dogen.utility/types/serialization/path.hpp"
#include "masd.dogen.utility/types/test/file_asserter.hpp"
#include "masd.dogen.utility/types/test_data/resolver.hpp"
#include "masd.dogen.utility/types/test_data/sequence.hpp"
#include "masd.dogen.utility/types/xml/text_reader_io.hpp"
#include "masd.dogen.utility/types/filesystem/io_error.hpp"
#include "masd.dogen.utility/types/io/unordered_map_io.hpp"
#include "masd.dogen.utility/types/io/unordered_set_io.hpp"
#include "masd.dogen.utility/types/test/json_validator.hpp"
#include "masd.dogen.utility/types/test_data/generator.hpp"
#include "masd.dogen.utility/types/test_data/northwind.hpp"
#include "masd.dogen.utility/types/test_data/test_data.hpp"
#include "masd.dogen.utility/types/test/equality_tester.hpp"
#include "masd.dogen.utility/types/test_data/xml_reader.hpp"
#include "masd.dogen.utility/types/test/less_than_tester.hpp"
#include "masd.dogen.utility/types/log/lifecycle_manager.hpp"
#include "masd.dogen.utility/types/test/exception_checkers.hpp"
#include "masd.dogen.utility/types/test_data/injection_dia.hpp"
#include "masd.dogen.utility/types/test_data/tds_test_good.hpp"
#include "masd.dogen.utility/types/serialization/xml_helper.hpp"
#include "masd.dogen.utility/types/test/construction_tester.hpp"
#include "masd.dogen.utility/types/test_data/injection_json.hpp"
#include "masd.dogen.utility/types/filesystem/file_not_found.hpp"
#include "masd.dogen.utility/types/test/serialization_tester.hpp"
#include "masd.dogen.utility/types/test_data/filesystem_tests.hpp"
#include "masd.dogen.utility/types/exception/utility_exception.hpp"
#include "masd.dogen.utility/types/serialization/archive_types.hpp"
#include "masd.dogen.utility/types/test/bytewise_file_asserter.hpp"
#include "masd.dogen.utility/types/exception/invalid_enum_value.hpp"
#include "masd.dogen.utility/types/test_data/generate_container.hpp"
#include "masd.dogen.utility/types/log/scoped_lifecycle_manager.hpp"
#include "masd.dogen.utility/types/test/xml_serialization_helper.hpp"
#include "masd.dogen.utility/types/test_data/test_data_exception.hpp"
#include "masd.dogen.utility/types/test_data/validating_resolver.hpp"
#include "masd.dogen.utility/types/test/move_assignment_copy_tester.hpp"

#endif

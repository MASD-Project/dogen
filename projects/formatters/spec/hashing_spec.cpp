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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/formatters/types/licence.hpp"
#include "dogen/formatters/io/licence_io.hpp"
#include "dogen/formatters/test_data/licence_td.hpp"
#include "dogen/formatters/hash/licence_hash.hpp"
#include "dogen/formatters/types/modeline.hpp"
#include "dogen/formatters/io/modeline_io.hpp"
#include "dogen/formatters/test_data/modeline_td.hpp"
#include "dogen/formatters/hash/modeline_hash.hpp"
#include "dogen/formatters/types/modeline_group.hpp"
#include "dogen/formatters/io/modeline_group_io.hpp"
#include "dogen/formatters/test_data/modeline_group_td.hpp"
#include "dogen/formatters/hash/modeline_group_hash.hpp"
#include "dogen/formatters/types/editors.hpp"
#include "dogen/formatters/io/editors_io.hpp"
#include "dogen/formatters/test_data/editors_td.hpp"
#include "dogen/formatters/hash/editors_hash.hpp"
#include "dogen/formatters/types/modeline_locations.hpp"
#include "dogen/formatters/io/modeline_locations_io.hpp"
#include "dogen/formatters/test_data/modeline_locations_td.hpp"
#include "dogen/formatters/hash/modeline_locations_hash.hpp"
#include "dogen/formatters/types/modeline_field.hpp"
#include "dogen/formatters/io/modeline_field_io.hpp"
#include "dogen/formatters/test_data/modeline_field_td.hpp"
#include "dogen/formatters/hash/modeline_field_hash.hpp"
#include "dogen/formatters/types/comment_styles.hpp"
#include "dogen/formatters/io/comment_styles_io.hpp"
#include "dogen/formatters/test_data/comment_styles_td.hpp"
#include "dogen/formatters/hash/comment_styles_hash.hpp"

namespace {

const std::string empty;
const std::string test_module("formatters");
const std::string test_suite("hashing_spec");

}

using namespace dogen::formatters;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(hashing)

BOOST_AUTO_TEST_CASE(validate_hashing) {
    SETUP_TEST_LOG("validate_hashing");

    test_hashing<licence_generator>();
    test_hashing<modeline_generator>();
    test_hashing<modeline_group_generator>();
    test_hashing<editors_generator>();
    test_hashing<modeline_locations_generator>();
    test_hashing<modeline_field_generator>();
    test_hashing<comment_styles_generator>();
}

BOOST_AUTO_TEST_SUITE_END()

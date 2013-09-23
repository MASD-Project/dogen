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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/om/types/licence.hpp"
#include "dogen/om/io/licence_io.hpp"
#include "dogen/om/test_data/licence_td.hpp"
#include "dogen/om/types/modeline.hpp"
#include "dogen/om/io/modeline_io.hpp"
#include "dogen/om/test_data/modeline_td.hpp"
#include "dogen/om/types/modeline_group.hpp"
#include "dogen/om/io/modeline_group_io.hpp"
#include "dogen/om/test_data/modeline_group_td.hpp"
#include "dogen/om/types/cpp_includes.hpp"
#include "dogen/om/io/cpp_includes_io.hpp"
#include "dogen/om/test_data/cpp_includes_td.hpp"
#include "dogen/om/types/editors.hpp"
#include "dogen/om/io/editors_io.hpp"
#include "dogen/om/test_data/editors_td.hpp"
#include "dogen/om/types/modeline_locations.hpp"
#include "dogen/om/io/modeline_locations_io.hpp"
#include "dogen/om/test_data/modeline_locations_td.hpp"
#include "dogen/om/types/modeline_field.hpp"
#include "dogen/om/io/modeline_field_io.hpp"
#include "dogen/om/test_data/modeline_field_td.hpp"
#include "dogen/om/types/comment_styles.hpp"
#include "dogen/om/io/comment_styles_io.hpp"
#include "dogen/om/test_data/comment_styles_td.hpp"

namespace {

const std::string empty;
const std::string test_module("om");
const std::string test_suite("equality_spec");

}

using namespace dogen::om;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(equality)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");

    test_equality<licence_generator>();
    test_equality<modeline_generator>();
    test_equality<modeline_group_generator>();
    test_equality<cpp_includes_generator>();
    test_equality<editors_generator>();
    test_equality<modeline_locations_generator>();
    test_equality<modeline_field_generator>();
    test_equality<comment_styles_generator>();
}

BOOST_AUTO_TEST_SUITE_END()

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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/om/types/all.hpp"
#include "dogen/om/io/all_io.hpp"
#include "dogen/om/test_data/all_td.hpp"

using dogen::sml::test::mock_model_factory;

namespace {

const std::string test_module("om");
const std::string test_suite("cpp_domain_header_formatter_spec");
const boost::filesystem::path empty_path;
const boost::filesystem::path non_empty_path("a/file.hpp");

const std::string with_guard(R"(#ifndef A_FILE_HPP
#define A_FILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif
#endif
)");

}

using namespace dogen::om;
using namespace dogen::utility::test;
typedef dogen::sml::test::mock_model_factory::object_types object_types;
typedef dogen::sml::test::mock_model_factory::property_types property_types;
typedef dogen::sml::test::mock_model_factory factory;

BOOST_AUTO_TEST_SUITE(cpp_domain_header_formatter)

BOOST_AUTO_TEST_CASE(enumeration_produces_expected_domain_header) {
    SETUP_TEST_LOG_SOURCE("enumeration_produces_expected_domain_header");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    const auto ot(object_types::enumeration);
    const auto m(factory::build_single_type_model(0, ot));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;
    BOOST_REQUIRE(m.enumerations().size() == 1);

    std::ostringstream s;
    dogen::om::cpp_domain_header_formatter f;
    const auto e(m.enumerations().begin()->second);
    f.format(s, e, dogen::om::licence(), dogen::om::modeline(),
        std::string()/*marker*/, m);
    const auto r(s.str());
    // BOOST_CHECK(r == with_guard);
    BOOST_LOG_SEV(lg, debug) << "expected: " << with_guard;
    BOOST_LOG_SEV(lg, debug) << "actual: " << r;
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_SUITE_END()

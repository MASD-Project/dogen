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
#include <istream>
#include <sstream>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/test/unit_test.hpp>
#include "dogen/sml/types/meta_data_writer.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/om/io/file_io.hpp"
#include "dogen/om/types/workflow.hpp"

namespace {

const std::string test_module("om");
const std::string test_suite("workflow_spec");

using dogen::sml::test::mock_model_factory;
const mock_model_factory factory;

const std::string type_with_no_properties(
    R"(/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * SAMPLE_MARKER
 *
 * Copyright (C) 2012 Person <name@company.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 *
 */
#ifndef SOME_MODEL_0_SOME_TYPE_0_HPP
#define SOME_MODEL_0_SOME_TYPE_0_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace some_model_0 {

/**
 * @brief Some documentation
 */
class some_type_0 final {
};

}

#endif
)");

const std::string model_with_comments(R"(/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * SAMPLE_MARKER
 *
 * Copyright (C) 2012 Person <name@company.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 *
 */
#ifndef SOME_MODEL_0_SOME_MODEL_0_HPP
#define SOME_MODEL_0_SOME_MODEL_0_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

/**
 * @brief Some documentation
 */
namespace some_model_0 {
}

#endif
)");

}

using namespace dogen::om;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(workflow)

BOOST_AUTO_TEST_CASE(empty_mock_model_results_in_expected_files) {
    SETUP_TEST_LOG_SOURCE("empty_mock_results_in_expected_files");

    using namespace dogen::utility::filesystem;
    const std::list<boost::filesystem::path> d = { data_files_directory() };
    dogen::om::workflow w(d);

    auto m(factory.build_empty_model());
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    const auto r(w.execute(m));
    BOOST_LOG_SEV(lg, debug) << "result: " << r;

    BOOST_REQUIRE(r.size() == 1);
    BOOST_CHECK(factory.is_file_for_qname(r.front().relative_path(), m.name()));

    BOOST_LOG_SEV(lg, debug) << "expected: <start>" << model_with_comments
                             << "<end>";
    BOOST_LOG_SEV(lg, debug) << "actual: <start>" << r.front().contents()
                             << "<end>";
    BOOST_CHECK(model_with_comments == r.front().contents());
}

BOOST_AUTO_TEST_CASE(single_type_model_results_in_expected_files) {
    SETUP_TEST_LOG_SOURCE("single_type_results_in_expected_files");

    using namespace dogen::utility::filesystem;
    const std::list<boost::filesystem::path> d = { data_files_directory() };
    dogen::om::workflow w(d);
    auto m(factory.build_single_type_model());

    BOOST_REQUIRE(m.objects().size() == 1);
    auto& o(*(m.objects().begin()->second));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    const auto r(w.execute(m));
    BOOST_LOG_SEV(lg, debug) << "result: " << r;
    BOOST_REQUIRE(r.size() == 2);

    bool found_model(false), found_type(false);
    for (const auto& f : r) {
        if (factory.is_file_for_qname(f.relative_path(), m.name())) {
            found_model = true;
            BOOST_LOG_SEV(lg, debug) << "expected: <start>"
                                     << model_with_comments
                                     << "<end>";
            BOOST_LOG_SEV(lg, debug) << "actual: <start>"
                                     << f.contents()
                                     << "<end>";
            BOOST_CHECK(model_with_comments == f.contents());
        } else if (factory.is_file_for_qname(f.relative_path(), o.name())) {
            found_type = true;
            BOOST_LOG_SEV(lg, debug) << "expected: <start>"
                                     << type_with_no_properties
                                     << "<end>";
            BOOST_LOG_SEV(lg, debug) << "actual: <start>"
                                     << f.contents()
                                     << "<end>";
            BOOST_CHECK(type_with_no_properties == f.contents());
        }
        else
            BOOST_FAIL("Unexpected file: " << f.relative_path());
    }
    BOOST_CHECK(found_model);
    BOOST_CHECK(found_type);
}

BOOST_AUTO_TEST_SUITE_END()

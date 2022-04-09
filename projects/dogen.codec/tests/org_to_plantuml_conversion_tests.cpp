/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2022 Marco Craveiro <marco.craveiro@gmail.com>
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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/types/mock_configuration_factory.hpp"
#include "dogen.utility/types/test/asserter.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.utility/types/string/differ.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/test_data/dogen_product.hpp"
#include "dogen.dia/io/entities/object_io.hpp"
#include "dogen.codec/types/entities/object.hpp"
#include "dogen.codec/types/helpers/dia_to_codec_projector.hpp"
#include "dogen.codec/io/entities/object_io.hpp"
#include "dogen.dia/test/mock_object_factory.hpp"
#include "dogen.codec/types/transforms/artefact_to_artefact_chain.hpp"
#include "dogen.codec/types/transforms/file_to_artefact_transform.hpp"
#include "dogen.codec/types/transforms/context_bootstrapping_chain.hpp"
#include "dogen.utility/types/test/exception_checkers.hpp"

namespace  {

const std::string test_module("masd.codec.tests");
const std::string test_suite("org_to_plantuml_projector_tests");
const std::string model_name("test");

const std::string run_activity("physical_production");
const std::string conversion_activity("model_to_model");

/*
 * Set these flag to true if you want to dump information for all
 * tests. All except for diffing should normally be set to false,
 * unless we are diagnosing some kind of problem. Don't check it in as
 * true as it slows down the tests for no good reason.
 */
const bool enable_tracing_globally(false);
const bool enable_reporting_globally(true);
const bool enable_diffing_globally(true);

std::string
apply_artefact_to_artefact_chain(const boost::filesystem::path& src,
    const bool enable_tracing_locally = false,
    const bool enable_reporting_locally = false,
    const bool enable_diffing_locally = false) {

    /*
     * Create the configuration.
     */
    const bool et(enable_tracing_globally || enable_tracing_locally);
    const bool er(enable_reporting_globally || enable_reporting_locally);
    const bool ed(enable_diffing_globally || enable_diffing_locally);
    using dogen::mock_configuration_factory;
    mock_configuration_factory f(et, er, ed);
    const auto cfg(f.make(src, run_activity));

    /*
     * Bootstrap the top-level context.
     */
    using namespace dogen::codec::transforms;
    using cbc = context_bootstrapping_chain;
    const auto ctx(cbc::bootstrap(cfg, conversion_activity));

    using dogen::codec::transforms::file_to_artefact_transform;
    const auto src_a(file_to_artefact_transform::apply(ctx, src));

    auto dst = src;
    dst.replace_extension("plantuml");

    using dogen::codec::transforms::artefact_to_artefact_chain;
    const auto dst_a(artefact_to_artefact_chain::apply(ctx, src_a, dst));

    using dogen::utility::filesystem::read_file_content;
    const auto expected = read_file_content(dst);

    using dogen::utility::string::differ;
    const auto r(differ::diff(expected, dst_a.content()));
    if (!r.empty()) {
        std::cout << "Conversion generated differences: "
                  << src.generic_path() << std::endl
                  << r << std::endl;
    }
    return r;
}

}

using dogen::utility::test_data::dogen_product;

BOOST_AUTO_TEST_SUITE(org_to_plantuml_projector_tests)

BOOST_AUTO_TEST_CASE(dogen_org_conversion_has_no_diffs) {
    SETUP_TEST_LOG("dogen_org_conversion_has_no_diffs");
    const auto t(dogen_product::input_dogen_org());
    const auto diff(apply_artefact_to_artefact_chain(t));
    BOOST_CHECK(diff.empty());
}

BOOST_AUTO_TEST_CASE(dogen_physical_org_conversion_has_no_diffs) {
    SETUP_TEST_LOG("dogen_physical_org_conversion_has_no_diffs");
    const auto t(dogen_product::input_dogen_physical_org());
    const auto diff(apply_artefact_to_artefact_chain(t));
    BOOST_CHECK(diff.empty());
}

BOOST_AUTO_TEST_CASE(dogen_cli_org_conversion_has_no_diffs) {
    SETUP_TEST_LOG("dogen_cli_org_conversion_has_no_diffs");
    const auto t(dogen_product::input_dogen_cli_org());
    const auto diff(apply_artefact_to_artefact_chain(t));
    BOOST_CHECK(diff.empty());
}

BOOST_AUTO_TEST_CASE(dogen_dia_org_conversion_has_no_diffs) {
    SETUP_TEST_LOG("dogen_dia_org_conversion_has_no_diffs");
    const auto t(dogen_product::input_dogen_dia_org());
    const auto diff(apply_artefact_to_artefact_chain(t));
    BOOST_CHECK(diff.empty());
}

BOOST_AUTO_TEST_CASE(dogen_org_org_conversion_has_no_diffs) {
    SETUP_TEST_LOG("dogen_org_org_conversion_has_no_diffs");
    const auto t(dogen_product::input_dogen_org_org());
    const auto diff(apply_artefact_to_artefact_chain(t));
    BOOST_CHECK(diff.empty());
}

BOOST_AUTO_TEST_CASE(dogen_tracing_org_conversion_has_no_diffs) {
    SETUP_TEST_LOG("dogen_tracing_org_conversion_has_no_diffs");
    const auto t(dogen_product::input_dogen_tracing_org());
    const auto diff(apply_artefact_to_artefact_chain(t));
    BOOST_CHECK(diff.empty());
}

BOOST_AUTO_TEST_CASE(dogen_codec_org_conversion_has_no_diffs) {
    SETUP_TEST_LOG("dogen_codec_org_conversion_has_no_diffs");
    const auto t(dogen_product::input_dogen_codec_org());
    const auto diff(apply_artefact_to_artefact_chain(t));
    BOOST_CHECK(diff.empty());
}

BOOST_AUTO_TEST_CASE(dogen_text_org_conversion_has_no_diffs) {
    SETUP_TEST_LOG("dogen_text_org_conversion_has_no_diffs");
    const auto t(dogen_product::input_dogen_text_org());
    const auto diff(apply_artefact_to_artefact_chain(t));
    BOOST_CHECK(diff.empty());
}

BOOST_AUTO_TEST_CASE(dogen_logical_org_conversion_has_no_diffs) {
    SETUP_TEST_LOG("dogen_logical_org_conversion_has_no_diffs");
    const auto t(dogen_product::input_dogen_logical_org());
    const auto diff(apply_artefact_to_artefact_chain(t));
    BOOST_CHECK(diff.empty());
}

BOOST_AUTO_TEST_CASE(dogen_templating_org_conversion_has_no_diffs) {
    SETUP_TEST_LOG("dogen_templating_org_conversion_has_no_diffs");
    const auto t(dogen_product::input_dogen_templating_org());
    const auto diff(apply_artefact_to_artefact_chain(t));
    BOOST_CHECK(diff.empty());
}

BOOST_AUTO_TEST_CASE(dogen_orchestration_org_conversion_has_no_diffs) {
    SETUP_TEST_LOG("dogen_orchestration_org_conversion_has_no_diffs");
    const auto t(dogen_product::input_dogen_orchestration_org());
    const auto diff(apply_artefact_to_artefact_chain(t));
    BOOST_CHECK(diff.empty());
}

BOOST_AUTO_TEST_CASE(dogen_utility_org_conversion_has_no_diffs) {
    SETUP_TEST_LOG("dogen_utility_org_conversion_has_no_diffs");
    const auto t(dogen_product::input_dogen_utility_org());
    const auto diff(apply_artefact_to_artefact_chain(t));
    BOOST_CHECK(diff.empty());
}

BOOST_AUTO_TEST_CASE(dogen_variability_org_conversion_has_no_diffs) {
    SETUP_TEST_LOG("dogen_variability_org_conversion_has_no_diffs");
    const auto t(dogen_product::input_dogen_variability_org());
    const auto diff(apply_artefact_to_artefact_chain(t));
    BOOST_CHECK(diff.empty());
}

BOOST_AUTO_TEST_CASE(dogen_identification_org_conversion_has_no_diffs) {
    SETUP_TEST_LOG("dogen_identification_org_conversion_has_no_diffs");
    const auto t(dogen_product::input_dogen_identification_org());
    const auto diff(apply_artefact_to_artefact_chain(t));
    BOOST_CHECK(diff.empty());
}

BOOST_AUTO_TEST_SUITE_END()

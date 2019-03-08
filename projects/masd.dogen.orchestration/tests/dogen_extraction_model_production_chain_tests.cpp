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
#include <boost/test/unit_test_monitor.hpp>
#include "masd.dogen.utility/types/test/logging.hpp"
#include "masd.dogen.utility/types/test_data/dogen_generation.hpp"
#include "masd.dogen.orchestration/types/transforms/scoped_context_manager.hpp"
#include "masd.dogen.orchestration/types/transforms/code_generation_chain.hpp"

/*
 * Comment these out as required if testing only one frontend. These
 * should all be enabled in git, do not check them in commented out by
 * mistake.
 */
#define ENABLE_DIA_TESTS
// #define ENABLE_JSON_TESTS
// #define ENABLE_CSHARP_TESTS

namespace  {

const std::string test_module("masd.dogen.coding.tests");
const std::string test_suite("dogen_extraction_model_production_chain_tests");

/*
 * Set this flag to true if you want to dump tracing information for
 * all tests. It should normally be set to false, unless we are
 * diagnosing some kind of problem. Don't check it in as true.
 */
// const bool enable_tracing_globally(false);

// masd::dogen::configuration make_configuration(
//     const boost::filesystem::path& /*target*/,
//     const std::string& /*output_dir*/, bool /*enable_tracing*/) {
//     masd::dogen::configuration r;
//     return r;
// }

// bool test_code_generation(const boost::filesystem::path& target,
//     const std::string& output_dir, bool enable_tracing) {
//     const auto cfg(make_configuration(target, output_dir, enable_tracing));
//     scoped_context_manager sco(cfg, output_directory);
//     code_generation_chain::transform(sco.context(), target);

    
//     const auto name(target.stem().string());
//     return test_code_generation(name, target, actual_dir,
//         enable_tracing, tracing_directory_path);
// }

}

BOOST_AUTO_TEST_SUITE(code_generator_tests)

#ifdef ENABLE_DIA_TESTS

BOOST_AUTO_TEST_CASE(masd_dogen_annotations_dia_generates_expected_code) {
    SETUP_TEST_LOG("masd_dogen_annotations_dia_generates_expected_code");
    // const bool ep(false/*enable tracing locally*/);


    // const auto dia(injection_dia::input_cpp_model_dia());
    // BOOST_CHECK(test_code_generation(dia, actual_dia_dir, ep, pd));
}

BOOST_AUTO_TEST_SUITE_END()

#endif // ENABLE_DIA_TESTS

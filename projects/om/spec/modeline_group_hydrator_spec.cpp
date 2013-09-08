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
#include <boost/filesystem/fstream.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/om/types/all.hpp"
#include "dogen/om/io/all_io.hpp"
#include "dogen/om/test_data/all_td.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

namespace {

const std::string empty;
const std::string test_module("om");
const std::string test_suite("modeline_group_hydrator_spec");

const std::string duplicate_group("Duplicate modeline group");
const std::string invalid_dir("INVALID_DIRECTORY__");
const std::string dir_not_found_message("Could not find directory");
const std::string not_a_dir_message("Not a directory");
const std::string invalid_file_message("Failed to parse INI file");
const std::string emacs_modeline_group("modeline_groups/emacs");
const std::string invalid_ini_file("NOTINITFILE");

const std::string no_editor(R"(
[c++]
location = top
mode = c++
tab-width = 4
indent-tabs-mode = nil
c-basic-offset = 4
)");
const std::string no_editor_message("Editor was not supplied");

const std::string unsupported_editor(R"(
[c++]
editor = gedit
location = top
mode = c++
tab-width = 4
indent-tabs-mode = nil
c-basic-offset = 4
)");
const std::string unsupported_editor_message("Invalid or unsupported editor");

const std::string no_location(R"(
[c++]
editor = emacs
mode = c++
tab-width = 4
indent-tabs-mode = nil
c-basic-offset = 4
)");

const std::string invalid_location(R"(
[c++]
editor = emacs
location = middle
mode = c++
tab-width = 4
indent-tabs-mode = nil
c-basic-offset = 4
)");
const std::string invalid_location_message("Invalid or unsupported modeline");

const std::string no_fields(R"(
[c++]
editor = emacs
location = top
)");
const std::string no_fields_message("Modeline must have at least");

}

using namespace dogen::om;
using namespace dogen::utility::test;
using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(modeline_group_hydrator)

BOOST_AUTO_TEST_CASE(hydrating_emacs_modeline_group_results_in_expected_modelines) {
    SETUP_TEST_LOG_SOURCE("hydrating_emacs_modeline_group_results_in_expected_modelines");
    using namespace dogen::utility::filesystem;
    boost::filesystem::path p(data_files_directory() / emacs_modeline_group);
    boost::filesystem::ifstream s(p);
    dogen::om::modeline_group_hydrator h;
    const auto r(h.hydrate(s));

    BOOST_LOG_SEV(lg, debug) << "modeline group: " << r;
    BOOST_CHECK(!r.modelines().empty());
    for (const auto& pair : r.modelines()) {
        BOOST_CHECK(!pair.first.empty());

        const auto& modeline(pair.second);
        BOOST_CHECK(!modeline.fields().empty());
        BOOST_CHECK(modeline.editor() == dogen::om::editors::emacs);
        BOOST_CHECK(modeline.location() == dogen::om::modeline_locations::top);

        // value  may be empty so nothing can be said about it.
        for (const auto& fields : modeline.fields())
            BOOST_CHECK(!fields.name().empty());
    }
}

BOOST_AUTO_TEST_CASE(supplying_invalid_ini_file_throws) {
    SETUP_TEST_LOG_SOURCE("supplying_invalid_ini_file_throws");

    std::istringstream s(invalid_ini_file);
    using namespace dogen::utility::filesystem;

    dogen::om::modeline_group_hydrator h;
    contains_checker<dogen::om::hydration_error> c(invalid_file_message);
    BOOST_CHECK_EXCEPTION(h.hydrate(s), dogen::om::hydration_error, c);
}

BOOST_AUTO_TEST_CASE(not_supplying_editor_throws) {
    SETUP_TEST_LOG_SOURCE("not_supplying_editor_throws");

    std::istringstream s(no_editor);
    using namespace dogen::utility::filesystem;

    dogen::om::modeline_group_hydrator h;
    contains_checker<dogen::om::hydration_error> c(no_editor_message);
    BOOST_CHECK_EXCEPTION(h.hydrate(s), dogen::om::hydration_error, c);
}

BOOST_AUTO_TEST_CASE(supplying_unsupported_editor_throws) {
    SETUP_TEST_LOG_SOURCE("supplying_unsupported_editor_throws");

    std::istringstream s(unsupported_editor);
    dogen::om::modeline_group_hydrator h;
    contains_checker<dogen::om::hydration_error> c(unsupported_editor_message);
    BOOST_CHECK_EXCEPTION(h.hydrate(s), dogen::om::hydration_error, c);
}

BOOST_AUTO_TEST_CASE(not_supplying_location_results_in_a_valid_location) {
    SETUP_TEST_LOG_SOURCE("not_supplying_location_results_in_a_valid_location");

    std::istringstream s(no_location);
    dogen::om::modeline_group_hydrator h;
    const auto r(h.hydrate(s));

    BOOST_LOG_SEV(lg, debug) << "modeline group: " << r;
    BOOST_CHECK(r.modelines().size() == 1);
    const auto& ml(r.modelines().begin()->second);
    BOOST_CHECK(ml.location() != dogen::om::modeline_locations::invalid);
}

BOOST_AUTO_TEST_CASE(supplying_invalid_location_throws) {
    SETUP_TEST_LOG_SOURCE("supplying_invalid_location_throws");

    std::istringstream s(invalid_location);
    dogen::om::modeline_group_hydrator h;
    contains_checker<dogen::om::hydration_error> c(invalid_location_message);
    BOOST_CHECK_EXCEPTION(h.hydrate(s), dogen::om::hydration_error, c);
}

BOOST_AUTO_TEST_CASE(supplying_no_fields_throws) {
    SETUP_TEST_LOG_SOURCE("supplying_no_fields_throws");

    std::istringstream s(no_fields);
    dogen::om::modeline_group_hydrator h;
    contains_checker<dogen::om::hydration_error> c(no_fields_message);
    BOOST_CHECK_EXCEPTION(h.hydrate(s), dogen::om::hydration_error, c);
}

BOOST_AUTO_TEST_SUITE_END()

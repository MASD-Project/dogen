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
#include <array>
#include <boost/throw_exception.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/sml/types/tags.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/tag_error.hpp"
#include "dogen/sml/types/keyed_entity.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/value_object.hpp"
#include "dogen/sml/types/entity.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/value_object_io.hpp"
#include "dogen/sml/io/service_io.hpp"
#include "dogen/sml/io/abstract_object_io.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/types/tagger.hpp"

using dogen::sml::test::mock_model_factory;
using dogen::sml::tag_error;

namespace {

const std::string test_module("sml");
const std::string test_suite("tagger_spec");

const std::string default_cpp_forward_declaration_postfix("_fwd");
const std::string default_cpp_implementation_file_extension(".cpp");
const std::string default_cpp_header_file_extension(".hpp");
const std::string default_cpp_types_directory("types");

std::string get(const std::unordered_map<std::string, std::string>& simple_tags,
    const std::string& key) {

    const auto i(simple_tags.find(key));
    if (i == simple_tags.end())
        BOOST_THROW_EXCEPTION(tag_error("could not find key: " + key));

    return i->second;
}

bool is_true(const std::unordered_map<std::string, std::string>& simple_tags,
    const std::string& key) {
    const auto value(get(simple_tags, key));
    return value == dogen::sml::tags::bool_true;
}

bool is_supported(const std::unordered_map<std::string, std::string>& simple_tags,
    const std::string& key) {
    const auto value(get(simple_tags, key));
    return value == dogen::sml::tags::status_supported;
}

}

using dogen::utility::test::contains_checker;
using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(tagger)

BOOST_AUTO_TEST_CASE(tagging_empty_model_without_any_configuration_options_results_in_expected_tags) {
    SETUP_TEST_LOG_SOURCE("tagging_empty_model_without_any_configuration_options_results_in_expected_tags");

    auto m(mock_model_factory::build_empty_model());
    dogen::sml::tagger t;
    t.tag(m);
    BOOST_LOG_SEV(lg, debug) << "m: " << m;

    BOOST_CHECK(m.complex_tags().empty());
    BOOST_CHECK(m.simple_tags().size() == 11);

    const auto& st(m.simple_tags());
    using dogen::sml::tags;
    BOOST_CHECK(is_supported(st, tags::cpp::types::status));

    boost::filesystem::path fn;
    fn /= m.name().model_name();
    fn /= default_cpp_types_directory;
    fn /= m.name().model_name() + default_cpp_header_file_extension;
    BOOST_CHECK(get(st, tags::cpp::types::header_file::file_name) ==
        fn.generic_string());

    BOOST_CHECK(get(st, tags::cpp::types::directory_name) ==
        default_cpp_types_directory);

    BOOST_CHECK(is_true(st, tags::cpp::enable_unique_file_names));
    BOOST_CHECK(is_true(st, tags::cpp::enable_facet_folders));
    BOOST_CHECK(is_true(st, tags::cpp::enable_facet_folders));
    BOOST_CHECK(is_true(st, tags::generate_preamble));
    BOOST_CHECK(get(st, tags::cpp::forward_declaration_postfix) ==
        default_cpp_forward_declaration_postfix);
    BOOST_CHECK(get(st, tags::cpp::implementation_file_extension) ==
        default_cpp_implementation_file_extension);
    BOOST_CHECK(get(st, tags::cpp::header_file_extension) ==
        default_cpp_header_file_extension);
}

BOOST_AUTO_TEST_SUITE_END()

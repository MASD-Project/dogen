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
#include "dogen/om/types/all.hpp"
#include "dogen/om/io/all_io.hpp"
#include "dogen/om/test_data/all_td.hpp"

namespace {

const std::string empty;
const std::string test_module("om");
const std::string test_suite("cpp_file_boilerplate_formatter_spec");

dogen::om::modeline mock_modeline(const dogen::om::modeline_locations l) {
    dogen::om::modeline r;
    r.editor(dogen::om::editors::emacs);
    r.location(l);

    using dogen::om::modeline_field;
    modeline_field mf;
    mf.name("a_field");
    mf.value("a_value");

    r.fields(std::list<modeline_field>{ mf });
    return r;
}

dogen::om::licence mock_licence() {
    dogen::om::licence r;
    r.copyright_holders(std::list<std::string>{"a_holder"});
    r.text("a licence");
    return r;
}

dogen::om::cpp_includes mock_includes() {
    dogen::om::cpp_includes r;
    r.user(std::list<std::string>{"user_include"});
    r.system(std::list<std::string>{"system_include"});
    return r;
}

}

using namespace dogen::om;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(cpp_file_boilerplate_formatter)

BOOST_AUTO_TEST_CASE(boilerplate_with_top_modeline_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("boilerplate_with_top_modeline_is_formatted_correctly");

    const auto m(mock_modeline(dogen::om::modeline_locations::top));
    const auto l(mock_licence());
    const std::string marker("this is a marker");
    const cpp_includes i(mock_includes());
    const boost::filesystem::path p("a/path.hpp");

    std::ostringstream s;
    dogen::om::cpp_file_boilerplate_formatter f;
    f.format_begin(s, l, m, marker, i, p);
    f.format_end(s, m);
    const auto r(s.str());
    // BOOST_CHECK(!r.empty());
    BOOST_LOG_SEV(lg, debug) << "contents: " << r;
}

BOOST_AUTO_TEST_SUITE_END()

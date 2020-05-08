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
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.templating/io/wale/text_template_io.hpp"
#include "dogen.templating/types/wale/formatter.hpp"

namespace {

const std::string test_module("dogen.templating.tests");
const std::string test_suite("wale_formatter_tests");

const std::string trivial_template_content(R"(<#+
some content {{one}} some content
some content {{two}} some content
some content {{three}} some content
some content {{four}}some content
some content{{five}}some content
{ { fake_key } }
#>)");

const std::string trivial_template_output(R"(<#+
some content um some content
some content dois some content
some content três some content
some content quatrosome content
some contentcincosome content
{ { fake_key } }
#>)");

}

BOOST_AUTO_TEST_SUITE(wale_formatter_tests)

BOOST_AUTO_TEST_CASE(trivial_template_formats_correctly) {
    SETUP_TEST_LOG_SOURCE("trivial_template_formats_correctly");

    dogen::templating::wale::text_template tt;
    tt.supplied_kvps(std::unordered_map<std::string, std::string> {
            { "one", "um" },
            { "two", "dois" },
            { "three", "três" },
            { "four", "quatro" },
            { "five", "cinco" } });
    tt.content(trivial_template_content);
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto& e(trivial_template_output);
    BOOST_LOG_SEV(lg, debug) << "expected: " << e;

    dogen::templating::wale::formatter f;
    const auto a(f.format(tt));
    BOOST_LOG_SEV(lg, debug) << "actual: " << a;

    BOOST_CHECK(a == e);
}

BOOST_AUTO_TEST_SUITE_END()

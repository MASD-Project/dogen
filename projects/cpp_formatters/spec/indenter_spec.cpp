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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/cpp_formatters/types/indenter.hpp"

namespace {

const std::string empty;
const std::string test_module("cpp");
const std::string test_suite("indenter_spec");

}

BOOST_AUTO_TEST_SUITE(indenter)

BOOST_AUTO_TEST_CASE(default_indenter_does_not_indent) {
    SETUP_TEST_LOG_SOURCE("default_indenter_does_not_indent");
    dogen::cpp_formatters::indenter i;
    std::ostringstream stream;
    stream << i;
    BOOST_CHECK(stream.str().empty());
    BOOST_CHECK(i.empty());
    BOOST_LOG_SEV(lg, debug) << "zero indent: '" << i << "'";
}

BOOST_AUTO_TEST_CASE(indenting_increases_indentation_level) {
    SETUP_TEST_LOG_SOURCE("indenting_increases_indentation_level");
    dogen::cpp_formatters::indenter i;
    std::ostringstream stream;
    stream << (++i);
    BOOST_CHECK(!stream.str().empty());
    BOOST_CHECK(!i.empty());
    BOOST_LOG_SEV(lg, debug) << "one indent: '" << i << "'";

    unsigned int one_indent_size(stream.str().length());
    stream.str(empty);
    stream << (++i);
    BOOST_CHECK(!i.empty());
    BOOST_CHECK(stream.str().length() == 2 * one_indent_size);
    BOOST_LOG_SEV(lg, debug) << "two indent: '" << i << "'";

    stream.str(empty);
    stream << (++i);
    BOOST_CHECK(!i.empty());
    BOOST_CHECK(stream.str().length() == 3 * one_indent_size);
    BOOST_LOG_SEV(lg, debug)  << "three indent: '" << i << "'";
}

BOOST_AUTO_TEST_CASE(unindenting_decreases_indentation_level) {
    SETUP_TEST_LOG_SOURCE("unindenting_decreases_indentation_level");
    dogen::cpp_formatters::indenter i;
    BOOST_CHECK(i.empty());

    std::ostringstream stream;
    stream << (++i);
    BOOST_CHECK(!stream.str().empty());
    BOOST_CHECK(!i.empty());

    unsigned int one_indent_size(stream.str().length());
    ++i;

    stream.str(empty);
    stream << (++i);
    BOOST_CHECK(stream.str().length() == 3 * one_indent_size);
    BOOST_LOG_SEV(lg, debug) << "three indent: '" << i << "'";

    stream.str(empty);
    stream << (--i);
    BOOST_CHECK(stream.str().length() == 2 * one_indent_size);
    BOOST_LOG_SEV(lg, debug) << "two indent: '" << i << "'";

    stream.str(empty);
    stream << (--i);
    BOOST_CHECK(stream.str().length() == one_indent_size);
    BOOST_LOG_SEV(lg, debug) << "one indent: '" << i << "'";

    stream.str(empty);
    stream << (--i);
    BOOST_CHECK(stream.str().empty());
    BOOST_CHECK(i.empty());
    BOOST_LOG_SEV(lg, debug) << "zero indent: '" << i << "'";
}

BOOST_AUTO_TEST_CASE(unindenting_at_zero_indentation_level_does_nothing) {
    SETUP_TEST_LOG("unindenting_at_zero_indentation_level_does_nothing");
    dogen::cpp_formatters::indenter i;

    std::ostringstream stream;
    stream << (--i);
    BOOST_CHECK(stream.str().empty());

    stream << (++i);
    BOOST_CHECK(!stream.str().empty());
}

BOOST_AUTO_TEST_CASE(positive_indenter_scope_correctly_increases_and_decreases_indentation_level) {
    SETUP_TEST_LOG("positive_indenter_scope_correctly_increases_and_decreases_indentation_level");
    dogen::cpp_formatters::indenter i;

    std::ostringstream stream;
    stream << i;
    BOOST_CHECK(stream.str().empty());
    {
        dogen::cpp_formatters::positive_indenter_scope s(i);
        stream << i;
        BOOST_CHECK(!stream.str().empty());
        unsigned int one_indent_size(stream.str().length());
        {
            dogen::cpp_formatters::positive_indenter_scope s(i);
            stream.str(empty);
            stream << i;
            BOOST_CHECK(stream.str().length() == 2 * one_indent_size);
        }
        stream.str(empty);
        stream << i;
        BOOST_CHECK(stream.str().length() == one_indent_size);
    }
    stream.str(empty);
    stream << i;
    BOOST_CHECK(stream.str().empty());
}

BOOST_AUTO_TEST_CASE(negative_indenter_scope_correctly_decreases_and_increases_indentation_level) {
    SETUP_TEST_LOG_SOURCE("negative_indenter_scope_correctly_decreases_and_increases_indentation_level");
    dogen::cpp_formatters::indenter i;

    std::ostringstream stream;
    stream << i;
    BOOST_CHECK(stream.str().empty());

    stream << (++i);
    BOOST_CHECK(!stream.str().empty());
    unsigned int one_indent_size(stream.str().length());
    ++i;
    {
        dogen::cpp_formatters::negative_indenter_scope s(i);
        stream.str(empty);
        stream << i;
        BOOST_CHECK(stream.str().length() == one_indent_size);
        {
            dogen::cpp_formatters::negative_indenter_scope s(i);
            stream.str(empty);
            stream << i;
            BOOST_CHECK(stream.str().empty());
        }
        stream.str(empty);
        stream << i;
        BOOST_CHECK(stream.str().length() == one_indent_size);
    }
    stream.str(empty);
    stream << i;
    BOOST_CHECK(stream.str().length() == 2 * one_indent_size);
}

BOOST_AUTO_TEST_CASE(negative_indenter_scope_correctly_handles_zero_indentation_level) {
    SETUP_TEST_LOG("negative_indenter_scope_correctly_handles_zero_indentation_level");
    dogen::cpp_formatters::indenter i;

    std::ostringstream stream;
    stream << i;
    BOOST_CHECK(stream.str().empty());
    {
        dogen::cpp_formatters::negative_indenter_scope s(i);
        stream.str(empty);
        stream << i;
        BOOST_CHECK(stream.str().empty());
    }
    stream.str(empty);
    stream << i;
    BOOST_CHECK(stream.str().empty());
}

BOOST_AUTO_TEST_SUITE_END()

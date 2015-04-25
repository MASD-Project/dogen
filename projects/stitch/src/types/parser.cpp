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
#include <memory>
#include <sstream>
#include <functional>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/stitch/io/text_template_io.hpp"
#include "dogen/stitch/types/parsing_error.hpp"
#include "dogen/stitch/types/parser.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("stitch.parser"));

const std::string empty;
const std::string equals("=");
const std::string start_scriptlet_block("<#+");
const std::string start_scriptlet_segment("<#=");
const std::string start_declaration("<#@");
const std::string end_block("#>");

const std::string error_msg("Failed to parse string: ");
const std::string cannot_start_scriptlet(
    "Cannot start scriptlet block in scriptlet block.");
const std::string cannot_start_scriptlet_in_middle(
    "Cannot start scriplet block in the middle of a line.");
const std::string scriptlet_expression_not_ended(
    "Scriptlet expressions must start and end in the same line.");
const std::string end_without_start("Found end block without a start block.");
const std::string unexpected_declaration("Unexpected declaration.");
const std::string unfinished_scriplet("Start scriptlet block without an end.");
const std::string unexpected_additional_content(
    "Unexpected additional content.");
const std::string unexpected_standard(
    "Standard control blocks are not supported in mixed lines");
const std::string separator_not_found("Expected separator on kvp.");

}

namespace dogen {
namespace stitch {

parser::parser(const dynamic::schema::workflow& w) : schema_workflow_(w) {}

text_template parser::parse(const std::string& s) const {
    BOOST_LOG_SEV(lg, debug) << "Parsing: " << s;
    if (s.empty())
        return text_template();

    text_template r;
    line output_line;
    bool in_scriplet_block(false), in_declarations_block(true);
    std::string input_line;
    std::istringstream is(s);
    std::list<std::pair<std::string, std::string> > kvps;
    while (std::getline(is, input_line)) {
        BOOST_LOG_SEV(lg, debug) << "Parsing line: " << input_line;

        if (boost::contains(input_line, start_scriptlet_segment)) {
            BOOST_LOG_SEV(lg, debug) << "Line has scriplet segment";

            unsigned int pos(0);
            const auto len(input_line.length());
            std::string s;
            bool in_expression(false);
            while (pos < len) {
                const auto c(input_line[pos]);
                BOOST_LOG_SEV(lg, debug) << "c: " << c;
                if (c == '<' && pos + 2 < len && input_line[pos + 1] == '#') {
                    const auto type(input_line[pos + 2]);
                    if (type == '@') {
                        BOOST_LOG_SEV(lg, error) << unexpected_declaration;
                        BOOST_THROW_EXCEPTION(
                            parsing_error(unexpected_declaration));
                    } else if (type == '+') {
                        BOOST_LOG_SEV(lg, error) << unexpected_standard;
                        BOOST_THROW_EXCEPTION(
                            parsing_error(unexpected_standard));
                    } else if (type == '=') {
                        BOOST_LOG_SEV(lg, debug) << "Line has expression start";
                        if (!s.empty()) {
                            segment sg;
                            sg.type(segment_types::text);
                            boost::trim(s);
                            sg.content(s);
                            output_line.segments().push_back(sg);
                            s.clear();
                        }

                        in_expression = true;
                        pos += 3;
                        continue;
                    }
                } else if (c == '#' && pos + 1 < len &&
                    input_line[pos + 1] == '>') {
                    BOOST_LOG_SEV(lg, debug) << "Line has expression end";
                    if (!in_expression) {
                        BOOST_LOG_SEV(lg, error) << end_without_start;
                        BOOST_THROW_EXCEPTION(parsing_error(end_without_start));
                    }

                    segment sg;
                    sg.type(segment_types::scriptlet);
                    boost::trim(s);
                    sg.content(s);
                    output_line.segments().push_back(sg);
                    s.clear();

                    in_expression = false;
                    pos += 2;
                    continue;
                }
                s += c;
                BOOST_LOG_SEV(lg, debug) << "s: " << s;
                ++pos;
            }

            if (in_expression) {
                BOOST_LOG_SEV(lg, error) << scriptlet_expression_not_ended;
                BOOST_THROW_EXCEPTION(
                    parsing_error(scriptlet_expression_not_ended));
            }

            if (!s.empty()) {
                segment sg;
                sg.type(segment_types::text);
                sg.content(s);
                output_line.segments().push_back(sg);
                s.clear();
            }
            r.lines().push_back(output_line);
            continue;
        }

        if (boost::starts_with(input_line, start_declaration)) {
            BOOST_LOG_SEV(lg, debug) << "Line is declaration";
            if (!in_declarations_block) {
                BOOST_LOG_SEV(lg, error) << unexpected_declaration;
                BOOST_THROW_EXCEPTION(parsing_error(unexpected_declaration));
            }

            boost::replace_all(input_line, start_declaration, empty);
            boost::replace_all(input_line, end_block, empty);
            boost::trim(input_line);

            const auto pos(input_line.find_first_of(equals));
            if (pos == std::string::npos) {
                BOOST_LOG_SEV(lg, error) << separator_not_found;
                BOOST_THROW_EXCEPTION(parsing_error(separator_not_found));
            }

            const auto key(input_line.substr(0, pos));
            const auto value(input_line.substr(pos + 1));
            kvps.push_back(std::make_pair(key, value));

            using dynamic::schema::scope_types;
            const auto scope(scope_types::root_module);
            r.extensions(schema_workflow_.execute(scope, kvps));
            continue;
        }

        in_declarations_block = false;

        if (boost::starts_with(input_line, start_scriptlet_block)) {
            BOOST_LOG_SEV(lg, debug) << "Line is scriplet";

            if (in_scriplet_block) {
                BOOST_LOG_SEV(lg, error) << cannot_start_scriptlet;
                BOOST_THROW_EXCEPTION(parsing_error(cannot_start_scriptlet));
            }

            if (boost::ends_with(input_line, end_block)) {
                BOOST_LOG_SEV(lg, debug) << "Line is one line scriplet";
                boost::replace_all(input_line, start_scriptlet_block, empty);
                boost::replace_all(input_line, end_block, empty);

                segment sg;
                sg.type(segment_types::scriptlet);
                boost::trim(input_line);
                sg.content(input_line);
                output_line.segments().push_back(sg);
                r.lines().push_back(output_line);
                output_line.segments().clear();
                continue;
            }

            if (input_line.size() != 3) {
                BOOST_LOG_SEV(lg, error) << unexpected_additional_content;
                BOOST_THROW_EXCEPTION(
                    parsing_error(unexpected_additional_content));
            }

            in_scriplet_block = true;
            continue;
        }

        if (boost::contains(input_line, start_scriptlet_block)) {
            BOOST_LOG_SEV(lg, error) << cannot_start_scriptlet_in_middle;
            BOOST_THROW_EXCEPTION(
                parsing_error(cannot_start_scriptlet_in_middle));
        }

        if (boost::contains(input_line, start_declaration)) {
            BOOST_LOG_SEV(lg, error) << unexpected_declaration;
            BOOST_THROW_EXCEPTION(parsing_error(unexpected_declaration));
        }

        if (boost::contains(input_line, end_block)) {
            BOOST_LOG_SEV(lg, debug) << "Closing end block";

            if (!in_scriplet_block) {
                BOOST_LOG_SEV(lg, error) << end_without_start;
                BOOST_THROW_EXCEPTION(parsing_error(end_without_start));
            }

            if (input_line.size() != 2) {
                BOOST_LOG_SEV(lg, error) << unexpected_additional_content;
                BOOST_THROW_EXCEPTION(
                    parsing_error(unexpected_additional_content));
            }

            if (in_scriplet_block) {
                BOOST_LOG_SEV(lg, debug) << "Closing scriptlet block";
                in_scriplet_block = false;
                continue;
            }
        }

        segment sg;
        sg.type(
            in_scriplet_block ? segment_types::scriptlet : segment_types::text);
        sg.content(input_line);
        output_line.segments().push_back(sg);
        r.lines().push_back(output_line);
        output_line.segments().clear();
    }

    if (in_scriplet_block) {
        BOOST_LOG_SEV(lg, error) << unfinished_scriplet;
        BOOST_THROW_EXCEPTION(parsing_error(unfinished_scriplet));
    }

    BOOST_LOG_SEV(lg, debug) << "Finished parsing.";
    BOOST_LOG_SEV(lg, debug) << "result: " << r;
    return r;
}

} }

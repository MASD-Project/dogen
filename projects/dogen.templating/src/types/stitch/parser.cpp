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
#include <memory>
#include <sstream>
#include <string_view>
#include <functional>
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.templating/io/stitch/line_io.hpp"
#include "dogen.templating/types/stitch/parsing_error.hpp"
#include "dogen.templating/io/stitch/text_template_body_io.hpp"
#include "dogen.templating/types/stitch/parser.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("templating.stitch.parser"));

constexpr std::string_view empty;
constexpr std::string_view equals("=");
constexpr std::string_view start_expression_block_marker("<#=");
constexpr std::string_view start_standard_control_block_marker("<#+");
constexpr std::string_view start_directive_marker("<#@");
constexpr std::string_view start_variable_marker("<#$");
constexpr std::string_view end_block_marker("#>");

const std::string error_msg("Failed to parse string: ");
const std::string cannot_start_expression_block(
    "Cannot start expression block in expresion block.");
const std::string cannot_start_standard_control_block(
    "Cannot start standard control block in standard control block.");
const std::string cannot_start_standard_control_block_in_middle(
    "Cannot start standard control block in the middle of a line.");
const std::string expression_block_not_ended(
    "Expression blocks must start and end in the same line.");
const std::string end_marker_without_start_marker(
    "Found end block marker without a corresponding start block marker.");
const std::string unexpected_directive("Unexpected directive.");
const std::string unfinished_control_block(
    "Start control block without an end.");
const std::string unexpected_additional_content(
    "Unexpected additional content.");
const std::string unexpected_standard(
    "Standard control blocks are not supported in mixed lines");
const std::string separator_not_found("Expected separator on kvp.");
const std::string invalid_directive(
    "Invalid characters used in directive: ");

const bool do_trim(true);

}

namespace dogen::templating::stitch {

block parser::create_block(const block_types bt, const std::string& c,
    const bool trim) const {
    block r;
    r.type(bt);
    r.content(trim ? boost::trim_copy(c) : c);
    return r;
}

block parser::create_text_block(const std::string& c, const bool trim) const {
    return create_block(block_types::text_block, c, trim);
}

block parser::create_standard_control_block(const std::string& c,
    const bool trim) const {
    return create_block(block_types::standard_control_block, c, trim);
}

block parser::create_expression_block(const std::string& c,
    const bool trim) const {
    return create_block(block_types::expression_block, c, trim);
}

line parser::
parse_expression_block(const std::string& input_line) const {
    BOOST_LOG_SEV(lg, debug) << "Parsing line with expression block.";

    std::string s;
    unsigned int pos(0);
    bool in_expression(false);
    std::list<block> blocks;
    const auto len(input_line.length());
    while (pos < len) {
        const auto c(input_line[pos]);
        BOOST_LOG_SEV(lg, debug) << "c: " << c;
        if (c == '<' && pos + 2 < len && input_line[pos + 1] == '#') {
            const auto type(input_line[pos + 2]);
            if (type == '@') {
                BOOST_LOG_SEV(lg, error) << unexpected_directive;
                BOOST_THROW_EXCEPTION(parsing_error(unexpected_directive));
            } else if (type == '+') {
                BOOST_LOG_SEV(lg, error) << unexpected_standard;
                BOOST_THROW_EXCEPTION(parsing_error(unexpected_standard));
            } else if (type == '=') {
                BOOST_LOG_SEV(lg, debug) << "Line has expression start";

                if (in_expression) {
                    BOOST_LOG_SEV(lg, error) << cannot_start_expression_block;
                    BOOST_THROW_EXCEPTION(
                        parsing_error(cannot_start_expression_block));
                }

                if (!s.empty()) {
                    blocks.push_back(create_text_block(s));
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
                BOOST_LOG_SEV(lg, error) << end_marker_without_start_marker;
                BOOST_THROW_EXCEPTION(parsing_error(
                        end_marker_without_start_marker));
            }

            blocks.push_back(create_expression_block(s, do_trim));
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
        BOOST_LOG_SEV(lg, error) << expression_block_not_ended;
        BOOST_THROW_EXCEPTION(parsing_error(expression_block_not_ended));
    }

    if (!s.empty()) {
        blocks.push_back(create_text_block(s));
        s.clear();
    }

    BOOST_LOG_SEV(lg, debug) << "Finished parsing line with expression block.";

    const line r(blocks);
    BOOST_LOG_SEV(lg, debug) << "Line: " << r;
    return r;
}

line parser::
parse_inline_standard_control_block(const std::string& input_line) const {
    BOOST_LOG_SEV(lg, debug) << "Line is inline control block";
    auto cooked_line(input_line);
    boost::replace_all(cooked_line, start_standard_control_block_marker, empty);
    boost::replace_all(cooked_line, end_block_marker, empty);

    const auto b(create_standard_control_block(cooked_line, do_trim));
    line r;
    r.blocks().push_back(b);
    return r;
}

identification::entities::tagged_value parser::
parse_directive(const std::string& input_line) const {

    auto cooked_line(input_line);
    boost::replace_first(cooked_line, start_directive_marker, empty);
    boost::replace_last(cooked_line, end_block_marker, empty);
    boost::trim(cooked_line);

    const std::string reserved("<#");
    if (boost::contains(cooked_line, reserved)) {
        BOOST_LOG_SEV(lg, error) << invalid_directive << cooked_line;
        BOOST_THROW_EXCEPTION(parsing_error(invalid_directive + cooked_line));
    }

    if (boost::contains(cooked_line, end_block_marker)) {
        BOOST_LOG_SEV(lg, error) << invalid_directive << cooked_line;
        BOOST_THROW_EXCEPTION(parsing_error(invalid_directive + cooked_line));
    }

    const auto pos(cooked_line.find_first_of(equals));
    if (pos == std::string::npos) {
        BOOST_LOG_SEV(lg, error) << separator_not_found << cooked_line;
        BOOST_THROW_EXCEPTION(parsing_error(separator_not_found + cooked_line));
    }

    identification::entities::tagged_value r;
    r.tag(cooked_line.substr(0, pos));
    r.value(cooked_line.substr(pos + 1));
    return r;
}

line parser::parse_variable(const std::string& input_line) const {
    auto cooked_line(input_line);
    boost::replace_first(cooked_line, start_variable_marker, empty);
    boost::replace_last(cooked_line, end_block_marker, empty);
    boost::trim(cooked_line);

    const std::string reserved("<#");
    if (boost::contains(cooked_line, reserved)) {
        BOOST_LOG_SEV(lg, error) << invalid_directive << cooked_line;
        BOOST_THROW_EXCEPTION(parsing_error(invalid_directive + cooked_line));
    }

    if (boost::contains(cooked_line, end_block_marker)) {
        BOOST_LOG_SEV(lg, error) << invalid_directive << cooked_line;
        BOOST_THROW_EXCEPTION(parsing_error(invalid_directive + cooked_line));
    }

    block b;
    b.type(block_types::variable_block);
    b.content(cooked_line);
    const line r(std::list<block> { b });
    return r;
}

text_template_body parser::parse(const std::string& s) const {
    BOOST_LOG_SEV(lg, debug) << "Parsing: " << s;
    if (s.empty())
        return text_template_body();

    std::list<line> lines;
    unsigned int line_number(0);
    std::list<identification::entities::tagged_value> tvs;
    try {
        line output_line;
        bool in_standard_control_block(false), in_directives_block(true);
        std::string input_line;
        std::istringstream is(s);

        while (std::getline(is, input_line)) {
            ++line_number;
            BOOST_LOG_SEV(lg, debug) << "Parsing line: " << input_line;

            if (boost::contains(input_line, start_expression_block_marker)) {
                lines.push_back(parse_expression_block(input_line));
                continue;
            }

            if (boost::starts_with(input_line, start_directive_marker)) {
                BOOST_LOG_SEV(lg, debug) << "Line is directive";
                if (!in_directives_block) {
                    BOOST_LOG_SEV(lg, error) << unexpected_directive;
                    BOOST_THROW_EXCEPTION(
                        parsing_error(unexpected_directive));
                }

                tvs.push_back(parse_directive(input_line));
                continue;
            }

            if (boost::starts_with(input_line, start_variable_marker)) {
                BOOST_LOG_SEV(lg, debug) << "Line is a variable";
                lines.push_back(parse_variable(input_line));
                continue;
            }

            in_directives_block = false;

            if (boost::starts_with(input_line,
                    start_standard_control_block_marker)) {
                BOOST_LOG_SEV(lg, debug) << "Line is standard control block";

                if (in_standard_control_block) {
                    BOOST_LOG_SEV(lg, error)
                        << cannot_start_standard_control_block;
                    BOOST_THROW_EXCEPTION(
                        parsing_error(cannot_start_standard_control_block));
                }

                if (boost::ends_with(input_line, end_block_marker)) {
                    const auto l(parse_inline_standard_control_block(
                            input_line));
                    lines.push_back(l);
                    continue;
                }

                if (input_line.size() != 3) {
                    BOOST_LOG_SEV(lg, error) << unexpected_additional_content;
                    BOOST_THROW_EXCEPTION(
                        parsing_error(unexpected_additional_content));
                }

                in_standard_control_block = true;
                continue;
            }

            if (boost::contains(input_line,
                    start_standard_control_block_marker)) {
                BOOST_LOG_SEV(lg, error)
                    << cannot_start_standard_control_block_in_middle;
                BOOST_THROW_EXCEPTION(parsing_error(
                        cannot_start_standard_control_block_in_middle));
            }

            if (boost::contains(input_line, start_directive_marker)) {
                BOOST_LOG_SEV(lg, error) << unexpected_directive;
                BOOST_THROW_EXCEPTION(parsing_error(unexpected_directive));
            }

            if (boost::contains(input_line, end_block_marker)) {
                BOOST_LOG_SEV(lg, debug) << "Closing end block";

                if (!in_standard_control_block) {
                    BOOST_LOG_SEV(lg, error) << end_marker_without_start_marker;
                    BOOST_THROW_EXCEPTION(
                        parsing_error(end_marker_without_start_marker));
                }

                if (input_line.size() != 2) {
                    BOOST_LOG_SEV(lg, error) << unexpected_additional_content;
                    BOOST_THROW_EXCEPTION(
                        parsing_error(unexpected_additional_content));
                }

                if (in_standard_control_block) {
                    BOOST_LOG_SEV(lg, debug)
                        << "Closing standard control block";
                    in_standard_control_block = false;
                    continue;
                }
            }

            block b;
            b.type(in_standard_control_block ?
                block_types::standard_control_block : block_types::text_block);
            b.content(input_line);
            output_line.blocks().push_back(b);
            lines.push_back(output_line);
            output_line.blocks().clear();
        }

        if (in_standard_control_block) {
            BOOST_LOG_SEV(lg, error) << unfinished_control_block;
            BOOST_THROW_EXCEPTION(parsing_error(unfinished_control_block));
        }
    } catch (boost::exception& e) {
        e << error_at_line(boost::lexical_cast<std::string>(line_number));
        throw;
    }

    text_template_body r;
    r.tagged_values(tvs);
    r.lines(lines);

    BOOST_LOG_SEV(lg, debug) << "Finished parsing. Result: " << r;
    return r;
}

}

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
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/stitch/types/parsing_error.hpp"
#include "dogen/stitch/types/parser.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("stitch.parser"));

const std::string start_scriptlet_block("<#+");
const std::string start_scriptlet_segment("<#=");
const std::string start_declaration("<#@");
const std::string end_block("#>");

const std::string cannot_start_scriptlet(
    "Cannot start scriptlet block in scriptlet block.");
const std::string end_without_start("Found end block without a start block.");
const std::string unexpected_declaration("Unexpected declaration.");
const std::string unfinished_scriplet("Start scriptlet block without an end.");
const std::string unexpected_additional_content(
    "Unexpected additional content.");

}

namespace dogen {
namespace stitch {

text_template parser::parse(const std::string& s) const {
    text_template r;

    if (s.empty())
        return r;

    scriptlet_block sb;
    mixed_content_block mcb;
    bool in_scriplet_block(false), in_mixed_content_block(false),
        in_declarations_block(true);
    std::string line;
    std::istringstream is(s);
    while (std::getline(is, line)) {
        if (boost::starts_with(line, start_declaration)) {
            BOOST_LOG_SEV(lg, debug) << "is declaration";
            if (!in_declarations_block) {
                BOOST_LOG_SEV(lg, error) << unexpected_declaration;
                BOOST_THROW_EXCEPTION(parsing_error(unexpected_declaration));
            }

            // FIXME
            continue;
        }
        in_declarations_block = false;

        if (boost::starts_with(line, start_scriptlet_block)) {
            if (line.size() != 3) {
                BOOST_LOG_SEV(lg, error) << unexpected_additional_content;
                BOOST_THROW_EXCEPTION(
                    parsing_error(unexpected_additional_content));
            }

            BOOST_LOG_SEV(lg, debug) << "is scriplet";

            if (in_scriplet_block) {
                BOOST_LOG_SEV(lg, error) << cannot_start_scriptlet;
                BOOST_THROW_EXCEPTION(parsing_error(cannot_start_scriptlet));
            }
            in_scriplet_block = true;

            if (in_mixed_content_block) {
                BOOST_LOG_SEV(lg, debug) << "closing mixed content";
                in_mixed_content_block = false;
                r.content().push_back(mcb);
                mcb.content().clear();
            }
            continue;
        }

        if (boost::starts_with(line, end_block)) {
            BOOST_LOG_SEV(lg, debug) << "is end block";

            if (line.size() != 2) {
                BOOST_LOG_SEV(lg, error) << unexpected_additional_content;
                BOOST_THROW_EXCEPTION(
                    parsing_error(unexpected_additional_content));
            }

            if (!in_scriplet_block && !in_mixed_content_block) {
                BOOST_LOG_SEV(lg, error) << end_without_start;
                BOOST_THROW_EXCEPTION(parsing_error(end_without_start));
            }

            if (in_scriplet_block) {
                BOOST_LOG_SEV(lg, debug) << "closing scriptlet block";

                in_scriplet_block = false;
                r.content().push_back(sb);
                sb.content().clear();
                continue;
            }

            BOOST_LOG_SEV(lg, debug) << "closing mixed content block";
            in_mixed_content_block = false;
            r.content().push_back(mcb);
            mcb.content().clear();
            continue;
        }

        if (in_scriplet_block) {
            BOOST_LOG_SEV(lg, debug) << "line in scriptlet block";
            sb.content().push_back(line);
            continue;
        }

        const auto i(line.find_first_of(start_scriptlet_segment));
        const bool has_mixed_content(i != std::string::npos);
        if (has_mixed_content) {
            BOOST_LOG_SEV(lg, debug) << "mixed content line";
            // FIXME
            continue;
        }

        in_mixed_content_block = true;
        BOOST_LOG_SEV(lg, debug) << "text line";
        mcb.content().push_back(line);
    }

    if (in_scriplet_block) {
        BOOST_LOG_SEV(lg, error) << unfinished_scriplet;
        BOOST_THROW_EXCEPTION(parsing_error(unfinished_scriplet));
    }

    if (in_mixed_content_block) {
        BOOST_LOG_SEV(lg, debug) << "finishing mixed content block";
        r.content().push_back(mcb);
    }

    return r;
}

} }

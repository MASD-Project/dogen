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
#include <regex>
#include <sstream>
#include <boost/throw_exception.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen.org/types/entities/affiliated_keyword.hpp"
#include "dogen.org/types/entities/block_type.hpp"
#include "dogen.org/types/entities/drawer_type.hpp"
#include "dogen.org/types/entities/tag.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.org/io/entities/document_io.hpp"
#include "dogen.org/types/helpers/parsing_error.hpp"
#include "dogen.org/types/helpers/parser.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("org.helpers.parser"));

const std::string empty;
const std::string space(" ");
const std::string colon(":");
const std::string property_drawer_start(":PROPERTIES:");
const std::string property_drawer_end(":END:");

const std::regex headline_regex("^\\*+\\s.+");
const std::regex priority_cookie_regex("^\\[#[a-zA-Z]\\]");
const std::regex todo_keyword_regex("^[A-Z].*");
const std::regex tags_regex("^\\:\\w+(:\\w+)*\\:");
const std::regex drawer_regex("^\\:\\w+\\:");
const std::regex drawer_content_regex("^\\:\\w+\\:\\s.+");
const std::regex affiliated_keyword_regex("^#\\+\\w+:\\s.*");

}

namespace dogen::org::helpers {

bool parser::is_empty_or_whitespace(const std::string& s) {
    const auto trimmed(boost::algorithm::trim_copy(s));
    if (trimmed.empty()) {
        BOOST_LOG_SEV(lg, debug) << "Line is empty or whitespace.";
        return true;
    }
    return false;
}

boost::optional<entities::headline>
parser::try_parse_headline(const std::string& s) {
    /*
     * If there is only white space in the string, there is nothing to
     * worry about.
     */
    if (is_empty_or_whitespace(s))
        return boost::optional<entities::headline>();

    /*
     * According to the org spec, a headline is defined as:
     *
     *    STARS KEYWORD PRIORITY TITLE TAGS
     *
     * Only lines starting with asterisks followed by a space are
     * considered headlines, so, if we're not one of those, there is
     * nothing to do.
     */
    if (!std::regex_match(s, headline_regex)) {
        BOOST_LOG_SEV(lg, debug) << "Line is not a headline.";
        return boost::optional<entities::headline>();
    }

    /*
     * Retrieve the asterisks and count them to determine the level.
     */
    BOOST_LOG_SEV(lg, debug) << "Line is a headline.";
    std::istringstream is(s);
    std::string token;
    is >> token;

    entities::headline r;
    r.level(static_cast<unsigned int>(token.size()));

    /*
     * The next element is the optional "keyword". We don't actually
     * validate we're one of the setup TODO keywords; instead we just
     * check to see if it matches our regex. If it is, we assume it
     * must be a valid keyword.
     */
    is >> token;
    if (std::regex_match(token, todo_keyword_regex)) {
        BOOST_LOG_SEV(lg, debug) << "Found a TODO keyword: " << token;
        r.todo_keyword(entities::todo_keyword(token));

        is >> token;
        if (is.fail()) {
            BOOST_LOG_SEV(lg, debug) << "Nothing left to read after keyword.";
            return r;
        }
    }

    /*
     * Priority cookies have the form [#CHARACTER].
     */
    if (std::regex_match(token, priority_cookie_regex)) {
        BOOST_LOG_SEV(lg, debug) << "Found a priority cookie: " << token;
        r.priority(entities::priority_cookie(token));

        is >> token;
        if (is.fail()) {
            BOOST_LOG_SEV(lg, debug) << "Nothing left to read after cookie.";
            return r;
        }
    }

    /*
     * Read all tokens until we reach the end or find a tag. These
     * tokens will make up the title.
     */
    bool found_tag(false);
    bool is_first(true);
    std::ostringstream os;
    do {
        BOOST_LOG_SEV(lg, debug) << "Processing token: '" << token << "'";
        if (std::regex_match(token, tags_regex)) {
            BOOST_LOG_SEV(lg, debug) << "Found tags.";
            found_tag = true;
            break;
        }

        BOOST_LOG_SEV(lg, debug) << "Not a tag.";
        if (is_first) {
            os << token;
            is_first = false;
        } else {
            /*
             * Note that we assume that the word delimiter is space,
             * for simplicity. At any rate, in Dogen we do not use
             * delimiters at present.
             */
            os << space << token;
        }
    } while(!found_tag && is >> token);
    r.title(os.str());

    /*
     * If we did find a tag, we need to split the string into its
     * constituent tags.
     */
    if (found_tag) {
        std::list<std::string> tags;
        boost::split(tags, token, boost::is_any_of(colon));
        for (const auto& tag : tags) {
            /*
             * For some reason, boost split returns the position of
             * the delimiters as empty strings, so we need to skip
             * those.
             */
            if (!tag.empty())
                r.tags().push_back(entities::tag(tag));
        }
    }

    return r;
}

boost::optional<entities::affiliated_keyword>
parser::try_parse_affiliated_keyword(const std::string& s) {
    /*
     * If there is only white space in the string, there is nothing to
     * worry about.
     */
    if (is_empty_or_whitespace(s))
        return boost::optional<entities::affiliated_keyword>();

    /*
     * As per org documentation: Affiliated keywords are built upon
     * one of the following patterns:
     *
     *   #+KEY: VALUE
     *   #+KEY[OPTIONAL]: VALUE
     *   #+ATTR_BACKEND: VALUE
     *
     * We only support the first and last syntax.
     */
    if (!std::regex_match(s, affiliated_keyword_regex)) {
        BOOST_LOG_SEV(lg, debug) << "Line is not an affiliated keyword.";
        return boost::optional<entities::affiliated_keyword>();
    }

    /*
     * Extract the key and value from the keywords. We move plus or
     * minus two of the colon to avoid the colon itself as well as the
     * spaces. These are known to be there due to the regex we used to
     * find keywords.
     */
    entities::affiliated_keyword r;
    const auto colon_pos(s.find_first_of(colon));
    r.key(s.substr(2, colon_pos - 2));
    r.value(s.substr(colon_pos + 2));
    return r;
}

boost::optional<entities::drawer>
parser::try_parse_drawer_start(const std::string& s) {
    /*
     * If there is only white space in the string, there is nothing to
     * worry about.
     */
    if (is_empty_or_whitespace(s))
        return boost::optional<entities::drawer>();

    /*
     * If we match the drawer end, we're not a drawer.
     */
    if (is_drawer_end(s))
        return boost::optional<entities::drawer>();

    /*
     * Check to see if the string matches the expected shape of the
     * start of a drawer.
     */
    if (!std::regex_match(s, drawer_regex)) {
        BOOST_LOG_SEV(lg, debug) << "Line is not the start of a drawer.";
        return boost::optional<entities::drawer>();
    }

    entities::drawer r;
    r.name(boost::replace_all_copy(s, colon, empty));

    using entities::drawer_type;
    const bool is_property(boost::to_upper_copy(s) == property_drawer_start);
    r.type(is_property ? drawer_type::property_drawer : drawer_type::regular);
    BOOST_LOG_SEV(lg, debug) << "Created drawer: '" << r.name()
                             << "'. Is property drawer: "
                             << is_property;
    return r;
}

bool parser::is_drawer_end(const std::string& s) {
    return boost::to_upper_copy(s) == property_drawer_end;
}

entities::drawer_content parser::parse_drawer_content(const std::string& s) {
    /*
     * If the line has no discernible structure, just push it as a
     * value.
     */
    entities::drawer_content r;
    if (is_empty_or_whitespace(s) ||
        !std::regex_match(s, drawer_content_regex)) {
        BOOST_LOG_SEV(lg, debug) << "Drawer contents have no structure.";
        r.value(s);
        return r;
    }

    /*
     * The structure of a property drawer is:
     *
     *    :KEY: VALUE
     */
    BOOST_LOG_SEV(lg, debug) << "Drawer contents are a KVP.";
    const auto first_colon_pos(s.find_first_of(colon));
    const auto second_colon_pos(s.find_first_of(colon, first_colon_pos + 1));
    r.key(s.substr(first_colon_pos + 1, second_colon_pos - 1));
    r.value(s.substr(second_colon_pos + 2)); // +2 to skip the space in-between
    return r;
}

}

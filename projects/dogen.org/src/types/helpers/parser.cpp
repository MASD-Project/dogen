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
#include "dogen.org/types/entities/block_type.hpp"
#include "dogen.org/types/entities/tag.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.org/io/entities/document_io.hpp"
#include "dogen.org/types/helpers/parsing_error.hpp"
#include "dogen.org/types/helpers/parser.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("org.helpers.parser"));

const std::string space(" ");
const std::string tag_start(":");
const std::regex headline_regex("^\\*+\\s.+");
const std::regex priority_cookie_regex("^\\[#[a-zA-Z]\\]");
const std::regex todo_keyword_regex("^[A-Z].*");
const std::regex tags_regex("^\\:\\w+(:\\w+)*\\:");

}

namespace dogen::org::helpers {

boost::optional<entities::headline>
parser::try_parse_headline(const std::string& s) {
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
     * check to see if its upper case. If it is, we assume it must be
     * a keyword.
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
        boost::split(tags, token, boost::is_any_of(":"));
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

}

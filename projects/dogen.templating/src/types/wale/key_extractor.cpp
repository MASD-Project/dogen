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
#include <sstream>
#include "dogen.utility/log/logger.hpp"
#include "dogen.utility/io/unordered_set_io.hpp"
#include "dogen.templating/types/wale/extraction_error.hpp"
#include "dogen.templating/types/wale/key_extractor.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("templating.wale.key_extractor"));

const char dot('.');
const char underscore('_');
const char open_curly('{');
const char close_curly('}');

const std::string unexpected_character_in_key("Unexpected character in key: ");
const std::string eol_before_close("Reached EOL before finding close markers");

}

namespace dogen {
namespace templating {
namespace wale {

enum states {
    waiting_first_open,
    waiting_second_open,
    waiting_first_close,
    waiting_second_close
};

void key_extractor::check_first_char(const char c) const {
    if (std::isalpha(c, locale_))
        return;

    BOOST_LOG_SEV(lg, error) << unexpected_character_in_key + c;
    BOOST_THROW_EXCEPTION(extraction_error(unexpected_character_in_key + c));
}

void key_extractor::check_char(const char c) const {
    if (std::isalnum(c, locale_) || c == dot || c == underscore)
        return;

    BOOST_LOG_SEV(lg, error) << unexpected_character_in_key + c;
    BOOST_THROW_EXCEPTION(extraction_error(unexpected_character_in_key + c));
}

std::unordered_set<std::string>
key_extractor::extract(const std::string& s) const {
    BOOST_LOG_SEV(lg, debug) << "Started key extraction.";
    std::unordered_set<std::string> r;
    std::string current_key;
    states state(waiting_first_open);

    std::string line;
    std::istringstream is(s);

    while (std::getline(is, line)) {
        BOOST_LOG_SEV(lg, debug) << "Reading line: " << line;
        for (const auto c : line) {
            if (c == open_curly) {
                if (state == waiting_first_open) {
                    state = waiting_second_open;
                    BOOST_LOG_SEV(lg, debug) << "State: waiting_second_open.";
                    continue;
                } else if (state == waiting_second_open) {
                    state = waiting_first_close;
                    BOOST_LOG_SEV(lg, debug) << "State: waiting_first_close.";
                    continue;
                }
            } else if (c == close_curly) {
                if (state == waiting_first_close) {
                    state = waiting_second_close;
                    BOOST_LOG_SEV(lg, debug) << "State: waiting_second_close.";
                    continue;
                } else if (state == waiting_second_close) {
                    BOOST_LOG_SEV(lg, debug) << "Complete key: " << current_key;
                    r.insert(current_key);
                    current_key.clear();

                    state = waiting_first_open;
                    BOOST_LOG_SEV(lg, debug) << "State: waiting_first_open.";
                    continue;
                }
            }

            if (state == waiting_second_open) {
                state = waiting_first_open;
                continue;
            } else if (state == waiting_first_close) {
                if (current_key.empty()) {
                    check_first_char(c);
                } else {
                    check_char(c);
                }
                current_key += c;
            } else if (state == waiting_second_close) {
                BOOST_LOG_SEV(lg, error) << unexpected_character_in_key + c;
                BOOST_THROW_EXCEPTION(
                    extraction_error(unexpected_character_in_key + c));
            }
        }

        if (state == waiting_first_close || state == waiting_second_close) {
            BOOST_LOG_SEV(lg, error) << eol_before_close;
            BOOST_THROW_EXCEPTION(extraction_error(eol_before_close));
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished key extraction. Result: " << r;
    return r;
}

} } }

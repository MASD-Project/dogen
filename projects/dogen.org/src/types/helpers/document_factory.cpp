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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.org/types/helpers/builder.hpp"
#include "dogen.org/types/helpers/document_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("org.helpers.document_factory"));

const char carriage_return('\r');
const char line_feed('\n');

}

namespace dogen::org::helpers {

entities::document document_factory::make(const std::string& s) {
    BOOST_LOG_SEV(lg, debug) << "Building an org mode document.";

    /*
     * If there is no content, return an empty document.
     */
    if (s.empty()) {
        entities::document r;
        return r;
    }

    /*
     * Add one line at a time to our builder. Note that getline
     * consumes the new lines, so the builder has some special
     * handling to cope with that.
     */
    std::string line;
    std::istringstream is(s);
    helpers::builder b;
    while(std::getline(is, line))
        b.add_line(line);

    /*
     * Determine if the document ended with a new line and if so tell
     * the builder about it. The builder logic is not able to detect
     * this particular case.
     */
    const auto last_char(*s.crbegin());
    BOOST_LOG_SEV(lg, debug) << "Last char:"
                             << static_cast<unsigned int>(last_char);
    if (last_char == carriage_return || last_char == line_feed)
        b.add_final_new_line();
    else
        BOOST_LOG_SEV(lg, debug) << "Not adding final new line.";

    /*
     * Build the document.
     */
    const auto r(b.build());
    BOOST_LOG_SEV(lg, debug) << "Finished building an org mode document.";
    return r;
}

}

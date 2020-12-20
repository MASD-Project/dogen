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

}

namespace dogen::org::helpers {

entities::document document_factory::make(const std::string& s) {
    /*
     * If there is no content, return an empty document.
     */
    if (s.empty()) {
        entities::document r;
        return r;
    }

    std::string line;
    std::istringstream is(s);
    helpers::builder b;
    while(std::getline(is, line)) {
        b.add_line(line);
    }

    const auto last_char(*s.rend());
    if (last_char == '\r' || last_char == '\n')
        b.add_final_new_line();

    return b.build();
}

}

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
 * MA 02110-1301, USA#include <string_view>.
 *
 */
#include <boost/algorithm/string/replace.hpp>
#include "dogen.templating/types/wale/formatter.hpp"

namespace {

const std::string prefix("{{");
const std::string postfix("}}");

}

namespace dogen::templating::wale {

std::string formatter::wrap_key(const std::string& key) const {
    return prefix + key + postfix;
}

std::string formatter::format(const text_template& tt) const {
    std::string r(tt.content());
    for (const auto& pair : tt.supplied_kvps()) {
        const auto key(wrap_key(pair.first));
        const auto& value(pair.second);

        // For some reason replace_all does not seem to work correctly
        // on clang debug, _sometimes_, when we use strings rather
        // than literals. This rather puzzling behaviour started when
        // we upgraded to kernel 5.2 with all dependencies otherwise
        // unchanged.
        boost::replace_all(r, key.c_str(), value.c_str());
    }
    return r;
}

}

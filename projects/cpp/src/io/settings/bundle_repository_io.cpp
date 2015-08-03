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
#include <ostream>
#include "dogen/tack/io/qname_io.hpp"
#include "dogen/cpp/io/settings/bundle_io.hpp"
#include "dogen/cpp/io/settings/bundle_repository_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::tack::qname, dogen::cpp::settings::bundle>& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << i->first;
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace dogen {
namespace cpp {
namespace settings {

std::ostream& operator<<(std::ostream& s, const bundle_repository& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::settings::bundle_repository\"" << ", "
      << "\"bundles_by_qname\": " << v.bundles_by_qname()
      << " }";
    return(s);
}

} } }

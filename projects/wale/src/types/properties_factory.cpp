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
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/wale/io/properties_io.hpp"
#include "dogen/wale/types/properties_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("wale.properties_factory"));

const std::string wale_template_path("wale.template_path");
const std::string wale_kvp("wale.kvp");

}

namespace dogen {
namespace wale {

std::ostream&
operator<<(std::ostream& s, const properties_factory::type_group& v) {
    s << " { "
      << "\"__type__\": " << "\"wale::properties_factory::type_group\"" << ", "
      << "\"template_path_directive\": " << v.template_path << ", "
      << "\"kvps\": " << v.kvps
      << " }";
    return s;
}

properties_factory::type_group properties_factory::
make_type_group(const annotations::type_repository& atrp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating type group.";

    type_group r;
    const annotations::type_repository_selector s(atrp);
    r.template_path = s.select_type_by_name(wale_template_path);
    r.kvps = s.select_type_by_name(wale_kvp);

    BOOST_LOG_SEV(lg, debug) << "Created type group. Result: " << r;
    return r;
}

properties properties_factory::
read_properties(const type_group& tg, const annotations::annotation& a) const {
    BOOST_LOG_SEV(lg, debug) << "Reading properties from annotation.";
    const annotations::entry_selector s(a);
    properties r;

    r.template_path(s.get_text_content(tg.template_path));
    r.supplied_kvps(s.get_kvp_content(tg.kvps));

    BOOST_LOG_SEV(lg, debug) << "Read properties. Result: " << r;
    return r;
}

bool properties_factory::
has_properties(const annotations::annotation& a) const {
    const annotations::entry_selector s(a);
    return s.has_entry(wale_template_path);
}

properties properties_factory::make(const annotations::type_repository& atrp,
    const annotations::annotation& a) const {
    BOOST_LOG_SEV(lg, debug) << "Creating properties.";

    const auto tg(make_type_group(atrp));
    const auto r(read_properties(tg, a));

    BOOST_LOG_SEV(lg, debug) << "Created properties.";
    return r;
}

} }

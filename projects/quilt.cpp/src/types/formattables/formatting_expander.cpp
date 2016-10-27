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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/formattables/formatting_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.formatting_expander"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {
/*
std::ostream&
operator<<(std::ostream& s, const formatting_expander::type_group& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "formatting_expander::type_group\"" << ", "
      << "\"formatting_style\": " << v.formatting_style << ", "
      << "\"formatting_input\": " << v.formatting_input
      << " }";

    return s;
}

formatting_expander::type_group formatting_expander::make_type_group(
    const annotations::type_repository& atrp,
    const formatters::repository& frp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating type group.";

    type_group r;
    const annotations::type_repository_selector s(atrp);
    const auto fs(traits::cpp::formatting_style());
    r.formatting_style = s.select_type_by_name(fs);

    const auto fi(traits::cpp::formatting_input());
    r.formatting_input = s.select_type_by_name(fi);

    BOOST_LOG_SEV(lg, debug) << "Created type group. Result: " << r;
    return r;
}

formatting_configuration formatting_expander::make_formatting_configuration(
    const type_group& tg, const annotations::annotation& a) const {
    formatting_configuration r;

    return r;
}

void formatting_expander::expand(const annotations::type_repository& atrp,
    const formatters::repository& frp, model& fm) const {

}
*/
} } } }

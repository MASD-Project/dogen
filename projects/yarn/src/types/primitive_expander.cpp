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
#include <ostream>
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/types/primitive_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.primitive_expander"));

}

namespace dogen {
namespace yarn {

std::ostream&
operator<<(std::ostream& s, const primitive_expander::type_group& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::primitive_expander::type_group\""
      << ", " << "\"is_nullable\": " << v.is_nullable << ", "
      << "\"use_type_aliasing\": " << v.use_type_aliasing
      << " }";

    return s;
}

primitive_expander::type_group primitive_expander::
make_type_group(const annotations::type_repository& atrp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating type group.";

    type_group r;

    const annotations::type_repository_selector s(atrp);

    const auto in(traits::primitive::is_nullable());
    r.is_nullable = s.select_type_by_name(in);

    const auto uta(traits::primitive::use_type_aliasing());
    r.use_type_aliasing = s.select_type_by_name(uta);

    BOOST_LOG_SEV(lg, debug) << "Created type group. Result" << r;
    return r;
}

void primitive_expander::
populate_from_annotations(const type_group& tg, primitive& p) const {
    const auto& a(p.annotation());
    const annotations::entry_selector s(a);
    p.is_nullable(s.get_boolean_content_or_default(tg.is_nullable));
    p.use_type_aliasing(s.get_boolean_content_or_default(tg.use_type_aliasing));
}

void primitive_expander::expand(const annotations::type_repository& atrp,
    intermediate_model& im) {
    BOOST_LOG_SEV(lg, debug) << "Started expanding primitives for model: "
                             << im.name().id();

    const auto tg(make_type_group(atrp));
    for (auto& pair : im.primitives()) {
        const auto& id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Expanding: " << id;

        auto& p(pair.second);
        populate_from_annotations(tg, p);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished expanding primitives for model.";
}

} }

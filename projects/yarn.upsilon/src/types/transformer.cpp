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
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn.upsilon/types/transformer.hpp"

namespace dogen {
namespace yarn {
namespace upsilon {

yarn::primitive
transformer::to_primitive(const yarn::origin_types ot,
    const yarn::name& model_name, const dogen::upsilon::primitive& p) const {

    dogen::yarn::name_factory nf;
    dogen::yarn::name n(nf.build_element_in_model(model_name, p.name()));

    yarn::primitive r;
    r.name(n);
    r.documentation(p.comment());
    r.origin_type(ot);
    return r;
}

yarn::object
transformer::to_object(const dogen::upsilon::compound& /*c*/) const {
    yarn::object r;
    return r;
}

yarn::object
transformer::to_object(const dogen::upsilon::collection& /*c*/) const {
    yarn::object r;
    return r;
}

yarn::enumeration
transformer::to_enumeration(const dogen::upsilon::enumeration& /*e*/) const {
    yarn::enumeration r;
    return r;
}

} } }

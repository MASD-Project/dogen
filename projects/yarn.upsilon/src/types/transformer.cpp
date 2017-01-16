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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn.upsilon/types/transformer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.upsilon.transformer"));

const std::string scope_operator("::");

}

namespace dogen {
namespace yarn {
namespace upsilon {

std::string
transformer::to_unparsed_type(const dogen::upsilon::type_name& tn) const {
    return tn.schema_name() + scope_operator + tn.name();
}

void transformer::populate_element_properties(const yarn::origin_types ot,
    const yarn::name& model_name, const dogen::upsilon::type& t,
    yarn::element& e) const {

    dogen::yarn::name_factory nf;
    const auto n(nf.build_element_in_model(model_name, t.name()));

    e.name(n);
    e.documentation(t.comment());
    e.origin_type(ot);
}

yarn::primitive
transformer::to_primitive(const yarn::origin_types ot,
    const yarn::name& model_name, const dogen::upsilon::primitive& p) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming primitive: " << p.name();
    yarn::primitive r;
    populate_element_properties(ot, model_name, p, r);
    BOOST_LOG_SEV(lg, debug) << "Finished transforming primitive";
    return r;
}

yarn::object
transformer::to_object(const yarn::origin_types ot,
    const yarn::name& model_name, const dogen::upsilon::compound& c) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming compound: " << c.name();
    yarn::object r;
    populate_element_properties(ot, model_name, c, r);

    dogen::yarn::name_factory nf;
    for (const auto& f : c.fields()) {
        yarn::attribute attr;
        attr.name(nf.build_attribute_name(r.name(), f.name()));
        attr.unparsed_type(to_unparsed_type(f.type_name()));
        attr.documentation(f.comment());
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming compound";
    return r;
}

yarn::object
transformer::to_object(const yarn::origin_types ot,
    const yarn::name& model_name, const dogen::upsilon::collection& c) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming collection: " << c.name();
    yarn::object r;
    populate_element_properties(ot, model_name, c, r);
    BOOST_LOG_SEV(lg, debug) << "Finished transforming collection";
    return r;
}

yarn::enumeration
transformer::to_enumeration(const yarn::origin_types ot,
    const yarn::name& model_name, const dogen::upsilon::enumeration& e) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming enumeration: " << e.name();
    yarn::enumeration r;
    populate_element_properties(ot, model_name, e, r);
    BOOST_LOG_SEV(lg, debug) << "Finished transforming enumeration";
    return r;
}

} } }

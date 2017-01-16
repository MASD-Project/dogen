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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/upsilon/io/name_io.hpp"
#include "dogen/yarn.upsilon/types/transformer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.upsilon.transformer"));

const std::string scope_operator("::");
const std::string collection_name("Collection");
const std::string less_than("<");
const std::string more_than(">");

}

namespace dogen {
namespace yarn {
namespace upsilon {

transformer::transformer(const std::unordered_map<std::string,
    dogen::upsilon::name>& collection_names)
    : collection_names_(collection_names) {}

std::string
transformer::to_unparsed_type(const dogen::upsilon::name& tn) const {
    const auto i(collection_names_.find(tn.id()));
    if (i == collection_names_.end()) {
        if (tn.schema_name().empty())
            return tn.value();

        return tn.schema_name() + scope_operator + tn.value();
    }

    std::ostringstream s;
    const auto& collection_tn(i->second);
    s << collection_name << less_than;
    if (collection_tn.schema_name().empty())
        s << collection_tn.value();
    else
        s << collection_tn.schema_name() << scope_operator
          << collection_tn.value();
    s << more_than;
    return s.str();
}

void transformer::populate_element_properties(const yarn::origin_types ot,
    const yarn::name& model_name, const dogen::upsilon::type& t,
    yarn::element& e) const {

    dogen::yarn::name_factory nf;
    const auto n(nf.build_element_in_model(model_name, t.name().value()));

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
    BOOST_LOG_SEV(lg, debug) << "Total fields: " << c.fields().size();
    for (const auto& f : c.fields()) {
        yarn::attribute attr;
        attr.name(nf.build_attribute_name(r.name(), f.name()));
        attr.unparsed_type(to_unparsed_type(f.type_name()));
        attr.documentation(f.comment());
        r.local_attributes().push_back(attr);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming compound";
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
#

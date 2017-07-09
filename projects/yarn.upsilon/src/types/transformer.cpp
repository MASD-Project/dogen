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
#include "dogen/yarn/types/helpers/name_factory.hpp"
#include "dogen/upsilon/io/name_io.hpp"
#include "dogen/yarn.upsilon/types/transformation_error.hpp"
#include "dogen/yarn.upsilon/types/transformer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.upsilon.transformer"));

const std::string scope_operator("::");
const std::string collection_name("Collection");
const std::string less_than("<");
const std::string more_than(">");

const std::string missing_schema_reference(
    "Type belongs to a schema that is not referenced: ");

}

namespace dogen {
namespace yarn {
namespace upsilon {

transformer::transformer(const yarn::name& target_model_name)
    : target_model_name_(target_model_name),
      schema_name_to_model_name_(),
      collection_names_() {}

transformer::
transformer(const yarn::name& target_model_name,
    const std::unordered_map<std::string, dogen::yarn::name>&
    schema_name_to_model_name,
    const std::unordered_map<std::string,
    dogen::upsilon::name>& collection_names)
    : target_model_name_(target_model_name),
      schema_name_to_model_name_(schema_name_to_model_name),
      collection_names_(collection_names) {}

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
    s << collection_name << less_than
      << to_unparsed_type(collection_tn)
      << more_than;

    return s.str();
}

void transformer::populate_element_properties(const dogen::upsilon::type& t,
    yarn::element& e) const {

    e.documentation(t.comment());

    dogen::yarn::helpers::name_factory nf;
    const auto sn(t.name().schema_name());
    if (sn.empty() || sn == target_model_name_.simple()) {
        /*
         * If we do not have a model name, or if the model name is the
         * same as the target model, this type belongs to the target
         * model.
         */
        e.name(nf.build_element_in_model(target_model_name_, t.name().value()));
        e.origin_type(dogen::yarn::origin_types::target);
    } else {
        /*
         * Otherwise the type must belong to a reference model. Given
         * upsilon, we know this must be a proxy reference.
         */
        const auto& snmn(schema_name_to_model_name_);
        const auto i(snmn.find(sn));
        if (i == snmn.end()) {
            BOOST_LOG_SEV(lg, error) << missing_schema_reference << sn
                                     << " Type: " << t.name().value();
            BOOST_THROW_EXCEPTION(
                transformation_error(missing_schema_reference + sn));
        }
        e.name(nf.build_element_in_model(i->second, t.name().value()));
        e.origin_type(dogen::yarn::origin_types::proxy_reference);
    }
}

yarn::builtin
transformer::to_builtin(const dogen::upsilon::primitive& p) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming primitive: " << p.name();
    yarn::builtin r;
    populate_element_properties(p, r);
    BOOST_LOG_SEV(lg, debug) << "Finished transforming primitive";
    return r;
}

yarn::object
transformer::to_object(const dogen::upsilon::compound& c) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming compound: " << c.name();
    yarn::object r;
    populate_element_properties(c, r);

    dogen::yarn::helpers::name_factory nf;
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
transformer::to_enumeration(const dogen::upsilon::enumeration& e) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming enumeration: " << e.name();
    yarn::enumeration r;
    populate_element_properties(e, r);
    BOOST_LOG_SEV(lg, debug) << "Finished transforming enumeration";
    return r;
}

} } }
#

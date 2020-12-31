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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.identification/io/entities/stereotype_io.hpp"
#include "dogen.identification/types/entities/codec_id.hpp"
#include "dogen.codec.dia/types/adaptation_error.hpp"
#include "dogen.codec.dia/types/adapter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("codec.dia.adapter"));

const std::string name_delimiter("::");
const std::string object_element("masd::object");
const std::string module_element("masd::module");
const std::string uml_large_package("UML - LargePackage");
const std::string uml_class("UML - Class");
const std::string uml_generalization("UML - Generalization");
const std::string uml_association("UML - Association");
const std::string uml_note("UML - Note");
const std::string uml_message("UML - Message");
const std::string uml_realization("UML - Realizes");

const std::string empty_dia_name("Dia name is empty.");

}

namespace dogen::codec::dia {

void adapter::validate_dia_name(const std::string& n) {
    if (n.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_name;
        BOOST_THROW_EXCEPTION(adaptation_error(empty_dia_name));
    }
}

std::string adapter::qualified_name(const std::string& contained_by,
    const std::string& simple_name) {

    if (contained_by.empty())
        return simple_name;

    return contained_by + name_delimiter + simple_name;
}

codec::entities::attribute adapter::adapt(const entities::attribute& a,
    const std::string& qualified_owner) {
    validate_dia_name(a.name().simple());

    codec::entities::attribute r;
    r.name(a.name());
    r.name().qualified(qualified_name(qualified_owner, a.name().simple()));
    r.type(a.type());
    r.value(a.value());
    r.comment().documentation(a.comment().documentation());
    r.tagged_values(a.comment().tagged_values());
    return r;
}

void adapter::process_stereotypes(const entities::object& o,
    codec::entities::element& e) {
    BOOST_LOG_SEV(lg, debug) << "Original stereotypes string: '"
                             << o.stereotypes() << "'";

    /*
     * Provide the appropriate element types defaulting based on the
     * dia UML types.
     */
    if (o.object_type() == uml_class)
        e.fallback_element_type(object_element);
    else if (o.object_type() == uml_large_package)
        e.fallback_element_type(module_element);

    /*
     * Split the user-supplied stereotype CSV strings, and convert
     * them to the strong type representation of stereotype.
     */
    using utility::string::splitter;
    const auto splitted(splitter::split_csv(o.stereotypes()));
    for(const auto& s : splitted) {
        identification::entities::stereotype st(s);
        e.stereotypes().push_back(st);
    }
    BOOST_LOG_SEV(lg, debug) << "Split stereotypes: " << e.stereotypes();
}

codec::entities::element
adapter::adapt(const entities::object& o, const std::string& contained_by,
    const std::list<std::string>& parents) {
    validate_dia_name(o.name());

    codec::entities::element r;
    r.name().simple(o.name());
    r.name().qualified(qualified_name(contained_by, o.name()));
    r.parents(parents);
    r.comment().documentation(o.comment().documentation());
    r.tagged_values(o.comment().tagged_values());

    using identification::entities::codec_id;
    r.provenance().codec_id(codec_id(o.id()));
    r.containing_element_id(codec_id(o.container_id()));
    process_stereotypes(o, r);

    for (const auto& attr : o.attributes())
        r.attributes().push_back(adapt(attr, r.name().qualified()));

    return r;
}

}

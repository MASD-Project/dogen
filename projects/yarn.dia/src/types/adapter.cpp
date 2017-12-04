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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/string/splitter.hpp"
#include "dogen/yarn/types/helpers/stereotypes_helper.hpp"
#include "dogen/yarn.dia/types/adaptation_error.hpp"
#include "dogen/yarn.dia/types/adapter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.dia.adapter"));

const std::string name_delimiter("::");

const std::string empty_dia_name("Dia name is empty.");

}

namespace dogen {
namespace yarn {
namespace dia {

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

meta_model::exoattribute adapter::adapt(const processed_attribute& a) {
    validate_dia_name(a.name());

    meta_model::exoattribute r;
    r.name(a.name());
    r.type(a.type());
    r.documentation(a.comment().documentation());
    r.tagged_values(a.comment().key_value_pairs());

    return r;
}

void adapter::
process_stereotypes(const processed_object& po, meta_model::exoelement& ee) {
    BOOST_LOG_SEV(lg, debug) << "Original stereotypes string: '"
                             << po.stereotypes() << "'";

    /*
     * Provide the appropriate element types defaulting based on the
     * dia UML types.
     */
    using meta_model::static_stereotypes;
    yarn::helpers::stereotypes_helper h;
    if (po.dia_object_type() == dia_object_types::uml_class)
        ee.fallback_element_type(h.to_string(static_stereotypes::object));
    else if (po.dia_object_type() == dia_object_types::uml_large_package)
        ee.fallback_element_type(h.to_string(static_stereotypes::module));

    /*
     * Split and copy across the user-supplied stereotypes.
     */
    using utility::string::splitter;
    const auto st(splitter::split_csv(po.stereotypes()));
    ee.stereotypes(st);

    BOOST_LOG_SEV(lg, debug) << "Split stereotypes: " << st;
}

meta_model::exoelement adapter::
adapt(const processed_object& po, const std::string& contained_by,
    const std::list<std::string>& parents) {
    validate_dia_name(po.name());

    meta_model::exoelement r;
    r.name(qualified_name(contained_by, po.name()));
    r.parents(parents);
    r.documentation(po.comment().documentation());
    r.tagged_values(po.comment().key_value_pairs());
    process_stereotypes(po, r);

    for (const auto& attr : po.attributes())
        r.attributes().push_back(adapt(attr));

    return r;
}

} } }

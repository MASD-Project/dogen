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
#include "dogen/yarn/io/meta_model/static_stereotypes_io.hpp"
#include "dogen/yarn/io/helpers/stereotypes_conversion_result_io.hpp"
#include "dogen/yarn/types/helpers/stereotypes_helper.hpp"
#include "dogen/yarn.dia/types/adaptation_error.hpp"
#include "dogen/yarn.dia/types/adapter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.dia.adapter"));

const std::string name_delimiter("::");

const std::string empty_dia_object_name("Dia object name is empty");
const std::string too_many_yarn_types(
    "Attempting to set the yarn type more than once.");


}

namespace dogen {
namespace yarn {
namespace dia {

void adapter::validate_dia_object_name(const std::string& n) {
    if (n.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(adaptation_error(empty_dia_object_name));
    }
}

std::string adapter::qualified_name(const std::string& contained_by,
    const std::string& simple_name) {

    if (contained_by.empty())
        return simple_name;

    return contained_by + name_delimiter + simple_name;
}

meta_model::exoattribute adapter::adapt(const processed_attribute& a) {
    validate_dia_object_name(a.name());

    meta_model::exoattribute r;
    r.name(a.name());
    r.type(a.type());
    r.documentation(a.comment().documentation());
    r.tagged_values(a.comment().key_value_pairs());

    return r;
}

void adapter::
process_stereotypes(const processed_object& po, meta_model::exoelement& ee) {
    yarn::helpers::stereotypes_helper h;

    BOOST_LOG_SEV(lg, debug) << "Original stereotypes string: '"
                             << po.stereotypes() << "'";
    const auto st(h.from_csv_string(po.stereotypes()));

    BOOST_LOG_SEV(lg, debug) << "Parsed stereotypes: " << st;
    ee.dynamic_stereotypes(st.dynamic_stereotypes());
    ee.static_stereotypes(st.static_stereotypes());

    using meta_model::static_stereotypes;
    const auto et(h.extract_element_types(st.static_stereotypes()));
    if (et.size() > 1) {
        /*
         * We can only have zero or one yarn element types set.
         */
        BOOST_LOG_SEV(lg, warn) << too_many_yarn_types;
        BOOST_THROW_EXCEPTION(adaptation_error(too_many_yarn_types));
    } else if (et.size() == 0) {
        using dot = dia_object_types;
        if (po.dia_object_type() == dot::uml_class)
            ee.static_stereotypes().push_back(static_stereotypes::object);
        else if (po.dia_object_type() == dot::uml_large_package)
            ee.static_stereotypes().push_back(static_stereotypes::module);
    }
}

meta_model::exoelement adapter::
adapt(const processed_object& po, const std::string& contained_by,
    const std::list<std::string>& parents) {
    validate_dia_object_name(po.name());

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

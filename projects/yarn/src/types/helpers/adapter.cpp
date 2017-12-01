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
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/io/meta_model/static_stereotypes_io.hpp"
#include "dogen/yarn/io/helpers/stereotypes_conversion_result_io.hpp"
#include "dogen/yarn/types/helpers/name_factory.hpp"
#include "dogen/yarn/types/helpers/name_builder.hpp"
#include "dogen/yarn/types/meta_model/attribute.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/object_template.hpp"
#include "dogen/yarn/types/helpers/stereotypes_helper.hpp"
#include "dogen/yarn/types/helpers/adaptation_error.hpp"
#include "dogen/yarn/types/helpers/adapter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.helpers.adapter"));

const std::string empty_name("Name is empty.");
const std::string enumerator_with_type("Enumerators cannot have a type: ");
const std::string too_many_element_types(
    "Attempting to set the yarn element type more than once. Element: ");
const std::string missing_element_type("Missing yarn element type. Element: ");
const std::string invalid_element_type(
    "Invalid or usupported yarn element type: ");

}

namespace dogen {
namespace yarn {
namespace helpers {

void adapter::ensure_not_empty(const std::string& n) const {
    if (n.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_name;
        BOOST_THROW_EXCEPTION(adaptation_error(empty_name));
    }
}

meta_model::name adapter::to_name(const naming_configuration& nc,
    const std::string& n) const {
    ensure_not_empty(n);

    helpers::name_builder b;
    b.simple_name(n);
    b.external_modules(nc.external_modules());
    b.model_modules(nc.model_modules());
    return b.build();
}

meta_model::attribute
adapter::to_attribute(const naming_configuration& /*nc*/,
    const meta_model::exoattribute& ea) const {
    ensure_not_empty(ea.name());

    meta_model::attribute r;
    r.name().simple(ea.name());
    r.unparsed_type(ea.type());
    r.documentation(ea.documentation());
    return r;
}

meta_model::enumerator
adapter::to_enumerator(const naming_configuration& /*nc*/,
    const meta_model::exoattribute& ea) const {
    ensure_not_empty(ea.name());

    if (!ea.type().empty()) {
        const auto t(ea.type());
        BOOST_LOG_SEV(lg, error) << enumerator_with_type << t;
        BOOST_THROW_EXCEPTION(adaptation_error(enumerator_with_type + t));
    }

    meta_model::enumerator r;
    r.name().simple(ea.name());
    r.documentation(ea.documentation());
    return r;
}

void adapter::populate_element(const naming_configuration& nc,
    const meta_model::exoelement& ee, meta_model::element& e) const {
    e.origin_type(meta_model::origin_types::not_yet_determined);
    e.documentation(ee.documentation());
    e.static_stereotypes(ee.static_stereotypes());
    e.dynamic_stereotypes(ee.dynamic_stereotypes());

    helpers::name_builder b;
    b.simple_name(ee.name());

    /*
     * Types placed in the global module must not have any of the
     * location properties set.
     */
    if (!nc.in_global_module()) {
        b.external_modules(nc.external_modules());
        b.model_modules(nc.model_modules());
    }
    e.name(b.build());
}

boost::shared_ptr<meta_model::element>
adapter::to_object(const naming_configuration& nc,
    const meta_model::exoelement& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming exoobject to object: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::object>());
    populate_element(nc, ee, *r);

    for (const auto& attr : ee.attributes())
        r->local_attributes().push_back(to_attribute(nc, attr));

    return r;
}

boost::shared_ptr<meta_model::element>
adapter::to_object_template(const naming_configuration& nc,
    const meta_model::exoelement& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming exoobject to object template: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::object_template>());
    populate_element(nc, ee, *r);

    for (const auto& attr : ee.attributes())
        r->local_attributes().push_back(to_attribute(nc, attr));

    return r;
}

boost::shared_ptr<meta_model::element>
adapter::to_exception(const naming_configuration& nc,
    const meta_model::exoelement& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming exoobject to exception: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::exception>());
    populate_element(nc, ee, *r);
    return r;
}

boost::shared_ptr<meta_model::element>
adapter::to_primitive(const naming_configuration& nc,
    const meta_model::exoelement& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming exoobject to primitive: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::primitive>());
    populate_element(nc, ee, *r);
    return r;
}

boost::shared_ptr<meta_model::element>
adapter::to_enumeration(const naming_configuration& nc,
    const meta_model::exoelement& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to enumeration: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::enumeration>());
    populate_element(nc, ee, *r);

    for (const auto& attr : ee.attributes())
        r->enumerators().push_back(to_enumerator(nc, attr));

    return r;
}

boost::shared_ptr<meta_model::element>
adapter::to_module(const naming_configuration& nc,
    const meta_model::exoelement& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming exoobject to module: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::module>());
    populate_element(nc, ee, *r);
    return r;
}

boost::shared_ptr<meta_model::element>
adapter::to_builtin(const naming_configuration& nc,
    const meta_model::exoelement& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming exoobject to builtin: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::builtin>());
    populate_element(nc, ee, *r);
    return r;
}

boost::shared_ptr<meta_model::element>
adapter::adapt(const naming_configuration& nc,
    const meta_model::exoelement& ee) const {
    yarn::helpers::stereotypes_helper h;
    auto et(h.extract_element_types(ee.static_stereotypes()));

    /*
     * We can only have one yarn element types set.
     */
    if (et.size() > 1) {
        BOOST_LOG_SEV(lg, warn) << too_many_element_types << ee.name();
        BOOST_THROW_EXCEPTION(
            adaptation_error(too_many_element_types + ee.name()));
    } else if (et.size() == 0) {
        BOOST_LOG_SEV(lg, warn) << missing_element_type << ee.name();
        BOOST_THROW_EXCEPTION(
            adaptation_error(missing_element_type + ee.name()));
    }

    using meta_model::static_stereotypes;
    switch (et.front()) {
    case static_stereotypes::object: return to_object(nc, ee);
    case static_stereotypes::object_template: return to_object_template(nc, ee);
    case static_stereotypes::exception: return to_exception(nc, ee);
    case static_stereotypes::primitive: return to_primitive(nc, ee);
    case static_stereotypes::enumeration: return to_enumeration(nc, ee);
    case static_stereotypes::module: return to_module(nc, ee);
    case static_stereotypes::builtin: return to_builtin(nc, ee);
    default: {
        const auto s(boost::lexical_cast<std::string>(et.front()));
        BOOST_LOG_SEV(lg, error) << invalid_element_type << s;;
        BOOST_THROW_EXCEPTION(adaptation_error(invalid_element_type + s));
    } }
}

} } }

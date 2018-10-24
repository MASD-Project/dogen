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
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.utility/string/splitter.hpp"
#include "masd.dogen.modeling/io/meta_model/location_io.hpp"
#include "masd.dogen.modeling/types/helpers/name_factory.hpp"
#include "masd.dogen.modeling/types/helpers/name_builder.hpp"
#include "masd.dogen.modeling/types/helpers/adaptation_error.hpp"
#include "masd.dogen.modeling/types/helpers/new_adapter.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory("yarn.helpers.new_adapter"));

const std::string empty_name("Name is empty.");
const std::string enumerator_with_type("Enumerators cannot have a type: ");

using masd::dogen::annotations::scope_types;
const scope_types entity_scope(scope_types::entity);
const scope_types root_scope(scope_types::root_module);
const scope_types property_scope(scope_types::property);

}

namespace masd::dogen::modeling::helpers {

new_adapter::new_adapter(const annotations::annotation_factory& f)
    : annotation_factory_(f) {}

void new_adapter::ensure_not_empty(const std::string& n) const {
    if (n.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_name;
        BOOST_THROW_EXCEPTION(adaptation_error(empty_name));
    }
}

meta_model::name new_adapter::to_name(const meta_model::location& l,
    const std::string& n) const {
    BOOST_LOG_SEV(lg, debug) << "Location: " << l;
    /*
     * Names are expected to be delimited by the scope operator,
     * denoting internal modules.
     */
    ensure_not_empty(n);
    auto tokens(utility::string::splitter::split_scoped(n));
    helpers::name_builder b;
    b.simple_name(tokens.back());
    tokens.pop_back();
    if (!tokens.empty())
        b.internal_modules(tokens);

    b.external_modules(l.external_modules());
    b.model_modules(l.model_modules());

    return b.build();
}

meta_model::attribute
new_adapter::to_attribute(const meta_model::location& /*l*/,
    const external::meta_model::attribute& ea) const {
    ensure_not_empty(ea.name());

    meta_model::attribute r;
    r.name().simple(ea.name()); // FIXME
    r.unparsed_type(ea.type());
    r.documentation(ea.documentation());
    r.annotation(annotation_factory_.make(ea.tagged_values(), property_scope));

    return r;
}

meta_model::enumerator
new_adapter::to_enumerator(const meta_model::location& /*l*/,
    const external::meta_model::attribute& ea) const {
    ensure_not_empty(ea.name());

    if (!ea.type().empty()) {
        const auto t(ea.type());
        BOOST_LOG_SEV(lg, error) << enumerator_with_type << t;
        BOOST_THROW_EXCEPTION(adaptation_error(enumerator_with_type + t));
    }

    meta_model::enumerator r;
    r.name().simple(ea.name()); // FIXME
    r.documentation(ea.documentation());
    r.annotation(annotation_factory_.make(ea.tagged_values(), property_scope));

    return r;
}

void new_adapter::populate_element(const annotations::scope_types scope,
    const meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const external::meta_model::element& ee, meta_model::element& e) const {
    e.name(to_name(l, ee.name()));
    e.origin_type(meta_model::origin_types::not_yet_determined);
    e.documentation(ee.documentation());
    e.static_stereotypes(scr.static_stereotypes());

    const auto& ds(scr.dynamic_stereotypes());
    e.dynamic_stereotypes(ds);

    const auto& tv(ee.tagged_values());
    e.annotation(annotation_factory_.make(tv, scope, ds));
    e.in_global_module(
        l.external_modules().empty() && l.model_modules().empty());
}

boost::shared_ptr<meta_model::object>
new_adapter::to_object(const meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const external::meta_model::element& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to object: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::object>());
    populate_element(entity_scope, l, scr, ee, *r);
    r->is_associative_container(ee.is_associative_container());
    r->can_be_primitive_underlier(ee.can_be_primitive_underlier());

    for (const auto& attr : ee.attributes())
        r->local_attributes().push_back(to_attribute(l, attr));

    for (const auto& p : ee.parents())
        r->parents().push_back(to_name(l, p));

    return r;
}

boost::shared_ptr<meta_model::object_template>
new_adapter::to_object_template(const meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const external::meta_model::element& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element "
                             << "to object template: " << ee.name();

    auto r(boost::make_shared<meta_model::object_template>());
    populate_element(entity_scope, l, scr, ee, *r);

    for (const auto& attr : ee.attributes())
        r->local_attributes().push_back(to_attribute(l, attr));

    for (const auto& p : ee.parents())
        r->parents().push_back(to_name(l, p));

    return r;
}

boost::shared_ptr<meta_model::exception>
new_adapter::to_exception(const meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const external::meta_model::element& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to exception: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::exception>());
    populate_element(entity_scope, l, scr, ee, *r);
    return r;
}

boost::shared_ptr<meta_model::primitive>
new_adapter::to_primitive(const meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const external::meta_model::element& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to primitive: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::primitive>());
    populate_element(entity_scope, l, scr, ee, *r);
    return r;
}

boost::shared_ptr<meta_model::enumeration>
new_adapter::to_enumeration(const meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const external::meta_model::element& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to enumeration: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::enumeration>());
    populate_element(entity_scope, l, scr, ee, *r);

    for (const auto& attr : ee.attributes())
        r->enumerators().push_back(to_enumerator(l, attr));

    return r;
}

boost::shared_ptr<meta_model::module> new_adapter::
to_module(const bool is_root_module, const meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const external::meta_model::element& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to module: "
                             << ee.name();

    const auto st(is_root_module ? root_scope : entity_scope);
    auto r(boost::make_shared<meta_model::module>());
    populate_element(st, l, scr, ee, *r);
    return r;
}

boost::shared_ptr<meta_model::builtin>
new_adapter::to_builtin(const meta_model::location& l,
    const stereotypes_conversion_result& scr,
    const external::meta_model::element& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming external element to builtin: "
                             << ee.name();

    const auto es(annotations::scope_types::entity);
    auto r(boost::make_shared<meta_model::builtin>());
    populate_element(es, l, scr, ee, *r);

    r->can_be_primitive_underlier(ee.can_be_primitive_underlier());
    r->is_default_enumeration_type(ee.is_default_enumeration_type());
    r->is_floating_point(ee.is_floating_point());
    r->can_be_enumeration_underlier(ee.can_be_enumeration_underlier());

    return r;
}

}

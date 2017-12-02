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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/string/splitter.hpp"
#include "dogen/yarn/types/helpers/name_factory.hpp"
#include "dogen/yarn/types/helpers/name_builder.hpp"
#include "dogen/yarn/types/helpers/adaptation_error.hpp"
#include "dogen/yarn/types/helpers/adapter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.helpers.adapter"));

const std::string empty_name("Name is empty.");
const std::string enumerator_with_type("Enumerators cannot have a type: ");

using dogen::annotations::scope_types;
const scope_types entity_scope(scope_types::entity);
const scope_types root_scope(scope_types::root_module);
const scope_types property_scope(scope_types::property);

}

namespace dogen {
namespace yarn {
namespace helpers {

adapter::adapter(const annotations::annotation_factory& f)
    : annotation_factory_(f) {}

void adapter::ensure_not_empty(const std::string& n) const {
    if (n.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_name;
        BOOST_THROW_EXCEPTION(adaptation_error(empty_name));
    }
}

meta_model::name adapter::to_name(const meta_model::location& l,
    const std::string& n) const {
    /*
     * Names are expected to be delimited by the scope operator,
     * denoting internal modules.
     */
    ensure_not_empty(n);
    auto tokens(utility::string::splitter::split_scoped(n));
    helpers::name_builder b;
    b.simple_name(tokens.front());
    tokens.pop_front();
    if (!tokens.empty())
        b.internal_modules(tokens);

    /*
     * Elements placed in the global module do not have any of the
     * location properties set.
     */
    // FIXME
    // if (!nc.in_global_module()) {
    b.external_modules(l.external_modules());
    b.model_modules(l.model_modules());
    // }

    return b.build();
}

meta_model::attribute
adapter::to_attribute(const meta_model::location& /*l*/,
    const meta_model::exoattribute& ea) const {
    ensure_not_empty(ea.name());

    meta_model::attribute r;
    r.name().simple(ea.name()); // FIXME
    r.unparsed_type(ea.type());
    r.documentation(ea.documentation());
    r.annotation(annotation_factory_.make(ea.tagged_values(), property_scope));

    return r;
}

meta_model::enumerator
adapter::to_enumerator(const meta_model::location& /*l*/,
    const meta_model::exoattribute& ea) const {
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

void adapter::populate_element(const annotations::scope_types scope,
    const meta_model::location& l, const meta_model::exoelement& ee,
    meta_model::element& e) const {
    e.name(to_name(l, ee.name()));
    e.origin_type(meta_model::origin_types::not_yet_determined);
    e.documentation(ee.documentation());
    e.static_stereotypes(ee.static_stereotypes());
    e.dynamic_stereotypes(ee.dynamic_stereotypes());

    const auto& tv(ee.tagged_values());
    const auto& ds(ee.dynamic_stereotypes());
    e.annotation(annotation_factory_.make(tv, scope, ds));
}

boost::shared_ptr<meta_model::object>
adapter::to_object(const meta_model::location& l,
    const meta_model::exoelement& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming exoobject to object: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::object>());
    populate_element(entity_scope, l, ee, *r);

    for (const auto& attr : ee.attributes())
        r->local_attributes().push_back(to_attribute(l, attr));

    for (const auto& p : ee.parents())
        r->parents().push_back(to_name(l, p));

    return r;
}

boost::shared_ptr<meta_model::object_template>
adapter::to_object_template(const meta_model::location& l,
    const meta_model::exoelement& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming exoobject to object template: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::object_template>());
    populate_element(entity_scope, l, ee, *r);

    for (const auto& attr : ee.attributes())
        r->local_attributes().push_back(to_attribute(l, attr));

    for (const auto& p : ee.parents())
        r->parents().push_back(to_name(l, p));

    return r;
}

boost::shared_ptr<meta_model::exception>
adapter::to_exception(const meta_model::location& l,
    const meta_model::exoelement& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming exoobject to exception: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::exception>());
    populate_element(entity_scope, l, ee, *r);
    return r;
}

boost::shared_ptr<meta_model::primitive>
adapter::to_primitive(const meta_model::location& l,
    const meta_model::exoelement& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming exoobject to primitive: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::primitive>());
    populate_element(entity_scope, l, ee, *r);
    return r;
}

boost::shared_ptr<meta_model::enumeration>
adapter::to_enumeration(const meta_model::location& l,
    const meta_model::exoelement& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to enumeration: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::enumeration>());
    populate_element(entity_scope, l, ee, *r);

    for (const auto& attr : ee.attributes())
        r->enumerators().push_back(to_enumerator(l, attr));

    return r;
}

boost::shared_ptr<meta_model::module> adapter::
to_module(const bool is_root_module, const meta_model::location& l,
    const meta_model::exoelement& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming exoobject to module: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::module>());
    const auto st(is_root_module ? root_scope : entity_scope);
    populate_element(st, l, ee, *r);
    return r;
}

boost::shared_ptr<meta_model::builtin>
adapter::to_builtin(const meta_model::location& l,
    const meta_model::exoelement& ee) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming exoobject to builtin: "
                             << ee.name();

    auto r(boost::make_shared<meta_model::builtin>());
    populate_element(entity_scope, l, ee, *r);
    return r;
}

} } }

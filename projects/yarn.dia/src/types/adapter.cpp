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
#include <boost/variant/get.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/helpers/name_factory.hpp"
#include "dogen/yarn/types/helpers/name_builder.hpp"
#include "dogen/dia/types/composite.hpp"
#include "dogen/yarn.dia/types/adaptation_error.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"
#include "dogen/yarn.dia/io/processed_object_io.hpp"
#include "dogen/yarn.dia/io/context_io.hpp"
#include "dogen/yarn.dia/types/validator.hpp"
#include "dogen/yarn.dia/types/adapter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.dia.adapter"));

const std::string enumerator_with_type("Enumerators cannot have a type: ");
const std::string duplicate_attribute_name("Attribute name already exists: ");
const std::string empty_dia_object_name("Dia object name is empty");
const std::string multiple_inheritance(
    "Child has more than one parent, but multiple inheritance not supported:");
const std::string package_not_mapped(
    "Dia package ID is not mapped to yarn module: ");

}

namespace dogen {
namespace yarn {
namespace dia {

adapter::adapter(const context& ctx) : context_(ctx) {
    BOOST_LOG_SEV(lg, debug) << "Initial context: " << context_;
}

void adapter::validate_dia_object_name(const std::string& n) const {
    if (n.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(adaptation_error(empty_dia_object_name));
    }
}

meta_model::name adapter::to_name(const std::string& n) const {
    validate_dia_object_name(n);
    helpers::name_builder b;
    b.simple_name(n);
    return b.build();
}

meta_model::name adapter::
to_name(const std::string& n, const meta_model::name& module_n) const {
    validate_dia_object_name(n);
    helpers::name_factory f;
    return f.build_element_in_module(module_n, n);
}

meta_model::attribute
adapter::to_attribute(const processed_attribute& a) const {
    validate_dia_object_name(a.name());

    meta_model::attribute r;
    r.name().simple(a.name());
    r.unparsed_type(a.type());
    r.documentation(a.comment().documentation());
    return r;
}

meta_model::enumerator
adapter::to_enumerator(const processed_attribute& a) const {
    validate_dia_object_name(a.name());

    if (!a.type().empty()) {
        const auto t(a.type());
        BOOST_LOG_SEV(lg, error) << enumerator_with_type << t;
        BOOST_THROW_EXCEPTION(adaptation_error(enumerator_with_type + t));
    }

    meta_model::enumerator r;
    r.name().simple(a.name());
    r.documentation(a.comment().documentation());
    return r;
}

void adapter::
update_element(const processed_object& po, meta_model::element& e) const {
    e.origin_type(meta_model::origin_types::not_yet_determined);

    const auto package_id(po.child_node_id());
    bool is_in_package(!package_id.empty());
    if (is_in_package) {
        /*
         * Create the element name taking into account the packages
         * the element is contained in.
         */
        const auto i(context_.dia_id_to_module().find(package_id));
        if (i == context_.dia_id_to_module().end()) {
            BOOST_LOG_SEV(lg, error) << package_not_mapped << package_id;
            BOOST_THROW_EXCEPTION(
                adaptation_error(package_not_mapped + package_id));
        }
        const auto& module(*i->second.second);
        e.name(to_name(po.name(), module.name()));
    } else {
        /*
         * Type is a top-level type - e.g. belongs to the
         * synthetic module for the model; do not add this
         * dependency to the name.
         */
        e.name(to_name(po.name()));
    }

    e.documentation(po.comment().documentation());

    e.stereotypes().reserve(po.stereotypes().size());
    for (const auto us : po.stereotypes())
        e.stereotypes().push_back(us);
}

annotations::scribble_group adapter::
to_scribble_group(const processed_object& po, const bool is_root_module) const {
    annotations::scribble psbl;
    const auto& kvps(po.comment().key_value_pairs());
    psbl.entries(kvps);

    using annotations::scope_types;
    psbl.scope(is_root_module ? scope_types::root_module : scope_types::entity);

    annotations::scribble_group r;
    r.parent(psbl);

    for (const auto& attr : po.attributes()) {
        const auto& kvps(attr.comment().key_value_pairs());
        if (kvps.empty())
            continue;

        annotations::scribble csbl;
        csbl.entries(kvps);
        csbl.scope(scope_types::property);

        const auto pair(std::make_pair(attr.name(), csbl));
        const auto&inserted(r.children().insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_attribute_name << attr.name();
            BOOST_THROW_EXCEPTION(
                adaptation_error(duplicate_attribute_name + attr.name()));
        }
    }

    return r;
}

std::pair<annotations::scribble_group, boost::shared_ptr<meta_model::object>>
adapter::to_object(const processed_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to object: "
                             << po.id();

    auto o(boost::make_shared<meta_model::object>());
    update_element(po, *o);

    for (const auto& attr : po.attributes())
        o->local_attributes().push_back(to_attribute(attr));

    const auto i(context_.child_dia_id_to_parent_names().find(po.id()));
    if (i == context_.child_dia_id_to_parent_names().end() || i->second.empty())
        BOOST_LOG_SEV(lg, debug) << "Object has no parents: " << o->name().id();
    else {
        o->is_child(true);
        o->parents(i->second);
    }

    const auto sg(to_scribble_group(po, false/*is_root_module*/));
    return std::make_pair(sg, o);
}

std::pair<annotations::scribble_group, boost::shared_ptr<meta_model::exception>>
adapter::to_exception(const processed_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to exception: "
                             << po.id();

    auto e(boost::make_shared<meta_model::exception>());
    update_element(po, *e);

    const auto sg(to_scribble_group(po, false/*is_root_module*/));
    return std::make_pair(sg, e);
}

std::pair<annotations::scribble_group,
          boost::shared_ptr<meta_model::enumeration>>
adapter::to_enumeration(const processed_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to enumeration: "
                             << po.id();

    auto e(boost::make_shared<meta_model::enumeration>());
    update_element(po, *e);

    for (const auto& attr : po.attributes())
        e->enumerators().push_back(to_enumerator(attr));

    const auto sg(to_scribble_group(po, false/*is_root_module*/));
    return std::make_pair(sg, e);
}

std::pair<annotations::scribble_group, boost::shared_ptr<meta_model::primitive>>
adapter::to_primitive(const processed_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to primitive: "
                             << po.id();

    auto p(boost::make_shared<meta_model::primitive>());
    update_element(po, *p);

    const auto sg(to_scribble_group(po, false/*is_root_module*/));
    return std::make_pair(sg, p);
}

boost::shared_ptr<meta_model::module>
adapter::to_module(const processed_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to module: "
                             << po.id();

    auto r(boost::make_shared<meta_model::module>());
    update_element(po, *r);
    return r;
}

std::pair<annotations::scribble_group, boost::shared_ptr<meta_model::concept>>
adapter::to_concept(const processed_object& po) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming dia object to concept: "
                             << po.id();

    auto c(boost::make_shared<meta_model::concept>());
    update_element(po, *c);

    for (const auto& attr : po.attributes())
        c->local_attributes().push_back(to_attribute(attr));

    const auto i(context_.child_dia_id_to_parent_names().find(po.id()));
    if (i == context_.child_dia_id_to_parent_names().end() || i->second.empty())
        BOOST_LOG_SEV(lg, debug) << "Object has no parents: " << c->name().id();
    else {
        c->is_child(true);
        c->refines(i->second);
    }

    const auto sg(to_scribble_group(po, false/*is_root_module*/));
    return std::make_pair(sg, c);
}

} } }

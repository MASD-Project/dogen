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
#include "dogen/utility/io/pair_io.hpp"
#include "dogen/annotations/types/scribble_group.hpp"
#include "dogen/annotations/io/scribble_group_io.hpp"
#include "dogen/yarn/types/helpers/name_factory.hpp"
#include "dogen/yarn.dia/types/building_error.hpp"
#include "dogen/yarn.dia/types/building_error.hpp"
#include "dogen/yarn.dia/types/builder.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.dia.builder"));

const std::string empty_package_id("Supplied package id is empty");
const std::string missing_module_for_name("Missing module for name: ");
const std::string missing_name_for_id("Missing name for dia object ID: ");
const std::string duplicate_element_id("Element id already exists: ");
const std::string duplicate_attribute_name("Attribute name already exists: ");
const std::string duplicate_dia_id("Duplicate dia id: ");
const std::string package_not_mapped(
    "Dia package ID is not mapped to yarn module: ");

}

namespace dogen {
namespace yarn {
namespace dia {

template<typename Element> void add_element(
    std::unordered_map<std::string, boost::shared_ptr<Element>>& container,
    const boost::shared_ptr<Element>& e) {

    const auto id(e->name().id());
    const auto pair(std::make_pair(id, e));
    bool inserted(container.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_element_id << id;
        BOOST_THROW_EXCEPTION(building_error(duplicate_element_id + id));
    }
    BOOST_LOG_SEV(lg, debug) << "Added element to model " << id;
}

builder::builder(const std::string& model_name,
    const std::string& external_modules,
    const std::unordered_map<std::string, std::list<std::string> >&
    parent_id_to_child_ids) : parent_id_to_child_ids_(parent_id_to_child_ids) {
    setup_model(model_name, external_modules);
}

meta_model::module& builder::module_for_name(const meta_model::name& n) {
    const auto i(model_.modules().find(n.id()));
    if (i == model_.modules().end()) {
        const auto sn(n.simple());
        BOOST_LOG_SEV(lg, error) << missing_module_for_name << sn;
        BOOST_THROW_EXCEPTION(building_error(missing_module_for_name + sn));
    }
    return *i->second;
}

boost::shared_ptr<meta_model::module>
builder::create_module_for_model(const meta_model::name& n) const {
    auto r(boost::make_shared<meta_model::module>());
    r->name(n);
    return r;
}

void builder::setup_model(const std::string& model_name,
    const std::string& external_modules) {

    helpers::name_factory nf;
    model_.name(nf.build_model_name(model_name, external_modules));
    BOOST_LOG_SEV(lg, debug) << "Model: " << model_.name().id();

    const auto mm(create_module_for_model(model_.name()));
    model_.modules().insert(std::make_pair(mm->name().id(), mm));
}

void builder::
update_scribble_group(const meta_model::name& n, const processed_object& po) {
    annotations::scribble psbl;
    const auto& kvps(po.comment().key_value_pairs());
    psbl.entries(kvps);

    using annotations::scope_types;
    psbl.scope(n == model_.name() ?
        scope_types::root_module : scope_types::entity);

    annotations::scribble_group sg;
    sg.parent(psbl);

    for (const auto& attr : po.attributes()) {
        const auto& kvps(attr.comment().key_value_pairs());
        if (kvps.empty())
            continue;

        annotations::scribble csbl;
        csbl.entries(kvps);
        csbl.scope(scope_types::property);

        const auto pair(std::make_pair(attr.name(), csbl));
        const auto&inserted(sg.children().insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_attribute_name << attr.name();
            BOOST_THROW_EXCEPTION(
                building_error(duplicate_attribute_name + attr.name()));
        }
    }

    bool no_kvps(sg.parent().entries().empty() && sg.children().empty());
    if (no_kvps)
        return;

    const auto pair(std::make_pair(n.id(), sg));
    BOOST_LOG_SEV(lg, debug) << "Inserting scribble group: " << pair;

    auto& sgrps(model_.scribble_groups());
    const bool inserted(sgrps.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_element_id << n.id();
        BOOST_THROW_EXCEPTION(building_error(duplicate_element_id + n.id()));
    }
}

void builder::
update_parentage(const std::string& dia_id, const meta_model::name& n) {
    const auto i(parent_id_to_child_ids_.find(dia_id));
    if (i == parent_id_to_child_ids_.end()) {
        /*
         * If we're not a parent, there is nothing to be done with
         * regards to parentage.
         */
        return;
    }

    /*
     * For every child of ours, map them against our name. Since we
     * are processing objects in dependency order, we know that all
     * parents have been processed before their children, and thus
     * this container is fully populated by the time the child reads
     * it.
     */
    for (const auto c : i->second)
        context_.child_dia_id_to_parent_names()[c].push_back(n);
}

void builder::update_module(const std::string& dia_id,
    boost::shared_ptr<meta_model::module> m) {

    const auto pair(std::make_pair(dia_id, m));
    bool inserted(context_.dia_id_to_module().insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_element_id << dia_id;
        BOOST_THROW_EXCEPTION(building_error(duplicate_element_id + dia_id));
    }
    BOOST_LOG_SEV(lg, debug) << "Added module to context: " << dia_id;
}

void builder::update_documentation(const processed_object& po) {
    BOOST_LOG_SEV(lg, debug) << "Object is a note: "
                             << po.id()
                             << ". Note text: '"
                             << po.comment().original_content() << "'";

    if (po.comment().original_content().empty() ||
        !po.comment().applicable_to_parent_object())
        return;

    const auto& documentation(po.comment().documentation());

    if (po.child_node_id().empty()) {
        auto& module(module_for_name(model_.name()));
        module.documentation(documentation);
        update_scribble_group(module.name(), po);
        return;
    }

    const auto package_id(po.child_node_id());
    const auto i(context_.dia_id_to_module().find(package_id));
    if (i == context_.dia_id_to_module().end()) {
        BOOST_LOG_SEV(lg, error) << package_not_mapped << package_id;
        BOOST_THROW_EXCEPTION(building_error(package_not_mapped + package_id));
    }
    auto& module(*i->second);
    module.documentation(documentation);
    update_scribble_group(module.name(), po);
}

void builder::add(const processed_object& po) {
    const transformer t(context_, model_.name());

    const auto id(po.id());
    const auto dot(po.dia_object_type());
    const auto yot(po.yarn_object_type());
    if (dot == dia_object_types::uml_note) {
        update_documentation(po);
        return;
    } else if (dot == dia_object_types::uml_large_package) {
        const auto m(t.to_module(po));
        update_module(id, m);
        add_element(model_.modules(), m);
        update_scribble_group(m->name(), po);
    } else if (yot == yarn_object_types::enumeration) {
        const auto e(t.to_enumeration(po));
        add_element(model_.enumerations(), e);
        update_scribble_group(e->name(), po);
    } else if (yot == yarn_object_types::primitive) {
        const auto p(t.to_primitive(po));
        add_element(model_.primitives(), p);
        update_scribble_group(p->name(), po);
    } else if (yot == yarn_object_types::concept) {
        const auto c(t.to_concept(po));
        update_parentage(po.id(), c->name());
        add_element(model_.concepts(), c);
        update_scribble_group(c->name(), po);
    } else if (yot == yarn_object_types::exception) {
        const auto e(t.to_exception(po));
        add_element(model_.exceptions(), e);
        update_scribble_group(e->name(), po);
    } else {
        const auto o(t.to_object(po));
        update_parentage(po.id(), o->name());
        add_element(model_.objects(), o);
        update_scribble_group(o->name(), po);
    }
}

meta_model::intermediate_model builder::build() {
    return model_;
}

} } }

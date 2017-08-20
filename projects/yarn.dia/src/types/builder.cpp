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
const std::string missing_name_for_id("Missing name for dia object ID: ");
const std::string duplicate_element_id("Element id already exists: ");
const std::string duplicate_dia_id("Duplicate dia id: ");
const std::string package_not_mapped(
    "Dia package ID is not mapped to yarn module: ");

}

namespace dogen {
namespace yarn {
namespace dia {

builder::builder(const std::unordered_map<std::string, std::list<std::string>>&
    parent_id_to_child_ids) : parent_id_to_child_ids_(parent_id_to_child_ids) {
    /*
     * Initialise the root module to (almost) nothing. We can't do
     * much more at the moment since we do not process the root module
     * name, nor do we know where it's scribbles are. We do it here
     * just to make sure the root module is initialised, in case the
     * user did not provide any documentation or scribbles for it.
     */
    auto rm(boost::make_shared<meta_model::module>());
    rm->is_root(true);
    model_.root_module().second = rm;
}

void builder::add_module_to_context(const std::string& dia_id,
    boost::shared_ptr<meta_model::module> m) {

    std::pair<annotations::scribble_group,
              boost::shared_ptr<yarn::meta_model::module>> module_pair;
    module_pair.second = m;

    const auto dia_pair(std::make_pair(dia_id, module_pair));
    bool inserted(context_.dia_id_to_module().insert(dia_pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_element_id << dia_id;
        BOOST_THROW_EXCEPTION(building_error(duplicate_element_id + dia_id));
    }
    BOOST_LOG_SEV(lg, debug) << "Added module to context: " << dia_id;
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

void builder::update_module(const processed_object& po) {
    BOOST_LOG_SEV(lg, debug) << "Object is a note: "
                             << po.id()
                             << ". Note text: '"
                             << po.comment().original_content() << "'";

    if (po.comment().original_content().empty() ||
        !po.comment().applicable_to_parent_object())
        return;

    const transformer t(context_);
    const auto& documentation(po.comment().documentation());
    if (po.child_node_id().empty()) {
        /*
         * Since this note does not have a child, it is a top-level
         * note. Thus is may be used to convey both scribbles and
         * documentation for the root module.
         */
        auto& pair(model_.root_module());
        pair.first = t.to_scribble_group(po, true/*is_root_module*/);
        pair.second->documentation(documentation);
        return;
    }

    /*
     * If the note is contained inside of a package, we need to ensure
     * we update the module for that package with its scribbles and
     * documentation. The module must already exist.
     */
    const auto package_id(po.child_node_id());
    const auto i(context_.dia_id_to_module().find(package_id));
    if (i == context_.dia_id_to_module().end()) {
        BOOST_LOG_SEV(lg, error) << package_not_mapped << package_id;
        BOOST_THROW_EXCEPTION(building_error(package_not_mapped + package_id));
    }
    auto& pair(i->second);
    pair.first = t.to_scribble_group(po, false/*is_root_module*/);
    pair.second->documentation(documentation);
}

void builder::add(const processed_object& po) {
    /*
     * First we handle module construction. Here, we have two
     * scenarios: either we are a UML package - in which case we
     * should process it into a yarn module - or we are a UML note,
     * containing the scribble and documentation information for a
     * module. This happens because dia does not support adding
     * comments directly to packages, so we "extended" it via the use
     * of UML notes.
     *
     * Note that we do not add the modules to the model at this stage;
     * this is done during the building phase.
     */
    const auto dot(po.dia_object_type());
    const transformer t(context_);
    if (dot == dia_object_types::uml_large_package) {
        add_module_to_context(po.id(), t.to_module(po));
        return;
    } else if (dot == dia_object_types::uml_note) {
        update_module(po);
        return;
    }

    /*
     * Now we can handle the remaining objects, all mapped to yarn
     * element types. For these, enumerations, primitives and
     * exceptions are trivial; we just need to transform
     * them. Concepts and objects have the notion of parenting, so for
     * them we must also resolve the dia object ID containment into
     * yarn names.
     */
    switch(po.yarn_object_type()) {
    case yarn_object_types::enumeration:
        model_.enumerations().push_back(t.to_enumeration(po));
        break;
    case yarn_object_types::primitive:
        model_.primitives().push_back(t.to_primitive(po));
        break;
    case yarn_object_types::exception:
        model_.exceptions().push_back(t.to_exception(po));
        break;
    case yarn_object_types::concept: {
        const auto pair(t.to_concept(po));
        update_parentage(po.id(), pair.second->name());
        model_.concepts().push_back(pair);
        break;
    }
    default: {
        /*
         * Objects are in effect anything which was not marked as
         * something else so they are our default case.
         */
        const auto pair(t.to_object(po));
        update_parentage(po.id(), pair.second->name());
        model_.objects().push_back(pair);
    } }
}

meta_model::exogenous_model builder::build() {
    /*
     * Add all modules in context into the modules container in the
     * model.
     */
    for (const auto& pair : context_.dia_id_to_module())
        model_.modules().push_back(pair.second);

    return model_;
}

} } }

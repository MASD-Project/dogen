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
#include "dogen.identification/io/entities/tagged_value_io.hpp"
#include "dogen.codec.dia/types/building_error.hpp"
#include "dogen.codec.dia/types/adapter.hpp"
#include "dogen.codec.dia/types/builder.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("codec.dia.builder"));

const std::string empty_contained_by;
const std::list<std::string> empty_parents;
const std::string duplicate_id("Duplicate id: ");
const std::string package_not_mapped("Dia package ID is not mapped: ");

}

namespace dogen::codec::dia {

builder::builder(const std::unordered_map<std::string, std::list<std::string>>&
    parent_id_to_child_ids) : parent_id_to_child_ids_(parent_id_to_child_ids) {}

void builder::update_parentage(const std::string& id, const std::string& n) {
    const auto i(parent_id_to_child_ids_.find(id));
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
    for (const auto& c : i->second)
        child_id_to_parent_names_[c].push_back(n);
}

const std::list<std::string>&
builder::parents_for_object(const std::string& id) const {
    const auto i(child_id_to_parent_names_.find(id));
    if (i != child_id_to_parent_names_.end())
        return i->second;

    return empty_parents;
}

std::string builder::contained_by(const std::string& id) const {
    auto& c(id_to_uml_large_package_properties_);
    const auto i(c.find(id));
    if (i != c.end())
        return i->second.name;

    return empty_contained_by;
}

void builder::
handle_uml_large_package(const processed_object& po, const std::string& n) {
    BOOST_LOG_SEV(lg, debug) << "Object is a UML Large package: '"
                             << po.id() << "'. Name: " << n;

    uml_large_package_properties p;
    p.name = n;

    /*
     * We have just finished inserting the element so we can be
     * confident that the last element is the one we're interested
     * in. This is not ideal but will do for now.
     */
    p.element = --(model_.elements().end());

    const auto& id(po.id());
    const auto pair(std::make_pair(id, p));

    auto& c(id_to_uml_large_package_properties_);
    const auto inserted(c.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_id << id;
        BOOST_THROW_EXCEPTION(building_error(duplicate_id + id));
    }
}

void builder::handle_uml_note(const processed_object& po) {
    const auto& c(po.comment());
    BOOST_LOG_SEV(lg, debug) << "Object is a note: '" << po.id()
                             << ";. Note text: '"
                             << c.original_content() << "'";

    if (c.original_content().empty() || !c.applicable_to_parent_object())
        return;

    if (po.child_node_id().empty()) {
        /*
         * Since this note does not have a child, it is a top-level
         * note. Thus is may be used to convey both tagged values and
         * documentation for the model.
         */
        model_.documentation(c.documentation());
        model_.tagged_values(c.tagged_values());
        BOOST_LOG_SEV(lg, debug) << "Model documentation: '"
                                 << c.documentation() << "'";
        BOOST_LOG_SEV(lg, debug) << "Model tagged values: "
                                 << c.tagged_values();
        return;
    }

    /*
     * If the note is contained inside of a package, we need to ensure
     * we update the element for the for that UML package with its
     * tagged values and documentation. The module must already exist.
     */
    const auto package_id(po.child_node_id());
    const auto i(id_to_uml_large_package_properties_.find(package_id));
    if (i == id_to_uml_large_package_properties_.end()) {
        BOOST_LOG_SEV(lg, error) << package_not_mapped << package_id;
        BOOST_THROW_EXCEPTION(building_error(package_not_mapped + package_id));
    }

    auto& e(*i->second.element);
    e.documentation(c.documentation());
    e.tagged_values(c.tagged_values());
}

void builder::add(const processed_object& po) {
    BOOST_LOG_SEV(lg, debug) << "Processing: '" << po.id() << "'"
                             << " Name: '" << po.name() << "'";

    /*
     * First, we handle UML notes. Since Dia does not support adding
     * comments directly to UML packages, we "extended" it via the use
     * of UML notes. This means that when we find a note, we need to
     * check if its contents must be added to its containing package.
     */
    const auto dot(po.dia_object_type());
    if (dot == dia_object_types::uml_note) {
        handle_uml_note(po);
        return;
    }

    /*
     * For all cases other than UML notes, we know we need to generate
     * an element. For these, the first thing we need to do is to
     * figure out the containment of the current process object.
     */
    const auto& id(po.id());
    const auto cby(contained_by(po.child_node_id()));
    BOOST_LOG_SEV(lg, debug) << "Contained by: '" << cby << "'";

    /*
     * Then we get the parents for the processed object.
     */
    const auto& p(parents_for_object(id));
    BOOST_LOG_SEV(lg, debug) << "Parents: " << p;

    /*
     * Adapt the processed object and add it to the model.
     */
    const auto e(adapter::adapt(po, cby, p));
    model_.elements().push_back(e);
    BOOST_LOG_SEV(lg, debug) << "Added element: " << e.name().simple();

    /*
     * Now we need to deal with the post-processing. For UML packages,
     * we need to remember them for later. As explained above, we need
     * to update them with the contents of UML notes.
     */
    if (dot == dia_object_types::uml_large_package) {
        handle_uml_large_package(po, e.name().simple());
        return;
    }

    /*
     * For processed objects which can be parents, we need to update
     * their parenting details. Note that this refers to the children
     * of the current object, not its parents (which were handled
     * above).
     */
    update_parentage(id, e.name().simple());

    BOOST_LOG_SEV(lg, debug) << "Finished processing: " << po.name();
}

codec::entities::model builder::build() {
    return model_;
}

}

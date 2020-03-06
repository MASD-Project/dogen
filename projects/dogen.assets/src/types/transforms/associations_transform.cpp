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
#include <set>
#include <list>
#include <boost/lexical_cast.hpp>
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.assets/io/meta_model/name_io.hpp"
#include "dogen.assets/io/meta_model/model_io.hpp"
#include "dogen.assets/types/transforms/transformation_error.hpp"
#include "dogen.assets/types/transforms/associations_transform.hpp"

namespace {

const std::string transform_id("assets.transforms.associations_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::assets::transforms {

/**
 * @brief Removes duplicate names, preserving the original order
 * of elements in the list.
 *
 * @param names list of names to process
 * @param processed list of names that have already been processed
 * somewhere else, if any.
 */
void remove_duplicates(std::list<meta_model::name>& names,
    std::unordered_set<meta_model::name> processed =
    std::unordered_set<meta_model::name>()) {
    BOOST_LOG_SEV(lg, debug) << "Removing duplicates from list. Original size: "
                             << names.size() << ". Processed starts with size: "
                             << processed.size();

    if (names.empty()) {
        BOOST_LOG_SEV(lg, debug) << "Nothing to do.";
        return;
    }

    auto i(names.begin());
    while (i != names.end()) {
        const auto n(*i);
        if (processed.find(n) != processed.end()) {
            const auto j(i++);
            names.erase(j);
            continue;
        }
        ++i;
        processed.insert(n);
    }

    BOOST_LOG_SEV(lg, debug) << "Removed duplicates from list. final size: "
                             << names.size();
}

/**
 * @brief Walks through the name tree, updating associations as it
 * goes along.
 */
template<typename Associatable>
void update_associations(const meta_model::model& m, Associatable& a,
    const meta_model::name_tree& nt,
    const bool inherit_opaqueness_from_parent) {

    const auto n(nt.current());
    if (inherit_opaqueness_from_parent)
        a.opaque_associations().push_back(n);
    else
        a.transparent_associations().push_back(n);

    /*
     * If the parent type is an associative container, the first child
     * type will represent the key of the associative container and
     * the second type will be its value. We need to remember the
     * keys.
     *
     * Note that we must still continue to walk the tree even if the
     * type is not an associative container, since there are other
     * properties to set (see above).
     */
    bool is_first(true);
    const auto& objs(m.structural_elements().objects());
    const auto i(objs.find(n.qualified().dot()));
    const auto is_associative_container(i != objs.end() &&
        i->second->is_associative_container());

    for (const auto c : nt.children()) {
        if (is_first && is_associative_container)
            a.associative_container_keys().push_back(c.current());

        update_associations(m, a, c, nt.are_children_opaque());
        is_first = false;
    }

    if (!a.associative_container_keys().empty())
        remove_duplicates(a.associative_container_keys());
}

template<typename Associatable>
void process(Associatable& a) {
    std::unordered_set<meta_model::name> transparent_associations;
    remove_duplicates(a.transparent_associations());
    for (const auto n : a.transparent_associations())
        transparent_associations.insert(n);

    /*
     * Ensure we remove any items which are simultaneously regular
     * and weak associations.
     */
    remove_duplicates(a.opaque_associations(), transparent_associations);
}

void associations_transform::
process_object(const meta_model::model& m, meta_model::structural::object& o) {
    BOOST_LOG_SEV(lg, debug) << "Expand object: " << o.name().qualified().dot();

    for (const auto& p : o.local_attributes()) {
        const auto& nt(p.parsed_type());
        update_associations(m, o, nt, false/*inherit_opaqueness_from_parent*/);
    }
    process(o);
}

void associations_transform::
process_feature_template_bundle(const meta_model::model& m,
    meta_model::variability::feature_template_bundle& fb) {

    for (const auto& ft : fb.feature_templates()) {
        const auto& nt(ft.parsed_type());
        update_associations(m, fb, nt, false/*inherit_opaqueness_from_parent*/);
    }
    process(fb);
}

void associations_transform::process_feature_bundle(const meta_model::model& m,
    meta_model::variability::feature_bundle& fb) {

    for (const auto& f : fb.features()) {
        const auto& nt(f.parsed_type());
        update_associations(m, fb, nt, false/*inherit_opaqueness_from_parent*/);
    }
    process(fb);
}

void associations_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "associations transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    auto& objs(m.structural_elements().objects());
    BOOST_LOG_SEV(lg, debug) << "Total objects: " << objs.size();

    for (auto& pair : objs)
        process_object(m, *pair.second);

    auto& templates(m.variability_elements().feature_template_bundles());
    BOOST_LOG_SEV(lg, debug) << "Total feature templates: " << templates.size();

    for (auto& pair : templates)
        process_feature_template_bundle(m, *pair.second);

    auto& bundles(m.variability_elements().feature_bundles());
    BOOST_LOG_SEV(lg, debug) << "Total feature bundles: " << bundles.size();

    for (auto& pair : bundles)
        process_feature_bundle(m, *pair.second);

    stp.end_transform(m);
}

}

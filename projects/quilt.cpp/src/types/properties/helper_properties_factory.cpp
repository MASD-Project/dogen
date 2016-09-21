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
#include <utility>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/properties/name_builder.hpp"
#include "dogen/quilt.cpp/types/properties/building_error.hpp"
#include "dogen/quilt.cpp/io/properties/helper_properties_io.hpp"
#include "dogen/quilt.cpp/io/annotations/helper_annotations_io.hpp"
#include "dogen/quilt.cpp/types/properties/helper_properties_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(
    logger_factory("quilt.cpp.properties.helper_properties_factory"));

const std::string qn_missing("Could not find qualified name for language.");
const std::string empty_identifiable(
    "Identifiable was not generated correctly and is empty.");
const std::string descriptor_expected(
    "Child name tree has no associated helper descriptor");
const std::string missing_helper_annotations("Helper annotations not found for: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

template<typename Qualified>
inline std::string get_qualified(const Qualified& iaq) {
    const auto i(iaq.qualified().find(yarn::languages::cpp));
    if (i == iaq.qualified().end()) {
        BOOST_LOG_SEV(lg, error) << qn_missing << yarn::languages::cpp;
        BOOST_THROW_EXCEPTION(building_error(qn_missing));
    }
    return i->second;
}

helper_properties_factory::helper_properties_factory(
    const std::unordered_map<std::string, std::unordered_set<std::string>>&
    facets_for_family,
    const annotations::helper_annotations_repository& hsrp,
    const annotations::streaming_annotations_repository& ss)
    : facets_for_family_(facets_for_family), helper_annotations_(hsrp),
      streaming_annotations_(ss) { }

bool helper_properties_factory::
requires_hashing_helper(const std::string& family) const {
    /*
     * If there is no entry on the container for this family, we
     * don't need a helper for hashing.
     */
    const auto i(facets_for_family_.find(family));
    if (i == facets_for_family_.end())
        return false;

    /*
     * If the hash facet is not present in the helpers for this family
     * then the family does not require hashing support.
     */
    const auto j(i->second.find(formatters::hash::traits::facet_name()));
    return j != i->second.end();
}

annotations::helper_annotations helper_properties_factory::
helper_annotations_for_id(const std::string& id) const {
    const auto i(helper_annotations_.by_id().find(id));
    if (i == helper_annotations_.by_id().end()) {
        BOOST_LOG_SEV(lg, debug) << missing_helper_annotations << id;
        BOOST_THROW_EXCEPTION(building_error(missing_helper_annotations + id));
    }

    BOOST_LOG_SEV(lg, debug) << "Found helper annotations for type: " << id
                             << ". Annotations: " << i->second;
    return i->second;
}

boost::optional<annotations::streaming_annotations> helper_properties_factory::
streaming_annotations_for_id(const std::string& id) const {
    const auto i(streaming_annotations_.by_id().find(id));
    if (i == streaming_annotations_.by_id().end())
        return boost::optional<annotations::streaming_annotations>();

    return i->second;
}

boost::optional<helper_descriptor>
helper_properties_factory::make(const bool in_inheritance_relationship,
    const bool inherit_opaqueness_from_parent, const yarn::name_tree& nt,
    std::unordered_set<std::string>& done,
    std::list<helper_properties>& properties) const {
    const auto id(nt.current().id());
    BOOST_LOG_SEV(lg, debug) << "Processing type: " << id;

    helper_descriptor r;
    properties::name_builder b;
    r.namespaces(b.namespace_list(nt.current()));
    r.is_simple_type(nt.is_current_simple_type());

    const auto ss(streaming_annotations_for_id(id));
    if (ss) {
        r.streaming_annotations(ss);
        BOOST_LOG_SEV(lg, debug) << "Adding streaming annotations for: " << id;
    }

    const auto hs(helper_annotations_for_id(id));
    r.helper_annotations(hs);
    r.requires_hashing_helper(requires_hashing_helper(hs.family()));
    BOOST_LOG_SEV(lg, debug) << "Adding helper annotations for: " << id;

    r.name_identifiable(nt.current().identifiable());
    r.name_qualified(get_qualified(nt.current()));
    r.name_tree_identifiable(nt.identifiable());
    r.name_tree_qualified(get_qualified(nt));
    r.is_circular_dependency(nt.is_circular_dependency());
    r.is_pointer(inherit_opaqueness_from_parent);

    /*
     * Ensure we have different helpers for pointer and non-pointer
     * support.
     */
    if (r.is_pointer())
        r.name_tree_identifiable().append("_ptr");

    helper_properties hp;
    hp.current(r);

    const auto iir(in_inheritance_relationship);
    hp.in_inheritance_relationship(iir);

    /*
     * Note that we are processing the children even though the parent
     * may not require a helper. This is over-caution and may even be
     * wrong. We are basically saying that in a name tree, there may
     * be nodes which do not require helpers followed by nodes that
     * do.
     */
    for (const auto c : nt.children()) {
        /*
         * We need to remember the descriptors of the direct
         * descendants (and just the direct descendants, not its
         * children). If we have a child, we must have a descriptor.
         */
        const auto aco(nt.are_children_opaque());
        const auto dd(make(iir, aco, c, done, properties));
        if (!dd) {
            BOOST_LOG_SEV(lg, error) << descriptor_expected;
            BOOST_THROW_EXCEPTION(building_error(descriptor_expected));
        }

        const auto ident(dd->name_tree_identifiable());
        if (ident.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_identifiable;
            BOOST_THROW_EXCEPTION(building_error(empty_identifiable));
        }
        hp.direct_descendants().push_back(*dd);
    }
    BOOST_LOG_SEV(lg, debug) << "Helper properties: " << hp;

    /*
     * Ensure we have not yet created a helper for this name
     * tree. Note that we must still do the processing above in
     * order to ensure the direct descendants are computed, even
     * though the helper itself may not be required. As an
     * example, take the case of a map of string to string. We
     * need the helper for the map to have two direct descendants
     * (one per string), but we do not want to generate two helper
     * methods for the strings.
     *
     * Note also we are using the return type's identifiable
     * rather than the input name tree's identifiable. This is
     * because we may have augmented it (e.g. the is pointer use
     * case).
     */
    const auto ident(r.name_tree_identifiable());
    if (ident.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_identifiable;
        BOOST_THROW_EXCEPTION(building_error(empty_identifiable));
    }

    if (done.find(ident) == done.end()) {
        properties.push_back(hp);
        done.insert(ident);
    } else {
        BOOST_LOG_SEV(lg, debug) << "Name tree already processed: "
                                 << ident;
    }
    return r;
}

std::list<helper_properties> helper_properties_factory::
make(const bool in_inheritance_relationship,
    const std::list<yarn::attribute>& attributes) const {
    if (attributes.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No properties found.";
        return std::list<helper_properties>();
    }

    BOOST_LOG_SEV(lg, debug) << "Properties found: " << attributes.size();
    std::list<helper_properties> r;
    std::unordered_set<std::string> done;
    for (const auto a : attributes) {
        const auto& nt(a.parsed_type());
        const bool opaqueness_from_parent(false);
        make(in_inheritance_relationship, opaqueness_from_parent, nt, done, r);
    }

    if (r.empty())
        BOOST_LOG_SEV(lg, debug) << "No helper properties found.";

    return r;
}

} } } }

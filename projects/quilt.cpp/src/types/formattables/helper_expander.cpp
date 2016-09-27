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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/quilt.cpp/types/annotations/helper_annotations_factory.hpp"
#include "dogen/quilt.cpp/types/annotations/streaming_annotations_factory.hpp"
#include "dogen/quilt.cpp/io/annotations/helper_annotations_io.hpp"
#include "dogen/quilt.cpp/io/annotations/streaming_annotations_io.hpp"
#include "dogen/quilt.cpp/io/formattables/helper_configuration_io.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/annotations/streaming_annotations_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/expansion_error.hpp"
#include "dogen/quilt.cpp/types/formattables/helper_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.annotations.helper_expander"));

const std::string qn_missing("Could not find qualified name for language.");
const std::string descriptor_expected(
    "Child name tree has no associated helper descriptor");
const std::string missing_helper_annotations(
    "Helper annotations not found for: ");
const std::string empty_identifiable(
    "Identifiable was not generated correctly and is empty.");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

template<typename Qualified>
inline std::string get_qualified(const Qualified& iaq) {
    const auto i(iaq.qualified().find(yarn::languages::cpp));
    if (i == iaq.qualified().end()) {
        BOOST_LOG_SEV(lg, error) << qn_missing << yarn::languages::cpp;
        BOOST_THROW_EXCEPTION(expansion_error(qn_missing));
    }
    return i->second;
}

inline std::ostream&
operator<<(std::ostream& s, const helper_expander::annotations& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "helper_expander::annotations\"" << ", "
      << "\"helper_annotations\": " << v.helper_annotations << ", "
      << "\"streaming_annotations\": " << v.streaming_annotations
      << " }";

    return s;
}

helper_expander::annotations
helper_expander::obtain_annotations(const dynamic::repository& drp,
    const std::unordered_map<std::string, formattable>& formattables) const {
    BOOST_LOG_SEV(lg, debug) << "Started making the annotations.";

    annotations r;
    cpp::annotations::helper_annotations_factory haf(drp);
    cpp::annotations::streaming_annotations_factory saf(drp);

    for (auto& pair : formattables) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        for (const auto& segment : formattable.element_segments()) {

            if (segment->is_element_extension())
                continue;

            const auto streaming_annotation(saf.make(segment->extensions()));
            if (streaming_annotation)
                r.streaming_annotations[id] = *streaming_annotation;

            r.helper_annotations[id] = haf.make(segment->extensions());
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished making the annotations. Result:" << r;
    return r;
}

helper_expander::facets_for_family_type
helper_expander::facets_for_family(const formatters::container& fc) const {
    BOOST_LOG_SEV(lg, debug) << "Started making facets for family.";

    facets_for_family_type r;

    /*
     * Unpack the helper formatter container to generate a mapping of
     * helper family to facet. The container has helpers by family, by
     * owning file formatter.
     */
    for (const auto& families_pair : fc.helper_formatters())
        for (const auto& file_formatter_pair : families_pair.second)
            for (const auto& hf : file_formatter_pair.second)
                for (const auto& f : hf->owning_facets())
                    r[hf->family()].insert(f);

    BOOST_LOG_SEV(lg, debug) << "Finished making facets for family. Result: "
                             << r;
    return r;
}

bool helper_expander::requires_hashing_helper(const facets_for_family_type& fff,
    const std::string& family) const {
    /*
     * If there is no entry on the container for this family, we
     * don't need a helper for hashing.
     */
    const auto i(fff.find(family));
    if (i == fff.end())
        return false;

    /*
     * If the hash facet is not present in the helpers for this family
     * then the family does not require hashing support.
     */
    const auto j(i->second.find(formatters::hash::traits::facet_name()));
    return j != i->second.end();
}

const cpp::annotations::helper_annotations& helper_expander::
helper_annotations_for_id(const annotations& a, const std::string& id) const {

    const auto i(a.helper_annotations.find(id));
    if (i == a.helper_annotations.end()) {
        BOOST_LOG_SEV(lg, debug) << missing_helper_annotations << id;
        BOOST_THROW_EXCEPTION(expansion_error(missing_helper_annotations + id));
    }

    BOOST_LOG_SEV(lg, debug) << "Found helper annotations for type: " << id
                             << ". Annotations: " << i->second;
    return i->second;
}

boost::optional<annotations::streaming_annotations>
helper_expander::streaming_annotations_for_id(const annotations& a,
    const std::string& id) const {

    const auto i(a.streaming_annotations.find(id));
    if (i == a.streaming_annotations.end())
        return boost::optional<cpp::annotations::streaming_annotations>();

    return i->second;
}



std::list<std::string>
helper_expander::namespace_list(const yarn::name& n) const {
    const auto& l(n.location());
    std::list<std::string> r(l.external_modules());

    for (const auto& m : l.model_modules())
        r.push_back(m);

    for (const auto& m : l.internal_modules())
        r.push_back(m);

    /* if the name belongs to the model's module, we need to remove the
     * module's simple name from the module path (it is in both the
     * module path and it is also the module's simple name).
     */
    const bool no_internal_modules(l.internal_modules().empty());
    const bool has_model_modules(!l.model_modules().empty());
    const bool is_model_name(no_internal_modules && has_model_modules &&
        n.simple() == l.model_modules().back());

    if (is_model_name)
        r.pop_back();

    return r;
}

boost::optional<helper_descriptor> helper_expander::walk_name_tree(
    const annotations& a, const facets_for_family_type& fff,
    const bool in_inheritance_relationship,
    const bool inherit_opaqueness_from_parent, const yarn::name_tree& nt,
    std::unordered_set<std::string>& done,
    std::list<helper_configuration>& configuration) const {

    const auto id(nt.current().id());
    BOOST_LOG_SEV(lg, debug) << "Processing type: " << id;

    helper_descriptor r;
    r.namespaces(namespace_list(nt.current()));
    r.is_simple_type(nt.is_current_simple_type());

    const auto ss(streaming_annotations_for_id(a, id));
    if (ss) {
        r.streaming_annotations(ss);
        BOOST_LOG_SEV(lg, debug) << "Adding streaming annotations for: " << id;
    }

    const auto hs(helper_annotations_for_id(a, id));
    r.helper_annotations(hs);
    r.requires_hashing_helper(requires_hashing_helper(fff, hs.family()));
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

    helper_configuration hc;
    hc.current(r);

    const auto iir(in_inheritance_relationship);
    hc.in_inheritance_relationship(iir);

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
        const auto dd(walk_name_tree(a, fff, iir, aco, c, done, configuration));
        if (!dd) {
            BOOST_LOG_SEV(lg, error) << descriptor_expected;
            BOOST_THROW_EXCEPTION(expansion_error(descriptor_expected));
        }

        const auto ident(dd->name_tree_identifiable());
        if (ident.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_identifiable;
            BOOST_THROW_EXCEPTION(expansion_error(empty_identifiable));
        }
        hc.direct_descendants().push_back(*dd);
    }
    BOOST_LOG_SEV(lg, debug) << "Helper properties: " << hc;

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
        BOOST_THROW_EXCEPTION(expansion_error(empty_identifiable));
    }

    if (done.find(ident) == done.end()) {
        configuration.push_back(hc);
        done.insert(ident);
    } else {
        BOOST_LOG_SEV(lg, debug) << "Name tree already processed: "
                                 << ident;
    }
    return r;
}

std::list<helper_configuration> helper_expander::compute_helper_configuration(
    const annotations& a, const facets_for_family_type& fff,
    const bool in_inheritance_relationship,
    const std::list<yarn::attribute>& attrs) const {

    BOOST_LOG_SEV(lg, debug) << "Started making helper configuration.";

    std::list<helper_configuration> r;
    if (attrs.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No properties found.";
        return r;
    }

    BOOST_LOG_SEV(lg, debug) << "Properties found: " << attrs.size();

    std::unordered_set<std::string> done;
    const bool opaqueness_from_parent(false);
    const bool iir(in_inheritance_relationship);
    for (const auto attr : attrs) {
        const auto& nt(attr.parsed_type());
        walk_name_tree(a, fff, iir, opaqueness_from_parent, nt, done, r);
    }

    if (r.empty())
        BOOST_LOG_SEV(lg, debug) << "No helper properties found.";

    BOOST_LOG_SEV(lg, debug) << "Finished making helper configuration.";
    return r;
}

void helper_expander::populate_helper_configuration(const annotations& a,
    const formatters::container& fc,
    std::unordered_map<std::string, formattable>& formattables) const {

    const auto fff(facets_for_family(fc));
    for (auto& pair : formattables) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        auto& cfg(formattable.configuration());
        for (const auto& segment : formattable.element_segments()) {
            /*
             * We only want to process the master segment; the
             * extensions can be ignored.
             */
            if (segment->is_element_extension())
                continue;

            /*
             * We are only interested in yarn objects; all other
             * element types do not need helpers.
             */
            const auto ptr(dynamic_cast<const yarn::object*>(segment.get()));
            if (ptr == nullptr)
                continue;

            /*
             * We only need to generate helpers for the target
             * model. However, we can't perform this after reduction
             * because the helper annotations must be build prior to
             * reduction or else we will not get helpers for
             * referenced models.
             */
            if (ptr->generation_type() == yarn::generation_types::no_generation)
                continue;

            /*
             * Update the helper configuration.
             */
            const auto& attrs(ptr->local_attributes());
            const auto iir(ptr->in_inheritance_relationship());
            const auto hc(compute_helper_configuration(a, fff, iir, attrs));
            cfg.helper_configuration(hc);
        }
    }
}

void helper_expander::expand(const dynamic::repository& drp,
    const formatters::container& fc,
    std::unordered_map<std::string, formattable>& formattables) const {

    const auto a(obtain_annotations(drp, formattables));
    populate_helper_configuration(a, fc, formattables);
}

} } } }

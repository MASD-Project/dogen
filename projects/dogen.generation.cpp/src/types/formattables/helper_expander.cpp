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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.logical/types/meta_model/element.hpp"
#include "dogen.logical/types/meta_model/structural/object.hpp"
#include "dogen.logical/types/meta_model/structural/primitive.hpp"
#include "dogen.logical/types/meta_model/name_tree.hpp"
#include "dogen.logical/types/meta_model/attribute.hpp"
#include "dogen.logical/types/meta_model/element_visitor.hpp"
#include "dogen.logical/types/helpers/name_flattener.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formattables/helper_properties.hpp"
#include "dogen.generation.cpp/io/formattables/helper_configuration_io.hpp"
#include "dogen.generation.cpp/io/formattables/streaming_properties_io.hpp"
#include "dogen.generation.cpp/io/formattables/helper_properties_io.hpp"
#include "dogen.generation.cpp/types/formatters/hash/traits.hpp"
#include "dogen.generation.cpp/types/formatters/artefact_formatter_interface.hpp"
#include "dogen.generation.cpp/types/formatters/helper_formatter_interface.hpp"
#include "dogen.generation.cpp/types/formattables/expansion_error.hpp"
#include "dogen.generation.cpp/types/formattables/helper_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.cpp.formattables.helper_expander"));

const std::string descriptor_expected(
    "Child name tree has no associated helper descriptor");
const std::string missing_helper_family("Helper family not found for: ");
const std::string empty_identifiable(
    "Identifiable was not generated correctly and is empty.");

}

namespace dogen::generation::cpp::formattables {

class helper_properties_generator : public logical::meta_model::element_visitor {
public:
    helper_properties_generator(const helper_configuration& cfg,
        const helper_expander::facets_for_family_type& fff);

private:
    bool requires_hashing_helper(
        const helper_expander::facets_for_family_type& fff,
        const std::string& family) const;

    std::string helper_family_for_id(const helper_configuration& cfg,
        const std::string& id) const;

    boost::optional<streaming_properties> streaming_properties_for_id(
        const helper_configuration& cfg, const std::string& id) const;

private:
    boost::optional<helper_descriptor>
    walk_name_tree(const helper_configuration& cfg,
        const helper_expander::facets_for_family_type& fff,
        const bool in_inheritance_relationship,
        const bool inherit_opaqueness_from_parent,
        const logical::meta_model::name_tree& nt,
        std::unordered_set<std::string>& done,
        std::list<helper_properties>& hps) const;

    std::list<helper_properties>
    compute_helper_properties(const helper_configuration& cfg,
        const helper_expander::facets_for_family_type& fff,
        const bool in_inheritance_relationship,
        const std::list<logical::meta_model::attribute>& attrs) const;

public:
    /*
     * We are only interested in yarn objects and primitives; all
     * other element types do not need helpers.
     */
    using logical::meta_model::element_visitor::visit;
    void visit(const logical::meta_model::structural::object& o);
    void visit(const logical::meta_model::structural::primitive& p);

public:
    const std::list<formattables::helper_properties>& result() const;

private:
    const helper_configuration& helper_configuration_;
    const helper_expander::facets_for_family_type& facets_for_family_;
    std::list<formattables::helper_properties> result_;
};

helper_properties_generator::
helper_properties_generator(const helper_configuration& cfg,
    const helper_expander::facets_for_family_type& fff)
    : helper_configuration_(cfg), facets_for_family_(fff) {}

bool helper_properties_generator::
requires_hashing_helper(const helper_expander::facets_for_family_type& fff,
    const std::string& family) const {

    /*
     * If there is no entry on the container for this family, we don't
     * need a helper for hashing.
     */
    const auto i(fff.find(family));
    if (i == fff.end())
        return false;

    /*
     * If the hash facet is not present in the helpers for this family
     * then the family does not require hashing support.
     */
    const auto j(i->second.find(formatters::hash::traits::facet()));
    return j != i->second.end();
}

std::string helper_properties_generator::helper_family_for_id(
    const helper_configuration& cfg, const std::string& id) const {

    const auto i(cfg.helper_families().find(id));
    if (i == cfg.helper_families().end()) {
        BOOST_LOG_SEV(lg, error) << missing_helper_family << id;
        BOOST_THROW_EXCEPTION(expansion_error(missing_helper_family + id));
    }

    BOOST_LOG_SEV(lg, debug) << "Found helper family for type: " << id
                             << ". Family:" << i->second;
    return i->second;
}

boost::optional<formattables::streaming_properties>
helper_properties_generator::streaming_properties_for_id(
    const helper_configuration& cfg, const std::string& id) const {

    const auto i(cfg.streaming_properties().find(id));
    if (i == cfg.streaming_properties().end())
        return boost::optional<formattables::streaming_properties>();

    BOOST_LOG_SEV(lg, debug) << "Found streaming configuration for type: " << id
                             << ". Configuration: " << i->second;
    return i->second;
}

boost::optional<helper_descriptor>
helper_properties_generator::walk_name_tree(const helper_configuration& cfg,
    const helper_expander::facets_for_family_type& fff,
    const bool in_inheritance_relationship,
    const bool inherit_opaqueness_from_parent,
    const logical::meta_model::name_tree& nt,
    std::unordered_set<std::string>& done,
    std::list<helper_properties>& hps) const {

    const auto id(nt.current().qualified().dot());
    BOOST_LOG_SEV(lg, debug) << "Processing type: " << id;

    helper_descriptor r;
    logical::helpers::name_flattener nf;
    r.namespaces(nf.flatten(nt.current()));
    r.is_simple_type(nt.is_current_simple_type());

    const auto sp(streaming_properties_for_id(cfg, id));
    if (sp)
        r.streaming_properties(sp);

    const auto fam(helper_family_for_id(cfg, id));
    r.family(fam);
    r.requires_hashing_helper(requires_hashing_helper(fff, fam));

    r.name_identifiable(nt.current().qualified().identifiable());
    r.name_qualified(nt.current().qualified().colon());
    r.name_tree_identifiable(nt.qualified().identifiable());
    r.name_tree_qualified(nt.qualified().colon());
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
     * may not require a helper. This is slight over-caution and may
     * even be wrong. We are basically saying that in a name tree,
     * there may be nodes which do not require helpers followed by
     * nodes that do.
     */
    for (const auto c : nt.children()) {
        /*
         * We need to remember the descriptors of the direct
         * descendants - and just the direct descendants, not its
         * children. If we have a child, we must have a descriptor.
         */
        const auto aco(nt.are_children_opaque());
        const auto dd(walk_name_tree(cfg, fff, iir, aco, c, done, hps));
        if (!dd) {
            BOOST_LOG_SEV(lg, error) << descriptor_expected;
            BOOST_THROW_EXCEPTION(expansion_error(descriptor_expected));
        }

        const auto ident(dd->name_tree_identifiable());
        if (ident.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_identifiable;
            BOOST_THROW_EXCEPTION(expansion_error(empty_identifiable));
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
     * Note also we are using the return type's identifiable name
     * rather than the input name tree's identifiable. This is because
     * we may have augmented it - e.g. the "is pointer" use case.
     */
    const auto ident(r.name_tree_identifiable());
    if (ident.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_identifiable;
        BOOST_THROW_EXCEPTION(expansion_error(empty_identifiable));
    }

    if (done.find(ident) == done.end()) {
        hps.push_back(hp);
        done.insert(ident);
    } else
        BOOST_LOG_SEV(lg, debug) << "Name tree already processed: " << ident;

    return r;
}

std::list<helper_properties>
helper_properties_generator::
compute_helper_properties(const helper_configuration& cfg,
    const helper_expander::facets_for_family_type& fff,
    const bool in_inheritance_relationship,
    const std::list<logical::meta_model::attribute>& attrs) const {

    BOOST_LOG_SEV(lg, debug) << "Started making helper properties.";

    std::list<helper_properties> r;
    if (attrs.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No attributes found.";
        return r;
    }

    BOOST_LOG_SEV(lg, debug) << "Attributes found: " << attrs.size();

    std::unordered_set<std::string> done;
    const bool opaqueness_from_parent(false);
    const bool iir(in_inheritance_relationship);
    for (const auto attr : attrs) {
        const auto& nt(attr.parsed_type());
        walk_name_tree(cfg, fff, iir, opaqueness_from_parent, nt, done, r);
    }

    if (r.empty())
        BOOST_LOG_SEV(lg, debug) << "No helper properties found.";

    BOOST_LOG_SEV(lg, debug) << "Finished making helper properties.";
    return r;
}

void helper_properties_generator::visit(const logical::meta_model::structural::object& o) {
    const auto& fff(facets_for_family_);
    const auto& cfg(helper_configuration_);
    const auto& attrs(o.local_attributes());
    const auto iir(o.in_inheritance_relationship());
    result_ = compute_helper_properties(cfg, fff, iir, attrs);
}

void helper_properties_generator::visit(const logical::meta_model::structural::primitive& p) {
    const auto& fff(facets_for_family_);
    const auto& cfg(helper_configuration_);
    const std::list<logical::meta_model::attribute> attrs({ p.value_attribute() });
    const auto iir(false/*in_inheritance_relationship*/);
    result_ = compute_helper_properties(cfg, fff, iir, attrs);
}

const std::list<formattables::helper_properties>&
helper_properties_generator::result() const {
    return result_;
}

helper_expander::feature_group helper_expander::
make_feature_group(const variability::meta_model::feature_model& fm) const {
    const variability::helpers::feature_selector s(fm);
    const auto hf(traits::cpp::helper::family());
    feature_group r;
    r.family = s.get_by_name(hf);
    return r;
}

helper_configuration helper_expander::
make_configuration(const feature_group& fg, const model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Started making the configuration.";
    helper_configuration r;
    r.streaming_properties(fm.streaming_properties());

    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        auto& segment(*formattable.element());
        const auto& cfg(*segment.configuration());
        const variability::helpers::configuration_selector s(cfg);
        const auto fam(s.get_text_content_or_default(fg.family));
        r.helper_families()[id] = fam;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished making the configuration. Result:"
                             << r;

    return r;
}


helper_expander::facets_for_family_type
helper_expander::facets_for_family(const formatters::repository& frp) const {
    BOOST_LOG_SEV(lg, debug) << "Started making facets for family.";

    /*
     * Unpack the helper formatter container to generate a mapping of
     * helper family to facet. The container has helpers by family, by
     * owning file formatter.
     */
    facets_for_family_type r;
    for (const auto& families_pair : frp.helper_formatters())
        for (const auto& file_formatter_pair : families_pair.second)
            for (const auto& hf : file_formatter_pair.second)
                for (const auto& f : hf->owning_facets())
                    r[hf->family()].insert(f);

    BOOST_LOG_SEV(lg, debug) << "Finished making facets for family. Result: "
                             << r;
    return r;
}

void helper_expander::populate_helper_properties(
    const helper_configuration& cfg, const formatters::repository& frp,
    std::unordered_map<std::string, formattable>& formattables) const {

    const auto fff(facets_for_family(frp));
    for (auto& pair : formattables) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        auto& eprops(formattable.element_properties());

        /*
         * We only want to process the master segment; the extensions
         * can be ignored.
         */
        auto& segment(formattable.element());

        /*
         * We only need to generate helpers for the target
         * model. However, we can't perform this after reduction
         * because the helper properties must be build prior to
         * reduction or else we will not get helpers for referenced
         * models.
         */
        if (segment->origin_type() != logical::meta_model::origin_types::target) {
            BOOST_LOG_SEV(lg, debug) << "Skipping non-target element.";
            continue;
        }

        /*
         * Update the helper properties, if any exist.
         */
        const auto& e(*segment);
        helper_properties_generator g(cfg, fff);
        e.accept(g);
        eprops.helper_properties(g.result());

        BOOST_LOG_SEV(lg, debug) << "Helper properties generated: "
                                 << g.result().size();
    }
}

void helper_expander::expand(
    const variability::meta_model::feature_model& feature_model,
    const formatters::repository& frp, model& fm) const {
    const auto fg(make_feature_group(feature_model));
    const auto cfg(make_configuration(fg, fm));
    populate_helper_properties(cfg, frp, fm.formattables());
}

}

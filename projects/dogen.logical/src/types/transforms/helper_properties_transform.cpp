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
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.identification/types/entities/logical_name_tree.hpp"
#include "dogen.identification/types/helpers/logical_name_flattener.hpp"
#include "dogen.logical/types/features/helpers.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/attribute.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/helper_descriptor.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.logical/types/entities/helper_properties.hpp"
#include "dogen.logical/io/entities/streaming_properties_io.hpp"
#include "dogen.logical/types/entities/elements_traversal.hpp"
#include "dogen.logical/io/entities/helper_properties_io.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/helper_properties_transform.hpp"

namespace {

const std::string
transform_id("logical.transforms.helper_properties_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string duplicate_id("Duplicate ID:");
const std::string descriptor_expected(
    "Child name tree has no associated helper descriptor");
const std::string missing_helper_family("Helper family not found for: ");
const std::string empty_identifiable(
    "Identifiable was not generated correctly and is empty.");

}

namespace dogen::logical::transforms {

using logical::entities::helper_properties;
using logical::entities::helper_descriptor;

namespace {

class helper_properties_generator : public logical::entities::element_visitor {
public:
    helper_properties_generator(const std::unordered_map<
        identification::entities::logical_id, std::string>& helper_families,
        const std::unordered_map<identification::entities::logical_id,
        logical::entities::streaming_properties>& streaming_properties,
        const std::unordered_map<std::string, std::unordered_set<std::string>>&
        fff);

private:
    bool requires_hashing_helper(const std::string& family) const;

    std::string helper_family_for_id(
        const identification::entities::logical_id& id) const;

    boost::optional<logical::entities::streaming_properties>
    streaming_properties_for_id(
        const identification::entities::logical_id& id) const;

private:
    boost::optional<helper_descriptor>
    walk_name_tree(const bool in_inheritance_relationship,
        const bool inherit_opaqueness_from_parent,
        const identification::entities::logical_name_tree& nt,
        std::unordered_set<std::string>& done,
        std::list<helper_properties>& hps) const;

    std::list<helper_properties>
    compute_helper_properties(const bool in_inheritance_relationship,
        const std::list<logical::entities::attribute>& attrs) const;

public:
    /*
     * We are only interested in yarn objects and primitives; all
     * other element types do not need helpers.
     */
    using logical::entities::element_visitor::visit;
    void visit(logical::entities::structural::object& o);
    void visit(logical::entities::structural::primitive& p);

public:
    const std::list<logical::entities::helper_properties>& result() const;

private:
    const std::unordered_map<
    identification::entities::logical_id, std::string>& helper_families_;
    const std::unordered_map<identification::entities::logical_id,
                             logical::entities::streaming_properties>&
    streaming_properties_;
    const std::unordered_map<std::string, std::unordered_set<std::string>>&
    facets_for_family_;
    std::list<logical::entities::helper_properties> result_;
};

helper_properties_generator::
helper_properties_generator(const std::unordered_map<
    identification::entities::logical_id, std::string>& helper_families,
    const std::unordered_map<identification::entities::logical_id,
    logical::entities::streaming_properties>& streaming_properties,
    const std::unordered_map<std::string, std::unordered_set<std::string>>&
    fff)
    : helper_families_(helper_families),
      streaming_properties_(streaming_properties), facets_for_family_(fff) {}

bool helper_properties_generator::
requires_hashing_helper(const std::string& family) const {

    /*
     * If there is no entry on the container for this family, we don't
     * need a helper for hashing.
     */
    const auto i(facets_for_family_.find(family));
    if (i == facets_for_family_.end())
        return false;

    /*
     * If the hash facet is not present in the helpers for this family
     * then the family does not require hashing support.
     */
    const auto j(i->second.find("masd.cpp.hash"));
    return j != i->second.end();
}

std::string helper_properties_generator::
helper_family_for_id(const identification::entities::logical_id& id) const {

    const auto i(helper_families_.find(id));
    if (i == helper_families_.end()) {
        BOOST_LOG_SEV(lg, error) << missing_helper_family << id;
        BOOST_THROW_EXCEPTION(
            transformation_error(missing_helper_family + id.value()));
    }

    BOOST_LOG_SEV(lg, debug) << "Found helper family for type: " << id
                             << ". Family:" << i->second;
    return i->second;
}

boost::optional<logical::entities::streaming_properties>
helper_properties_generator::streaming_properties_for_id(
    const identification::entities::logical_id& id) const {

    const auto i(streaming_properties_.find(id));
    if (i == streaming_properties_.end())
        return boost::optional<logical::entities::streaming_properties>();

    BOOST_LOG_SEV(lg, debug) << "Found streaming configuration for type: " << id
                             << ". Configuration: " << i->second;
    return i->second;
}

boost::optional<helper_descriptor> helper_properties_generator::
walk_name_tree(const bool in_inheritance_relationship,
    const bool inherit_opaqueness_from_parent,
    const identification::entities::logical_name_tree& nt,
    std::unordered_set<std::string>& done,
    std::list<helper_properties>& hps) const {

    const auto id(nt.current().id());
    BOOST_LOG_SEV(lg, debug) << "Processing type: " << id;

    helper_descriptor r;
    identification::helpers::logical_name_flattener nf;
    r.namespaces(nf.flatten(nt.current()));
    r.is_simple_type(nt.is_current_simple_type());

    const auto sp(streaming_properties_for_id(id));
    if (sp)
        r.streaming_properties(sp);

    const auto fam(helper_family_for_id(id));
    r.family(fam);
    r.requires_hashing_helper(requires_hashing_helper(fam));

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
    for (const auto& c : nt.children()) {
        /*
         * We need to remember the descriptors of the direct
         * descendants - and just the direct descendants, not its
         * children. If we have a child, we must have a descriptor.
         */
        const auto aco(nt.are_children_opaque());
        const auto dd(walk_name_tree(iir, aco, c, done, hps));
        if (!dd) {
            BOOST_LOG_SEV(lg, error) << descriptor_expected;
            BOOST_THROW_EXCEPTION(transformation_error(descriptor_expected));
        }

        const auto ident(dd->name_tree_identifiable());
        if (ident.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_identifiable;
            BOOST_THROW_EXCEPTION(transformation_error(empty_identifiable));
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
        BOOST_THROW_EXCEPTION(transformation_error(empty_identifiable));
    }

    if (done.find(ident) == done.end()) {
        hps.push_back(hp);
        done.insert(ident);
    } else
        BOOST_LOG_SEV(lg, debug) << "Name tree already processed: " << ident;

    return r;
}


class configuration_generator {
public:
    explicit configuration_generator(
        const features::helpers::feature_group& fg);

public:
    void operator()(entities::element& e);

public:
    const std::unordered_map<identification::entities::logical_id, std::string>&
    result() { return result_; }

private:
    const features::helpers::feature_group& feature_group_;
    std::unordered_map<identification::entities::logical_id, std::string>
    result_;
};

configuration_generator::
configuration_generator(const features::helpers::feature_group& fg)
    : feature_group_(fg) {}

void configuration_generator::operator()(entities::element& e) {
    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id.value();

    const auto& cfg(*e.configuration());
    using features::helpers;
    const auto scfg(helpers::make_static_configuration(feature_group_, cfg));
    const auto pair(std::make_pair(id, scfg.family));
    const auto result(result_.insert(pair).second);
    if (!result) {
        BOOST_LOG_SEV(lg, error) << duplicate_id << id;
        BOOST_THROW_EXCEPTION(
            transformation_error(duplicate_id + id.value()));
    }
}

std::list<helper_properties>
helper_properties_generator::compute_helper_properties(
    const bool in_inheritance_relationship,
    const std::list<logical::entities::attribute>& attrs) const {

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
    for (const auto& attr : attrs) {
        const auto& nt(attr.parsed_type());
        walk_name_tree(iir, opaqueness_from_parent, nt, done, r);
    }

    if (r.empty())
        BOOST_LOG_SEV(lg, debug) << "No helper properties found.";

    BOOST_LOG_SEV(lg, debug) << "Finished making helper properties.";
    return r;
}

void helper_properties_generator::
visit(logical::entities::structural::object& o) {
    const auto& attrs(o.local_attributes());
    const auto iir(o.in_inheritance_relationship());
    result_ = compute_helper_properties(iir, attrs);
}

void helper_properties_generator::
visit(logical::entities::structural::primitive& p) {
    const std::list<logical::entities::attribute> attrs({ p.value_attribute() });
    const auto iir(false/*in_inheritance_relationship*/);
    result_ = compute_helper_properties(iir, attrs);
}

const std::list<logical::entities::helper_properties>&
helper_properties_generator::result() const {
    return result_;
}

}

std::unordered_map<identification::entities::logical_id, std::string>
helper_properties_transform::
make_configuration(const variability::entities::feature_model& fm,
    const entities::model& m) {

    BOOST_LOG_SEV(lg, debug) << "Started making the configuration.";

    using logical::features::helpers;
    const auto fg(helpers::make_feature_group(fm));
    configuration_generator cg(fg);
    elements_traversal(m, cg);

    const auto& r(cg.result());
    BOOST_LOG_SEV(lg, debug) << "Finished making the configuration. Result:"
                             << r;
    return r;
}

std::unordered_map<std::string, std::unordered_set<std::string>>
helper_properties_transform::
facets_for_family(const physical::entities::meta_model& pmm) {
    std::unordered_map<std::string, std::unordered_set<std::string>> r;
    for (const auto& be : pmm.backends()) {
        for (const auto& fct_pair : be.facets()) {
            const auto& fct(fct_pair.second);
            for (const auto& hlp_pair : fct.helpers()) {
                const auto& hlp(hlp_pair.second);
                const auto family(hlp.family());
                for (const auto& owning_fct : hlp.owning_facets())
                    r[family].insert(owning_fct.value());
            }
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished making facets for family. Result: "
                             << r;
    return r;
}

void helper_properties_transform::
populate_helper_properties(const std::unordered_map<
    identification::entities::logical_id, std::string>& /*helper_families*/,
    const std::unordered_map<identification::entities::logical_id,
    logical::entities::streaming_properties>& /*streaming_properties*/,
    const std::unordered_map<std::string, std::unordered_set<std::string>>&
    /*facets_for_family*/, entities::model& /*m*/) {

}

void helper_properties_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "helper properties",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    /*
     * First we read the configuration.
     */
    const auto& fm(*ctx.feature_model());
    const auto cfg(make_configuration(fm, m));

    /*
     * Then we map facets to families of helpers
     */
    const auto& pmm(*ctx.physical_meta_model());
    const auto fff(facets_for_family(pmm));

    /*
     * Finally we can generate the helper properties.
     */
    const auto& sp(m.streaming_properties());
    populate_helper_properties(cfg, sp, fff, m);

    stp.end_transform(m);
}

}

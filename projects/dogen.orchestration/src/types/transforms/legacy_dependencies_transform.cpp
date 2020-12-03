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
#include <string>
#include <sstream>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.identification/types/helpers/physical_meta_id_builder.hpp"
#include "dogen.identification/io/entities/logical_meta_physical_id_io.hpp"
#include "dogen.physical/io/entities/inclusion_directives_io.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/variability/feature_bundle.hpp"
#include "dogen.logical/types/entities/variability/feature_template_bundle.hpp"
#include "dogen.logical/types/entities/variability/initializer.hpp"
#include "dogen.logical/types/entities/physical/archetype.hpp"
#include "dogen.logical/types/entities/physical/facet.hpp"
#include "dogen.logical/types/entities/physical/backend.hpp"
#include "dogen.logical/types/entities/physical/part.hpp"
#include "dogen.logical/types/entities/physical/helper.hpp"
#include "dogen.logical/types/entities/physical/archetype_kind.hpp"
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/structural/visitor.hpp"
#include "dogen.logical/types/entities/structural/entry_point.hpp"
#include "dogen.logical/types/entities/serialization/type_registrar.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.text/io/entities/model_io.hpp"
#include "dogen.text/types/transforms/context.hpp"
#include "dogen.orchestration/types/helpers/dependencies_builder.hpp"
#include "dogen.orchestration/types/transforms/transform_exception.hpp"
#include "dogen.orchestration/types/transforms/legacy_dependencies_transform.hpp"

namespace {

const std::string
transform_id("orchestration.transforms.legacy_dependencies_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string std_list("<list>");
const std::string std_string("<string>");
const std::string std_iosfwd("<iosfwd>");
const std::string std_algorithm("<algorithm>");
const std::string std_ostream("<ostream>");
const std::string std_iostream("<iostream>");
const std::string std_sstream("<sstream>");
const std::string std_functional("<functional>");
const std::string std_stdexcept("<stdexcept>");
const std::string boost_shared_ptr("<boost/shared_ptr.hpp>");
const std::string boost_lexical_cast("<boost/lexical_cast.hpp>");
const std::string boost_predef("<boost/predef.h>");
const std::string boost_property_tree_ptree("<boost/property_tree/ptree.hpp>");
const std::string boost_property_tree_json_parser(
    "<boost/property_tree/json_parser.hpp>");
const std::string boost_type_traits_is_virtual_base_of(
    "<boost/type_traits/is_virtual_base_of.hpp>");
const std::string boost_archive_xml_iarchive(
    "<boost/archive/xml_iarchive.hpp>");
const std::string boost_archive_xml_oarchive(
    "<boost/archive/xml_oarchive.hpp>");
const std::string boost_archive_text_iarchive(
    "<boost/archive/text_iarchive.hpp>");
const std::string boost_archive_text_oarchive(
    "<boost/archive/text_oarchive.hpp>");
const std::string boost_archive_binary_iarchive(
    "<boost/archive/binary_iarchive.hpp>");
const std::string boost_archive_binary_oarchive(
    "<boost/archive/binary_oarchive.hpp>");
const std::string boost_archive_polymorphic_iarchive(
    "<boost/archive/polymorphic_iarchive.hpp>");
const std::string boost_archive_polymorphic_oarchive(
    "<boost/archive/polymorphic_oarchive.hpp>");
const std::string boost_serialization_nvp(
    "<boost/serialization/nvp.hpp>");
const std::string boost_serialization_split_free(
    "<boost/serialization/split_free.hpp>");
const std::string boost_serialization_assume_abstract(
    "<boost/serialization/assume_abstract.hpp>");
const std::string boost_serialization_shared_ptr(
    "<boost/serialization/shared_ptr.hpp>");
const std::string boost_exception_info("<boost/exception/info.hpp>");
const std::string boost_exception_diagnostic_information(
    "<boost/exception/diagnostic_information.hpp>");
const std::string boost_test_unit_test(
    "<boost/test/unit_test.hpp>");
const std::string boost_test_unit_test_monitor(
    "<boost/test/unit_test_monitor.hpp>");
const char angle_bracket('<');
const std::string double_quote("\"");
const std::string boost_name("boost");
const std::string boost_serialization_gregorian("greg_serialize.hpp");

const std::string duplicate_id("Duplicate logical-physical ID: ");
const std::string empty_include_directive("Include directive is empty.");

bool include_directive_comparer(
    const std::string& lhs, const std::string& rhs) {

    if (lhs.empty() || rhs.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_include_directive;
        using dogen::orchestration::transforms::transform_exception;
        BOOST_THROW_EXCEPTION(transform_exception(empty_include_directive));
    }

    const bool lhs_has_angle_brackets(lhs[0] == angle_bracket);
    const bool rhs_has_angle_brackets(rhs[0] == angle_bracket);

    if (lhs_has_angle_brackets && !rhs_has_angle_brackets)
        return true;

    if (!lhs_has_angle_brackets && rhs_has_angle_brackets)
        return false;

    if (lhs_has_angle_brackets && rhs_has_angle_brackets) {
        const auto npos(std::string::npos);
        const bool lhs_is_boost(lhs.find_first_of(boost_name) != npos);
        const bool rhs_is_boost(rhs.find_first_of(boost_name) != npos);
        if (!lhs_is_boost && rhs_is_boost)
            return false;

        if (lhs_is_boost && !rhs_is_boost)
            return true;

        // FIXME: hacks for headers that must be last
        const bool lhs_is_gregorian(
            lhs.find_first_of(boost_serialization_gregorian) != npos);
        const bool rhs_is_gregorian(
            rhs.find_first_of(boost_serialization_gregorian) != npos);
        if (lhs_is_gregorian && !rhs_is_gregorian)
            return true;

        if (!lhs_is_gregorian && rhs_is_gregorian)
            return false;
    }

    if (lhs.size() != rhs.size())
        return lhs.size() < rhs.size();

    return lhs < rhs;
}

}

namespace dogen::orchestration::transforms {

using helpers::dependencies_builder;
using identification::entities::technical_space;
using identification::entities::logical_name;
using identification::entities::logical_meta_physical_id;
using physical::entities::inclusion_directives;
using text::entities::logical_physical_region;

class region_processor : public logical::entities::element_visitor {
public:
    region_processor(const std::unordered_map<logical_meta_physical_id,
        inclusion_directives>& ids,
        const std::unordered_set<logical_meta_physical_id>&
        enabled_archetype_for_element, logical_physical_region& region) :
        inclusion_directives_(ids),
        enabled_archetype_for_element_(enabled_archetype_for_element),
        region_(region) {}

private:
    /**
     * @brief Returns the inclusion directive group for a given name
     * and formatter name.
     *
     * @pre name must exist in path derivatives collection.
     */
    boost::optional<inclusion_directives> get_directive_group(
        const logical_name& n, const std::string& archetype) const;

private:
    void build(dependencies_builder builder, physical::entities::artefact& a);

public:
    using logical::entities::element_visitor::visit;
    void visit(const logical::entities::physical::archetype& v);
    void visit(const logical::entities::physical::facet& v);
    void visit(const logical::entities::physical::backend& v);
    void visit(const logical::entities::physical::part& v);
    void visit(const logical::entities::physical::helper& v);
    void visit(const logical::entities::physical::archetype_kind& v);
    void visit(const logical::entities::serialization::type_registrar& v);
    void visit(const logical::entities::variability::feature_bundle& v);
    void visit(const logical::entities::variability::feature_template_bundle& v);
    void visit(const logical::entities::variability::initializer& v);
    void visit(const logical::entities::structural::object& v);
    void visit(const logical::entities::structural::enumeration& v);
    void visit(const logical::entities::structural::primitive& v);
    void visit(const logical::entities::structural::exception& v);
    void visit(const logical::entities::structural::visitor& v);
    void visit(const logical::entities::structural::entry_point& v);

private:
    const std::unordered_map<identification::entities::logical_meta_physical_id,
                             physical::entities::inclusion_directives>&
    inclusion_directives_;
    const std::unordered_set<
        identification::entities::logical_meta_physical_id>&
    enabled_archetype_for_element_;
    logical_physical_region& region_;
};

void region_processor::build(dependencies_builder builder,
    physical::entities::artefact& a) {
    /*
     * First, we generate the list of dependencies as setup previously
     * by the caller.
     */
    auto deps(builder.build());

    /*
     * Now, we ensure the dependencies are sorted according to a well
     * defined order and all duplicates are removed. Duplicates arise
     * because an element may refer to another element more than once
     * - e.g. std::list<T> as well as std::vector<T>.
     */
    deps.sort(include_directive_comparer);
    deps.unique();

    /*
     * Finally, we slot in the results in the archetype.
     */
    a.path_properties().inclusion_dependencies(deps);
}

void region_processor::
visit(const logical::entities::physical::archetype& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << pmid.value();

        dependencies_builder
            b(inclusion_directives_, enabled_archetype_for_element_);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.archetype_class_header_transform") {
            using identification::entities::technical_space;
            if (v.major_technical_space() == technical_space::cpp) {
                b.add_as_user(
                    "dogen.text.cpp/types/transforms/model_to_text_transform.hpp");
            } else if (v.major_technical_space() == technical_space::csharp) {
                b.add_as_user(
                    "dogen.text.csharp/types/transforms/model_to_text_transform.hpp");
            }
        } else if (pmid.value() == "masd.cpp.types.archetype_class_implementation_transform") {
            // no deps
        } else if (pmid.value() == "masd.cpp.types.archetype_class_implementation_factory") {
            b.add(v.name(),
                "masd.cpp.types.archetype_class_header_factory");
            b.add_as_user(
                "dogen.identification/types/helpers/physical_meta_name_factory.hpp");
        } else if (pmid.value() == "masd.cpp.types.archetype_class_header_factory") {
            b.add_as_user("dogen.physical/types/entities/archetype.hpp");
        }
        build(b, a);
    }
}

void region_processor::
visit(const logical::entities::physical::facet& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << pmid.value();

        dependencies_builder
            b(inclusion_directives_, enabled_archetype_for_element_);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.facet_class_header_transform") {
            b.add_as_user("dogen.physical/types/entities/facet.hpp");
            using identification::entities::technical_space;
            if (v.major_technical_space() == technical_space::cpp) {
                b.add_as_user(
                    "dogen.text.cpp/types/transforms/registrar.hpp");
            } else if (v.major_technical_space() == technical_space::csharp) {
                b.add_as_user(
                    "dogen.text.csharp/types/transforms/registrar.hpp");
            }
        } else if (pmid.value() == "masd.cpp.types.facet_class_implementation_transform") {
            const auto ch_arch("masd.cpp.types.canonical_archetype");
            b.add(v.name(), ch_arch);
            b.add(v.archetypes(), ch_arch);
            b.add_as_user(
                "dogen.identification/io/entities/physical_meta_id_io.hpp");
            b.add_as_user(
                "dogen.identification/types/helpers/physical_meta_name_builder.hpp");
            b.add_as_user("dogen.utility/types/log/logger.hpp");
            b.add_as_user(
                "dogen.text/types/transforms/transformation_error.hpp");
        } else if (pmid.value() == "masd.cpp.types.facet_class_header_factory") {
            b.add_as_user("dogen.physical/types/entities/facet.hpp");
        } else if (pmid.value() == "masd.cpp.types.facet_class_implementation_factory") {
            const auto fct_ch_arch("masd.cpp.types.facet_class_header_factory");
            b.add(v.name(), fct_ch_arch);

            const auto ch_arch("masd.cpp.types.archetype_class_header_factory");
            b.add(v.archetypes(), ch_arch);

            const auto ch_hlp("masd.cpp.types.helper_class_header_factory");
            b.add(v.helpers(), ch_hlp);

            b.add_as_user(
                "dogen.utility/types/log/logger.hpp");
            b.add_as_user(
                "dogen.text/types/transforms/transformation_error.hpp");
            b.add_as_user(
                "dogen.identification/io/entities/physical_meta_id_io.hpp");
            b.add_as_user(
                "dogen.identification/types/helpers/physical_meta_name_builder.hpp");
        }
        build(b, a);
    }
}

void region_processor::visit(const logical::entities::physical::backend& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << pmid.value();

        dependencies_builder
            b(inclusion_directives_, enabled_archetype_for_element_);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.backend_class_header_transform") {
            b.add_as_user("dogen.physical/types/entities/backend.hpp");
            using identification::entities::technical_space;
            if (v.major_technical_space() == technical_space::cpp) {
                b.add_as_user(
                    "dogen.text.cpp/types/transforms/registrar.hpp");
            } else if (v.major_technical_space() == technical_space::csharp) {
                b.add_as_user(
                    "dogen.text.csharp/types/transforms/registrar.hpp");
            }
        } else if (pmid.value() == "masd.cpp.types.backend_class_implementation_transform") {
            const auto ch_arch("masd.cpp.types.canonical_archetype");
            b.add(v.name(), ch_arch);
            b.add(v.facets(), ch_arch);
            b.add_as_user(
                "dogen.identification/io/entities/physical_meta_id_io.hpp");
            b.add_as_user(
                "dogen.identification/types/helpers/physical_meta_name_builder.hpp");
            b.add_as_user("dogen.utility/types/log/logger.hpp");
            b.add_as_user(
                "dogen.text/types/transforms/transformation_error.hpp");
        } else if (pmid.value() == "masd.cpp.types.backend_class_header_factory") {
            b.add_as_user("dogen.physical/types/entities/backend.hpp");
        } else if (pmid.value() == "masd.cpp.types.backend_class_implementation_factory") {
            const auto be_ch_arch("masd.cpp.types.backend_class_header_factory");
            b.add(v.name(), be_ch_arch);

            const auto fct_ch_arch("masd.cpp.types.facet_class_header_factory");
            b.add(v.facets(), fct_ch_arch);

            const auto ak_ch_arch("masd.cpp.types.archetype_kind_class_header_factory");
            b.add(v.archetype_kinds(), ak_ch_arch);

            const auto part_ch_arch("masd.cpp.types.part_class_header_factory");
            b.add(v.parts(), part_ch_arch);
            b.add_as_user(
                "dogen.identification/io/entities/physical_meta_id_io.hpp");
            b.add_as_user(
                "dogen.identification/types/helpers/physical_meta_name_builder.hpp");
            b.add_as_user(
                "dogen.utility/types/log/logger.hpp");
            b.add_as_user(
                "dogen.text/types/transforms/transformation_error.hpp");
        }
        build(b, a);
    }
}

void region_processor::visit(const logical::entities::physical::part& v) {
    auto& pr(region_.physical_region());

    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << pmid.value();

        dependencies_builder
            b(inclusion_directives_, enabled_archetype_for_element_);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.part_class_header_factory") {
            b.add_as_user("dogen.physical/types/entities/part.hpp");
        } else if (pmid.value() == "masd.cpp.types.part_class_implementation_factory") {
            const auto part_ch_arch("masd.cpp.types.part_class_header_factory");
            b.add(v.name(), part_ch_arch);

            b.add_as_user(
                "dogen.identification/io/entities/physical_meta_id_io.hpp");
            b.add_as_user(
                "dogen.identification/types/helpers/physical_meta_name_builder.hpp");
            b.add_as_user(
                "dogen.utility/types/log/logger.hpp");
            b.add_as_user(
                "dogen.text/types/transforms/transformation_error.hpp");
        }
        build(b, a);
    }
}

void region_processor::visit(const logical::entities::physical::helper& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << pmid.value();

        dependencies_builder
            b(inclusion_directives_, enabled_archetype_for_element_);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.helper_class_header_transform") {
            b.add_as_user(
                    "dogen.text/types/transforms/helper_transform.hpp");
        } else if (pmid.value() == "masd.cpp.types.helper_class_implementation_transform") {
            // no deps
        } else if (pmid.value() == "masd.cpp.types.helper_class_implementation_factory") {
            b.add(v.name(),
                "masd.cpp.types.helper_class_header_factory");
            b.add_as_user(
                "dogen.identification/types/helpers/physical_meta_name_factory.hpp");
        } else if (pmid.value() == "masd.cpp.types.helper_class_header_factory") {
            b.add_as_user("dogen.physical/types/entities/helper.hpp");
        }
        build(b, a);
    }
}

void region_processor::visit(const logical::entities::physical::archetype_kind& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << pmid.value();

        dependencies_builder
            b(inclusion_directives_, enabled_archetype_for_element_);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.archetype_kind_class_header_factory") {
            b.add_as_user(
                "dogen.physical/types/entities/archetype_kind.hpp");

        } else if (pmid.value() == "masd.cpp.types.archetype_kind_class_implementation_factory") {
            const auto ak_ch_arch(
                "masd.cpp.types.archetype_kind_class_header_factory");
            b.add(v.name(), ak_ch_arch);
            b.add_as_user(
                "dogen.identification/io/entities/physical_meta_id_io.hpp");
            b.add_as_user("dogen.utility/types/log/logger.hpp");
            b.add_as_user(
                "dogen.text/types/transforms/transformation_error.hpp");
        }
        build(b, a);
    }
}

void region_processor::visit(const logical::entities::serialization::type_registrar& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << pmid.value();

        dependencies_builder
            b(inclusion_directives_, enabled_archetype_for_element_);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.serialization.type_registrar_implementation") {
            const auto rh_fn("masd.cpp.serialization.type_registrar_header");
            b.add(v.name(), rh_fn);

            b.add(boost_archive_text_iarchive);
            b.add(boost_archive_text_oarchive);
            b.add(boost_archive_binary_iarchive);
            b.add(boost_archive_binary_oarchive);
            b.add(boost_archive_polymorphic_iarchive);
            b.add(boost_archive_polymorphic_oarchive);

            // XML serialisation
            b.add(boost_archive_xml_iarchive);
            b.add(boost_archive_xml_oarchive);

            const auto ch_fn("masd.cpp.serialization.class_header");
            b.add(v.leaves(), ch_fn);

            const std::string
                carch("masd.cpp.serialization.canonical_archetype");
            b.add(v.registrar_dependencies(), carch);
        }
        build(b, a);
    }
}

void region_processor::
visit(const logical::entities::variability::feature_bundle& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << pmid.value();

        dependencies_builder
            b(inclusion_directives_, enabled_archetype_for_element_);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.feature_bundle_header") {
            b.add(std_list);
            b.add_as_user(
                "dogen.variability/types/entities/feature.hpp");

            if (v.generate_static_configuration()) {
                b.add_as_user(
                    "dogen.variability/types/entities/feature_model.hpp");
                b.add_as_user(
                    "dogen.variability/types/entities/configuration.hpp");

                const auto ch_arch("masd.cpp.types.class_header");
                b.add(v.transparent_associations(), ch_arch);

                const auto fwd_arch(
                    "masd.cpp.types.class_forward_declarations");
                b.add(v.opaque_associations(), fwd_arch);
            }
        } else if (pmid.value() == "masd.cpp.types.feature_bundle_implementation") {
            const auto ch_arch("masd.cpp.types.feature_bundle_header");
            b.add(v.name(), ch_arch);
            b.add_as_user(
                "dogen.variability/types/helpers/value_factory.hpp");

            if (v.generate_static_configuration()) {
                b.add_as_user(
                    "dogen.variability/types/helpers/feature_selector.hpp");
                b.add_as_user(
                    "dogen.variability/types/helpers/configuration_selector.hpp");            }
        }
        build(b, a);
    }
}

void region_processor::
visit(const logical::entities::variability::feature_template_bundle& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << pmid.value();

        dependencies_builder
            b(inclusion_directives_, enabled_archetype_for_element_);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.feature_template_bundle_header") {
            b.add(std_list);
            b.add_as_user(
                "dogen.variability/types/entities/feature_template.hpp");

            if (v.generate_static_configuration()) {
                b.add_as_user(
                    "dogen.variability/types/entities/feature_model.hpp");
                b.add_as_user(
                    "dogen.variability/types/entities/configuration.hpp");
                b.add_as_user(
                    "dogen.variability/types/entities/feature.hpp");

                const auto ch_arch("masd.cpp.types.class_header");
                b.add(v.transparent_associations(), ch_arch);

                const auto fwd_arch(
                    "masd.cpp.types.class_forward_declarations");
                b.add(v.opaque_associations(), fwd_arch);
            }
        } else if (pmid.value() == "masd.cpp.types.feature_template_bundle_implementation") {
            const auto ch_arch(
                "masd.cpp.types.feature_template_bundle_header");
            b.add(v.name(), ch_arch);
            b.add_as_user(
                "dogen.variability/types/helpers/value_factory.hpp");

            if (v.generate_static_configuration()) {
                b.add_as_user(
                    "dogen.variability/types/helpers/feature_selector.hpp");
                b.add_as_user(
                    "dogen.variability/types/helpers/configuration_selector.hpp");
            }
        }
        build(b, a);
    }
}

void region_processor::visit(const logical::entities::variability::initializer& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << pmid.value();

        dependencies_builder
            b(inclusion_directives_, enabled_archetype_for_element_);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.variability_initializer_header") {
            b.add_as_user(
                "dogen.variability/types/entities/feature_template.hpp");
            b.add_as_user(
                "dogen.variability/types/helpers/registrar.hpp");
        } else if (pmid.value() == "masd.cpp.types.variability_initializer_implementation") {
            const auto ch_arch("masd.cpp.types.variability_initializer_header");
            b.add(v.name(), ch_arch);

            const auto
                ftb_arch("masd.cpp.types.feature_template_bundle_header");
            b.add(v.feature_template_bundles(), ftb_arch);

            const auto fb_arch("masd.cpp.types.feature_bundle_header");
            b.add(v.feature_bundles(), fb_arch);
        }
        build(b, a);
    }
}

void region_processor::visit(const logical::entities::structural::object& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << pmid.value();

        dependencies_builder
            b(inclusion_directives_, enabled_archetype_for_element_);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.class_header") {
            // algorithm: domain headers need it for the swap function.
            b.add(std_algorithm);

            const auto io_arch("masd.cpp.io.class_header");
            const bool in_inheritance(v.is_parent() || v.is_child());
            const bool io_enabled(b.is_enabled(v.name(), io_arch));
            const bool requires_io(io_enabled && in_inheritance);

            const auto ios(std_iosfwd);
            if (requires_io)
                b.add(ios);

            const auto ser_fwd_arch(
                "masd.cpp.serialization.class_forward_declarations");
            b.add(v.name(), ser_fwd_arch);

            const identification::entities::physical_meta_id
                carch("masd.cpp.types.canonical_archetype");
            b.add(v.transparent_associations(), carch);

            const auto fwd_arch("masd.cpp.types.class_forward_declarations");
            b.add(v.opaque_associations(), fwd_arch);

            const auto self_arch("masd.cpp.types.class_header");
            b.add(v.parents(), self_arch);

            const auto hash_carch("masd.cpp.hash.canonical_archetype");
            b.add(v.associative_container_keys(), hash_carch);

            if (v.is_visitation_root()) {
                /*
                 * On the header files of the visitation root we only care
                 * about the base visitor; as such we can get away with a
                 * forward declaration. For the visitation leaves, since we
                 * must include the parent we do not need any additional
                 * includes.
                 */
                const auto visitor_fwd_arch(
                    "masd.cpp.types.visitor_forward_declarations");
                b.add(*v.base_visitor(), visitor_fwd_arch);
            }
        } else if (pmid.value() == "masd.cpp.types.class_implementation") {
            const auto ch_arch("masd.cpp.types.class_header");
            b.add(v.name(), ch_arch);
            b.add(v.opaque_associations(), ch_arch);

            const auto io_arch("masd.cpp.io.class_header");
            const bool in_inheritance(v.is_parent() || v.is_child());
            const bool io_enabled(b.is_enabled(v.name(), io_arch));
            const bool requires_io(io_enabled && in_inheritance);

            if (requires_io) {
                const auto os(std_ostream);
                b.add(os);

                const auto io_carch("masd.cpp.io.canonical_archetype");
                b.add(v.transparent_associations(), io_carch);
                b.add(v.opaque_associations(), io_carch);
                b.add(v.parents(), io_carch);

                if (v.is_visitation_leaf()) {
                    /*
                     * Only leaves have a visitation
                     * implementation. Note that we don't bother
                     * including the base if we are already including
                     * the derived visitor.
                     */
                    const auto v_arch("masd.cpp.types.visitor_header");
                    if (v.derived_visitor())
                        b.add(*v.derived_visitor(), v_arch);
                    else
                        b.add(*v.base_visitor(), v_arch);
                }
            }
        } else if (pmid.value() == "masd.cpp.hash.class_header") {
            b.add(std_functional);
            b.add(v.name(), "masd.cpp.types.canonical_archetype");
        } else if (pmid.value() == "masd.cpp.hash.class_implementation") {
            const std::string carch("masd.cpp.hash.canonical_archetype");
            b.add(v.name(), carch);
            b.add(v.transparent_associations(), carch);
            b.add(v.opaque_associations(), carch);
            b.add(v.parents(), carch);
        } else if (pmid.value() == "masd.cpp.io.class_header") {
            b.add(std_iosfwd);
            b.add(v.name(), "masd.cpp.types.class_header");
        } else if (pmid.value() == "masd.cpp.io.class_implementation") {
            const auto ch_fn("masd.cpp.io.class_header");
            b.add(v.name(), ch_fn);
            b.add(v.opaque_associations(), ch_fn);

            const auto io_carch("masd.cpp.io.canonical_archetype");
            const auto self_fn("masd.cpp.io.class_implementation");
            const bool io_enabled(b.is_enabled(v.name(), self_fn));

            if (io_enabled) {
                b.add(std_ostream);
                b.add(v.transparent_associations(), io_carch);
                b.add(v.opaque_associations(), io_carch);
                b.add(v.parents(), io_carch);
            }
        } else if (pmid.value() == "masd.cpp.serialization.class_header") {
            b.add(v.name(), "masd.cpp.types.class_header");
            b.add(boost_serialization_split_free);

            if (v.is_parent())
                b.add(boost_serialization_assume_abstract);

            if (!v.is_parent() && v.is_child())
                b.add(boost_type_traits_is_virtual_base_of);
        } else if (pmid.value() == "masd.cpp.serialization.class_implementation") {
            const auto ch_fn("masd.cpp.serialization.class_header");
            b.add(v.name(), ch_fn);

            b.add(boost_archive_text_iarchive);
            b.add(boost_archive_text_oarchive);
            b.add(boost_archive_binary_iarchive);
            b.add(boost_archive_binary_oarchive);
            b.add(boost_archive_polymorphic_iarchive);
            b.add(boost_archive_polymorphic_oarchive);

            // XML serialisation
            b.add(boost_serialization_nvp);
            b.add(boost_archive_xml_iarchive);
            b.add(boost_archive_xml_oarchive);

            const std::string
                carch("masd.cpp.serialization.canonical_archetype");
            b.add(v.transparent_associations(), carch);
            b.add(v.opaque_associations(), carch);
            b.add(v.parents(), carch);
            b.add(v.leaves(), carch);
        } else if (pmid.value() == "masd.cpp.serialization.class_forward_declarations") {
            const auto tp_fn("masd.cpp.types.class_forward_declarations");
            b.add(v.name(), tp_fn);
        } else if (pmid.value() == "masd.cpp.test_data.class_header") {
            b.add(v.name(), "masd.cpp.types.class_header");
        } else if (pmid.value() == "masd.cpp.test_data.class_implementation") {
            b.add(v.name(), "masd.cpp.test_data.class_header");

            const std::string carch("masd.cpp.test_data.canonical_archetype");
            b.add(v.transparent_associations(), carch);
            b.add(v.opaque_associations(), carch);
            b.add(v.parents(), carch);
            b.add(v.leaves(), carch);
        } else if (pmid.value() == "masd.cpp.odb.class_header") {
            b.add(v.name(), "masd.cpp.types.class_header");
            const std::string carch("masd.cpp.odb.canonical_archetype");
            b.add(v.transparent_associations(), carch);
            b.add(v.opaque_associations(), carch);

            const auto self_fn("masd.cpp.odb.class_header");
            b.add(v.parents(), self_fn);
        } else if (pmid.value() == "masd.cpp.tests.class_implementation") {
            b.add(v.name(), "masd.cpp.types.class_header");
            b.add(v.name(), "masd.cpp.test_data.class_header");

            b.add(std_string);
            b.add(boost_test_unit_test);

            if (v.is_parent())
                b.add(boost_shared_ptr);

            const auto io_arch("masd.cpp.io.class_header");
            const bool io_enabled(b.is_enabled(v.name(), io_arch));
            if (io_enabled) {
                b.add(v.name(), io_arch);
                b.add(std_sstream);
                b.add(boost_property_tree_ptree);
                b.add(boost_property_tree_json_parser);
            }

            const auto ser_arch("masd.cpp.serialization.class_header");
            const bool ser_enabled(b.is_enabled(v.name(), ser_arch));
            if (ser_enabled) {
                b.add(v.name(), ser_arch);

                if (v.type_registrar())
                    b.add(v.type_registrar(),
                        "masd.cpp.serialization.type_registrar_header");

                b.add(boost_archive_text_iarchive);
                b.add(boost_archive_text_oarchive);
                b.add(boost_archive_binary_iarchive);
                b.add(boost_archive_binary_oarchive);
                b.add(boost_archive_polymorphic_iarchive);
                b.add(boost_archive_polymorphic_oarchive);
                b.add(boost_serialization_nvp);
                b.add(boost_archive_xml_iarchive);
                b.add(boost_archive_xml_oarchive);

                if (v.is_parent())
                    b.add(boost_serialization_shared_ptr);
            }

            const auto hash_arch("masd.cpp.hash.class_header");
            const bool hash_enabled(b.is_enabled(v.name(), hash_arch));
            if (hash_enabled)
                b.add(v.name(), hash_arch);
        }
        build(b, a);
    }
}

void region_processor::visit(const logical::entities::structural::exception& /*v*/) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << pmid.value();

        dependencies_builder
            b(inclusion_directives_, enabled_archetype_for_element_);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.exception_header") {
            b.add(std_string);
            b.add(boost_exception_info);
        }
        build(b, a);
    }
}

void region_processor::visit(const logical::entities::structural::enumeration& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << pmid.value();

        dependencies_builder
            b(inclusion_directives_, enabled_archetype_for_element_);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.enum_header") {
            const std::string arch("masd.cpp.types.canonical_archetype");
            b.add(v.underlying_element(), arch);
        } else if (pmid.value() == "masd.cpp.hash.enum_header") {
            b.add(std_functional);
            b.add(v.name(), "masd.cpp.types.enum_header");
        } else if (pmid.value() == "masd.cpp.io.enum_header") {
            b.add(std_iosfwd);
            const auto eh_fn("masd.cpp.types.enum_header");
            b.add(v.name(), eh_fn);
        } else if (pmid.value() == "masd.cpp.io.enum_implementation") {
            b.add(std_ostream);
            b.add(std_stdexcept);
            b.add(std_string);

            const auto eh_fn("masd.cpp.io.enum_header");
            b.add(v.name(), eh_fn);
        } else if (pmid.value() == "masd.cpp.serialization.enum_header") {
            b.add(v.name(), "masd.cpp.types.enum_header");
            b.add(boost_serialization_nvp);
        } else if (pmid.value() == "masd.cpp.test_data.enum_header") {
            b.add(v.name(), "masd.cpp.types.enum_header");
        } else if (pmid.value() == "masd.cpp.test_data.enum_implementation") {
            b.add(v.name(),"masd.cpp.test_data.enum_header");
        } else if (pmid.value() == "masd.cpp.odb.enum_header") {
            b.add(v.name(), "masd.cpp.types.enum_header");
        } else if (pmid.value() == "masd.cpp.lexical_cast.enum_header") {
            const auto eh_fn("masd.cpp.types.enum_header");
            b.add(v.name(), eh_fn);
            b.add(boost_lexical_cast);
        } else if (pmid.value() == "masd.cpp.tests.enum_implementation") {
            b.add(v.name(), "masd.cpp.types.enum_header");
            b.add(v.name(), "masd.cpp.test_data.enum_header");

            b.add(std_string);
            b.add(boost_test_unit_test);
            b.add(boost_predef);

            const auto io_arch("masd.cpp.io.enum_header");
            const bool io_enabled(b.is_enabled(v.name(), io_arch));
            if (io_enabled) {
                b.add(v.name(), io_arch);
                b.add(std_sstream);
                b.add(boost_property_tree_ptree);
                b.add(boost_property_tree_json_parser);
            }

            const auto lc_arch("masd.cpp.lexical_cast.enum_header");
            const bool lc_enabled(b.is_enabled(v.name(), lc_arch));
            if (lc_enabled) {
                b.add(v.name(), lc_arch);
                b.add(boost_lexical_cast);
            }

            const auto ser_arch("masd.cpp.serialization.enum_header");
            const bool ser_enabled(b.is_enabled(v.name(), ser_arch));
            if (ser_enabled) {
                b.add(v.name(), ser_arch);

                b.add(boost_archive_text_iarchive);
                b.add(boost_archive_text_oarchive);
                b.add(boost_archive_binary_iarchive);
                b.add(boost_archive_binary_oarchive);
                b.add(boost_archive_polymorphic_iarchive);
                b.add(boost_archive_polymorphic_oarchive);
                b.add(boost_serialization_nvp);
                b.add(boost_archive_xml_iarchive);
                b.add(boost_archive_xml_oarchive);
            }

            const auto hash_arch("masd.cpp.hash.enum_header");
            const bool hash_enabled(b.is_enabled(v.name(), hash_arch));
            if (hash_enabled)
                b.add(v.name(), hash_arch);
        }
        build(b, a);
    }
}

void region_processor::visit(const logical::entities::structural::primitive& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << pmid.value();

        dependencies_builder
            b(inclusion_directives_, enabled_archetype_for_element_);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.primitive_header") {
            // algorithm: domain headers need it for the swap function.
            b.add(std_algorithm);

            const auto ser_fwd_arch(
                "masd.cpp.serialization.primitive_forward_declarations");
            b.add(v.name(), ser_fwd_arch);

            const std::string carch("masd.cpp.types.canonical_archetype");
            b.add(v.value_attribute().parsed_type().current(), carch);
        } else if (pmid.value() == "masd.cpp.types.primitive_implementation") {
            const auto ch_arch("masd.cpp.types.primitive_header");
            b.add(v.name(), ch_arch);
        } else if (pmid.value() == "masd.cpp.hash.primitive_header") {
            b.add(std_functional);
            b.add(v.name(), "masd.cpp.types.canonical_archetype");
        } else if (pmid.value() == "masd.cpp.hash.primitive_implementation") {
            const std::string carch("masd.cpp.hash.canonical_archetype");
            b.add(v.name(), carch);
        } else if (pmid.value() == "masd.cpp.io.primitive_header") {
            b.add(std_iosfwd);
            b.add(v.name(), "masd.cpp.types.canonical_archetype");
        } else if (pmid.value() == "masd.cpp.io.primitive_implementation") {
            const auto ph_fn("masd.cpp.io.primitive_header");
            b.add(v.name(), ph_fn);

            const auto io_carch("masd.cpp.io.canonical_archetype");
            const auto self_fn("masd.cpp.io.primitive_implementation");
            const bool io_enabled(b.is_enabled(v.name(), self_fn));

            if (io_enabled) {
                b.add(std_ostream);
                const auto& va(v.value_attribute());
                b.add(va.parsed_type().current(), io_carch);
            }
        } else if (pmid.value() == "masd.cpp.serialization.primitive_header") {
            b.add(v.name(), "masd.cpp.types.primitive_header");
            b.add(boost_serialization_split_free);

        } else if (pmid.value() == "masd.cpp.serialization.primitive_implementation") {
            const auto ph_fn("masd.cpp.serialization.primitive_header");
            b.add(v.name(), ph_fn);

            b.add(boost_archive_text_iarchive);
            b.add(boost_archive_text_oarchive);
            b.add(boost_archive_binary_iarchive);
            b.add(boost_archive_binary_oarchive);
            b.add(boost_archive_polymorphic_iarchive);
            b.add(boost_archive_polymorphic_oarchive);

            // XML serialisation
            b.add(boost_serialization_nvp);
            b.add(boost_archive_xml_iarchive);
            b.add(boost_archive_xml_oarchive);

            const std::string
                carch("masd.cpp.serialization.canonical_archetype");
            b.add(v.value_attribute().parsed_type().current(), carch);
        } else if (pmid.value() == "masd.cpp.serialization.primitive_forward_declarations") {
            const auto tp_fn("masd.cpp.types.primitive_forward_declarations");
            b.add(v.name(), tp_fn);
        } else if (pmid.value() == "masd.cpp.test_data.primitive_header") {
            b.add(v.name(), "masd.cpp.types.primitive_header");
        } else if (pmid.value() == "masd.cpp.test_data.primitive_implementation") {
            b.add(v.name(), "masd.cpp.test_data.primitive_header");
            const std::string carch("masd.cpp.test_data.canonical_archetype");
            b.add(v.value_attribute().parsed_type().current(), carch);
        } else if (pmid.value() == "masd.cpp.odb.primitive_header") {
            b.add(v.name(), "masd.cpp.types.primitive_header");
        }
        build(b, a);
    }
}

void region_processor::visit(const logical::entities::structural::visitor& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << pmid.value();

        dependencies_builder
            b(inclusion_directives_, enabled_archetype_for_element_);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.visitor_header") {
            const auto fwd_arch("masd.cpp.types.class_forward_declarations");
            b.add(v.visits(), fwd_arch);

            if (v.parent())
                b.add(*v.parent(), "masd.cpp.types.visitor_header");
        }
        build(b, a);
    }
}

void region_processor::
visit(const logical::entities::structural::entry_point& /*v*/) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << pmid.value();

        auto& a(*pair.second);
        dependencies_builder
            b(inclusion_directives_, enabled_archetype_for_element_);

        if (pmid.value() == "masd.cpp.tests.main") {
            b.add(boost_test_unit_test);
            b.add(boost_test_unit_test_monitor);
            b.add(boost_exception_info);
            b.add(std_iostream);
            b.add(boost_exception_diagnostic_information);
        }
        build(b, a);
    }
}

std::unordered_map<logical_meta_physical_id, inclusion_directives>
legacy_dependencies_transform::
get_inclusion_directives(const physical::entities::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Gathering inclusion directives.";

    std::unordered_map<logical_meta_physical_id, inclusion_directives> r;

    for (const auto& region_pair : m.regions_by_logical_id()) {
        const auto& region(region_pair.second);
        const auto& ln(region.provenance().logical_name());
        BOOST_LOG_SEV(lg, trace) << "Processing element: "
                                 << ln.id().value();

        for (const auto& artefact_pair  : region.artefacts_by_archetype()) {
            const auto& a(*artefact_pair.second);
            BOOST_LOG_SEV(lg, trace) << "Processing archetype: "
                                     << a.meta_name().id().value();

            /*
             * Skip any artefact without a primary directive.
             */
            const auto& directives(a.path_properties().inclusion_directives());
            if (directives.primary().empty()) {
                BOOST_LOG_SEV(lg, trace) << "Empty primary directive.";
                continue;
            }

            const auto pair(std::make_pair(a.id(), directives));
            const bool inserted(r.insert(pair).second);
            if (!inserted) {
                std::ostringstream os;
                os << duplicate_id
                   << a.id().logical_id().value() << "-"
                   << a.id().physical_meta_id().value();
                const auto msg(os.str());
                BOOST_LOG_SEV(lg, error) << msg;
                BOOST_THROW_EXCEPTION(transform_exception(msg));
            }

            const auto rs(a.relations().status());
            using physical::entities::relation_status;
            if (rs == relation_status::facet_default) {
                using identification::helpers::physical_meta_id_builder;
                physical_meta_id_builder b;
                const auto& l(a.meta_name().location());

                logical_meta_physical_id lmpid;
                lmpid.logical_id(a.id().logical_id());
                lmpid.physical_meta_id(b.build_facet(l, true/*add_canonical*/));

                const auto pair(std::make_pair(lmpid, directives));
                const bool inserted(r.insert(pair).second);
                if (!inserted) {
                    std::ostringstream os;
                    os << duplicate_id
                       << a.id().logical_id().value() << "-"
                       << a.id().physical_meta_id().value();
                    const auto msg(os.str());
                    BOOST_LOG_SEV(lg, error) << msg;
                    BOOST_THROW_EXCEPTION(transform_exception(msg));
                }
            }
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    return r;
}

void legacy_dependencies_transform::apply(const text::transforms::context& ctx,
    text::entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "legacy dependencies",
        transform_id, m.logical().name().id().value(), *ctx.tracer(), m);

    const auto ids(get_inclusion_directives(m.physical()));
    const auto& mmp(m.physical().meta_model_properties());
    const auto& eafe(mmp.enabled_archetype_for_element());
    for (auto& region : m.logical_physical_regions()) {
        const auto& e(*region.logical_element());
        BOOST_LOG_SEV(lg, debug) << "Processing element: "
                                 << e.name().id().value();

        using logical::entities::generability_status;
        if (e.generability_status() == generability_status::generatable) {
            region_processor rp(ids, eafe, region);
            e.accept(rp);
        } else
            BOOST_LOG_SEV(lg, debug) << "Element is not generatable.";
    }

    stp.end_transform(m);
}

}

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
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.logical/types/entities/element.hpp"

#include "dogen.logical/types/entities/variability/feature_bundle.hpp"
#include "dogen.logical/types/entities/variability/feature_template_bundle.hpp"
#include "dogen.logical/types/entities/variability/initializer.hpp"

#include "dogen.logical/types/entities/physical/archetype.hpp"
#include "dogen.logical/types/entities/physical/facet.hpp"
#include "dogen.logical/types/entities/physical/backend.hpp"
#include "dogen.logical/types/entities/physical/part.hpp"
#include "dogen.logical/types/entities/physical/archetype_kind.hpp"

#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/structural/visitor.hpp"

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

const std::string duplicate_id("Duplicate logical-physical ID: ");

/*

masd.cpp.build.include_cmakelists
masd.cpp.build.source_cmakelists
masd.cpp.io.builtin_header
masd.cpp.io.class_header
masd.cpp.io.class_implementation
masd.cpp.io.enum_header
masd.cpp.io.enum_implementation
masd.cpp.io.primitive_header
masd.cpp.io.primitive_implementation
masd.cpp.lexical_cast.enum_header
masd.cpp.odb.builtin_header
masd.cpp.odb.class_header
masd.cpp.odb.common_odb_options
masd.cpp.odb.enum_header
masd.cpp.odb.object_odb_options
masd.cpp.odb.primitive_header
masd.cpp.odb.primitive_odb_options
masd.cpp.serialization.builtin_header
masd.cpp.serialization.class_forward_declarations
masd.cpp.serialization.class_header
masd.cpp.serialization.class_implementation
masd.cpp.serialization.enum_header
masd.cpp.serialization.primitive_forward_declarations
masd.cpp.serialization.primitive_header
masd.cpp.serialization.primitive_implementation
masd.cpp.serialization.type_registrar_header
masd.cpp.serialization.type_registrar_implementation
masd.cpp.templates.logic_less_template
masd.cpp.test_data.builtin_header
masd.cpp.test_data.class_header
masd.cpp.test_data.class_implementation
masd.cpp.test_data.enum_header
masd.cpp.test_data.enum_implementation
masd.cpp.test_data.primitive_header
masd.cpp.test_data.primitive_implementation
masd.cpp.tests.class_implementation masd.cpp.tests.cmakelists
masd.cpp.tests.enum_implementation masd.cpp.tests.main
masd.cpp.visual_studio.msbuild_targets
masd.cpp.visual_studio.project masd.cpp.visual_studio.solution
masd.csharp.io.assistant masd.csharp.io.class masd.csharp.io.enum
masd.csharp.io.primitive masd.csharp.test_data.assistant
masd.csharp.test_data.class masd.csharp.test_data.enum
masd.csharp.test_data.primitive
masd.csharp.types.builtin
masd.csharp.types.class
masd.csharp.types.enum
masd.csharp.types.exception
masd.csharp.types.primitive
masd.csharp.visual_studio.project masd.csharp.visual_studio.solution

*/

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
    "<boost/property_tree/json_parser.hpp");
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
    "<boost/archive/binary_iarchive.hpp");
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

}

namespace dogen::orchestration::transforms {

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
        builder_(ids, enabled_archetype_for_element),
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

public:
    using logical::entities::element_visitor::visit;
    void visit(const logical::entities::physical::archetype& v);
    void visit(const logical::entities::physical::facet& v);
    void visit(const logical::entities::physical::backend& v);
    void visit(const logical::entities::physical::part& v);
    void visit(const logical::entities::physical::archetype_kind& v);

    void visit(const logical::entities::variability::feature_bundle& v);
    void visit(const logical::entities::variability::feature_template_bundle& v);
    void visit(const logical::entities::variability::initializer& v);

    void visit(const logical::entities::structural::object& v);
    void visit(const logical::entities::structural::module& v);
    void visit(const logical::entities::structural::object_template& v);
    void visit(const logical::entities::structural::builtin& v);
    void visit(const logical::entities::structural::enumeration& v);
    void visit(const logical::entities::structural::primitive& v);
    void visit(const logical::entities::structural::exception& v);
    void visit(const logical::entities::structural::visitor& v);

private:
    helpers::dependencies_builder builder_;
    logical_physical_region& region_;
};

void region_processor::
visit(const logical::entities::physical::archetype& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.archetype_class_header_transform") {
            const auto ts(a.technical_space());
            if (ts == technical_space::cpp) {
                builder_.add_as_user(
                    "dogen.text.cpp/types/transforms/model_to_text_transform.hpp");
            } else if (ts == technical_space::csharp) {
                builder_.add_as_user(
                    "dogen.text.csharp/types/transforms/model_to_text_transform.hpp");
            }
        } else if (pmid.value() == "masd.cpp.types.archetype_class_implementation_transform") {
            // no deps
        } else if (pmid.value() == "masd.cpp.types.archetype_class_implementation_factory") {
            builder_.add(v.name(),
                "masd.cpp.types.archetype_class_header_factory");
            builder_.add_as_user(
                "dogen.identification/types/helpers/physical_meta_name_factory.hpp");
        } else if (pmid.value() == "masd.cpp.types.archetype_class_header_factory") {
            builder_.add_as_user("dogen.physical/types/entities/archetype.hpp");
        }
        a.path_properties().inclusion_dependencies(builder_.build());
    }
}

void region_processor::
visit(const logical::entities::physical::facet& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.facet_class_header_transform") {
            builder_.add_as_user("dogen.physical/types/entities/facet.hpp");
            using identification::entities::technical_space;
            if (v.major_technical_space() == technical_space::cpp) {
                builder_.add_as_user(
                    "dogen.text.cpp/types/transforms/registrar.hpp");
            } else if (v.major_technical_space() == technical_space::csharp) {
                builder_.add_as_user(
                    "dogen.text.csharp/types/transforms/registrar.hpp");
            }
        } else if (pmid.value() == "masd.cpp.types.facet_class_implementation_transform") {
            const auto ch_arch("masd.cpp.types.canonical_archetype");
            builder_.add(v.name(), ch_arch);
            builder_.add(v.archetypes(), ch_arch);
            builder_.add_as_user(
                "dogen.identification/io/entities/physical_meta_id_io.hpp");
            builder_.add_as_user(
                "dogen.identification/types/helpers/physical_meta_name_builder.hpp");
            builder_.add_as_user("dogen.utility/types/log/logger.hpp");
            builder_.add_as_user(
                "dogen.text/types/transforms/transformation_error.hpp");
        } else if (pmid.value() == "masd.cpp.types.facet_class_header_factory") {
            builder_.add_as_user("dogen.physical/types/entities/facet.hpp");
        } else if (pmid.value() == "masd.cpp.types.facet_class_implementation_factory") {
            builder_.add_as_user("dogen.physical/types/entities/facet.hpp");

            const auto fct_ch_arch("masd.cpp.types.facet_class_header_factory");
            builder_.add(v.name(), fct_ch_arch);

            const auto ch_arch("masd.cpp.types.archetype_class_header_transform");
            builder_.add(v.archetypes(), ch_arch);
            builder_.add_as_user(
                "dogen.utility/types/log/logger.hpp");
            builder_.add_as_user(
                "dogen.text/types/transforms/transformation_error.hpp");
            builder_.add_as_user(
                "dogen.identification/io/entities/physical_meta_id_io.hpp");
            builder_.add_as_user(
                "dogen.identification/types/helpers/physical_meta_name_builder.hpp");
        }

        a.path_properties().inclusion_dependencies(builder_.build());
    }
}

void region_processor::visit(const logical::entities::physical::backend& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.backend_class_header_transform") {
            builder_.add_as_user("dogen.physical/types/entities/backend.hpp");
            using identification::entities::technical_space;
            if (v.major_technical_space() == technical_space::cpp) {
                builder_.add_as_user(
                    "dogen.text.cpp/types/transforms/registrar.hpp");
            } else if (v.major_technical_space() == technical_space::csharp) {
                builder_.add_as_user(
                    "dogen.text.csharp/types/transforms/registrar.hpp");
            }
        } else if (pmid.value() == "masd.cpp.types.backend_class_implementation_transform") {
            const auto ch_arch("masd.cpp.types.canonical_archetype");
            builder_.add(v.name(), ch_arch);
            builder_.add(v.facets(), ch_arch);
            builder_.add_as_user(
                "dogen.identification/io/entities/physical_meta_id_io.hpp");
            builder_.add_as_user(
                "dogen.identification/types/helpers/physical_meta_name_builder.hpp");
            builder_.add_as_user("dogen.utility/types/log/logger.hpp");
            builder_.add_as_user(
                "dogen.text/types/transforms/transformation_error.hpp");
        } else if (pmid.value() == "masd.cpp.types.backend_class_header_factory") {
            builder_.add_as_user("dogen.physical/types/entities/backend.hpp");
        } else if (pmid.value() == "masd.cpp.types.backend_class_implementation_factory") {
            const auto be_ch_arch("masd.cpp.types.backend_class_header_factory");
            builder_.add(v.name(), be_ch_arch);

            const auto fct_ch_arch("masd.cpp.types.facet_class_header_factory");
            builder_.add(v.facets(), fct_ch_arch);

            const auto ak_ch_arch("masd.cpp.types.archetype_kind_class_header_factory");
            builder_.add(v.archetype_kinds(), ak_ch_arch);

            const auto part_ch_arch("masd.cpp.types.part_class_header_factory");
            builder_.add(v.parts(), part_ch_arch);
            builder_.add_as_user(
                "dogen.identification/io/entities/physical_meta_id_io.hpp");
            builder_.add_as_user(
                "dogen.identification/types/helpers/physical_meta_name_builder.hpp");
            builder_.add_as_user(
                "dogen.utility/types/log/logger.hpp");
            builder_.add_as_user(
                "dogen.text/types/transforms/transformation_error.hpp");
        }


        a.path_properties().inclusion_dependencies(builder_.build());
    }
}

void region_processor::visit(const logical::entities::physical::part& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.part_class_header_factory") {
            builder_.add_as_user("dogen.physical/types/entities/part.hpp");
        } else if (pmid.value() == "masd.cpp.types.part_class_implementation_factory") {
            const auto part_ch_arch("masd.cpp.types.part_class_header_factory");
            builder_.add(v.name(), part_ch_arch);

            builder_.add_as_user(
                "dogen.identification/io/entities/physical_meta_id_io.hpp");
            builder_.add_as_user(
                "dogen.identification/types/helpers/physical_meta_name_builder.hpp");
            builder_.add_as_user(
                "dogen.utility/types/log/logger.hpp");
            builder_.add_as_user(
                "dogen.text/types/transforms/transformation_error.hpp");
        }
        a.path_properties().inclusion_dependencies(builder_.build());
    }
}

void region_processor::visit(const logical::entities::physical::archetype_kind& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.archetype_kind_class_header_factory") {
            builder_.add_as_user(
                "dogen.physical/types/entities/archetype_kind.hpp");

        } else if (pmid.value() == "masd.cpp.types.archetype_kind_class_implementation_factory") {
            const auto ak_ch_arch(
                "masd.cpp.types.archetype_kind_class_header_factory");
            builder_.add(v.name(), ak_ch_arch);
            builder_.add_as_user(
                "dogen.identification/io/entities/physical_meta_id_io.hpp");
            builder_.add_as_user("dogen.utility/types/log/logger.hpp");
            builder_.add_as_user(
                "dogen.text/types/transforms/transformation_error.hpp");
        }
        a.path_properties().inclusion_dependencies(builder_.build());
    }
}

void region_processor::
visit(const logical::entities::variability::feature_bundle& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.feature_bundle_header") {
            builder_.add(std_list);
            builder_.add_as_user(
                "dogen.variability/types/entities/feature.hpp");

            if (v.generate_static_configuration()) {
                builder_.add_as_user(
                    "dogen.variability/types/entities/feature_model.hpp");
                builder_.add_as_user(
                    "dogen.variability/types/entities/configuration.hpp");

                const auto ch_arch("masd.cpp.types.class_header");
                builder_.add(v.transparent_associations(), ch_arch);

                const auto fwd_arch(
                    "masd.cpp.types.class_forward_declarations");
                builder_.add(v.opaque_associations(), fwd_arch);
            }
        } else if (pmid.value() == "masd.cpp.types.feature_bundle_implementation") {
            const auto ch_arch("masd.cpp.types.feature_bundle_header");
            builder_.add(v.name(), ch_arch);
            builder_.add_as_user(
                "dogen.variability/types/helpers/value_factory.hpp");

            if (v.generate_static_configuration()) {
                builder_.add_as_user(
                    "dogen.variability/types/helpers/feature_selector.hpp");
                builder_.add_as_user(
                    "dogen.variability/types/helpers/configuration_selector.hpp");            }
        }
        a.path_properties().inclusion_dependencies(builder_.build());
    }
}

void region_processor::
visit(const logical::entities::variability::feature_template_bundle& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.feature_template_bundle_header") {
            builder_.add(std_list);
            builder_.add_as_user(
                "dogen.variability/types/entities/feature_template.hpp");

            if (v.generate_static_configuration()) {
                builder_.add_as_user(
                    "dogen.variability/types/entities/feature_model.hpp");
                builder_.add_as_user(
                    "dogen.variability/types/entities/configuration.hpp");
                builder_.add_as_user(
                    "dogen.variability/types/entities/feature.hpp");

                const auto ch_arch("masd.cpp.types.class_header");
                builder_.add(v.transparent_associations(), ch_arch);

                const auto fwd_arch(
                    "masd.cpp.types.class_forward_declarations");
                builder_.add(v.opaque_associations(), fwd_arch);
            }
        } else if (pmid.value() == "masd.cpp.types.feature_template_bundle_implementation") {
            const auto ch_arch(
                "masd.cpp.types.feature_template_bundle_header");
            builder_.add(v.name(), ch_arch);
            builder_.add_as_user(
                "dogen.variability/types/helpers/value_factory.hpp");

            if (v.generate_static_configuration()) {
                builder_.add_as_user(
                    "dogen.variability/types/helpers/feature_selector.hpp");
                builder_.add_as_user(
                    "dogen.variability/types/helpers/configuration_selector.hpp");
            }
        }
        a.path_properties().inclusion_dependencies(builder_.build());
    }
}

void region_processor::visit(const logical::entities::variability::initializer& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.variability_initializer_header") {
            builder_.add_as_user(
                "dogen.variability/types/entities/feature_template.hpp");
            builder_.add_as_user(
                "dogen.variability/types/helpers/registrar.hpp");
        } else if (pmid.value() == "masd.cpp.types.variability_initializer_implementation") {
            const auto ch_arch("masd.cpp.types.variability_initializer_header");
            builder_.add(v.name(), ch_arch);

            const auto
                ftb_arch("masd.cpp.types.feature_template_bundle_header");
            builder_.add(v.feature_template_bundles(), ftb_arch);

            const auto fb_arch("masd.cpp.types.feature_template_bundle_header");
            builder_.add(v.feature_bundles(), fb_arch);
        }
        a.path_properties().inclusion_dependencies(builder_.build());
    }
}

void region_processor::visit(const logical::entities::structural::object& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.class_header") {
            // algorithm: domain headers need it for the swap function.
            builder_.add(std_algorithm);

            const auto io_arch("masd.cpp.io.class_header");
            const bool in_inheritance(v.is_parent() || v.is_child());
            const bool io_enabled(builder_.is_enabled(v.name(), io_arch));
            const bool requires_io(io_enabled && in_inheritance);

            const auto ios(std_iosfwd);
            if (requires_io)
                builder_.add(ios);

            const auto ser_fwd_arch(
                "masd.cpp.serialization.class_forward_declarations");
            builder_.add(v.name(), ser_fwd_arch);

            const identification::entities::physical_meta_id
                carch("masd.cpp.types.canonical_archetype");
            builder_.add(v.transparent_associations(), carch);

            const auto fwd_arch("masd.cpp.types.class_forward_declarations");
            builder_.add(v.opaque_associations(), fwd_arch);

            const auto self_arch("masd.cpp.types.class_header");
            builder_.add(v.parents(), self_arch);

            const auto hash_carch("masd.cpp.hash.canonical_archetype");
            builder_.add(v.associative_container_keys(), hash_carch);

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
                builder_.add(*v.base_visitor(), visitor_fwd_arch);
            }
        } else if (pmid.value() == "masd.cpp.types.class_implementation") {
            const auto ch_arch("masd.cpp.types.class_header");
            builder_.add(v.name(), ch_arch);
            builder_.add(v.opaque_associations(), ch_arch);

            const auto io_arch("masd.cpp.io.class_header");
            const bool in_inheritance(v.is_parent() || v.is_child());
            const bool io_enabled(builder_.is_enabled(v.name(), io_arch));
            const bool requires_io(io_enabled && in_inheritance);

            if (requires_io) {
                const auto os(std_ostream);
                builder_.add(os);

                const auto io_carch("masd.cpp.io.canonical_archetype");
                builder_.add(v.transparent_associations(), io_carch);
                builder_.add(v.opaque_associations(), io_carch);
                builder_.add(v.parents(), io_carch);

                if (v.is_visitation_leaf()) {
                    /*
                     * Only leaves have a visitation
                     * implementation. Note that we don't bother
                     * including the base if we are already including
                     * the derived visitor.
                     */
                    const auto v_arch("masd.cpp.types.visitor_header");
                    if (v.derived_visitor())
                        builder_.add(*v.derived_visitor(), v_arch);
                    else
                        builder_.add(*v.base_visitor(), v_arch);
                }
            }
        } else if (pmid.value() == "masd.cpp.hash.class_header") {
            builder_.add(std_functional);
            builder_.add(v.name(), "masd.cpp.types.canonical_archetype");
        } else if (pmid.value() == "masd.cpp.hash.class_implementation") {
            const std::string carch("masd.cpp.io.canonical_archetype");
            builder_.add(v.name(), carch);
            builder_.add(v.transparent_associations(), carch);
            builder_.add(v.opaque_associations(), carch);
            builder_.add(v.parents(), carch);
        }
        a.path_properties().inclusion_dependencies(builder_.build());
    }
}

void region_processor::visit(const logical::entities::structural::exception& /*v*/) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.exception_header") {
            builder_.add(std_string);
            builder_.add(boost_exception_info);
        }

        a.path_properties().inclusion_dependencies(builder_.build());
    }
}

void region_processor::visit(const logical::entities::structural::module& /*v*/) {

}

void region_processor::visit(const logical::entities::structural::object_template& /*v*/) {

}

void region_processor::visit(const logical::entities::structural::builtin& /*v*/) {

}

void region_processor::visit(const logical::entities::structural::enumeration& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.enum_header") {
            const std::string arch("masd.cpp.types.canonical_archetype");
            builder_.add(v.underlying_element(), arch);
        } else if (pmid.value() == "masd.cpp.hash.enum_header") {
            builder_.add(std_functional);
            builder_.add(v.name(), "masd.cpp.types.enum_header");
        }

        a.path_properties().inclusion_dependencies(builder_.build());
    }
}

void region_processor::visit(const logical::entities::structural::primitive& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.primitive_header") {
            // algorithm: domain headers need it for the swap function.
            builder_.add(std_algorithm);

            const auto ser_fwd_arch(
                "masd.cpp.serialization.primitive_forward_declarations");
            builder_.add(v.name(), ser_fwd_arch);

            const std::string carch("masd.cpp.types.canonical_archetype");
            builder_.add(v.value_attribute().parsed_type().current(), carch);
        } else if (pmid.value() == "masd.cpp.types.primitive_implementation") {
            const auto ch_arch("masd.cpp.types.primitive_header");
            builder_.add(v.name(), ch_arch);
        } else if (pmid.value() == "masd.cpp.hash.primitive_header") {
            builder_.add(std_functional);
            builder_.add(v.name(), "masd.cpp.types.canonical_archetype");
        } else if (pmid.value() == "masd.cpp.hash.primitive_implementation") {
            const std::string carch("masd.cpp.types.canonical_archetype");
            builder_.add(v.name(), carch);
        }


        a.path_properties().inclusion_dependencies(builder_.build());
    }

}

void region_processor::visit(const logical::entities::structural::visitor& v) {
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.visitor_header") {
            const auto fwd_arch("masd.cpp.types.class_forward_declarations");
            builder_.add(v.visits(), fwd_arch);

            if (v.parent())
                builder_.add(*v.parent(), "masd.cpp.types.visitor_header");
        }
        a.path_properties().inclusion_dependencies(builder_.build());
    }
}

std::unordered_map<logical_meta_physical_id, inclusion_directives>
legacy_dependencies_transform::
get_inclusion_directives(const physical::entities::model& m) {
    std::unordered_map<logical_meta_physical_id, inclusion_directives> r;

    for (const auto& region_pair : m.regions_by_logical_id()) {
        const auto& region(region_pair.second);
        for (const auto& artefact_pair  : region.artefacts_by_archetype()) {
            const auto& a(*artefact_pair.second);

            const auto& directives(a.path_properties().inclusion_directives());
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
        }
    }
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
        auto& e(*region.logical_element());
        region_processor rp(ids, eafe, region);
        e.accept(rp);
    }

    stp.end_transform(m);
}

}

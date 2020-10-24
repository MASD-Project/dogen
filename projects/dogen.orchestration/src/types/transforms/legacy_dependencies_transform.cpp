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
#include <sstream>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/physical/archetype.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
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
masd.cpp.build.include_cmakelists,
masd.cpp.build.source_cmakelists, masd.cpp.hash.builtin_header,
masd.cpp.hash.class_header, masd.cpp.hash.class_implementation,
masd.cpp.hash.enum_header, masd.cpp.hash.primitive_header,
masd.cpp.hash.primitive_implementation, masd.cpp.io.builtin_header,
masd.cpp.io.class_header, masd.cpp.io.class_implementation,
masd.cpp.io.enum_header, masd.cpp.io.enum_implementation,
masd.cpp.io.primitive_header, masd.cpp.io.primitive_implementation,
masd.cpp.lexical_cast.enum_header, masd.cpp.odb.builtin_header,
masd.cpp.odb.class_header, masd.cpp.odb.common_odb_options,
masd.cpp.odb.enum_header, masd.cpp.odb.object_odb_options,
masd.cpp.odb.primitive_header, masd.cpp.odb.primitive_odb_options,
masd.cpp.serialization.builtin_header,
masd.cpp.serialization.class_forward_declarations,
masd.cpp.serialization.class_header,
masd.cpp.serialization.class_implementation,
masd.cpp.serialization.enum_header,
masd.cpp.serialization.primitive_forward_declarations,
masd.cpp.serialization.primitive_header,
masd.cpp.serialization.primitive_implementation,
masd.cpp.serialization.type_registrar_header,
masd.cpp.serialization.type_registrar_implementation,
masd.cpp.templates.logic_less_template,
masd.cpp.test_data.builtin_header, masd.cpp.test_data.class_header,
masd.cpp.test_data.class_implementation, masd.cpp.test_data.enum_header,
masd.cpp.test_data.enum_implementation,
masd.cpp.test_data.primitive_header,
masd.cpp.test_data.primitive_implementation,
masd.cpp.tests.class_implementation, masd.cpp.tests.cmakelists,
masd.cpp.tests.enum_implementation, masd.cpp.tests.main,
masd.cpp.types.archetype_class_header_factory,

masd.cpp.types.archetype_class_implementation_factory,
masd.cpp.types.archetype_class_implementation_transform,
masd.cpp.types.archetype_kind_class_header_factory,
masd.cpp.types.archetype_kind_class_implementation_factory,
masd.cpp.types.backend_class_header_factory,
masd.cpp.types.backend_class_header_transform,
masd.cpp.types.backend_class_implementation_factory,
masd.cpp.types.backend_class_implementation_transform,
masd.cpp.types.builtin_header,
masd.cpp.types.class_forward_declarations, masd.cpp.types.class_header,
masd.cpp.types.class_implementation, masd.cpp.types.enum_header,
masd.cpp.types.exception_header,
masd.cpp.types.facet_class_header_factory,
masd.cpp.types.facet_class_header_transform,
masd.cpp.types.facet_class_implementation_factory,
masd.cpp.types.facet_class_implementation_transform,
masd.cpp.types.feature_bundle_header,
masd.cpp.types.feature_bundle_implementation,
masd.cpp.types.feature_template_bundle_header,
masd.cpp.types.feature_template_bundle_implementation,
masd.cpp.types.main, masd.cpp.types.namespace_header,
masd.cpp.types.part_class_header_factory,
masd.cpp.types.part_class_header_transform,
masd.cpp.types.part_class_implementation_factory,
masd.cpp.types.part_class_implementation_transform,
masd.cpp.types.primitive_forward_declarations,
masd.cpp.types.primitive_header,
masd.cpp.types.primitive_implementation,
masd.cpp.types.variability_initializer_header,
masd.cpp.types.variability_initializer_implementation,
masd.cpp.types.visitor_forward_declarations,
masd.cpp.types.visitor_header, masd.cpp.visual_studio.msbuild_targets,
masd.cpp.visual_studio.project, masd.cpp.visual_studio.solution,
masd.csharp.io.assistant, masd.csharp.io.class, masd.csharp.io.enum,
masd.csharp.io.primitive, masd.csharp.test_data.assistant,
masd.csharp.test_data.class, masd.csharp.test_data.enum,
masd.csharp.test_data.primitive, masd.csharp.types.builtin,
masd.csharp.types.class, masd.csharp.types.enum,
masd.csharp.types.exception, masd.csharp.types.primitive,
masd.csharp.visual_studio.project, masd.csharp.visual_studio.solution

*/

}

namespace dogen::orchestration::transforms {

// using identification::entities::technical_space;
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

    void visit(const logical::entities::structural::object& v);
    void visit(const logical::entities::structural::module& v);
    void visit(const logical::entities::structural::object_template& v);
    void visit(const logical::entities::structural::builtin& v);
    void visit(const logical::entities::structural::enumeration& v);
    void visit(const logical::entities::structural::primitive& v);
    void visit(const logical::entities::structural::exception& v);
    void visit(const logical::entities::structural::visitor& v);

private:
    const helpers::dependencies_builder builder_;
    logical_physical_region& region_;
};

void region_processor::
visit(const logical::entities::physical::archetype& /*v*/) {
    /*
    auto& pr(region_.physical_region());
    for (auto& pair : pr.artefacts_by_archetype()) {
        const auto& pmid(pair.first);
        auto& a(*pair.second);
        if (pmid.value() == "masd.cpp.types.archetype_class_header_transform") {

            if (a.major_technical_space() == technical_space::cpp) {
                builder_.add_as_user(
                    "dogen.text.cpp/types/transforms/model_to_text_transform.hpp");
            } else if (arch.major_technical_space() == technical_space::csharp) {
                builder.add_as_user(
                    "dogen.text.csharp/types/transforms/model_to_text_transform.hpp");
            }

            return builder.build();


        }
    }
    */
}

void region_processor::visit(const logical::entities::structural::object& /*v*/) {
}

void region_processor::visit(const logical::entities::structural::module& /*v*/) {

}

void region_processor::visit(const logical::entities::structural::object_template& /*v*/) {

}

void region_processor::visit(const logical::entities::structural::builtin& /*v*/) {

}

void region_processor::visit(const logical::entities::structural::enumeration& /*v*/) {

}

void region_processor::visit(const logical::entities::structural::primitive& /*v*/) {

}

void region_processor::visit(const logical::entities::structural::exception& /*v*/) {

}

void region_processor::visit(const logical::entities::structural::visitor& /*v*/) {

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

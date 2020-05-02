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
#include <iostream>
#include <boost/filesystem/operations.hpp>
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/physical/archetype.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/types/archetype_stitch_class_implementation_transform_old.hpp"
#include "dogen.templating/types/helpers/stitch_template_builder.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"

namespace dogen::m2t::cpp::transforms::types {

physical::entities::archetype archetype_stitch_class_implementation_transform_old::static_archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using physical::helpers::meta_name_factory;
        r.meta_name(meta_name_factory::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::archetype_stitch_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_physical_archetype_name().qualified().dot());
        return r;
    }());
    return r;
}

physical::entities::archetype archetype_stitch_class_implementation_transform_old::archetype() const {
    return static_archetype();
}

inclusion_support_types archetype_stitch_class_implementation_transform_old::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path archetype_stitch_class_implementation_transform_old::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().qualified());
}

boost::filesystem::path archetype_stitch_class_implementation_transform_old::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    auto r(l.make_full_path_for_cpp_implementation(n, archetype().meta_name().qualified()));
    r.replace_extension(".stitch");
    return r;
}

std::list<std::string> archetype_stitch_class_implementation_transform_old::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const logical::entities::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

void archetype_stitch_class_implementation_transform_old::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, archetype().meta_name(), false/*requires_header_guard*/, a);

    /*
     * If the stitch template already exists, load it. Note that we do not do any
     * checks at this point (is it empty, is it valid etc). We leave that to the
     * post-processing step.
     */
    // FIXME: must update the artefact to get the path.
    ast.update_artefact();
    const auto p(a.name().qualified());
    if (boost::filesystem::exists(p)) {
        using utility::filesystem::read_file_content;
        const auto c(read_file_content(p));
        a.content(c);
        a.overwrite(true); // FIXME: hack for now to make life easier during development
        return;
    }

    /*
     * The template does not yet exist, so we need to provide a basic skeleton
     * for the user.
     */
    // const auto& o(ast.as<logical::entities::physical::archetype>(e));

    dogen::templating::helpers::stitch_template_builder b(ast.stream());
    b.add_directive_block("masd.stitch.stream_variable_name", "ast.stream()");
    b.add_directive_block("masd.stitch.containing_namespaces", "dogen::m2t::cpp::transforms::types");

    const auto dep("masd.stitch.inclusion_dependency");
    b.add_directive_block(dep, "dogen.physical/types/helpers/meta_name_factory.hpp");
    b.add_directive_block(dep, "dogen.logical/types/entities/physical/archetype.hpp");
    b.add_directive_block(dep, "dogen.logical/types/helpers/meta_name_factory.hpp");
    b.add_directive_block(dep, "dogen.m2t.cpp/types/transforms/assistant.hpp");
    b.add_directive_block(dep, "dogen.m2t.cpp/types/transforms/types/archetype_stitch_class_implementation_transform_old.hpp");
    b.add_directive_block(dep, "dogen.templating/types/helpers/stitch_template_builder.hpp");
    b.add_directive_block(dep, "dogen.m2t.cpp/types/traits.hpp");
    b.add_directive_block(dep, "dogen.m2t.cpp/types/transforms/types/traits.hpp");
    b.add_start_standard_control_block();
ast.stream() << "physical::entities::archetype archetype_stitch_class_implementation_transform_old::static_archetype() const {" << std::endl;
ast.stream() << "    static physical::entities::archetype r([]() {" << std::endl;
ast.stream() << "        physical::entities::archetype r;" << std::endl;
ast.stream() << "        using pmnf = physical::helpers::meta_name_factory;" << std::endl;
ast.stream() << "        r.meta_name(pmnf::make(cpp::traits::backend_sn()," << std::endl;
ast.stream() << "            traits::facet_sn(), traits::archetype_stitch_class_implementation_archetype_sn()));" << std::endl;
ast.stream() << "        using lmnf = logical::helpers::meta_name_factory;" << std::endl;
ast.stream() << "        r.logical_meta_element_id(lmnf::make_physical_archetype_name().qualified().dot());" << std::endl;
ast.stream() << "        return r;" << std::endl;
ast.stream() << "    }());" << std::endl;
ast.stream() << "    return r;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "physical::entities::archetype archetype_stitch_class_implementation_transform_old::archetype() const {" << std::endl;
ast.stream() << "    return static_archetype();" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "inclusion_support_types archetype_stitch_class_implementation_transform_old::inclusion_support_type() const {" << std::endl;
ast.stream() << "    return inclusion_support_types::not_supported;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "boost::filesystem::path archetype_stitch_class_implementation_transform_old::inclusion_path(" << std::endl;
ast.stream() << "    const formattables::locator& l, const logical::entities::name& n) const {" << std::endl;
ast.stream() << "    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().qualified());" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "boost::filesystem::path archetype_stitch_class_implementation_transform_old::full_path(" << std::endl;
ast.stream() << "    const formattables::locator& l, const logical::entities::name& n) const {" << std::endl;
ast.stream() << "    auto r(l.make_full_path_for_cpp_implementation(n, archetype().meta_name().qualified()));" << std::endl;
ast.stream() << "    r.replace_extension(\".stitch\");" << std::endl;
ast.stream() << "    return r;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "std::list<std::string> archetype_stitch_class_implementation_transform_old::inclusion_dependencies(" << std::endl;
ast.stream() << "    const formattables::dependencies_builder_factory& /*f*/," << std::endl;
ast.stream() << "    const logical::entities::element& /*e*/) const {" << std::endl;
ast.stream() << "    static std::list<std::string> r;" << std::endl;
ast.stream() << "    return r;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "void archetype_stitch_class_implementation_transform_old::apply(const context& ctx, const logical::entities::element& e," << std::endl;
ast.stream() << "    physical::entities::artefact& a) const {" << std::endl;
ast.stream() << "    assistant ast(ctx, e, archetype().meta_name(), false/*requires_header_guard*/, a);" << std::endl;
ast.stream() << "    const auto& o(ast.as<logical::entities::physical::archetype>(e));" << std::endl;
ast.stream() << "    ast.update_artefact();" << std::endl;
ast.stream() << "}" << std::endl;
    ast.update_artefact();
}

}

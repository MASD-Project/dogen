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
#include "dogen.utility/types/io/shared_ptr_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.physical/io/entities/artefact_io.hpp"
#include <boost/throw_exception.hpp>
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/physical/backend.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/types/backend_class_implementation_transform_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/backend_class_implementation_transform_factory.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"

namespace dogen::text::cpp::transforms::types {
namespace {

const std::string transform_id("text.cpp.transforms.types.backend_class_implementation_transform_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& backend_class_implementation_transform_transform::static_archetype() {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::backend_class_implementation_transform_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_physical_backend_name().qualified().dot());
        r.referencing_status(physical::entities::referencing_status::not_referable);
        return r;
    }());
    return r;
}

const physical::entities::archetype& backend_class_implementation_transform_transform::archetype() const {
    static auto r(backend_class_implementation_transform_factory::make());
    return r;
}

inclusion_support_types backend_class_implementation_transform_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path backend_class_implementation_transform_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(logger_factory(archetype().meta_name().qualified()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path backend_class_implementation_transform_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, archetype().meta_name().qualified());
}

std::list<std::string> backend_class_implementation_transform_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    auto builder(f.make());
    const auto ch_arch(traits::canonical_archetype());
    const auto& be(assistant::as<logical::entities::physical::backend>(e));

    builder.add(be.name(), ch_arch);
    builder.add(be.facets(), ch_arch);
    builder.add_as_user("dogen.physical/types/helpers/meta_name_builder.hpp");
    builder.add_as_user("dogen.utility/types/log/logger.hpp");
    builder.add_as_user("dogen.text/types/transforms/transformation_error.hpp");

    return builder.build();
}

void backend_class_implementation_transform_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "backend class implementation transform",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    const auto& be(ast.as<logical::entities::physical::backend>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(be));
        {
            const auto ns(ast.make_namespaces(be.name(),
                    false/*detect_model_name*/));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            const auto sn(be.name().simple() + "_backend_chain");
ast.stream() << "namespace {" << std::endl;
ast.stream() << std::endl;
ast.stream() << "using namespace dogen::utility::log;" << std::endl;
ast.stream() << "static logger lg(logger_factory(\"" << be.name().qualified().dot() << "\"));" << std::endl;
ast.stream() << std::endl;
ast.stream() << "physical::entities::backend make_backend() {" << std::endl;
ast.stream() << "    physical::helpers::meta_name_builder b;" << std::endl;
ast.stream() << "    b.meta_model(\"" << be.meta_model_name() << "\");" << std::endl;
ast.stream() << "    b.backend(\"" << be.backend_name() << "\");" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    physical::entities::backend r;" << std::endl;
ast.stream() << "    r.meta_name(b.build());" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    const auto lambda([&](const auto& fct) {" << std::endl;
ast.stream() << "        const auto id(fct.meta_name().qualified());" << std::endl;
ast.stream() << "        const auto pair(std::make_pair(id, fct));" << std::endl;
ast.stream() << "        const auto inserted(r.facets().insert(pair).second);" << std::endl;
ast.stream() << "        if (!inserted) {" << std::endl;
ast.stream() << "            using text::transforms::transformation_error;" << std::endl;
ast.stream() << "            const std::string duplicate_facet(\"Duplicate facet: \");" << std::endl;
ast.stream() << "            BOOST_LOG_SEV(lg, error) << duplicate_facet << id;" << std::endl;
ast.stream() << "            BOOST_THROW_EXCEPTION(transformation_error(duplicate_facet + id));" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << "    });" << std::endl;
ast.stream() << std::endl;
            for (const auto& n : be.facets()) {
ast.stream() << "    lambda(" << n.simple() << "::" << n.simple() << "_facet_chain::static_facet());" << std::endl;
            }
ast.stream() << "    return r;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "const physical::entities::backend& " << sn << "::static_backend() {" << std::endl;
ast.stream() << "    static const auto r(make_backend());" << std::endl;
ast.stream() << "    return r;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "const physical::entities::backend& " << sn << "::backend() const {" << std::endl;
ast.stream() << "    return static_backend();" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
        } // snf
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);

}
}

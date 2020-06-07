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
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/lexical_cast/traits.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/lexical_cast/enum_header_transform.hpp"

namespace dogen::text::cpp::transforms::lexical_cast {
namespace {

const std::string transform_id("text.cpp.transforms.lexical_cast.enum_header_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& enum_header_transform::static_archetype() {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::enum_header_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_enumeration_name().qualified().dot());
        r.referencing_status(physical::entities::referencing_status::not_referable);
        return r;
    }());
    return r;
}

const physical::entities::archetype& enum_header_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types enum_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path enum_header_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().qualified());
}

boost::filesystem::path enum_header_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, archetype().meta_name().qualified());
}

std::list<std::string> enum_header_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    auto builder(f.make());

    const auto eh_fn(types::traits::enum_header_archetype_qn());
    builder.add(e.name(), eh_fn);
    builder.add(inclusion_constants::boost::lexical_cast());

    return builder.build();
}

void enum_header_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "enum header transform",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    const auto& enm(ast.as<logical::entities::structural::enumeration>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(enm));
        const auto qn(ast.get_qualified_name(enm.name()));
        const auto sn(enm.name().simple());
ast.stream() << std::endl;
ast.stream() << "namespace boost {" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template<>" << std::endl;
ast.stream() << "inline std::string lexical_cast(const " << qn << "& v) {" << std::endl;
        if (!ast.is_cpp_standard_98()) {
ast.stream() << "    using " << qn << ";" << std::endl;
ast.stream() << std::endl;
        }
ast.stream() << "    switch (v) {" << std::endl;
        for (const auto& enu : enm.enumerators()) {
            const auto enu_sn(enu.name().simple());
            std::string enu_qn;
            if (ast.is_cpp_standard_98())
                enu_qn = ast.get_qualified_namespace(enm.name()) + "::" + enu_sn;
            else
                enu_qn = sn + "::" + enu_sn;
ast.stream() << "    case " << enu_qn << ":" << std::endl;
ast.stream() << "        return \"" << sn + "::" + enu_sn << "\";" << std::endl;
        }
ast.stream() << "    default:" << std::endl;
ast.stream() << "        throw boost::bad_lexical_cast();" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template<>" << std::endl;
ast.stream() << "inline " << qn << " lexical_cast(const std::string & s) {" << std::endl;
        if (!ast.is_cpp_standard_98()) {
ast.stream() << "    using " << qn << ";" << std::endl;
ast.stream() << std::endl;
        }

        for (const auto& enu : enm.enumerators()) {
           const auto enu_sn(enu.name().simple());
           std::string enu_qn;
           if (ast.is_cpp_standard_98())
               enu_qn = ast.get_qualified_namespace(enm.name()) + "::" + enu_sn;
           else
               enu_qn = sn + "::" + enu_sn;
ast.stream() << "    if (s == \"" << enu_sn << "\" || s == \"" << sn + "::" + enu_sn << "\")" << std::endl;
ast.stream() << "        return " << enu_qn << ";" << std::endl;
        }
ast.stream() << "    throw boost::bad_lexical_cast();" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}

}

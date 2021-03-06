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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/serialization/type_registrar.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text/types/transforms/cpp/serialization/type_registrar_implementation_transform.hpp"
#include "dogen.text/types/transforms/cpp/serialization/type_registrar_implementation_factory.hpp"

namespace dogen::text::transforms::cpp::serialization {
namespace {

const std::string transform_id("text.transforms.serialization.type_registrar_implementation_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& type_registrar_implementation_transform::static_archetype() {
    static auto r(type_registrar_implementation_factory::make());
    return r;
}

const physical::entities::archetype& type_registrar_implementation_transform::archetype() const {
    return static_archetype();
}

void type_registrar_implementation_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
   tracing::scoped_transform_tracer stp(lg, "type registrar implementation",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    text::formatters::assistant ast(lps, e, a, false/*requires_header_guard*/);
    const auto& rg(ast.as<logical::entities::serialization::type_registrar>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(ast.make_namespaces(rg.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            const auto deps(rg.registrar_dependencies());
            const identification::entities::physical_meta_id carch("masd.cpp.types.canonical_archetype");
            const auto leaves(ast.names_with_enabled_archetype(carch, rg.leaves()));
            const bool has_types(!deps.empty() || !leaves.empty());
            const std::string arg_name(has_types ? " ar" : "");
            const auto sn(e.name().simple());
ast.stream() << std::endl;
ast.stream() << "template<typename Archive>" << std::endl;
ast.stream() << "void " << sn << "::register_types(Archive&" << arg_name << ") {" << std::endl;
            if (has_types) {
                for (const auto& d : deps) {
                    const auto dqn(ast.get_qualified_name(d));
ast.stream() << "    " << dqn << "::register_types(ar);" << std::endl;
                }

                if (!deps.empty() && !leaves.empty())
ast.stream() << std::endl;
                for (const auto& l : leaves) {
                    const auto lqn(ast.get_qualified_name(l));
ast.stream() << "    ar.template register_type<" << lqn << ">();" << std::endl;
                }
            }
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template void " << sn << "::register_types(boost::archive::polymorphic_oarchive&" << arg_name << ");" << std::endl;
ast.stream() << "template void " << sn << "::register_types(boost::archive::polymorphic_iarchive&" << arg_name << ");" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template void " << sn << "::register_types(boost::archive::text_oarchive&" << arg_name << ");" << std::endl;
ast.stream() << "template void " << sn << "::register_types(boost::archive::text_iarchive&" << arg_name << ");" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template void " << sn << "::register_types(boost::archive::binary_oarchive&" << arg_name << ");" << std::endl;
ast.stream() << "template void " << sn << "::register_types(boost::archive::binary_iarchive&" << arg_name << ");" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template void " << sn << "::register_types(boost::archive::xml_oarchive&" << arg_name << ");" << std::endl;
ast.stream() << "template void " << sn << "::register_types(boost::archive::xml_iarchive&" << arg_name << ");" << std::endl;
ast.stream() << std::endl;
        } // snf
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}

}

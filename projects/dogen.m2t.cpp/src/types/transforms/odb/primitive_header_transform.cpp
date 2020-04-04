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
#include "dogen.physical/types/helpers/name_factory.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/odb/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/odb/primitive_header_transform.hpp"

namespace dogen::m2t::cpp::transforms::odb {

std::string primitive_header_transform::static_id() {
    return traits::primitive_header_archetype_qn();
}

std::string primitive_header_transform::id() const {
    return static_id();
}

physical::entities::meta_name
primitive_header_transform::physical_name() const {
    using physical::helpers::name_factory;
    static auto r(name_factory::make(cpp::traits::backend_sn(),
        traits::facet_sn(), traits::primitive_header_archetype_sn()));
    return r;
}

const logical::entities::name& primitive_header_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_primitive_name());
    return r;
}

inclusion_support_types primitive_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path primitive_header_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path primitive_header_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> primitive_header_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    using logical::entities::structural::primitive;
    const auto& p(assistant::as<primitive>(e));
    auto builder(f.make());
    builder.add(p.name(), types::traits::primitive_header_archetype_qn());

    return builder.build();
}

physical::entities::artefact primitive_header_transform::
apply(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, physical_name(), true/*requires_header_guard*/);
    const auto& p(a.as<logical::entities::structural::primitive>(e));

    {
        const auto sn(p.name().simple());
        const auto qn(a.get_qualified_name(p.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        const auto attr(p.value_attribute());

        if (!p.orm_properties() || p.orm_properties()->odb_pragmas().empty()) {
a.stream() << "// class has no ODB pragmas defined." << std::endl;
a.stream() << std::endl;
        } else {
            {
                const auto ns(a.make_namespaces(p.name()));
                auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
a.stream() << "#ifdef ODB_COMPILER" << std::endl;
a.stream() << std::endl;
                for (const auto& pg : p.orm_properties()->odb_pragmas())
a.stream() << pg << std::endl;

                bool is_first(true);
                if (p.value_attribute().orm_properties() &&
                    !p.value_attribute().orm_properties()->odb_pragmas().empty()) {
                    for (const auto& pg : p.value_attribute().orm_properties()->odb_pragmas()) {
                        if (is_first)
a.stream() << std::endl;
                            is_first = false;
a.stream() << pg << std::endl;
                    }
a.stream() << std::endl;
a.stream() << "#endif" << std::endl;
a.stream() << std::endl;
                }
            }
a.stream() << std::endl;
        }
    } // sbf
    return a.make_artefact();
}

}

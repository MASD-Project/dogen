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
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/types/enum_header_transform.hpp"
#include "dogen.m2t.cpp/types/transforms/types/enum_header_transform.hpp"

namespace dogen::m2t::cpp::transforms::types {

std::string enum_header_transform::static_id() {
    return traits::enum_header_archetype();
}

std::string enum_header_transform::id() const {
    return static_id();
}

physical::entities::location
enum_header_transform::archetype_location() const {
    static physical::entities::location
        r(cpp::traits::backend(), traits::facet(),
          enum_header_transform::static_id());
    return r;
}

const logical::entities::name& enum_header_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_enumeration_name());
    return r;
}

std::string enum_header_transform::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types enum_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path enum_header_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path enum_header_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> enum_header_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    using logical::entities::structural::enumeration;
    const auto& en(assistant::as<enumeration>(e));
    auto builder(f.make());
    const auto arch(traits::canonical_archetype());
    builder.add(en.underlying_element(), arch);
    return builder.build();
}

physical::entities::artefact enum_header_transform::
format(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location(), true/*requires_header_guard*/);
    const auto& ye(a.as<logical::entities::structural::enumeration>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
            a.comment(e.documentation());
            if (a.is_cpp_standard_98()) {
a.stream() << "enum " << ye.name().simple() << " {" << std::endl;
            } else {
                if (ye.use_implementation_defined_underlying_element())
a.stream() << "enum class " << ye.name().simple() << " {" << std::endl;
                else
a.stream() << "enum class " << ye.name().simple() << " : " << a.get_qualified_name(ye.underlying_element()) << " {" << std::endl;
            }

            m2t::formatters::sequence_formatter sf(ye.enumerators().size());
            for (const auto& en : ye.enumerators()) {
                if (ye.use_implementation_defined_enumerator_values())
a.stream() << "    " << en.name().simple() << sf.postfix() << a.comment_inline(en.documentation()) << std::endl;
                else
a.stream() << "    " << en.name().simple() << " = " << en.value() << sf.postfix() << a.comment_inline(en.documentation()) << std::endl;
                sf.next();
            }
a.stream() << "};" << std::endl;
a.stream() << std::endl;
        } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}

}

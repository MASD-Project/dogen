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
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/types/helpers/meta_name_factory.hpp"
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen.generation.cpp/types/formatters/odb/traits.hpp"
#include "dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/odb/class_header_formatter.hpp"

namespace dogen::generation::cpp::formatters::odb {

std::string class_header_formatter::static_id() {
    return traits::class_header_archetype();
}

std::string class_header_formatter::id() const {
    return static_id();
}

archetypes::location
class_header_formatter::archetype_location() const {
    static archetypes::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          class_header_formatter::static_id());
    return r;
}

const assets::meta_model::name& class_header_formatter::meta_name() const {
    using assets::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_object_name());
    return r;
}

std::string class_header_formatter::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types class_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path class_header_formatter::inclusion_path(
    const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path class_header_formatter::full_path(
    const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> class_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const assets::meta_model::element& e) const {
    using assets::meta_model::structural::object;
    const auto& o(assistant::as<object>(e));
    auto builder(f.make());
    builder.add(o.name(), types::traits::class_header_archetype());

    const auto carch(traits::canonical_archetype());
    builder.add(o.transparent_associations(), carch);
    builder.add(o.opaque_associations(), carch);

    const auto self_fn(class_header_formatter::static_id());
    builder.add(o.parents(), self_fn);

    return builder.build();
}

extraction::meta_model::artefact
class_header_formatter::
format(const context& ctx, const assets::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), true/*requires_header_guard*/);
    const auto& o(a.as<assets::meta_model::structural::object>(e));

    {
        const auto sn(o.name().simple());
        const auto qn(a.get_qualified_name(o.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(e));

        if (!o.orm_properties() || o.orm_properties()->odb_pragmas().empty()) {
a.stream() << "// class has no ODB pragmas defined." << std::endl;
a.stream() << std::endl;
        } else {
            {
                const auto ns(a.make_namespaces(o.name()));
                auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
a.stream() << "#ifdef ODB_COMPILER" << std::endl;
a.stream() << std::endl;
                for (const auto& pg : o.orm_properties()->odb_pragmas())
a.stream() << "#pragma db " << a.get_odb_type() << "(" << sn << ") " << pg << std::endl;

                bool is_first(true);
                for (const auto& attr : o.local_attributes()) {
                    if (!attr.orm_properties() ||
                        attr.orm_properties()->odb_pragmas().empty())
                        continue;

                    const auto attr_level_pragmas(attr.orm_properties()->odb_pragmas());
                    for (const auto pg : attr_level_pragmas) {
                        if (is_first)
a.stream() << std::endl;
                        is_first = false;
a.stream() << "#pragma db member(" << sn << "::" << a.make_member_variable_name(attr) << ") " << pg << std::endl;
                    }
                }
a.stream() << std::endl;
a.stream() << "#endif" << std::endl;
a.stream() << std::endl;
            }
a.stream() << std::endl;
        }
    } // sbf
    return a.make_artefact();
}
}

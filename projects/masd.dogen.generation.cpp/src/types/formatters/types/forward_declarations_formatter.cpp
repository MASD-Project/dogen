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
#include "masd.dogen.generation.cpp/types/formatters/types/forward_declarations_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/assistant.hpp"
#include "masd.dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "masd.dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/traits.hpp"
#include "masd.dogen.generation.cpp/types/traits.hpp"
#include "masd.dogen.generation.cpp/types/fabric/forward_declarations.hpp"
#include "masd.dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "masd.dogen.generation.cpp/types/traits.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"

namespace masd::dogen::generation::cpp::formatters::types {

std::string forward_declarations_formatter::static_id() {
    return traits::forward_declarations_archetype();
}

std::string forward_declarations_formatter::id() const {
    return static_id();
}

archetypes::location
forward_declarations_formatter::archetype_location() const {
    static archetypes::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          forward_declarations_formatter::static_id());
    return r;
}

const coding::meta_model::name& forward_declarations_formatter::meta_name() const {
    using fabric::meta_name_factory;
    static auto r(meta_name_factory::make_forward_declarations_name());
    return r;
}

std::string forward_declarations_formatter::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types forward_declarations_formatter::inclusion_support_type() const {
    return inclusion_support_types::regular_support;
}

boost::filesystem::path forward_declarations_formatter::inclusion_path(
    const formattables::locator& l, const coding::meta_model::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path forward_declarations_formatter::full_path(
    const formattables::locator& l, const coding::meta_model::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> forward_declarations_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const coding::meta_model::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

extraction::meta_model::artefact forward_declarations_formatter::
format(const context& ctx, const coding::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), true/*requires_header_guard*/);
    const auto& fd(a.as<fabric::forward_declarations>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(fd.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));

            if (fd.is_enum()) {
a.stream() << std::endl;
a.stream() << "enum class " << fd.name().simple() << " : " << fd.underlying_element().simple() << ";" << std::endl;
a.stream() << std::endl;
            } else {
a.stream() << std::endl;
a.stream() << "class " << fd.name().simple() << ";" << std::endl;
a.stream() << std::endl;
            }
        } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}

}

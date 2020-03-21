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
#include "dogen.logical/types/entities/serialization/type_registrar.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/formatters/assistant.hpp"
#include "dogen.m2t.cpp/types/formatters/traits.hpp"
#include "dogen.m2t.cpp/types/formatters/serialization/traits.hpp"
#include "dogen.m2t.cpp/types/formatters/serialization/type_registrar_header_formatter.hpp"

namespace dogen::m2t::cpp::formatters::serialization {

std::string type_registrar_header_formatter::static_id() {
    return traits::type_registrar_header_archetype();
}

std::string type_registrar_header_formatter::id() const {
    return static_id();
}

physical::entities::location
type_registrar_header_formatter::archetype_location() const {
    static physical::entities::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          type_registrar_header_formatter::static_id());
    return r;
}

const logical::entities::name& type_registrar_header_formatter::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_serialization_type_registrar_name());
    return r;
}

std::string type_registrar_header_formatter::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types type_registrar_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path type_registrar_header_formatter::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path type_registrar_header_formatter::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> type_registrar_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const logical::entities::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

physical::entities::artefact type_registrar_header_formatter::
format(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& rg(a.as<logical::entities::serialization::type_registrar>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(rg.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            const auto sn(e.name().simple());
a.stream() << std::endl;
a.stream() << "class " << sn << " {" << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << std::endl;
a.stream() << "template<typename Archive>" << std::endl;
a.stream() << "static void register_types(Archive& ar);" << std::endl;
a.stream() << std::endl;
a.stream() << "};" << std::endl;
        } // snf
a.stream() << std::endl;

    } // sbf
    return a.make_artefact();
}

}

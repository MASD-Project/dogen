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
#include "dogen.logical/types/entities/structural/visitor.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/types/visitor_forward_declarations_transform.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"

namespace dogen::m2t::cpp::transforms::types {

std::string visitor_forward_declarations_transform::static_id() {
    return traits::visitor_forward_declarations_archetype();
}

std::string visitor_forward_declarations_transform::id() const {
    return static_id();
}

physical::entities::location
visitor_forward_declarations_transform::archetype_location() const {
    static physical::entities::location
        r(cpp::traits::backend(), traits::facet(),
          visitor_forward_declarations_transform::static_id());
    return r;
}

const logical::entities::name& visitor_forward_declarations_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_visitor_name());
    return r;
}

inclusion_support_types visitor_forward_declarations_transform::inclusion_support_type() const {
    return inclusion_support_types::regular_support;
}

boost::filesystem::path visitor_forward_declarations_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path visitor_forward_declarations_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> visitor_forward_declarations_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const logical::entities::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

physical::entities::artefact visitor_forward_declarations_transform::
format(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location(), true/*requires_header_guard*/);
    const auto& o(a.as<logical::entities::structural::visitor>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(o));
        {
            const auto ns(a.make_namespaces(o.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
a.stream() << "class " << o.name().simple() << ";" << std::endl;
a.stream() << std::endl;
        } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}

}

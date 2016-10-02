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
#include <typeinfo>
#include <boost/make_shared.hpp>
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/registrar_header_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/registrar_header_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace serialization {

std::string registrar_header_formatter::static_formatter_name() {
    return traits::registrar_header_formatter_name();
}

std::string registrar_header_formatter::id() const {
    static auto r(ownership_hierarchy().formatter_name());
    return r;
}

dynamic::ownership_hierarchy
registrar_header_formatter::ownership_hierarchy() const {
    static dynamic::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            registrar_header_formatter::static_formatter_name());
    return r;
}

std::type_index registrar_header_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(fabric::registrar)));
    return r;
}

std::list<std::string> registrar_header_formatter::inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& /*f*/,
    const yarn::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

inclusion_support_types registrar_header_formatter::
inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path registrar_header_formatter::inclusion_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_formatter_name());
}

boost::filesystem::path registrar_header_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_formatter_name());
}

dogen::formatters::file registrar_header_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, ownership_hierarchy(), false/*requires_header_guard*/, id);
    const auto& rg(a.as<fabric::registrar>(static_formatter_name(), e));
    const auto r(registrar_header_formatter_stitch(a, rg));
    return r;
}

} } } } }

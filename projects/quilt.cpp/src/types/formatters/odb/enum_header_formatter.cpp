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
#include "dogen/yarn/types/object.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/enum_header_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/enum_header_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace odb {

std::string enum_header_formatter::static_formatter_name() {
    return traits::enum_header_formatter_name();
}

std::string enum_header_formatter::id() const {
    static auto r(ownership_hierarchy().formatter_name());
    return r;
}

annotations::ownership_hierarchy
enum_header_formatter::ownership_hierarchy() const {
    static annotations::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            enum_header_formatter::static_formatter_name());
    return r;
}

std::type_index enum_header_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(yarn::enumeration)));
    return r;
}

std::list<std::string> enum_header_formatter::inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& f,
    const yarn::element& e) const {
    auto builder(f.make());
    builder.add(e.name(), types::traits::enum_header_formatter_name());
    return builder.build();
}

inclusion_support_types enum_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path enum_header_formatter::inclusion_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_formatter_name());
}

boost::filesystem::path enum_header_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_formatter_name());
}

dogen::formatters::file enum_header_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, ownership_hierarchy(), true/*requires_header_guard*/, id);
    const auto& ye(a.as<yarn::enumeration>(static_formatter_name(), e));
    const auto r(enum_header_formatter_stitch(a, ye));
    return r;
}

} } } } }

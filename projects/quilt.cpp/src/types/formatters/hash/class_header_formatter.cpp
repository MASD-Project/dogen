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
#include <boost/make_shared.hpp>
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/class_header_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/class_header_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace hash {

class provider final : public formattables::provider_interface<yarn::object> {
 public:
    std::string facet_name() const override;
    std::string formatter_name() const override;

    std::list<std::string> provide_inclusion_dependencies(
        const formattables::inclusion_dependencies_builder_factory& f,
        const yarn::object& o) const override;

    formattables::inclusion_path_support inclusion_path_support() const override;

    boost::filesystem::path provide_inclusion_path(const formattables::locator& l,
        const yarn::name& n) const override;

    boost::filesystem::path provide_full_path(const formattables::locator& l,
        const yarn::name& n) const override;
};

std::list<std::string> provider::provide_inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& f,
    const yarn::object& o) const {

    auto builder(f.make());
    builder.add(inclusion_constants::std::functional());
    builder.add(o.name(), types::traits::facet_name());

    return builder.build();
}

formattables::inclusion_path_support provider::inclusion_path_support() const {
    return formattables::inclusion_path_support::is_default;
}

boost::filesystem::path
provider::provide_inclusion_path(const formattables::locator& l,
    const yarn::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, formatter_name());
}

boost::filesystem::path
provider::provide_full_path(const formattables::locator& l,
    const yarn::name& n) const {
    return l.make_full_path_for_cpp_header(n, formatter_name());
}

std::string provider::facet_name() const {
    return traits::facet_name();
}

std::string provider::formatter_name() const {
    return class_header_formatter::static_formatter_name();
}

std::string class_header_formatter::static_formatter_name() {
    return traits::class_header_formatter_name();
}

std::string class_header_formatter::id() const {
    static auto r(ownership_hierarchy().formatter_name());
    return r;
}

dynamic::ownership_hierarchy
class_header_formatter::ownership_hierarchy() const {
    static dynamic::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            class_header_formatter::static_formatter_name(),
            formatters::traits::header_formatter_group_name());
    return r;
}

file_types class_header_formatter::file_type() const {
    return file_types::cpp_header;
}

void class_header_formatter::
register_provider(formattables::registrar& rg) const {
    rg.register_provider(boost::make_shared<provider>());
}

dogen::formatters::file class_header_formatter::
format(const context& ctx, const yarn::object& o) const {
    assistant a(ctx, ownership_hierarchy(), file_type(), o.name().id());
    const auto r(class_header_formatter_stitch(a, o));
    return r;
}

} } } } }

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
#include <sstream>
#include <boost/make_shared.hpp>
#include "dogen/yarn/types/object.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/forward_declarations_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/forward_declarations_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace serialization {

namespace {

class provider :
        public formattables::provider_interface<fabric::forward_declarations> {
public:
    std::string facet_name() const override;
    std::string formatter_name() const override;

    std::list<std::string> provide_inclusion_dependencies(
        const formattables::inclusion_dependencies_builder_factory& f,
        const fabric::forward_declarations& fd) const override;

    formattables::inclusion_path_support inclusion_path_support() const override;

    boost::filesystem::path provide_inclusion_path(const formattables::locator& l,
        const yarn::name& n) const override;

    boost::filesystem::path provide_full_path(const formattables::locator& l,
        const yarn::name& n) const override;
};

std::string provider::facet_name() const {
    return traits::facet_name();
}

std::string provider::formatter_name() const {
    return forward_declarations_formatter::static_formatter_name();
}

std::list<std::string> provider::provide_inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& f,
    const fabric::forward_declarations& fd) const {

    auto builder(f.make());

    using tp = formatters::types::traits;
    const auto tp_fn(tp::forward_declarations_formatter_name());
    builder.add(fd.name(), tp_fn);

    return builder.build();
}

formattables::inclusion_path_support provider::inclusion_path_support() const {
    return formattables::inclusion_path_support::regular;
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

}

std::string forward_declarations_formatter::static_formatter_name() {
    return traits::forward_declarations_formatter_name();
}

std::string forward_declarations_formatter::id() const {
    static auto r(ownership_hierarchy().formatter_name());
    return r;
}

dynamic::ownership_hierarchy
forward_declarations_formatter::ownership_hierarchy() const {
    static dynamic::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            forward_declarations_formatter::static_formatter_name(),
            formatters::traits::header_formatter_group_name());
    return r;
}

file_types forward_declarations_formatter::file_type() const {
    return file_types::cpp_header;
}

void forward_declarations_formatter::
register_provider(formattables::registrar& rg) const {
    rg.register_provider(boost::make_shared<provider>());
}

dogen::formatters::file forward_declarations_formatter::
format(const context& ctx, const fabric::forward_declarations& fd) const {
    // FIXME: hack: legacy formatters do not support serialisation
    // forward declarations for some types.
    if (fd.is_enum() || fd.is_exception())
        return dogen::formatters::file();

    assistant a(ctx, ownership_hierarchy(), file_type(), fd.name().id());
    const auto r(forward_declarations_formatter_stitch(a, fd));
    return r;
}

} } } } }

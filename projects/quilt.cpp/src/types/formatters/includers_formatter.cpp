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
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/includers_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/includers_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

namespace {

class provider final : public properties::
        inclusion_dependencies_provider_interface<yarn::object> {
public:
    explicit provider(const std::string& formatter_name);

public:
    std::string formatter_name() const override;

    boost::optional<std::list<std::string> >
        provide(const properties::inclusion_dependencies_builder_factory& f,
            const yarn::object& o) const override;

private:
    const std::string formatter_name_;
};

provider::provider(const std::string& formatter_name)
    : formatter_name_(formatter_name) { }

boost::optional<std::list<std::string> >
provider::provide(const properties::inclusion_dependencies_builder_factory& f,
    const yarn::object& /*o*/) const {

    auto builder(f.make());
    return builder.build();
}

std::string provider::formatter_name() const {
    return formatter_name_;
}

}

includers_formatter::includers_formatter(const std::string& facet_name)
    : ownership_hierarchy_(formatters::traits::model_name(), facet_name,
        traits::includers_formatter_name(facet_name),
        formatters::traits::header_formatter_group_name()) { }

std::string includers_formatter::id() const {
    static auto r(ownership_hierarchy().formatter_name());
    return r;
}

dynamic::ownership_hierarchy
includers_formatter::ownership_hierarchy() const {
    return ownership_hierarchy_;
}

file_types includers_formatter::file_type() const {
    return file_types::cpp_header;
}

properties::origin_types includers_formatter::
formattable_origin_type() const {
    return properties::origin_types::internal;
}

void includers_formatter::register_inclusion_dependencies_provider(
    properties::registrar& rg) const {
    rg.register_provider(
        boost::make_shared<provider>(ownership_hierarchy_.formatter_name()));
}

dogen::formatters::file
includers_formatter::format(const context& ctx,
    const properties::includers_info& i) const {
    assistant a(ctx, ownership_hierarchy(), file_type());
    const auto r(includers_formatter_stitch(a, i));
    return r;
}

} } } }

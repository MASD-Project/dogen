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
#include "dogen/tack/types/enumeration.hpp"
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/test_data/traits.hpp"
#include "dogen/cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/cpp/types/formatters/entity_formatting_assistant.hpp"
#include "dogen/cpp/types/formatters/test_data/enum_implementation_formatter_stitch.hpp"
#include "dogen/cpp/types/formatters/test_data/enum_implementation_formatter.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace test_data {

namespace {

class provider final : public formattables::
        inclusion_dependencies_provider_interface<tack::enumeration> {
public:
    std::string formatter_name() const override;

    boost::optional<std::list<std::string> >
        provide(const formattables::inclusion_dependencies_builder_factory& f,
            const tack::enumeration& o) const override;
};

std::string provider::formatter_name() const {
    return enum_implementation_formatter::static_formatter_name();
}

boost::optional<std::list<std::string> >
provider::provide(const formattables::inclusion_dependencies_builder_factory& f,
  const tack::enumeration& o) const {
  auto builder(f.make());

  const auto ch_fn(traits::class_header_formatter_name());
  builder.add(o.name(), ch_fn);
  return builder.build();
}

}

std::string enum_implementation_formatter::static_formatter_name() {
    return traits::enum_implementation_formatter_name();
}

dynamic::ownership_hierarchy enum_implementation_formatter::
ownership_hierarchy() const {
    static dynamic::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            enum_implementation_formatter::static_formatter_name(),
            formatters::traits::implementation_formatter_group_name());
    return r;
}

file_types enum_implementation_formatter::file_type() const {
    return file_types::cpp_implementation;
}

formattables::origin_types
enum_implementation_formatter::formattable_origin_type() const {
    return formattables::origin_types::external;
}

void enum_implementation_formatter::register_inclusion_dependencies_provider(
    formattables::registrar& rg) const {
    rg.register_provider(boost::make_shared<provider>());
}

dogen::formatters::file enum_implementation_formatter::
format(const formattables::enum_info& c) const {
    entity_formatting_assistant fa(c, ownership_hierarchy(), file_type());
    const auto r(enum_implementation_formatter_stitch(fa, c));
    return r;
}

} } } }

/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/cpp/types/expansion/inclusion_dependencies_provider_interface.hpp"
#include "dogen/cpp/types/expansion/inclusion_dependencies_builder.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/cpp/types/formatters/types/forward_declarations_formatter_stitch.hpp"
#include "dogen/cpp/types/formatters/types/forward_declarations_formatter.hpp"

namespace {

using namespace dogen::utility::log;
using namespace dogen::cpp::formatters::types;
static logger
lg(logger_factory(forward_declarations_formatter::static_formatter_name()));

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

namespace {

class provider final : public expansion::
        inclusion_dependencies_provider_interface<sml::object> {
public:
    std::string formatter_name() const override;

    boost::optional<std::list<std::string> >
    provide(const dynamic::schema::repository& rp,
        const expansion::inclusion_directives_repository& idr,
        const sml::object& o) const override;
};

std::string provider::formatter_name() const {
    return forward_declarations_formatter::static_formatter_name();
}

boost::optional<std::list<std::string> >
provider::provide(const dynamic::schema::repository& /*rp*/,
    const expansion::inclusion_directives_repository& idr,
    const sml::object& o) const {
    if (o.object_type() != sml::object_types::exception)
        return boost::optional<std::list<std::string> >();

    const auto self_fn(forward_declarations_formatter::static_formatter_name());
    expansion::inclusion_dependencies_builder builder(idr);
    builder.add(inclusion_constants::std::string());
    builder.add(inclusion_constants::boost::exception::info());
    return builder.build();
}

}

std::string forward_declarations_formatter::static_formatter_name() {
    return traits::forward_declarations_formatter_name();
}

dynamic::schema::ownership_hierarchy
forward_declarations_formatter::ownership_hierarchy() const {
    static dynamic::schema::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            forward_declarations_formatter::static_formatter_name(),
            formatters::traits::header_formatter_group_name());
    return r;
}

file_types forward_declarations_formatter::file_type() const {
    return file_types::cpp_header;
}

void forward_declarations_formatter::register_inclusion_dependencies_provider(
    expansion::registrar& rg) const {
    rg.register_provider(boost::make_shared<provider>());
}

dogen::formatters::file forward_declarations_formatter::
format(const formattables::forward_declarations_info& fd) const {
    formatting_assistant fa(fd, ownership_hierarchy(), file_type());
    const auto r(forward_declarations_formatter_stitch(fa, fd));
    return r;
}

} } } }

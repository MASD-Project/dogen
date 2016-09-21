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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/enum_implementation_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/enum_implementation_formatter.hpp"

namespace {

using namespace dogen::utility::log;
using namespace dogen::quilt::cpp::formatters::test_data;
static logger lg(
    logger_factory(enum_implementation_formatter::static_formatter_name()));

const std::string not_supported("Inclusion path is not supported: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace test_data {

namespace {

class provider final :
        public formattables::provider_interface<yarn::enumeration> {
public:
    std::string facet_name() const override;
    std::string formatter_name() const override;

    std::list<std::string> provide_inclusion_dependencies(
        const formattables::inclusion_dependencies_builder_factory& f,
        const yarn::enumeration& e) const override;

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
    return enum_implementation_formatter::static_formatter_name();
}

std::list<std::string>
provider::provide_inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& f,
    const yarn::enumeration& o) const {
    auto builder(f.make());

    const auto eh_fn(traits::enum_header_formatter_name());
    builder.add(o.name(), eh_fn);
    return builder.build();
}

formattables::inclusion_path_support provider::inclusion_path_support() const {
    return formattables::inclusion_path_support::not_supported;
}

boost::filesystem::path
provider::provide_inclusion_path(const formattables::locator& /*l*/,
    const yarn::name& n) const {

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path
provider::provide_full_path(const formattables::locator& l,
    const yarn::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, formatter_name());
}

}

std::string enum_implementation_formatter::static_formatter_name() {
    return traits::enum_implementation_formatter_name();
}

std::string enum_implementation_formatter::id() const {
    static auto r(ownership_hierarchy().formatter_name());
    return r;
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

void enum_implementation_formatter::
register_provider(formattables::registrar& rg) const {
    rg.register_provider(boost::make_shared<provider>());
}

dogen::formatters::file enum_implementation_formatter::
format(const context& ctx, const yarn::enumeration& e) const {
    assistant a(ctx, ownership_hierarchy(), file_type(), e.name().id());
    const auto r(enum_implementation_formatter_stitch(a, e));
    return r;
}

} } } } }

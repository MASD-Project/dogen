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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/odb_options_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/odb_options_formatter.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("quilt.cpp.formatters.odb.odb_options_formatter"));

const std::string not_supported("Inclusion path is not supported: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace odb {

namespace {

class provider final :
        public formattables::provider_interface<fabric::odb_options> {
public:
    std::string facet_name() const override;
    std::string formatter_name() const override;

    std::list<std::string> provide_inclusion_dependencies(
        const formattables::inclusion_dependencies_builder_factory& f,
        const fabric::odb_options& o) const override;

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
    return odb_options_formatter::static_formatter_name();
}

std::list<std::string> provider::provide_inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& /*f*/,
    const fabric::odb_options& /*o*/) const {
    static std::list<std::string> r;
    return r;
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
    return l.make_full_path_for_odb_options(n, formatter_name());
}

}

std::string odb_options_formatter::static_formatter_name() {
    return traits::odb_options_formatter_name();
}

std::string odb_options_formatter::id() const {
    static auto r(ownership_hierarchy().formatter_name());
    return r;
}

dynamic::ownership_hierarchy
odb_options_formatter::ownership_hierarchy() const {
    static dynamic::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            odb_options_formatter::static_formatter_name(),
            formatters::traits::header_formatter_group_name());
    return r;
}

file_types odb_options_formatter::file_type() const {
    return file_types::odb_options;
}

void odb_options_formatter::
register_provider(formattables::registrar& rg) const {
    rg.register_provider(boost::make_shared<provider>());
}

std::type_index odb_options_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(fabric::odb_options)));
    return r;
}

dogen::formatters::file odb_options_formatter::
format(const context& ctx, const yarn::element& e) const {
    assistant a(ctx, ownership_hierarchy(), file_type(), e.name().id());
    const auto& oo(a.as<fabric::odb_options>(e));
    const auto r(odb_options_formatter_stitch(a, oo));
    return r;
}

} } } } }

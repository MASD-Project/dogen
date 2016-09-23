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
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/include_cmakelists_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/include_cmakelists_formatter.hpp"

namespace {

using namespace dogen::utility::log;
using namespace dogen::quilt::cpp::formatters;
static logger lg(
    logger_factory(include_cmakelists_formatter::static_formatter_name()));

const std::string empty;
const std::string not_supported("Inclusion path is not supported: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

namespace {

class provider final :
        public formattables::provider_interface<fabric::cmakelists> {
public:
    std::string facet_name() const override;
    std::string formatter_name() const override;

    std::list<std::string> provide_inclusion_dependencies(
        const formattables::inclusion_dependencies_builder_factory& f,
        const fabric::cmakelists& p) const override;

    formattables::inclusion_path_support inclusion_path_support() const override;

    boost::filesystem::path provide_inclusion_path(const formattables::locator& l,
        const yarn::name& n) const override;

    boost::filesystem::path provide_full_path(const formattables::locator& l,
        const yarn::name& n) const override;
};

std::string provider::facet_name() const {
    return empty;
}

std::string provider::formatter_name() const {
    return include_cmakelists_formatter::static_formatter_name();
}

std::list<std::string> provider::provide_inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& /*f*/,
    const fabric::cmakelists& /*c*/) const {
    static std::list<std::string> r;
    return r;
}

formattables::inclusion_path_support provider::
inclusion_path_support() const {
    return formattables::inclusion_path_support::not_supported;
}

boost::filesystem::path
provider::provide_inclusion_path(const formattables::locator& /*l*/,
    const yarn::name& /*n*/) const {
    static boost::filesystem::path r;
    return r;
}

boost::filesystem::path
provider::provide_full_path(const formattables::locator& l,
    const yarn::name& n) const {
    return l.make_full_path_for_include_cmakelists(n, formatter_name());
}

}

std::string include_cmakelists_formatter::static_formatter_name() {
    return traits::include_cmakelists_formatter_name();
}

std::string include_cmakelists_formatter::id() const {
    static auto r(ownership_hierarchy().formatter_name());
    return r;
}

dynamic::ownership_hierarchy include_cmakelists_formatter::
ownership_hierarchy() const {
    static dynamic::ownership_hierarchy
        r(formatters::traits::model_name(), traits::cmake_facet_name(),
            include_cmakelists_formatter::static_formatter_name(),
            empty/*group name*/);
    return r;
}

std::type_index include_cmakelists_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(fabric::cmakelists)));
    return r;
}

std::list<std::string> include_cmakelists_formatter::inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& /*f*/,
    const yarn::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

inclusion_support_types include_cmakelists_formatter::
inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path include_cmakelists_formatter::inclusion_path(
    const formattables::locator& /*l*/, const yarn::name& n) const {
    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path include_cmakelists_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_include_cmakelists(n, static_formatter_name());
}

void include_cmakelists_formatter::
register_provider(formattables::registrar& rg) const {
    rg.register_provider(boost::make_shared<provider>());
}

dogen::formatters::file include_cmakelists_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, ownership_hierarchy(), false/*requires_header_guard*/, id);
    const auto& cm(a.as<fabric::cmakelists>(static_formatter_name(), e));
    const auto r(include_cmakelists_formatter_stitch(a, cm));
    return r;
}

} } } }

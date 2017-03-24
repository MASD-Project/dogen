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
#include "dogen/quilt.cpp/types/formatters/odb/object_odb_options_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/fabric/object_odb_options.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/utility/log/logger.hpp"
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/throw_exception.hpp>
#include <boost/make_shared.hpp>
#include <typeinfo>

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace odb {

std::string object_odb_options_formatter::static_artefact() {
    return traits::object_odb_options_archetype();
}

std::string object_odb_options_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location
object_odb_options_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::family(), cpp::traits::kernel(),
          traits::facet(), object_odb_options_formatter::static_artefact());
    return r;
}

std::type_index object_odb_options_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(fabric::object_odb_options)));
    return r;
}

inclusion_support_types object_odb_options_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path object_odb_options_formatter::inclusion_path(
    const formattables::locator& /*l*/, const yarn::name& n) const {
    using namespace dogen::utility::log;
    static logger
        lg(logger_factory("quilt.cpp.formatters.odb.object_odb_options_formatter"));

        const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path object_odb_options_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_odb_options(n, static_artefact());
}

std::list<std::string> object_odb_options_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const yarn::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

dogen::formatters::artefact object_odb_options_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), false/*requires_header_guard*/, id);
    const auto& ooo(a.as<fabric::object_odb_options>(static_artefact(), e));

    {
        a.make_decoration_preamble(e);
a.stream() << "# epilogue" << std::endl;
a.stream() << "--odb-epilogue " << ooo.epilogue() << std::endl;
a.stream() << std::endl;
        if (!ooo.include_regexes().empty()) {
a.stream() << "# regexes" << std::endl;
            for (const auto& regex : ooo.include_regexes())
a.stream() << "--include-regex " << regex << std::endl;
a.stream() << std::endl;
        }
    } // sbf
    return a.make_artefact();
}
} } } } }

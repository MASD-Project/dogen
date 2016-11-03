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
#include "dogen/quilt.cpp/types/formatters/source_cmakelists_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/fabric/cmakelists.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/utility/log/logger.hpp"
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/throw_exception.hpp>
#include <boost/make_shared.hpp>
#include <typeinfo>

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

std::string source_cmakelists_formatter::static_artefact() {
    return traits::source_cmakelists_archetype();
}

std::string source_cmakelists_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location source_cmakelists_formatter::
archetype_location() const {
    static annotations::archetype_location
        r(formatters::traits::kernel(), traits::cmake_facet(),
            source_cmakelists_formatter::static_artefact());
    return r;
}

std::type_index source_cmakelists_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(fabric::cmakelists)));
    return r;
}

inclusion_support_types source_cmakelists_formatter::
inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path source_cmakelists_formatter::inclusion_path(
    const formattables::locator& /*l*/, const yarn::name& n) const {

    using namespace dogen::utility::log;
    using namespace dogen::quilt::cpp::formatters;
    static logger lg(
        logger_factory(source_cmakelists_formatter::static_artefact()));

    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path source_cmakelists_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_source_cmakelists(n, static_artefact());
}

std::list<std::string> source_cmakelists_formatter::inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& /*f*/,
    const yarn::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

dogen::formatters::artefact source_cmakelists_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), false/*requires_header_guard*/, id);
    const auto& c(a.as<fabric::cmakelists>(static_artefact(), e));

    {
        a.make_decoration_preamble();
        const auto model_name(a.get_identifiable_model_name(c.name()));
        const auto product_name(a.get_product_name(c.name()));
a.stream() << "set(files \"\")" << std::endl;
a.stream() << "file(GLOB_RECURSE files RELATIVE" << std::endl;
a.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/\"" << std::endl;
a.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp\")" << std::endl;
a.stream() << std::endl;
a.stream() << "add_library(" << model_name << " STATIC ${files})" << std::endl;
a.stream() << "set_target_properties(" << model_name << " PROPERTIES" << std::endl;
a.stream() << "    OUTPUT_NAME " << product_name << (product_name.empty() ? "" : ".") << model_name << ")" << std::endl;
a.stream() << std::endl;
a.stream() << "install(TARGETS " << model_name << " ARCHIVE DESTINATION lib COMPONENT libraries)" << std::endl;
    } // sbf
        return a.make_artefact();
}
} } } }

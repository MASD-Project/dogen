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
#include "masd.dogen.generation.cpp/types/formatters/tests/source_cmakelists_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "masd.dogen.generation.cpp/types/formatters/assistant.hpp"
#include "masd.dogen.generation.cpp/types/fabric/cmakelists.hpp"
#include "masd.dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "masd.dogen.generation.cpp/types/formatters/traits.hpp"
#include "masd.dogen.generation.cpp/types/traits.hpp"
#include "masd.dogen.extraction/types/sequence_formatter.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/throw_exception.hpp>
#include <boost/make_shared.hpp>

namespace masd::dogen::generation::cpp::formatters::tests {

std::string source_cmakelists_formatter::static_id() {
    return traits::source_cmakelists_archetype();
}

std::string source_cmakelists_formatter::id() const {
    return static_id();
}

annotations::archetype_location source_cmakelists_formatter::
archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::cmake_facet(),
          source_cmakelists_formatter::static_id());
    return r;
}

const coding::meta_model::name& source_cmakelists_formatter::meta_name() const {
    static auto r(fabric::meta_name_factory::make_cmakelists_name());
    return r;
}

std::string source_cmakelists_formatter::family() const {
    return cpp::traits::cmake_family();
}

inclusion_support_types source_cmakelists_formatter::
inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path source_cmakelists_formatter::inclusion_path(
    const formattables::locator& /*l*/, const coding::meta_model::name& n) const {

    using namespace masd::dogen::utility::log;
    using namespace masd::dogen::generation::cpp::formatters;
    static logger lg(logger_factory(source_cmakelists_formatter::static_id()));

    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path source_cmakelists_formatter::full_path(
    const formattables::locator& l, const coding::meta_model::name& n) const {
    return l.make_full_path_for_source_cmakelists(n, static_id());
}

std::list<std::string> source_cmakelists_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const coding::meta_model::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

extraction::meta_model::artefact source_cmakelists_formatter::
format(const context& ctx, const coding::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& c(a.as<fabric::cmakelists>(e));

    {
        const auto cs(dogen::extraction::comment_styles::shell_style);
        a.make_decoration_preamble(cs, e);
        const auto model_name(a.get_identifiable_model_name(c.name()));
        const auto product_name(a.get_product_name(c.name()));
a.stream() << "set(files \"\")" << std::endl;
a.stream() << "file(GLOB_RECURSE files RELATIVE" << std::endl;
a.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/\"" << std::endl;
a.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/*." << c.implementation_file_extension() << "\")" << std::endl;
a.stream() << std::endl;
        if (a.is_odb_facet_enabled() && !c.odb_targets().targets().empty()) {
a.stream() << "if(NOT ODB_LIBODB_FOUND)" << std::endl;
a.stream() << "    message(FATAL \"ODB include directories not defined.\")" << std::endl;
a.stream() << "endif()" << std::endl;
a.stream() << std::endl;
a.stream() << "set(odb_files \"\")" << std::endl;
a.stream() << "file(GLOB_RECURSE odb_files RELATIVE" << std::endl;
a.stream() << "   \"${CMAKE_CURRENT_SOURCE_DIR}/\"" << std::endl;
a.stream() << "   \"${CMAKE_CURRENT_SOURCE_DIR}/*.cxx\")" << std::endl;
a.stream() << "set(files ${files} ${odb_files})" << std::endl;
a.stream() << std::endl;
a.stream() << "add_library(" << model_name << " STATIC ${files})" << std::endl;
a.stream() << "set_target_properties(" << model_name << " PROPERTIES" << std::endl;
        }
    } // sbf
        return a.make_artefact();
}
}

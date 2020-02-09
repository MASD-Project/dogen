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
#include <boost/algorithm/string/case_conv.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "dogen.generation.cpp/types/fabric/cmakelists.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "dogen.generation.cpp/types/formatters/include_cmakelists_formatter.hpp"

namespace dogen::generation::cpp::formatters {

std::string include_cmakelists_formatter::static_id() {
    return traits::include_cmakelists_archetype();
}

std::string include_cmakelists_formatter::id() const {
    return static_id();
}

archetypes::location include_cmakelists_formatter::
archetype_location() const {
    static archetypes::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::cmake_facet(),
          include_cmakelists_formatter::static_id());
    return r;
}

const assets::meta_model::name& include_cmakelists_formatter::meta_name() const {
    static auto r(fabric::meta_name_factory::make_cmakelists_name());
    return r;
}

std::string include_cmakelists_formatter::family() const {
    return cpp::traits::cmake_family();
}

inclusion_support_types include_cmakelists_formatter::
inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path include_cmakelists_formatter::inclusion_path(
    const formattables::locator& /*l*/, const assets::meta_model::name& n) const {

    using namespace dogen::utility::log;
    using namespace dogen::generation::cpp::formatters;
    static logger lg(logger_factory(include_cmakelists_formatter::static_id()));

    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path include_cmakelists_formatter::full_path(
    const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_full_path_for_include_cmakelists(n, static_id());
}

std::list<std::string> include_cmakelists_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const assets::meta_model::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

extraction::meta_model::artefact include_cmakelists_formatter::
format(const context& ctx, const assets::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& c(a.as<fabric::cmakelists>(e));

    {
        const auto ts(assets::meta_model::technical_space::cmake);
        a.make_decoration_preamble(e, ts);
a.stream() << "add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/" << c.source_directory_name() << ")" << std::endl;
       if (a.is_tests_enabled()) {
a.stream() << "add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/" << c.tests_directory_name() << ")" << std::endl;
       }
a.stream() << std::endl;
a.stream() << "install(" << std::endl;
a.stream() << "    DIRECTORY " << c.include_directory_path() << "/" << std::endl;
a.stream() << "    DESTINATION " << c.include_directory_path() << "/" << std::endl;
a.stream() << "    COMPONENT headers" << std::endl;
a.stream() << "    FILES_MATCHING PATTERN \"*." << c.header_file_extension() << "\")" << std::endl;
    } // sbf
    return a.make_artefact();
}
}

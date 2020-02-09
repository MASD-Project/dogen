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
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.generation.cpp/types/fabric/object_odb_options.hpp"
#include "dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "dogen.generation.cpp/types/formatters/odb/traits.hpp"
#include "dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/odb/object_odb_options_formatter.hpp"

namespace dogen::generation::cpp::formatters::odb {

std::string object_odb_options_formatter::static_id() {
    return traits::object_odb_options_archetype();
}

std::string object_odb_options_formatter::id() const {
    static auto r(archetype_location().archetype());
    return r;
}

archetypes::location
object_odb_options_formatter::archetype_location() const {
    static archetypes::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(), object_odb_options_formatter::static_id());
    return r;
}

const assets::meta_model::name& object_odb_options_formatter::meta_name() const {
    static auto r(fabric::meta_name_factory::make_object_odb_options_name());
    return r;
}

std::string object_odb_options_formatter::family() const {
    return cpp::traits::odb_family();
}

inclusion_support_types
object_odb_options_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path object_odb_options_formatter::inclusion_path(
    const formattables::locator& /*l*/, const assets::meta_model::name& n) const {
    using namespace dogen::utility::log;
    static logger lg(logger_factory(
            "generation.cpp.formatters.odb.object_odb_options_formatter"));

        const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path object_odb_options_formatter::full_path(
    const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_full_path_for_odb_options(n, static_id());
}

std::list<std::string> object_odb_options_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const assets::meta_model::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

extraction::meta_model::artefact object_odb_options_formatter::
format(const context& ctx, const assets::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& ooo(a.as<fabric::object_odb_options>(e));

    {
        const auto ts(assets::meta_model::technical_space::odb);
        a.make_decoration_preamble(e, ts);
a.stream() << "# epilogue" << std::endl;
a.stream() << "--odb-epilogue " << ooo.epilogue() << std::endl;
a.stream() << std::endl;
        if (!ooo.include_regexes().empty()) {
a.stream() << "# regexes" << std::endl;
            for (const auto& regex : ooo.include_regexes())
a.stream() << "--include-regex " << regex << std::endl;
a.stream() << std::endl;
a.stream() << "# debug regexes" << std::endl;
a.stream() << "# --include-regex-trace" << std::endl;
a.stream() << std::endl;
a.stream() << "# make the header guards similar to dogen ones" << std::endl;
a.stream() << "--guard-prefix " << ooo.header_guard_prefix() << std::endl;
        }
    } // sbf
    return a.make_artefact();
}
}

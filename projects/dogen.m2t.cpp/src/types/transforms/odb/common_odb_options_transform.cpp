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
#include "dogen.logical/types/entities/orm/common_odb_options.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/odb/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/odb/common_odb_options_transform.hpp"

namespace dogen::m2t::cpp::transforms::odb {

std::string common_odb_options_transform::static_id() {
    return traits::common_odb_options_archetype();
}

std::string common_odb_options_transform::id() const {
    static auto r(archetype_location().archetype());
    return r;
}

physical::entities::location
common_odb_options_transform::archetype_location() const {
    static physical::entities::location
        r(cpp::traits::backend(), traits::facet(),
          common_odb_options_transform::static_id());
    return r;
}

const logical::entities::name& common_odb_options_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_orm_common_odb_options_name());
    return r;
}

inclusion_support_types
common_odb_options_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path common_odb_options_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {
    using namespace dogen::utility::log;
    static logger
        lg(logger_factory("m2t.cpp.formatters.odb.common_odb_options_transform"));

    const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path common_odb_options_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_odb_options(n, static_id());
}

std::list<std::string> common_odb_options_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const logical::entities::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

physical::entities::artefact common_odb_options_transform::
format(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    using logical::entities::orm::common_odb_options;
    const auto& o(a.as<common_odb_options>(e));

    {
        const auto ts(logical::entities::technical_space::odb);
        a.make_decoration_preamble(e, ts);

        if (!a.is_cpp_standard_98()) {
a.stream() << "# enable C++11" << std::endl;
a.stream() << "--std c++11" << std::endl;
a.stream() << std::endl;
        }

        if (!o.sql_name_case().empty()) {
a.stream() << "# casing" << std::endl;
a.stream() << "--sql-name-case " << o.sql_name_case() << std::endl;
a.stream() << std::endl;
        }

        if (o.databases().size() > 1) {
a.stream() << "# enable multi-database support" << std::endl;
a.stream() << "--multi-database static" << std::endl;
a.stream() << std::endl;
        }

        if (!o.databases().empty()) {
a.stream() << "# target databases" << std::endl;

            for (const auto& d : o.databases())
a.stream() << "--database " << d << std::endl;
a.stream() << std::endl;
        }
a.stream() << "# use the boost profile" << std::endl;
a.stream() << "--profile boost" << std::endl;
a.stream() << std::endl;
a.stream() << "# generate queries and embedded schemas" << std::endl;
a.stream() << "--generate-query" << std::endl;
a.stream() << "--generate-schema" << std::endl;
a.stream() << "--schema-format embedded" << std::endl;
a.stream() << std::endl;
a.stream() << "# force odb extensions to be different from dogen ones just in case." << std::endl;
a.stream() << "--ixx-suffix .ixx" << std::endl;
a.stream() << "--hxx-suffix .hxx" << std::endl;
a.stream() << "--cxx-suffix .cxx" << std::endl;
a.stream() << std::endl;
a.stream() << "# debug regexes" << std::endl;
a.stream() << "# --include-regex-trace" << std::endl;
    } // sbf
    return a.make_artefact();
}
}

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
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/odb/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/odb/primitive_odb_options_transform.hpp"

namespace dogen::m2t::cpp::transforms::odb {

std::string primitive_odb_options_transform::static_id() {
    return traits::primitive_odb_options_archetype();
}

std::string primitive_odb_options_transform::id() const {
    static auto r(archetype_location().archetype());
    return r;
}

physical::entities::location
primitive_odb_options_transform::archetype_location() const {
    static physical::entities::location
        r(cpp::traits::backend(), traits::facet(),
          primitive_odb_options_transform::static_id());
    return r;
}

const logical::entities::name& primitive_odb_options_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_primitive_name());
    return r;
}

inclusion_support_types
primitive_odb_options_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path primitive_odb_options_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {
    using namespace dogen::utility::log;
    static logger lg(logger_factory(
            "m2t.cpp.formatters.odb.primitive_odb_options_transform"));

        const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path primitive_odb_options_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_odb_options(n, static_id());
}

std::list<std::string> primitive_odb_options_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const logical::entities::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

physical::entities::artefact primitive_odb_options_transform::
apply(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& p(a.as<logical::entities::structural::primitive>(e));

    {
        const auto ts(logical::entities::technical_space::odb);
        a.make_decoration_preamble(e, ts);

        if (!p.orm_properties()) {
a.stream() << std::endl;
a.stream() << "#" << std::endl;
a.stream() << "# class has no ODB options defined." << std::endl;
a.stream() << "#" << std::endl;
        } else {
            const auto ooo(p.orm_properties()->odb_options());
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
        }
    } // sbf
    return a.make_artefact();
}
}

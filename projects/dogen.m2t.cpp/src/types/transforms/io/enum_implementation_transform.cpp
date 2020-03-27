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
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.physical/types/helpers/name_factory.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/io/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/io/enum_implementation_transform.hpp"

namespace dogen::m2t::cpp::transforms::io {

std::string enum_implementation_transform::static_id() {
    return traits::enum_implementation_archetype();
}

std::string enum_implementation_transform::id() const {
    return static_id();
}

physical::entities::name
enum_implementation_transform::physical_name() const {
    using physical::helpers::name_factory;
    static auto r(name_factory::make(cpp::traits::backend_qn(),
        cpp::traits::implementation_part(), traits::facet_qn(),
        enum_implementation_transform::static_id()));
    return r;
}

const logical::entities::name& enum_implementation_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_enumeration_name());
    return r;
}

inclusion_support_types enum_implementation_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path enum_implementation_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(enum_implementation_transform::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path enum_implementation_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_id());
}

std::list<std::string> enum_implementation_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    auto builder(f.make());

    builder.add(inclusion_constants::std::ostream());
    builder.add(inclusion_constants::std::stdexcept());
    builder.add(inclusion_constants::std::string());

    const auto eh_fn(traits::enum_header_archetype());
    builder.add(e.name(), eh_fn);
    return builder.build();
}

physical::entities::artefact enum_implementation_transform::
apply(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, physical_name().location(), false/*requires_header_guard*/);
    const auto& ye(a.as<logical::entities::structural::enumeration>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(ye.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
a.stream() << "std::ostream& operator<<(std::ostream& s, const " << ye.name().simple() << "& v) {" << std::endl;
a.stream() << "    s << \"{ \" << \"\\\"__type__\\\": \" << \"\\\"" << ye.name().simple() << "\\\", \" << \"\\\"value\\\": \";" << std::endl;
a.stream() << std::endl;
a.stream() << "    std::string attr;" << std::endl;
a.stream() << "    switch (v) {" << std::endl;
            for (const auto& en : ye.enumerators()) {
                if (a.is_cpp_standard_98())
a.stream() << "    case " << en.name().simple() << ":" << std::endl;
                else
a.stream() << "    case " << ye.name().simple() << "::" << en.name().simple() << ":" << std::endl;
a.stream() << "        attr = \"\\\"" << en.name().simple() << "\\\"\";" << std::endl;
a.stream() << "        break;" << std::endl;
            }
a.stream() << "    default:" << std::endl;
a.stream() << "        throw std::invalid_argument(\"Invalid value for " << ye.name().simple() << "\");" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "    s << attr << \" }\";" << std::endl;
a.stream() << "    return s;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
         } // snf
    } // sbf
    return a.make_artefact();
}

}

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
#include "dogen.text/types/formatters/sequence_formatter.hpp"
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/io/traits.hpp"
#include "dogen.text.cpp/types/transforms/io/enum_implementation_transform.hpp"

namespace dogen::text::cpp::transforms::io {

physical::entities::archetype enum_implementation_transform::static_archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::enum_implementation_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_enumeration_name().qualified().dot());
        return r;
    }());
    return r;
}

physical::entities::archetype enum_implementation_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types enum_implementation_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path enum_implementation_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(logger_factory(archetype().meta_name().qualified()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path enum_implementation_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, archetype().meta_name().qualified());
}

std::list<std::string> enum_implementation_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    auto builder(f.make());

    builder.add(inclusion_constants::std::ostream());
    builder.add(inclusion_constants::std::stdexcept());
    builder.add(inclusion_constants::std::string());

    const auto eh_fn(traits::enum_header_archetype_qn());
    builder.add(e.name(), eh_fn);
    return builder.build();
}

void enum_implementation_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    const auto& ye(ast.as<logical::entities::structural::enumeration>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(ast.make_namespaces(ye.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << std::endl;
ast.stream() << "std::ostream& operator<<(std::ostream& s, const " << ye.name().simple() << "& v) {" << std::endl;
ast.stream() << "    s << \"{ \" << \"\\\"__type__\\\": \" << \"\\\"" << ye.name().simple() << "\\\", \" << \"\\\"value\\\": \";" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    std::string attr;" << std::endl;
ast.stream() << "    switch (v) {" << std::endl;
            for (const auto& en : ye.enumerators()) {
                if (ast.is_cpp_standard_98())
ast.stream() << "    case " << en.name().simple() << ":" << std::endl;
                else
ast.stream() << "    case " << ye.name().simple() << "::" << en.name().simple() << ":" << std::endl;
ast.stream() << "        attr = \"\\\"" << en.name().simple() << "\\\"\";" << std::endl;
ast.stream() << "        break;" << std::endl;
            }
ast.stream() << "    default:" << std::endl;
ast.stream() << "        throw std::invalid_argument(\"Invalid value for " << ye.name().simple() << "\");" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << "    s << attr << \" }\";" << std::endl;
ast.stream() << "    return s;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
         } // snf
    } // sbf
    ast.update_artefact();
}

}

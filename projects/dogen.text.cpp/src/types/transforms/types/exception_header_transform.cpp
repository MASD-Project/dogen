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
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/io/traits.hpp"
#include "dogen.text.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/hash/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/exception_header_transform.hpp"

namespace dogen::text::cpp::transforms::types {

physical::entities::archetype exception_header_transform::static_archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::exception_header_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_exception_name().qualified().dot());
        return r;
    }());
    return r;
}

physical::entities::archetype exception_header_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types exception_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path exception_header_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().qualified());
}

boost::filesystem::path exception_header_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, archetype().meta_name().qualified());
}

std::list<std::string> exception_header_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& /*e*/) const {
    auto builder(f.make());
    builder.add(inclusion_constants::std::string());
    builder.add(inclusion_constants::boost::exception::info());
    return builder.build();
}

void exception_header_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, archetype().meta_name(), true/*requires_header_guard*/, a);
    const auto& ye(ast.as<logical::entities::structural::exception>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(ast.make_namespaces(ye.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << std::endl;
            ast.comment(ye.documentation());
ast.stream() << "class " << ye.name().simple() << " : public virtual std::exception, public virtual boost::exception {" << std::endl;
ast.stream() << "public:" << std::endl;
            if (ast.is_cpp_standard_98()) {
ast.stream() << "    " << ye.name().simple() << "() {}" << std::endl;
ast.stream() << "    ~" << ye.name().simple() << "() {}" << std::endl;
            } else {
ast.stream() << "    " << ye.name().simple() << "() = default;" << std::endl;
ast.stream() << "    ~" << ye.name().simple() << "()" << ast.make_noexcept_keyword_text() << " = default;" << std::endl;
            }
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    explicit " << ye.name().simple() << "(const std::string& message) : message_(message) { }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
            if (ast.is_cpp_standard_98()) {
                // Note: we are using BOOST_NOEXCEPT here by design. The problem is
                // users may include this header in a C++ 98 project or in a C++ > 11 project;
                // and we need to have different behaviours. Depending on this inclusion.
                // If we do not, we will cause compilation errors when including C++ 98 code
                // on a C++ 11 project. This is because the standard library will have noexcept
                // but we won't (as we were generated for C++ 98), so we'd be weakening the exception
                // guarantees. By using the boost macro we will do the right thing hopefully.
                // And since we already need boost for exception, we should be ok.
ast.stream() << "    const char* what() const BOOST_NOEXCEPT { return(message_.c_str()); }" << std::endl;
            } else {
ast.stream() << "    const char* what() const" << ast.make_noexcept_keyword_text() << " { return(message_.c_str()); }" << std::endl;
            }
ast.stream() << std::endl;
ast.stream() << "private:" << std::endl;
ast.stream() << "    const std::string message_;" << std::endl;
ast.stream() << "};" << std::endl;
ast.stream() << std::endl;
        } // snf
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
}

}

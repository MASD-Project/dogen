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
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/types/primitive_header_transform.hpp"

namespace dogen::text::cpp::transforms::types {
physical::entities::archetype primitive_header_transform::static_archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::primitive_header_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_primitive_name().qualified().dot());
        return r;
    }());
    return r;
}

physical::entities::archetype primitive_header_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types primitive_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path primitive_header_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().qualified());
}

boost::filesystem::path primitive_header_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, archetype().meta_name().qualified());
}

std::list<std::string> primitive_header_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    using logical::entities::structural::primitive;
    const auto& p(assistant::as<primitive>(e));
    auto builder(f.make());

    // algorithm: domain headers need it for the swap function.
    builder.add(inclusion_constants::std::algorithm());

    using ser = transforms::serialization::traits;
    const auto ser_fwd_arch(ser::primitive_forward_declarations_archetype_qn());
    builder.add(p.name(), ser_fwd_arch);

    const auto carch(traits::canonical_archetype());
    builder.add(p.value_attribute().parsed_type().current(), carch);

    return builder.build();
}

void primitive_header_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, archetype().meta_name(), true/*requires_header_guard*/, a);
    const auto& p(ast.as<logical::entities::structural::primitive>(e));

    const auto sn(p.name().simple());
    const auto qn(ast.get_qualified_name(p.name()));
    {

        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(ast.make_namespaces(p.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            const auto attr(p.value_attribute());

            ast.comment(p.documentation());
ast.stream() << "class " << sn << " final {" << std::endl;
ast.stream() << "public:" << std::endl;
            /*
             * Compiler generated constructors and destructors.
             */
            if (!ast.requires_manual_default_constructor())
ast.stream() << "    " << sn << "() = default;" << std::endl;
ast.stream() << "    " << sn << "(const " << sn << "&) = default;" << std::endl;
            if (!ast.requires_manual_move_constructor())
ast.stream() << "    " << sn << "(" << sn << "&&) = default;" << std::endl;
ast.stream() << "    ~" << sn << "() = default;" << std::endl;
            if (p.is_immutable())
ast.stream() << "    " << sn << "& operator=(const " << sn << "&) = delete;" << std::endl;
            /*
             * Manually generated default constructor.
             */
            if (ast.requires_manual_default_constructor()) {
ast.stream() << "public:" << std::endl;
ast.stream() << "    " << sn << "();" << std::endl;
ast.stream() << std::endl;
            }

            /*
             * Manually generated move constructor.
             */
            if (ast.requires_manual_move_constructor()) {
ast.stream() << "public:" << std::endl;
ast.stream() << "    " << sn << "(" << sn << "&& rhs);" << std::endl;
ast.stream() << std::endl;
            }

            /*
             * Manually generated complete constructor.
             */
ast.stream() << "public:" << std::endl;
ast.stream() << "    explicit " << sn << "(const " << ast.get_qualified_name(attr.parsed_type()) << ast.make_by_ref_text(attr) << " " << attr.name().simple() << ");" << std::endl;
ast.stream() << std::endl;
            /*
             * Serialisaton Friends
             */
            if (ast.is_serialization_enabled()) {
ast.stream() << "private:" << std::endl;
ast.stream() << "    template<typename Archive>" << std::endl;
ast.stream() << "    friend void boost::serialization::save(Archive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    template<typename Archive>" << std::endl;
ast.stream() << "    friend void boost::serialization::load(Archive& ar, " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << std::endl;
            }

            /*
             * Getters and setters.
             */
ast.stream() << "public:" << std::endl;
            ast.comment_start_method_group(attr.documentation(), !attr.is_immutable());
            if (attr.parsed_type().is_current_simple_type()) {
ast.stream() << "    " << ast.get_qualified_name(attr.parsed_type()) << " " << attr.name().simple() << "() const;" << std::endl;
                if (attr.is_immutable()) {
ast.stream() << std::endl;

                } else {
ast.stream() << "    " << ast.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << ast.get_qualified_name(attr.parsed_type()) << ast.make_by_ref_text(attr) << " v);" << std::endl;
                }
            } else {
ast.stream() << "    const " << ast.get_qualified_name(attr.parsed_type()) << "& " << attr.name().simple() << "() const;" << std::endl;
                if (attr.is_immutable()) {
ast.stream() << std::endl;
                } else {
ast.stream() << "    " << ast.get_qualified_name(attr.parsed_type()) << ast.make_by_ref_text(attr) << " " << attr.name().simple() << "();" << std::endl;
ast.stream() << "    " << ast.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << ast.get_qualified_name(attr.parsed_type()) << ast.make_by_ref_text(attr) << " v);" << std::endl;
ast.stream() << "    " << ast.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << ast.get_qualified_name(attr.parsed_type()) << "&& v);" << std::endl;
                }
            }
            ast.comment_end_method_group(attr.documentation(), !attr.is_immutable());

            /*
             * Explicit cast.
             */
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    explicit operator " << ast.get_qualified_name(attr.parsed_type()) << "() const {" << std::endl;
ast.stream() << "        return " << attr.member_variable_name() << ";" << std::endl;
ast.stream() << "    }" << std::endl;
            /*
             * Equality.
             */
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    bool operator==(const " << sn << "& rhs) const;" << std::endl;
ast.stream() << "    bool operator!=(const " << sn << "& rhs) const {" << std::endl;
ast.stream() << "        return !this->operator==(rhs);" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
            /*
             * Swap and assignment.
             */
ast.stream() << "public:" << std::endl;
ast.stream() << "    void swap(" << sn << "& other)" << ast.make_noexcept_keyword_text() << ";" << std::endl;
            if (!p.is_immutable()) {
ast.stream() << "    " << sn << "& operator=(" << sn << " other);" << std::endl;
            }

            /*
             * Member variables.
             */
ast.stream() << std::endl;
ast.stream() << "private:" << std::endl;
ast.stream() << "    " << ast.get_qualified_name(attr.parsed_type()) << " " << attr.member_variable_name() << ";" << std::endl;
ast.stream() << "};" << std::endl;
ast.stream() << std::endl;
        } // snf

        if (!p.is_immutable()) {
ast.stream() << std::endl;
ast.stream() << "namespace std {" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template<>" << std::endl;
ast.stream() << "inline void swap(" << std::endl;
ast.stream() << "    " << qn << "& lhs," << std::endl;
ast.stream() << "    " << qn << "& rhs) {" << std::endl;
ast.stream() << "    lhs.swap(rhs);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "}" << std::endl;
        }
ast.stream() << std::endl;
    } //ah  sbf
    ast.update_artefact();
}

}

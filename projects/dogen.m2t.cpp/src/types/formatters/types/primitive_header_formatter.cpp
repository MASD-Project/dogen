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
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/formatters/traits.hpp"
#include "dogen.m2t.cpp/types/formatters/types/traits.hpp"
#include "dogen.m2t.cpp/types/formatters/serialization/traits.hpp"
#include "dogen.m2t.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/formatters/assistant.hpp"
#include "dogen.m2t.cpp/types/formatters/types/primitive_header_formatter.hpp"

namespace dogen::m2t::cpp::formatters::types {

std::string primitive_header_formatter::static_id() {
    return traits::primitive_header_archetype();
}

std::string primitive_header_formatter::id() const {
    return static_id();
}

physical::entities::location
primitive_header_formatter::archetype_location() const {
    static physical::entities::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          primitive_header_formatter::static_id());
    return r;
}

const logical::entities::name& primitive_header_formatter::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_primitive_name());
    return r;
}

std::string primitive_header_formatter::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types primitive_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path primitive_header_formatter::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path primitive_header_formatter::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> primitive_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    using logical::entities::structural::primitive;
    const auto& p(assistant::as<primitive>(e));
    auto builder(f.make());

    // algorithm: domain headers need it for the swap function.
    builder.add(inclusion_constants::std::algorithm());

    using ser = formatters::serialization::traits;
    const auto ser_fwd_arch(ser::primitive_forward_declarations_archetype());
    builder.add(p.name(), ser_fwd_arch);

    const auto carch(traits::canonical_archetype());
    builder.add(p.value_attribute().parsed_type().current(), carch);

    return builder.build();
}

physical::entities::artefact primitive_header_formatter::
format(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location(), true/*requires_header_guard*/);
    const auto& p(a.as<logical::entities::structural::primitive>(e));

    const auto sn(p.name().simple());
    const auto qn(a.get_qualified_name(p.name()));
    {

        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(p.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            const auto attr(p.value_attribute());

            a.comment(p.documentation());
a.stream() << "class " << sn << " final {" << std::endl;
a.stream() << "public:" << std::endl;
            /*
             * Compiler generated constructors and destructors.
             */
            if (!a.requires_manual_default_constructor())
a.stream() << "    " << sn << "() = default;" << std::endl;
a.stream() << "    " << sn << "(const " << sn << "&) = default;" << std::endl;
            if (!a.requires_manual_move_constructor())
a.stream() << "    " << sn << "(" << sn << "&&) = default;" << std::endl;
a.stream() << "    ~" << sn << "() = default;" << std::endl;
            if (p.is_immutable())
a.stream() << "    " << sn << "& operator=(const " << sn << "&) = delete;" << std::endl;
            /*
             * Manually generated default constructor.
             */
            if (a.requires_manual_default_constructor()) {
a.stream() << "public:" << std::endl;
a.stream() << "    " << sn << "();" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Manually generated move constructor.
             */
            if (a.requires_manual_move_constructor()) {
a.stream() << "public:" << std::endl;
a.stream() << "    " << sn << "(" << sn << "&& rhs);" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Manually generated complete constructor.
             */
a.stream() << "public:" << std::endl;
a.stream() << "    explicit " << sn << "(const " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " " << attr.name().simple() << ");" << std::endl;
a.stream() << std::endl;
            /*
             * Serialisaton Friends
             */
            if (a.is_serialization_enabled()) {
a.stream() << "private:" << std::endl;
a.stream() << "    template<typename Archive>" << std::endl;
a.stream() << "    friend void boost::serialization::save(Archive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
a.stream() << "    template<typename Archive>" << std::endl;
a.stream() << "    friend void boost::serialization::load(Archive& ar, " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Getters and setters.
             */
a.stream() << "public:" << std::endl;
            a.comment_start_method_group(attr.documentation(), !attr.is_immutable());
            if (attr.parsed_type().is_current_simple_type()) {
a.stream() << "    " << a.get_qualified_name(attr.parsed_type()) << " " << attr.name().simple() << "() const;" << std::endl;
                if (attr.is_immutable()) {
a.stream() << std::endl;

                } else {
a.stream() << "    " << a.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " v);" << std::endl;
                }
            } else {
a.stream() << "    const " << a.get_qualified_name(attr.parsed_type()) << "& " << attr.name().simple() << "() const;" << std::endl;
                if (attr.is_immutable()) {
a.stream() << std::endl;
                } else {
a.stream() << "    " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " " << attr.name().simple() << "();" << std::endl;
a.stream() << "    " << a.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " v);" << std::endl;
a.stream() << "    " << a.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << a.get_qualified_name(attr.parsed_type()) << "&& v);" << std::endl;
                }
            }
            a.comment_end_method_group(attr.documentation(), !attr.is_immutable());

            /*
             * Explicit cast.
             */
a.stream() << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    explicit operator " << a.get_qualified_name(attr.parsed_type()) << "() const {" << std::endl;
a.stream() << "        return " << attr.member_variable_name() << ";" << std::endl;
a.stream() << "    }" << std::endl;
            /*
             * Equality.
             */
a.stream() << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    bool operator==(const " << sn << "& rhs) const;" << std::endl;
a.stream() << "    bool operator!=(const " << sn << "& rhs) const {" << std::endl;
a.stream() << "        return !this->operator==(rhs);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
            /*
             * Swap and assignment.
             */
a.stream() << "public:" << std::endl;
a.stream() << "    void swap(" << sn << "& other)" << a.make_noexcept_keyword_text() << ";" << std::endl;
            if (!p.is_immutable()) {
a.stream() << "    " << sn << "& operator=(" << sn << " other);" << std::endl;
            }

            /*
             * Member variables.
             */
a.stream() << std::endl;
a.stream() << "private:" << std::endl;
a.stream() << "    " << a.get_qualified_name(attr.parsed_type()) << " " << attr.member_variable_name() << ";" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
        } // snf

        if (!p.is_immutable()) {
a.stream() << std::endl;
a.stream() << "namespace std {" << std::endl;
a.stream() << std::endl;
a.stream() << "template<>" << std::endl;
a.stream() << "inline void swap(" << std::endl;
a.stream() << "    " << qn << "& lhs," << std::endl;
a.stream() << "    " << qn << "& rhs) {" << std::endl;
a.stream() << "    lhs.swap(rhs);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "}" << std::endl;
        }
a.stream() << std::endl;
    } //ah  sbf
    return a.make_artefact();
}

}

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
#include "dogen/quilt.cpp/types/formatters/types/primitive_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/io/inserter_implementation_helper.hpp"
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/utility/log/logger.hpp"
#include <boost/throw_exception.hpp>
#include <boost/make_shared.hpp>
#include <typeinfo>

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace types {

std::string primitive_implementation_formatter::static_artefact() {
    return traits::primitive_implementation_archetype();
}

std::string primitive_implementation_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location
primitive_implementation_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::family(),  cpp::traits::kernel(),
          traits::facet(),
          primitive_implementation_formatter::static_artefact());
    return r;
}

std::type_index primitive_implementation_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(yarn::primitive)));
    return r;
}

inclusion_support_types primitive_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path primitive_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const yarn::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(primitive_implementation_formatter::static_artefact()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path primitive_implementation_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_artefact());
}

std::list<std::string> primitive_implementation_formatter::inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& f,
    const yarn::element& e) const {
    const auto& o(assistant::as<yarn::primitive>(static_artefact(), e));
    auto builder(f.make());

    const auto ch_arch(traits::primitive_header_archetype());
    builder.add(o.name(), ch_arch);
    return builder.build();
}

dogen::formatters::artefact primitive_implementation_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), false/*requires_header_guard*/, id);
    const auto& p(a.as<yarn::primitive>(static_artefact(), e));

    const auto sn(p.name().simple());
    const auto qn(a.get_qualified_name(p.name()));
    {

        auto sbf(a.make_scoped_boilerplate_formatter());
        {
            const auto ns(a.make_namespaces(p.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            const auto attr(p.value_attribute());

            /*
             * Default constructor.
             */
            if (a.requires_manual_default_constructor()) {
a.stream() << std::endl;
a.stream() << sn << "::" << sn << "()" << std::endl;
a.stream() << "    : " << a.make_member_variable_name(attr) << "(static_cast<" << a.get_qualified_name(attr.parsed_type()) << ">(0)) { }" << std::endl;
            }

            /*
             * Move constructor.
             */
            if (a.requires_manual_move_constructor()) {
a.stream() << std::endl;
a.stream() << sn << "::" << sn << "(" << sn << "&& rhs)" << std::endl;
a.stream() << "    : " << a.make_member_variable_name(attr) << "(std::move(rhs." << a.make_member_variable_name(attr) << ")) { }" << std::endl;
            }

            /*
             * Complete constructor.
             */
a.stream() << std::endl;
a.stream() << sn << "::" << sn << "(const " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " " << attr.name().simple() << ")" << std::endl;
a.stream() << "    : " << a.make_member_variable_name(attr) << "(" << attr.name().simple() << ") { }" << std::endl;
a.stream() << std::endl;
            /*
             * Getters and setters
             */
a.stream() << a.get_qualified_name(attr.parsed_type()) << " " << sn << "::" << attr.name().simple() << "() const {" << std::endl;
a.stream() << "    return " << a.make_member_variable_name(attr) << ";" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            if (!p.is_immutable()) {
a.stream() << "void " << sn << "::" << attr.name().simple() << "(const " << a.get_qualified_name(attr.parsed_type()) << " v) {" << std::endl;
a.stream() << "    " << a.make_member_variable_name(attr) << " = v;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Equality.
             */
a.stream() << "bool " << sn << "::operator==(const " << sn << "& rhs) const {" << std::endl;
a.stream() << "    return " << a.make_member_variable_name(attr) << " == rhs." << a.make_member_variable_name(attr) << ";" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            /*
             * Swap and assignment.
             */
            if (!p.is_immutable()) {
a.stream() << "void " << sn << "::swap(" << sn << "& other) noexcept {" << std::endl;
a.stream() << "    using std::swap;" << std::endl;
a.stream() << "    swap(" << a.make_member_variable_name(attr) << ", other." << a.make_member_variable_name(attr) << ");" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << sn << "& " << sn << "::operator=(" << sn << " other) {" << std::endl;
a.stream() << "    using std::swap;" << std::endl;
a.stream() << "    swap(*this, other);" << std::endl;
a.stream() << "    return *this;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }
        } // snf
    } // sbf
    return a.make_artefact();
}
} } } } }

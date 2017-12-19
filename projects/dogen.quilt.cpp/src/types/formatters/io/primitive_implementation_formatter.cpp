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
#include "dogen.quilt.cpp/types/formatters/io/primitive_implementation_formatter.hpp"
#include "dogen.quilt.cpp/types/formatters/io/inserter_implementation_helper.hpp"
#include "dogen.quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen.quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen.quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen.quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen.quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen.quilt.cpp/types/formatters/assistant.hpp"
#include "dogen.quilt.cpp/types/formatters/traits.hpp"
#include "dogen.quilt.cpp/types/traits.hpp"
#include "dogen.yarn/types/helpers/meta_name_factory.hpp"
#include "dogen.yarn/types/meta_model/primitive.hpp"
#include "dogen.formatting/types/sequence_formatter.hpp"
#include "dogen.utility/log/logger.hpp"
#include <boost/throw_exception.hpp>
#include <boost/make_shared.hpp>

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace io {

std::string primitive_implementation_formatter::static_id() {
    return traits::primitive_implementation_archetype();
}

std::string primitive_implementation_formatter::id() const {
    return static_id();
}

annotations::archetype_location
primitive_implementation_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::kernel(),  cpp::traits::backend(),
          traits::facet(),
          primitive_implementation_formatter::static_id());
    return r;
}

const yarn::meta_model::name& primitive_implementation_formatter::meta_name() const {
    using yarn::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_primitive_name());
    return r;
}

std::string primitive_implementation_formatter::family() const {
    return cpp::traits::implementation_family();
}

inclusion_support_types primitive_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path primitive_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const yarn::meta_model::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(primitive_implementation_formatter::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path primitive_implementation_formatter::full_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_id());
}

std::list<std::string>
primitive_implementation_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const yarn::meta_model::element& e) const {

    using yarn::meta_model::primitive;
    const auto& p(assistant::as<primitive>(e));
    auto builder(f.make());
    const auto ph_fn(traits::primitive_header_archetype());
    builder.add(p.name(), ph_fn);

    const auto io_carch(formatters::io::traits::canonical_archetype());
    const auto self_fn(primitive_implementation_formatter::static_id());
    const bool io_enabled(builder.is_enabled(p.name(), self_fn));

    if (!io_enabled)
        return builder.build();

    const auto os(inclusion_constants::std::ostream());
    builder.add(os);
    builder.add(p.value_attribute().parsed_type().current(), io_carch);

    return builder.build();
}

yarn::meta_model::artefact primitive_implementation_formatter::
format(const context& ctx, const yarn::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& p(a.as<yarn::meta_model::primitive>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        a.add_helper_methods(p.name().id());

        {
            const auto ns(a.make_namespaces(p.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            const auto sn(p.name().simple());
            const auto qn(a.get_qualified_name(p.name()));
            const auto attr(p.value_attribute());
a.stream() << std::endl;
a.stream() << "std::ostream& operator<<(std::ostream& s, const " << sn << "& v) {" << std::endl;
            if (a.requires_stream_manipulators()) {
a.stream() << "    boost::io::ios_flags_saver ifs(s);" << std::endl;
a.stream() << "    s.setf(std::ios_base::boolalpha);" << std::endl;
a.stream() << "    s.setf(std::ios::fixed, std::ios::floatfield);" << std::endl;
a.stream() << "    s.precision(6);" << std::endl;
a.stream() << "    s.setf(std::ios::showpoint);" << std::endl;
            }

            const std::string variable_name = "v." + a.make_getter_setter_name(attr) + "()";
a.stream() << std::endl;
a.stream() << "    s << \" { \"" << std::endl;
a.stream() << "      << \"\\\"__type__\\\": \" << \"\\\"" << qn << "\\\"\" << \", \"" << std::endl;
a.stream() << "      << \"\\\"" << attr.name().simple() << "\\\": \" << " << a.streaming_for_type(attr.parsed_type().current(), variable_name) << std::endl;
a.stream() << "      << \" }\";" << std::endl;
a.stream() << std::endl;
a.stream() << "    return s;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}
} } } } }

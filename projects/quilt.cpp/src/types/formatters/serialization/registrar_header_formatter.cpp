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
#include "dogen/quilt.cpp/types/formatters/serialization/registrar_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/fabric/meta_name_factory.hpp"
#include "dogen/quilt.cpp/types/fabric/registrar.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include <boost/make_shared.hpp>
#include <typeinfo>
#include "dogen/formatters/types/cpp/scoped_boilerplate_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace serialization {

std::string registrar_header_formatter::static_artefact() {
    return traits::registrar_header_archetype();
}

std::string registrar_header_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location
registrar_header_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::family(), cpp::traits::kernel(),
          traits::facet(),
          registrar_header_formatter::static_artefact());
    return r;
}

std::type_index registrar_header_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(fabric::registrar)));
    return r;
}

const yarn::meta_model::name& registrar_header_formatter::meta_name() const {
    using fabric::meta_name_factory;
    static auto r(meta_name_factory::make_registrar_name());
    return r;
}

inclusion_support_types registrar_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path registrar_header_formatter::inclusion_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_artefact());
}

boost::filesystem::path registrar_header_formatter::full_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_artefact());
}

std::list<std::string> registrar_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const yarn::meta_model::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

dogen::formatters::artefact registrar_header_formatter::
format(const context& ctx, const yarn::meta_model::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), false/*requires_header_guard*/, id);
    const auto& rg(a.as<fabric::registrar>(static_artefact(), e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(rg.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
a.stream() << "template<typename Archive>" << std::endl;
a.stream() << "void register_types(Archive& ar);" << std::endl;
a.stream() << std::endl;
        } // snf
a.stream() << std::endl;

    } // sbf
    return a.make_artefact();
}

} } } } }

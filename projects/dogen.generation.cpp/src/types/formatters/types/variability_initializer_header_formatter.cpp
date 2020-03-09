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
#include "dogen.assets/types/meta_model/variability/initializer.hpp"
#include "dogen.assets/types/helpers/meta_name_factory.hpp"
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen.generation.cpp/types/formatters/io/traits.hpp"
#include "dogen.generation.cpp/types/formatters/serialization/traits.hpp"
#include "dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/hash/traits.hpp"
#include "dogen.generation.cpp/types/formatters/types/variability_initializer_header_formatter.hpp"

namespace dogen::generation::cpp::formatters::types {

std::string variability_initializer_header_formatter::static_id() {
    return traits::variability_initializer_header_archetype();
}

std::string variability_initializer_header_formatter::id() const {
    return static_id();
}

archetypes::location
variability_initializer_header_formatter::archetype_location() const {
    static archetypes::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          variability_initializer_header_formatter::static_id());
    return r;
}

const assets::meta_model::name& variability_initializer_header_formatter::meta_name() const {
    using assets::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_variability_initializer_name());
    return r;
}

std::string variability_initializer_header_formatter::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types variability_initializer_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path variability_initializer_header_formatter::inclusion_path(
    const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path variability_initializer_header_formatter::full_path(
    const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> variability_initializer_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const assets::meta_model::element& /*e*/) const {

    using assets::meta_model::variability::initializer;
    auto builder(f.make());
    builder.add("\"dogen.variability/types/meta_model/feature_template.hpp\"");
    builder.add("\"dogen.variability/types/helpers/registrar.hpp\"");

    return builder.build();
}

extraction::meta_model::artefact variability_initializer_header_formatter::
format(const context& ctx, const assets::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), true/*requires_header_guard*/);
    const auto& o(a.as<assets::meta_model::variability::initializer>(e));

    {
        const auto sn(o.name().simple());
        const auto qn(a.get_qualified_name(o.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(o.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
a.stream() << "/**" << std::endl;
a.stream() << " * @brief Registers all of the available feature templates with registrar." << std::endl;
a.stream() << " */" << std::endl;
a.stream() << "class " << sn << " final {" << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    static void register_entities(variability::helpers::registrar& rg);" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
        }
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}
}

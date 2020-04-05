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
#include "dogen.logical/types/entities/variability/initializer.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/io/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/hash/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/variability_initializer_header_transform.hpp"

namespace dogen::m2t::cpp::transforms::types {

std::string variability_initializer_header_transform::static_id() {
    return traits::variability_initializer_header_archetype_qn();
}

std::string variability_initializer_header_transform::id() const {
    return static_id();
}

physical::entities::meta_name
variability_initializer_header_transform::physical_name() const {
    using physical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make(cpp::traits::backend_sn(),
        traits::facet_sn(), traits::variability_initializer_header_archetype_sn()));
    return r;
}

const logical::entities::name& variability_initializer_header_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_variability_initializer_name());
    return r;
}

inclusion_support_types variability_initializer_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path variability_initializer_header_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path variability_initializer_header_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> variability_initializer_header_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& /*e*/) const {

    using logical::entities::variability::initializer;
    auto builder(f.make());
    builder.add("\"dogen.variability/types/entities/feature_template.hpp\"");
    builder.add("\"dogen.variability/types/helpers/registrar.hpp\"");

    return builder.build();
}

physical::entities::artefact variability_initializer_header_transform::
apply(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, physical_name(), true/*requires_header_guard*/);
    const auto& o(a.as<logical::entities::variability::initializer>(e));

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

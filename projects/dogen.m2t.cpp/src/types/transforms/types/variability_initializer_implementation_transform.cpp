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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/variability/initializer.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/io/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/io/inserter_implementation_helper.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/variability_initializer_implementation_transform.hpp"

namespace dogen::m2t::cpp::transforms::types {

std::string variability_initializer_implementation_transform::static_id() {
    return traits::variability_initializer_implementation_archetype_qn();
}

std::string variability_initializer_implementation_transform::id() const {
    return static_id();
}

physical::entities::meta_name
variability_initializer_implementation_transform::physical_meta_name() const {
    using physical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make(cpp::traits::backend_sn(),
        traits::facet_sn(), traits::variability_initializer_implementation_archetype_sn()));
    return r;
}

physical::entities::archetype variability_initializer_implementation_transform::archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using physical::helpers::meta_name_factory;
        r.meta_name(meta_name_factory::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::variability_initializer_implementation_archetype_sn()));
        return r;
    }());
    return r;
}

const logical::entities::name& variability_initializer_implementation_transform::logical_meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_variability_initializer_name());
    return r;
}

inclusion_support_types variability_initializer_implementation_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path variability_initializer_implementation_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(variability_initializer_implementation_transform::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path variability_initializer_implementation_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_id());
}

std::list<std::string> variability_initializer_implementation_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    using logical::entities::variability::initializer;
    const auto& o(assistant::as<initializer>(e));
    auto builder(f.make());

    const auto ch_arch(traits::variability_initializer_header_archetype_qn());
    builder.add(o.name(), ch_arch);

    const auto ftb_arch(traits::feature_template_bundle_header_archetype_qn());
    builder.add(o.feature_template_bundles(), ftb_arch);

    const auto fb_arch(traits::feature_bundle_header_archetype_qn());
    builder.add(o.feature_bundles(), fb_arch);

    return builder.build();
}

void variability_initializer_implementation_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, physical_meta_name(), false/*requires_header_guard*/, a);
    const auto& o(ast.as<logical::entities::variability::initializer>(e));

    {
        const auto sn(o.name().simple());
        const auto qn(ast.get_qualified_name(o.name()));
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        ast.add_helper_methods(o.name().qualified().dot());

        {
            const auto ns(ast.make_namespaces(o.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << std::endl;
ast.stream() << "void " << sn << "::" << std::endl;
ast.stream() << "register_entities(variability::helpers::registrar& rg) {" << std::endl;
            for (const auto& n : o.feature_template_bundles())
ast.stream() << "    rg.register_templates(" << n.qualified().colon() << "::make_templates());" << std::endl;
            if (!o.feature_bundles().empty()) {
                for (const auto& n : o.feature_bundles())
ast.stream() << "    rg.register_features(" << n.qualified().colon() << "::make_features());" << std::endl;
            }
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
        } // snf
    } // sbf
    ast.update_artefact();
}

}

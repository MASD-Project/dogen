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
#include "dogen.assets/types/meta_model/variability/feature_template_initializer.hpp"
#include "dogen.assets/types/helpers/meta_name_factory.hpp"
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "dogen.generation.cpp/types/formatters/io/traits.hpp"
#include "dogen.generation.cpp/types/formatters/io/inserter_implementation_helper.hpp"
#include "dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/types/feature_template_initializer_implementation_formatter.hpp"

namespace dogen::generation::cpp::formatters::types {

std::string feature_template_initializer_implementation_formatter::static_id() {
    return traits::feature_template_initializer_implementation_archetype();
}

std::string feature_template_initializer_implementation_formatter::id() const {
    return static_id();
}

archetypes::location
feature_template_initializer_implementation_formatter::archetype_location() const {
    static archetypes::location
        r(cpp::traits::kernel(),  cpp::traits::backend(),
          traits::facet(),
          feature_template_initializer_implementation_formatter::static_id());
    return r;
}

const assets::meta_model::name& feature_template_initializer_implementation_formatter::meta_name() const {
    using assets::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_variability_feature_template_initializer_name());
    return r;
}

std::string feature_template_initializer_implementation_formatter::family() const {
    return cpp::traits::implementation_family();
}

inclusion_support_types feature_template_initializer_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path feature_template_initializer_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const assets::meta_model::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(feature_template_initializer_implementation_formatter::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path feature_template_initializer_implementation_formatter::full_path(
    const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_id());
}

std::list<std::string> feature_template_initializer_implementation_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const assets::meta_model::element& e) const {
    using assets::meta_model::variability::feature_template_initializer;
    const auto& o(assistant::as<feature_template_initializer>(e));
    auto builder(f.make());

    const auto ch_arch(traits::feature_template_initializer_header_archetype());
    builder.add(o.name(), ch_arch);

    const auto fb_arch(traits::feature_template_bundle_header_archetype());
    builder.add(o.bundles(), fb_arch);

    return builder.build();
}

extraction::meta_model::artefact feature_template_initializer_implementation_formatter::
format(const context& ctx, const assets::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& o(a.as<assets::meta_model::variability::feature_template_initializer>(e));

    {
        const auto sn(o.name().simple());
        const auto qn(a.get_qualified_name(o.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        a.add_helper_methods(o.name().qualified().dot());

        {
            const auto ns(a.make_namespaces(o.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
a.stream() << "void " << sn << "::" << std::endl;
a.stream() << "register_templates(variability::helpers::feature_template_registrar& rg) {" << std::endl;
            for (const auto& n : o.bundles())
a.stream() << "    rg.register_templates(" << n.qualified().colon() << "::make_templates());" << std::endl;
a.stream() << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}

}

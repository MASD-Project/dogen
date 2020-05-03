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
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.variability/types/helpers/enum_mapper.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/variability/feature_template_bundle.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.text/types/formatters/sequence_formatter.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/io/traits.hpp"
#include "dogen.text.cpp/types/transforms/io/inserter_implementation_helper.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/feature_template_bundle_implementation_transform.hpp"

namespace dogen::text::cpp::transforms::types {

physical::entities::archetype feature_template_bundle_implementation_transform::static_archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::feature_template_bundle_implementation_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_variability_feature_template_bundle_name().qualified().dot());
        return r;
    }());
    return r;
}

physical::entities::archetype feature_template_bundle_implementation_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types feature_template_bundle_implementation_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path feature_template_bundle_implementation_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(logger_factory(archetype().meta_name().qualified()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path feature_template_bundle_implementation_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, archetype().meta_name().qualified());
}

std::list<std::string> feature_template_bundle_implementation_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    using logical::entities::variability::feature_template_bundle;
    const auto& fb(assistant::as<feature_template_bundle>(e));
    auto builder(f.make());

    const auto ch_arch(traits::feature_template_bundle_header_archetype_qn());
    builder.add(fb.name(), ch_arch);
    builder.add("\"dogen.variability/types/helpers/value_factory.hpp\"");

    if (fb.generate_static_configuration()) {
        builder.add("\"dogen.variability/types/helpers/feature_selector.hpp\"");
        builder.add("\"dogen.variability/types/helpers/configuration_selector.hpp\"");
    }

    return builder.build();
}

void feature_template_bundle_implementation_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    const auto& ftb(ast.as<logical::entities::variability::feature_template_bundle>(e));

    {
        const auto sn(ftb.name().simple());
        const auto qn(ast.get_qualified_name(ftb.name()));
        auto sbf(ast.make_scoped_boilerplate_formatter(ftb));
        ast.add_helper_methods(ftb.name().qualified().dot());

        {
            const auto ns(ast.make_namespaces(ftb.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            using namespace variability::helpers;
            using utility::string::splitter;

            if (ftb.generate_registration()) {
ast.stream() << std::endl;
ast.stream() << "namespace {" << std::endl;
                for (const auto& ft : ftb.feature_templates()) {
                    const auto simple_key(splitter::split_scoped(ft.key()).back());
                    const bool has_qualified_name(simple_key != ft.key());
ast.stream() << std::endl;
ast.stream() << "dogen::variability::entities::feature_template" << std::endl;
ast.stream() << "make_" << ft.identifiable_key() << "() {" << std::endl;
ast.stream() << "    using namespace dogen::variability::entities;" << std::endl;
ast.stream() << "    feature_template r;" << std::endl;
ast.stream() << "    r.name().simple(\"" << simple_key << "\");" << std::endl;
                    if (has_qualified_name) {
ast.stream() << "    r.name().qualified(\"" << ft.key() << "\");" << std::endl;
                    }
ast.stream() << "    r.description(R\"(" << ft.documentation() << std::endl;
ast.stream() << ")\");" << std::endl;
ast.stream() << "    const auto vt(" << enum_mapper::from_value_type(ft.value_type()) << ");" << std::endl;
ast.stream() << "    r.value_type(vt);" << std::endl;
ast.stream() << "    r.binding_point(" << enum_mapper::from_binding_point(*ft.binding_point()) << ");" << std::endl;
ast.stream() << "    r.instantiation_domain_name(\"" << ftb.instantiation_domain_name() << "\");" << std::endl;

                    if (!ft.default_value().empty()) {
ast.stream() << "    dogen::variability::helpers::value_factory f;" << std::endl;
ast.stream() << "    r.default_value(f.make(vt, std::list<std::string>{ " << ft.default_value() << " }));" << std::endl;
                        for (const auto& dvo : ft.default_value_overrides()) {
ast.stream() << "    r.default_value_overrides().push_back(" << std::endl;
ast.stream() << "        default_value_override(\"" << dvo.key_ends_with() << "\"," << std::endl;
ast.stream() << "            f.make(vt, std::list<std::string>{ " << dvo.default_value() << " })));" << std::endl;
                       }
                   }
ast.stream() << "    return r;" << std::endl;
ast.stream() << "}" << std::endl;
                }
ast.stream() << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
            }

            if (ftb.generate_static_configuration()) {
ast.stream() << sn << "::feature_group" << std::endl;
ast.stream() << sn << "::make_feature_group(const dogen::variability::entities::feature_model& fm) {" << std::endl;
ast.stream() << "    feature_group r;" << std::endl;
ast.stream() << "    const dogen::variability::helpers::feature_selector s(fm);" << std::endl;
ast.stream() << std::endl;
                for (const auto& ft : ftb.feature_templates()) {
                    const auto simple_key(splitter::split_scoped(ft.key()).back());
ast.stream() << "    r." << simple_key << " = s.get_by_name(\"" << ft.key() << "\");" << std::endl;
                }
ast.stream() << std::endl;
ast.stream() << "    return r;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << sn << "::static_configuration " << sn << "::make_static_configuration(" << std::endl;
ast.stream() << "    const feature_group& fg," << std::endl;
ast.stream() << "    const dogen::variability::entities::configuration& cfg) {" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    static_configuration r;" << std::endl;
ast.stream() << "    const dogen::variability::helpers::configuration_selector s(cfg);" << std::endl;
                for (const auto& ft : ftb.feature_templates()) {
                    const auto simple_key(splitter::split_scoped(ft.key()).back());

                    const bool has_default_value(!ft.default_value().empty());
                    if (has_default_value) {
ast.stream() << "    r." << simple_key << " = s.get_" << enum_mapper::from_value_type(ft.value_type(), false/*simple*/) << "_content_or_default(fg." << simple_key << ");" << std::endl;
                    } else if (ft.is_optional()) {
ast.stream() << "    if (s.has_configuration_point(fg." << simple_key << "))" << std::endl;
ast.stream() << "        r." << simple_key << " = s.get_" << enum_mapper::from_value_type(ft.value_type(), false/*simple*/) << "_content(fg." << simple_key << ");" << std::endl;
                    } else {
ast.stream() << "    r." << simple_key << " = s.get_" << enum_mapper::from_value_type(ft.value_type(), false/*simple*/) << "_content(fg." << simple_key << ");" << std::endl;
                    }
                }
ast.stream() << "    return r;" << std::endl;
ast.stream() << "}" << std::endl;
            }

            if (ftb.generate_registration()) {

ast.stream() << std::endl;
ast.stream() << "std::list<dogen::variability::entities::feature_template>" << std::endl;
ast.stream() << sn << "::make_templates() {" << std::endl;
ast.stream() << "    using namespace dogen::variability::entities;" << std::endl;
ast.stream() << "    std::list<dogen::variability::entities::feature_template> r;" << std::endl;

                for (const auto& ft : ftb.feature_templates()) {
ast.stream() << "    r.push_back(make_" << ft.identifiable_key() << "());" << std::endl;
                }
ast.stream() << "    return r;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
            }
        } // snf
    } // sbf
    ast.update_artefact();
}

}

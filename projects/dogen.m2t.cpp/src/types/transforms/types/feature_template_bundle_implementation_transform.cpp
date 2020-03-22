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
#include "dogen.logical/types/entities/variability/feature_template_bundle.hpp"
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
#include "dogen.m2t.cpp/types/transforms/types/feature_template_bundle_implementation_transform.hpp"

namespace dogen::m2t::cpp::transforms::types {

std::string feature_template_bundle_implementation_transform::static_id() {
    return traits::feature_template_bundle_implementation_archetype();
}

std::string feature_template_bundle_implementation_transform::id() const {
    return static_id();
}

physical::entities::location
feature_template_bundle_implementation_transform::archetype_location() const {
    static physical::entities::location
        r(cpp::traits::backend(), traits::facet(),
          feature_template_bundle_implementation_transform::static_id());
    return r;
}

const logical::entities::name& feature_template_bundle_implementation_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_variability_feature_template_bundle_name());
    return r;
}

inclusion_support_types feature_template_bundle_implementation_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path feature_template_bundle_implementation_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(feature_template_bundle_implementation_transform::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path feature_template_bundle_implementation_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_id());
}

std::list<std::string> feature_template_bundle_implementation_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    using logical::entities::variability::feature_template_bundle;
    const auto& fb(assistant::as<feature_template_bundle>(e));
    auto builder(f.make());

    const auto ch_arch(traits::feature_template_bundle_header_archetype());
    builder.add(fb.name(), ch_arch);
    builder.add("\"dogen.variability/types/helpers/value_factory.hpp\"");

    if (fb.generate_static_configuration()) {
        builder.add("\"dogen.variability/types/helpers/feature_selector.hpp\"");
        builder.add("\"dogen.variability/types/helpers/configuration_selector.hpp\"");
    }

    return builder.build();
}

physical::entities::artefact feature_template_bundle_implementation_transform::
apply(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& ftb(a.as<logical::entities::variability::feature_template_bundle>(e));

    {
        const auto sn(ftb.name().simple());
        const auto qn(a.get_qualified_name(ftb.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(ftb));
        a.add_helper_methods(ftb.name().qualified().dot());

        {
            const auto ns(a.make_namespaces(ftb.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            using namespace variability::helpers;
            using utility::string::splitter;

            if (ftb.generate_registration()) {
a.stream() << std::endl;
a.stream() << "namespace {" << std::endl;
                for (const auto& ft : ftb.feature_templates()) {
                    const auto simple_key(splitter::split_scoped(ft.key()).back());
                    const bool has_qualified_name(simple_key != ft.key());
a.stream() << std::endl;
a.stream() << "dogen::variability::entities::feature_template" << std::endl;
a.stream() << "make_" << ft.identifiable_key() << "() {" << std::endl;
a.stream() << "    using namespace dogen::variability::entities;" << std::endl;
a.stream() << "    feature_template r;" << std::endl;
a.stream() << "    r.name().simple(\"" << simple_key << "\");" << std::endl;
                    if (has_qualified_name) {
a.stream() << "    r.name().qualified(\"" << ft.key() << "\");" << std::endl;
                    }
a.stream() << "    r.description(R\"(" << ft.documentation() << std::endl;
a.stream() << ")\");" << std::endl;
a.stream() << "    const auto vt(" << enum_mapper::from_value_type(ft.value_type()) << ");" << std::endl;
a.stream() << "    r.value_type(vt);" << std::endl;
a.stream() << "    r.binding_point(" << enum_mapper::from_binding_point(*ft.binding_point()) << ");" << std::endl;
a.stream() << "    r.instantiation_domain_name(\"" << ftb.instantiation_domain_name() << "\");" << std::endl;

                    if (!ft.default_value().empty()) {
a.stream() << "    dogen::variability::helpers::value_factory f;" << std::endl;
a.stream() << "    r.default_value(f.make(vt, std::list<std::string>{ " << ft.default_value() << " }));" << std::endl;
                        for (const auto& dvo : ft.default_value_overrides()) {
a.stream() << "    r.default_value_overrides().push_back(" << std::endl;
a.stream() << "        default_value_override(\"" << dvo.key_ends_with() << "\"," << std::endl;
a.stream() << "            f.make(vt, std::list<std::string>{ " << dvo.default_value() << " })));" << std::endl;
                       }
                   }
a.stream() << "    return r;" << std::endl;
a.stream() << "}" << std::endl;
                }
a.stream() << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }

            if (ftb.generate_static_configuration()) {
a.stream() << sn << "::feature_group" << std::endl;
a.stream() << sn << "::make_feature_group(const dogen::variability::entities::feature_model& fm) {" << std::endl;
a.stream() << "    feature_group r;" << std::endl;
a.stream() << "    const dogen::variability::helpers::feature_selector s(fm);" << std::endl;
a.stream() << std::endl;
                for (const auto& ft : ftb.feature_templates()) {
                    const auto simple_key(splitter::split_scoped(ft.key()).back());
a.stream() << "    r." << simple_key << " = s.get_by_name(\"" << ft.key() << "\");" << std::endl;
                }
a.stream() << std::endl;
a.stream() << "    return r;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << sn << "::static_configuration " << sn << "::make_static_configuration(" << std::endl;
a.stream() << "    const feature_group& fg," << std::endl;
a.stream() << "    const dogen::variability::entities::configuration& cfg) {" << std::endl;
a.stream() << std::endl;
a.stream() << "    static_configuration r;" << std::endl;
a.stream() << "    const dogen::variability::helpers::configuration_selector s(cfg);" << std::endl;
                for (const auto& ft : ftb.feature_templates()) {
                    const auto simple_key(splitter::split_scoped(ft.key()).back());

                    const bool has_default_value(!ft.default_value().empty());
                    if (has_default_value) {
a.stream() << "    r." << simple_key << " = s.get_" << enum_mapper::from_value_type(ft.value_type(), false/*simple*/) << "_content_or_default(fg." << simple_key << ");" << std::endl;
                    } else if (ft.is_optional()) {
a.stream() << "    if (s.has_configuration_point(fg." << simple_key << "))" << std::endl;
a.stream() << "        r." << simple_key << " = s.get_" << enum_mapper::from_value_type(ft.value_type(), false/*simple*/) << "_content(fg." << simple_key << ");" << std::endl;
                    } else {
a.stream() << "    r." << simple_key << " = s.get_" << enum_mapper::from_value_type(ft.value_type(), false/*simple*/) << "_content(fg." << simple_key << ");" << std::endl;
                    }
                }
a.stream() << "    return r;" << std::endl;
a.stream() << "}" << std::endl;
            }

            if (ftb.generate_registration()) {

a.stream() << std::endl;
a.stream() << "std::list<dogen::variability::entities::feature_template>" << std::endl;
a.stream() << sn << "::make_templates() {" << std::endl;
a.stream() << "    using namespace dogen::variability::entities;" << std::endl;
a.stream() << "    std::list<dogen::variability::entities::feature_template> r;" << std::endl;

                for (const auto& ft : ftb.feature_templates()) {
a.stream() << "    r.push_back(make_" << ft.identifiable_key() << "());" << std::endl;
                }
a.stream() << "    return r;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }
        } // snf
    } // sbf
    return a.make_artefact();
}

}

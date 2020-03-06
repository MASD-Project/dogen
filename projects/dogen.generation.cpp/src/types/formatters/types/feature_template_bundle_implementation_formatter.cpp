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
#include "dogen.assets/types/meta_model/variability/feature_template_bundle.hpp"
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
#include "dogen.generation.cpp/types/formatters/types/feature_template_bundle_implementation_formatter.hpp"

namespace dogen::generation::cpp::formatters::types {

std::string feature_template_bundle_implementation_formatter::static_id() {
    return traits::feature_template_bundle_implementation_archetype();
}

std::string feature_template_bundle_implementation_formatter::id() const {
    return static_id();
}

archetypes::location
feature_template_bundle_implementation_formatter::archetype_location() const {
    static archetypes::location
        r(cpp::traits::kernel(),  cpp::traits::backend(),
          traits::facet(),
          feature_template_bundle_implementation_formatter::static_id());
    return r;
}

const assets::meta_model::name& feature_template_bundle_implementation_formatter::meta_name() const {
    using assets::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_variability_feature_template_bundle_name());
    return r;
}

std::string feature_template_bundle_implementation_formatter::family() const {
    return cpp::traits::implementation_family();
}

inclusion_support_types feature_template_bundle_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path feature_template_bundle_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const assets::meta_model::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(feature_template_bundle_implementation_formatter::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path feature_template_bundle_implementation_formatter::full_path(
    const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_id());
}

std::list<std::string> feature_template_bundle_implementation_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const assets::meta_model::element& e) const {
    using assets::meta_model::variability::feature_template_bundle;
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

extraction::meta_model::artefact feature_template_bundle_implementation_formatter::
format(const context& ctx, const assets::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& fb(a.as<assets::meta_model::variability::feature_template_bundle>(e));

    {
        const auto sn(fb.name().simple());
        const auto qn(a.get_qualified_name(fb.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(fb));
        a.add_helper_methods(fb.name().qualified().dot());

        {
            const auto ns(a.make_namespaces(fb.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            using namespace variability::helpers;
            using utility::string::splitter;
a.stream() << std::endl;
a.stream() << "namespace {" << std::endl;
            for (const auto& fb_ft : fb.feature_templates()) {
                const auto simple_key(splitter::split_scoped(fb_ft.key()).back());
                const bool has_qualified_name(simple_key != fb_ft.key());
a.stream() << std::endl;
a.stream() << "dogen::variability::meta_model::feature_template" << std::endl;
a.stream() << "make_" << fb_ft.identifiable_key() << "() {" << std::endl;
a.stream() << "    using namespace dogen::variability::meta_model;" << std::endl;
a.stream() << "    feature_template r;" << std::endl;
a.stream() << "    r.name().simple(\"" << simple_key << "\");" << std::endl;
               if (has_qualified_name) {
a.stream() << "    r.name().qualified(\"" << fb_ft.key() << "\");" << std::endl;
               }
a.stream() << "    const auto vt(" << enum_mapper::from_value_type(fb_ft.value_type()) << ");" << std::endl;
a.stream() << "    r.value_type(vt);" << std::endl;
a.stream() << "    r.binding_point(" << enum_mapper::from_binding_point(*fb_ft.binding_point()) << ");" << std::endl;
a.stream() << "    r.kind(" << enum_mapper::from_template_kind(fb.template_kind()) << ");" << std::endl;
    if (!fb_ft.value().empty()) {
a.stream() << "    dogen::variability::helpers::value_factory f;" << std::endl;
a.stream() << "    r.default_value(f.make(vt, std::list<std::string>{ " << fb_ft.value() << " }));" << std::endl;
    }
a.stream() << std::endl;
a.stream() << "    archetypes::location al;" << std::endl;
                if (!fb.location().kernel().empty())
a.stream() << "    al.kernel(\"" << fb.location().kernel() << "\");" << std::endl;
                if (!fb.location().backend().empty())
a.stream() << "    al.backend(\"" << fb.location().backend() << "\");" << std::endl;
                if (!fb.location().facet().empty())
a.stream() << "    al.facet(\"" << fb.location().facet() << "\");" << std::endl;
                if (!fb.location().archetype().empty())
a.stream() << "    al.archetype(\"" << fb.location().archetype() << "\");" << std::endl;
a.stream() << std::endl;
a.stream() << "    r.location(al);" << std::endl;
a.stream() << "    return r;" << std::endl;
a.stream() << "}" << std::endl;
            }
a.stream() << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            if (fb.generate_static_configuration()) {
a.stream() << sn << "::feature_group" << std::endl;
a.stream() << sn << "::make_feature_group(const dogen::variability::meta_model::feature_model& fm) {" << std::endl;
a.stream() << "    feature_group r;" << std::endl;
a.stream() << "    const dogen::variability::helpers::feature_selector s(fm);" << std::endl;
a.stream() << std::endl;
                for (const auto& fb_ft : fb.feature_templates()) {
                    const auto simple_key(splitter::split_scoped(fb_ft.key()).back());
a.stream() << "    r." << simple_key << " = s.get_by_name(\"" << fb_ft.key() << "\");" << std::endl;
                }
a.stream() << std::endl;
a.stream() << "    return r;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << sn << "::static_configuration " << sn << "::make_static_configuration(" << std::endl;
a.stream() << "    const feature_group& fg," << std::endl;
a.stream() << "    const dogen::variability::meta_model::configuration& cfg) {" << std::endl;
a.stream() << std::endl;
a.stream() << "    static_configuration r;" << std::endl;
a.stream() << "    const dogen::variability::helpers::configuration_selector s(cfg);" << std::endl;
                for (const auto& fb_ft : fb.feature_templates()) {
                    const auto simple_key(splitter::split_scoped(fb_ft.key()).back());

                    const bool has_default_value(!fb_ft.value().empty());
                    if (has_default_value) {
a.stream() << "    r." << simple_key << " = s.get_" << enum_mapper::from_value_type(fb_ft.value_type(), false/*simple*/) << "_content_or_default(fg." << simple_key << ");" << std::endl;
                    } else if (fb_ft.is_optional()) {
a.stream() << "    if (s.has_configuration_point(fg." << simple_key << "))" << std::endl;
a.stream() << "        r." << simple_key << " = s.get_" << enum_mapper::from_value_type(fb_ft.value_type(), false/*simple*/) << "_content(fg." << simple_key << ");" << std::endl;
                    } else {
a.stream() << "    r." << simple_key << " = s.get_" << enum_mapper::from_value_type(fb_ft.value_type(), false/*simple*/) << "_content(fg." << simple_key << ");" << std::endl;
                    }
                }
a.stream() << "    return r;" << std::endl;
a.stream() << "}" << std::endl;
            }
a.stream() << std::endl;
a.stream() << "std::list<dogen::variability::meta_model::feature_template>" << std::endl;
a.stream() << sn << "::make_templates() {" << std::endl;
a.stream() << "    using namespace dogen::variability::meta_model;" << std::endl;
a.stream() << "    std::list<dogen::variability::meta_model::feature_template> r;" << std::endl;

            for (const auto& fb_ft : fb.feature_templates()) {
a.stream() << "    r.push_back(make_" << fb_ft.identifiable_key() << "());" << std::endl;
            }
a.stream() << "    return r;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}

}
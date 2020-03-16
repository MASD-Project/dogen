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
#include "dogen.logical/types/entities/variability/feature_template_bundle.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "dogen.generation.cpp/types/formatters/io/traits.hpp"
#include "dogen.generation.cpp/types/formatters/io/inserter_implementation_helper.hpp"
#include "dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/types/feature_template_bundle_header_formatter.hpp"

namespace dogen::generation::cpp::formatters::types {

std::string feature_template_bundle_header_formatter::static_id() {
    return traits::feature_template_bundle_header_archetype();
}

std::string feature_template_bundle_header_formatter::id() const {
    return static_id();
}

physical::entities::location
feature_template_bundle_header_formatter::archetype_location() const {
    static physical::entities::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          feature_template_bundle_header_formatter::static_id());
    return r;
}

const logical::entities::name& feature_template_bundle_header_formatter::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_variability_feature_template_bundle_name());
    return r;
}

std::string feature_template_bundle_header_formatter::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types feature_template_bundle_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path feature_template_bundle_header_formatter::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path feature_template_bundle_header_formatter::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> feature_template_bundle_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    using logical::entities::variability::feature_template_bundle;

    const auto& fb(assistant::as<feature_template_bundle>(e));
    auto builder(f.make());

    builder.add(inclusion_constants::std::list());
    builder.add("\"dogen.variability/types/entities/feature_template.hpp\"");

    if (fb.generate_static_configuration()) {
        builder.add("\"dogen.variability/types/entities/feature_model.hpp\"");
        builder.add("\"dogen.variability/types/entities/configuration.hpp\"");
        builder.add("\"dogen.variability/types/entities/feature.hpp\"");

        const auto ch_arch(traits::class_header_archetype());
        builder.add(fb.transparent_associations(), ch_arch);

        const auto fwd_arch(traits::class_forward_declarations_archetype());
        builder.add(fb.opaque_associations(), fwd_arch);
    }

    return builder.build();
}

extraction::entities::artefact feature_template_bundle_header_formatter::
format(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& fb(a.as<logical::entities::variability::feature_template_bundle>(e));

    {
        const auto sn(fb.name().simple());
        const auto qn(a.get_qualified_name(fb.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(fb));
        a.add_helper_methods(fb.name().qualified().dot());

        {
            const auto ns(a.make_namespaces(fb.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            using utility::string::splitter;
a.stream() << std::endl;
            a.comment(fb.documentation());
a.stream() << "class " << sn << " final {" << std::endl;
            if (fb.generate_static_configuration()) {
a.stream() << "public:" << std::endl;
a.stream() << "    struct feature_group {" << std::endl;
                for (const auto& fb_ft : fb.feature_templates()) {
                    const auto simple_key(splitter::split_scoped(fb_ft.key()).back());
a.stream() << "        variability::entities::feature " << simple_key << ";" << std::endl;
                }
a.stream() << "    };" << std::endl;
a.stream() << std::endl;
a.stream() << "    static feature_group" << std::endl;
a.stream() << "    make_feature_group(const variability::entities::feature_model& fm);" << std::endl;
a.stream() << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    struct static_configuration {" << std::endl;
                for (const auto& fb_ft : fb.feature_templates()) {
                    const auto simple_key(splitter::split_scoped(fb_ft.key()).back());
a.stream() << "        " << a.get_qualified_name(fb_ft.parsed_type()) << " " << simple_key << ";" << std::endl;
                }

                if (fb.requires_manual_default_constructor()) {
                    bool is_first(true);
                    std::ostringstream ss;
                    for (const auto& fb_ft : fb.feature_templates()) {
                        if (!fb_ft.parsed_type().is_current_simple_type())
                            continue;

                        const auto simple_key(splitter::split_scoped(fb_ft.key()).back());

                        if (!is_first)
                            ss << "," << std::endl << "            ";

                        ss << simple_key << "()";
                        is_first = false;
                    }
a.stream() << std::endl;
a.stream() << "        static_configuration() :" << std::endl;
a.stream() << "            " << ss.str() << " {}" << std::endl;
                }
a.stream() << "    };" << std::endl;
a.stream() << std::endl;
a.stream() << "    static static_configuration make_static_configuration(" << std::endl;
a.stream() << "        const feature_group& fg," << std::endl;
a.stream() << "        const variability::entities::configuration& cfg);" << std::endl;
a.stream() << std::endl;
a.stream() << "    template<typename Configurable>" << std::endl;
a.stream() << "    static static_configuration make_static_configuration(" << std::endl;
a.stream() << "        const feature_group& fg, const Configurable& c) {" << std::endl;
a.stream() << "        return make_static_configuration(fg, *c.configuration());" << std::endl;
a.stream() << "    }" << std::endl;
            }

            if (fb.generate_registration()) {
a.stream() << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    static std::list<dogen::variability::entities::feature_template>" << std::endl;
a.stream() << "    make_templates();" << std::endl;
            }
a.stream() << "};" << std::endl;
a.stream() << std::endl;
        } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}
}

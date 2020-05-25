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
#include "dogen.utility/types/io/shared_ptr_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.physical/io/entities/artefact_io.hpp"
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/variability/feature_bundle.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/io/traits.hpp"
#include "dogen.text.cpp/types/transforms/io/inserter_implementation_helper.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/feature_bundle_header_transform.hpp"

namespace dogen::text::cpp::transforms::types {
namespace {

const std::string transform_id("text.cpp.transforms.types.feature_bundle_header_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& feature_bundle_header_transform::static_archetype() {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::feature_bundle_header_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_variability_feature_bundle_name().qualified().dot());
        return r;
    }());
    return r;
}

const physical::entities::archetype& feature_bundle_header_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types feature_bundle_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path feature_bundle_header_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().qualified());
}

boost::filesystem::path feature_bundle_header_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, archetype().meta_name().qualified());
}

std::list<std::string> feature_bundle_header_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    using logical::entities::variability::feature_bundle;

    const auto& fb(assistant::as<feature_bundle>(e));
    auto builder(f.make());

    builder.add(inclusion_constants::std::list());
    builder.add_as_user("dogen.variability/types/entities/feature.hpp");

    if (fb.generate_static_configuration()) {
        builder.add_as_user("dogen.variability/types/entities/feature_model.hpp");
        builder.add_as_user("dogen.variability/types/entities/configuration.hpp");

        const auto ch_arch(traits::class_header_archetype_qn());
        builder.add(fb.transparent_associations(), ch_arch);

        const auto fwd_arch(traits::class_forward_declarations_archetype_qn());
        builder.add(fb.opaque_associations(), fwd_arch);
    }

    return builder.build();
}

void feature_bundle_header_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "feature bundle header transform",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    const auto& fb(ast.as<logical::entities::variability::feature_bundle>(e));

    {
        const auto sn(fb.name().simple());
        const auto qn(ast.get_qualified_name(fb.name()));
        auto sbf(ast.make_scoped_boilerplate_formatter(fb));
        ast.add_helper_methods(fb.name().qualified().dot());

        {
            const auto ns(ast.make_namespaces(fb.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            using utility::string::splitter;
ast.stream() << std::endl;
            ast.comment(fb.documentation());
ast.stream() << "class " << sn << " final {" << std::endl;
            if (fb.generate_static_configuration()) {
ast.stream() << "public:" << std::endl;
ast.stream() << "    struct feature_group {" << std::endl;
                for (const auto& fb_ft : fb.features()) {
                    const auto simple_key(splitter::split_scoped(fb_ft.key()).back());
ast.stream() << "        variability::entities::feature " << simple_key << ";" << std::endl;
                }
ast.stream() << "    };" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    static feature_group" << std::endl;
ast.stream() << "    make_feature_group(const variability::entities::feature_model& fm);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    struct static_configuration {" << std::endl;
                for (const auto& fb_ft : fb.features()) {
                    const auto simple_key(splitter::split_scoped(fb_ft.key()).back());
ast.stream() << "        " << ast.get_qualified_name(fb_ft.parsed_type()) << " " << simple_key << ";" << std::endl;
                }

                if (fb.requires_manual_default_constructor()) {
                    bool is_first(true);
                    std::ostringstream ss;
                    for (const auto& fb_ft : fb.features()) {
                        if (!fb_ft.parsed_type().is_current_simple_type())
                            continue;

                        const auto simple_key(splitter::split_scoped(fb_ft.key()).back());

                        if (!is_first)
                            ss << "," << std::endl << "            ";

                        ss << simple_key << "()";
                        is_first = false;
                    }
ast.stream() << std::endl;
ast.stream() << "        static_configuration() :" << std::endl;
ast.stream() << "            " << ss.str() << " {}" << std::endl;
                }
ast.stream() << "    };" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    static static_configuration make_static_configuration(" << std::endl;
ast.stream() << "        const feature_group& fg," << std::endl;
ast.stream() << "        const variability::entities::configuration& cfg);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    template<typename Configurable>" << std::endl;
ast.stream() << "    static static_configuration make_static_configuration(" << std::endl;
ast.stream() << "        const feature_group& fg, const Configurable& c) {" << std::endl;
ast.stream() << "        return make_static_configuration(fg, *c.configuration());" << std::endl;
ast.stream() << "    }" << std::endl;
            }
ast.stream() << std::endl;
            if (fb.generate_registration()) {
ast.stream() << "public:" << std::endl;
ast.stream() << "    static std::list<dogen::variability::entities::feature>" << std::endl;
ast.stream() << "    make_features();" << std::endl;
            }
ast.stream() << "};" << std::endl;
ast.stream() << std::endl;
        } // snf
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}
}

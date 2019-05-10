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
#include "masd.dogen.generation.cpp/types/formatters/types/feature_bundle_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/inserter_implementation_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "masd.dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "masd.dogen.generation.cpp/types/formatters/assistant.hpp"
#include "masd.dogen.generation.cpp/types/formatters/traits.hpp"
#include "masd.dogen.generation.cpp/types/traits.hpp"
#include "masd.dogen.generation/types/formatters/sequence_formatter.hpp"
#include "masd.dogen.coding/types/helpers/meta_name_factory.hpp"
#include "masd.dogen.coding/types/meta_model/variability/feature_bundle.hpp"
#include "masd.dogen.variability/types/helpers/enum_mapper.hpp"
#include "masd.dogen.utility/types/string/splitter.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include <boost/throw_exception.hpp>

namespace masd::dogen::generation::cpp::formatters::types {

std::string feature_bundle_implementation_formatter::static_id() {
    return traits::feature_bundle_implementation_archetype();
}

std::string feature_bundle_implementation_formatter::id() const {
    return static_id();
}

archetypes::location
feature_bundle_implementation_formatter::archetype_location() const {
    static archetypes::location
        r(cpp::traits::kernel(),  cpp::traits::backend(),
          traits::facet(),
          feature_bundle_implementation_formatter::static_id());
    return r;
}

const coding::meta_model::name& feature_bundle_implementation_formatter::meta_name() const {
    using coding::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_variability_feature_bundle_name());
    return r;
}

std::string feature_bundle_implementation_formatter::family() const {
    return cpp::traits::implementation_family();
}

inclusion_support_types feature_bundle_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path feature_bundle_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const coding::meta_model::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(feature_bundle_implementation_formatter::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path feature_bundle_implementation_formatter::full_path(
    const formattables::locator& l, const coding::meta_model::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_id());
}

std::list<std::string> feature_bundle_implementation_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const coding::meta_model::element& e) const {
    using coding::meta_model::variability::feature_bundle;
    const auto& o(assistant::as<feature_bundle>(e));
    auto builder(f.make());

    const auto ch_arch(traits::feature_bundle_header_archetype());
    builder.add(o.name(), ch_arch);

    return builder.build();
}

extraction::meta_model::artefact feature_bundle_implementation_formatter::
format(const context& ctx, const coding::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& fb(a.as<coding::meta_model::variability::feature_bundle>(e));

    {
        const auto sn(fb.name().simple());
        const auto qn(a.get_qualified_name(fb.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(fb));
        a.add_helper_methods(fb.name().qualified().dot());

        {
            const auto ns(a.make_namespaces(fb.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
a.stream() << "std::list<masd::dogen::variability::meta_model::feature_template>" << std::endl;
a.stream() << sn << "::make_templates() {" << std::endl;
a.stream() << "    using namespace masd::dogen::variability::meta_model;" << std::endl;
a.stream() << "    std::list<feature_template> r;" << std::endl;
a.stream() << std::endl;
            using namespace variability::helpers;
            using utility::string::splitter;
            for (const auto& fb_ft : fb.feature_templates()) {
                const auto simple_key(splitter::split_scoped(fb_ft.key()).back());
a.stream() << "    {" << std::endl;
a.stream() << "        feature_template ft;" << std::endl;
a.stream() << "        ft.name().simple(\"" << simple_key << "\");" << std::endl;
a.stream() << "        ft.name().qualified(\"" << fb_ft.key() << "\");" << std::endl;
a.stream() << "        ft.value_type(" << enum_mapper::from_value_type(fb_ft.value_type()) << ");" << std::endl;
a.stream() << std::endl;
a.stream() << "        archetypes::location al;" << std::endl;
                if (!fb_ft.location().kernel().empty())
a.stream() << "        al.kernel(\"" << fb_ft.location().kernel() << "\");" << std::endl;
                if (!fb_ft.location().backend().empty())
a.stream() << "        al.backend(\"" << fb_ft.location().backend() << "\");" << std::endl;
                if (!fb_ft.location().facet().empty())
a.stream() << "        al.facet(\"" << fb_ft.location().facet() << "\");" << std::endl;
                if (!fb_ft.location().archetype().empty())
a.stream() << "        al.archetype(\"" << fb_ft.location().archetype() << "\");" << std::endl;
a.stream() << std::endl;
a.stream() << "        ft.location(al);" << std::endl;
a.stream() << "        r.push_back(ft);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
            }
a.stream() << "    return r;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}

}

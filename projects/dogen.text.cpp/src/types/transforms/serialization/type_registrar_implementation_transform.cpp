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
#include "dogen.logical/types/entities/serialization/type_registrar.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/serialization/type_registrar_implementation_transform.hpp"

namespace dogen::text::cpp::transforms::serialization {

physical::entities::archetype type_registrar_implementation_transform::static_archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::type_registrar_implementation_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_serialization_type_registrar_name().qualified().dot());
        r.text_to_text_transform("");
        return r;
    }());
    return r;
}

physical::entities::archetype type_registrar_implementation_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types type_registrar_implementation_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path type_registrar_implementation_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(logger_factory(archetype().meta_name().qualified()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path type_registrar_implementation_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, archetype().meta_name().qualified());
}

std::list<std::string> type_registrar_implementation_transform::
inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    const auto& rg(assistant::as<logical::entities::serialization::type_registrar>(e));
    auto builder(f.make());

    const auto rh_fn(traits::type_registrar_header_archetype_qn());
    builder.add(rg.name(), rh_fn);

    using ic = inclusion_constants;
    builder.add(ic::boost::archive::text_iarchive());
    builder.add(ic::boost::archive::text_oarchive());
    builder.add(ic::boost::archive::binary_iarchive());
    builder.add(ic::boost::archive::binary_oarchive());
    builder.add(ic::boost::archive::polymorphic_iarchive());
    builder.add(ic::boost::archive::polymorphic_oarchive());

    // XML serialisation
    builder.add(ic::boost::archive::xml_iarchive());
    builder.add(ic::boost::archive::xml_oarchive());

    const auto ch_fn(traits::class_header_archetype_qn());
    builder.add(rg.leaves(), ch_fn);

    const auto carch(traits::canonical_archetype());
    builder.add(rg.registrar_dependencies(), carch);
    return builder.build();
}

void type_registrar_implementation_transform::apply(const context& ctx, const logical::entities::element& e,
   physical::entities::artefact& a) const {
    assistant ast(ctx, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    const auto& rg(ast.as<logical::entities::serialization::type_registrar>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(ast.make_namespaces(rg.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            const auto deps(rg.registrar_dependencies());
            const auto carch(traits::canonical_archetype());
            const auto leaves(ast.names_with_enabled_archetype(carch, rg.leaves()));
            const bool has_types(!deps.empty() || !leaves.empty());
            const std::string arg_name(has_types ? " ar" : "");
            const auto sn(e.name().simple());
ast.stream() << std::endl;
ast.stream() << "template<typename Archive>" << std::endl;
ast.stream() << "void " << sn << "::register_types(Archive&" << arg_name << ") {" << std::endl;
            if (has_types) {
                for (const auto& d : deps) {
                    const auto dqn(ast.get_qualified_name(d));
ast.stream() << "    " << dqn << "::register_types(ar);" << std::endl;
                }

                if (!deps.empty() && !leaves.empty())
ast.stream() << std::endl;
                for (const auto& l : leaves) {
                    const auto lqn(ast.get_qualified_name(l));
ast.stream() << "    ar.template register_type<" << lqn << ">();" << std::endl;
                }
            }
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template void " << sn << "::register_types(boost::archive::polymorphic_oarchive&" << arg_name << ");" << std::endl;
ast.stream() << "template void " << sn << "::register_types(boost::archive::polymorphic_iarchive&" << arg_name << ");" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template void " << sn << "::register_types(boost::archive::text_oarchive&" << arg_name << ");" << std::endl;
ast.stream() << "template void " << sn << "::register_types(boost::archive::text_iarchive&" << arg_name << ");" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template void " << sn << "::register_types(boost::archive::binary_oarchive&" << arg_name << ");" << std::endl;
ast.stream() << "template void " << sn << "::register_types(boost::archive::binary_iarchive&" << arg_name << ");" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template void " << sn << "::register_types(boost::archive::xml_oarchive&" << arg_name << ");" << std::endl;
ast.stream() << "template void " << sn << "::register_types(boost::archive::xml_iarchive&" << arg_name << ");" << std::endl;
ast.stream() << std::endl;
        } // snf
    } // sbf
    ast.update_artefact();
}

}

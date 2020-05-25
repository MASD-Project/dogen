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
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/hash/traits.hpp"
#include "dogen.text.cpp/types/transforms/hash/class_implementation_transform.hpp"

namespace dogen::text::cpp::transforms::hash {
const physical::entities::archetype& class_implementation_transform::static_archetype() {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::class_implementation_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_object_name().qualified().dot());
        return r;
    }());
    return r;
}

const physical::entities::archetype& class_implementation_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types class_implementation_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path class_implementation_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(logger_factory(archetype().meta_name().qualified()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path class_implementation_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, archetype().meta_name().qualified());
}

std::list<std::string> class_implementation_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    const auto& o(assistant::as<logical::entities::structural::object>(e));
    const auto carch(traits::canonical_archetype());
    auto builder(f.make());
    builder.add(o.name(), carch);

    builder.add(o.transparent_associations(), carch);
    builder.add(o.opaque_associations(), carch);
    builder.add(o.parents(), carch);

    return builder.build();
}

void class_implementation_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    const auto& o(ast.as<logical::entities::structural::object>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
ast.stream() << std::endl;
ast.stream() << "namespace {" << std::endl;
ast.stream() << std::endl;
        if (!o.local_attributes().empty() || !o.parents().empty()) {
ast.stream() << "template <typename HashableType>" << std::endl;
ast.stream() << "inline void combine(std::size_t& seed, const HashableType& value) {" << std::endl;
ast.stream() << "    std::hash<HashableType> hasher;" << std::endl;
ast.stream() << "    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);" << std::endl;
ast.stream() << "}" << std::endl;
        }

        ast.add_helper_methods(o.name().qualified().dot());
ast.stream() << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
        {
            const auto ns(ast.make_namespaces(o.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            const auto sn(o.name().simple());
            const auto qn(ast.get_qualified_name(o.name()));

ast.stream() << std::endl;
ast.stream() << "std::size_t " << sn << "_hasher::hash(const " << sn << "&" << ((o.local_attributes().empty() && o.parents().empty()) ? "" : " v") << ") {" << std::endl;
ast.stream() << "    std::size_t seed(0);" << std::endl;
            if (!o.parents().empty()) {
ast.stream() << std::endl;
                const auto& pn(o.parents().front());
                const auto pqn(ast.get_qualified_name(pn));
ast.stream() << "    combine(seed, dynamic_cast<const " << pqn << "&>(v));" << std::endl;
            }

            if (!o.local_attributes().empty()) {
ast.stream() << std::endl;
                for (const auto& attr : o.local_attributes()) {
                    if (ast.requires_hashing_helper_method(attr))
ast.stream() << "    combine(seed, hash_" << attr.parsed_type().qualified().identifiable() << "(v." << attr.name().simple() << "()));" << std::endl;
                    else
ast.stream() << "    combine(seed, v." << attr.name().simple() << "());" << std::endl;
                }

                if (o.local_attributes().size() > 1)
ast.stream() << std::endl;
            }
ast.stream() << "    return seed;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
        } // snf
    } // sbf
    ast.update_artefact();
}
}

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
#include "dogen.physical/types/helpers/name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/hash/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/hash/class_implementation_transform.hpp"

namespace dogen::m2t::cpp::transforms::hash {

std::string class_implementation_transform::static_id() {
    return traits::class_implementation_archetype();
}

std::string class_implementation_transform::id() const {
    return static_id();
}

physical::entities::name
class_implementation_transform::physical_name() const {
    using physical::helpers::name_factory;
    static auto r(name_factory::make(cpp::traits::backend_qn(),
        cpp::traits::implementation_part(), traits::facet_qn(),
        class_implementation_transform::static_id()));
    return r;
}

const logical::entities::name& class_implementation_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_object_name());
    return r;
}

inclusion_support_types class_implementation_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path class_implementation_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(class_implementation_transform::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path class_implementation_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_id());
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

physical::entities::artefact class_implementation_transform::
apply(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, physical_name(), false/*requires_header_guard*/);
    const auto& o(a.as<logical::entities::structural::object>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
a.stream() << std::endl;
a.stream() << "namespace {" << std::endl;
a.stream() << std::endl;
        if (!o.local_attributes().empty() || !o.parents().empty()) {
a.stream() << "template <typename HashableType>" << std::endl;
a.stream() << "inline void combine(std::size_t& seed, const HashableType& value) {" << std::endl;
a.stream() << "    std::hash<HashableType> hasher;" << std::endl;
a.stream() << "    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);" << std::endl;
a.stream() << "}" << std::endl;
        }

        a.add_helper_methods(o.name().qualified().dot());
a.stream() << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        {
            const auto ns(a.make_namespaces(o.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            const auto sn(o.name().simple());
            const auto qn(a.get_qualified_name(o.name()));

a.stream() << std::endl;
a.stream() << "std::size_t " << sn << "_hasher::hash(const " << sn << "&" << ((o.local_attributes().empty() && o.parents().empty()) ? "" : " v") << ") {" << std::endl;
a.stream() << "    std::size_t seed(0);" << std::endl;
            if (!o.parents().empty()) {
a.stream() << std::endl;
                const auto& pn(o.parents().front());
                const auto pqn(a.get_qualified_name(pn));
a.stream() << "    combine(seed, dynamic_cast<const " << pqn << "&>(v));" << std::endl;
            }

            if (!o.local_attributes().empty()) {
a.stream() << std::endl;
                for (const auto attr : o.local_attributes()) {
                    if (a.requires_hashing_helper_method(attr))
a.stream() << "    combine(seed, hash_" << attr.parsed_type().qualified().identifiable() << "(v." << attr.name().simple() << "()));" << std::endl;
                    else
a.stream() << "    combine(seed, v." << attr.name().simple() << "());" << std::endl;
                }

                if (o.local_attributes().size() > 1)
a.stream() << std::endl;
            }
a.stream() << "    return seed;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}
}

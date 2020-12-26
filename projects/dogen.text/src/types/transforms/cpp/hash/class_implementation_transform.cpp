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
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text/types/transforms/cpp/hash/class_implementation_transform.hpp"
#include "dogen.text/types/transforms/cpp/hash/class_implementation_factory.hpp"

namespace dogen::text::transforms::cpp::hash {
namespace {

const std::string transform_id("text.transforms.hash.class_implementation_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& class_implementation_transform::static_archetype() {
    static auto r(class_implementation_factory::make());
    return r;
}

const physical::entities::archetype& class_implementation_transform::archetype() const {
    return static_archetype();
}

void class_implementation_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "FIXME",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    text::formatters::assistant ast(lps, e, a, false/*requires_header_guard*/);
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
    stp.end_transform(a);
}
}

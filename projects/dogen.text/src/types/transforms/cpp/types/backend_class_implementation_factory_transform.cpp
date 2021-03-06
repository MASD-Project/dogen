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
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/physical/backend.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/cpp/types/backend_class_implementation_factory_transform.hpp"
#include "dogen.text/types/transforms/cpp/types/backend_class_implementation_factory_factory.hpp"

namespace dogen::text::transforms::cpp::types {
namespace {

const std::string transform_id("text.transforms.types.backend_class_implementation_factory_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& backend_class_implementation_factory_transform::static_archetype() {
    static auto r(backend_class_implementation_factory_factory::make());
    return r;
}

const physical::entities::archetype& backend_class_implementation_factory_transform::archetype() const {
    return static_archetype();
}

void backend_class_implementation_factory_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "backend class implementation",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    text::formatters::assistant ast(lps, e, a, false/*requires_header_guard*/);
    const auto& be(ast.as<logical::entities::physical::backend>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(be));
        {
            const auto ns(ast.make_namespaces(be.name(),
                    false/*detect_model_name*/));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            const auto sn(be.name().simple() + "_factory");
ast.stream() << "namespace {" << std::endl;
ast.stream() << std::endl;
ast.stream() << "using namespace dogen::utility::log;" << std::endl;
ast.stream() << "static logger lg(logger_factory(\"" << be.name().qualified().dot() << "\"));" << std::endl;
ast.stream() << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "physical::entities::backend " << sn << "::make() {" << std::endl;
ast.stream() << "    identification::helpers::physical_meta_name_builder b;" << std::endl;
ast.stream() << "    b.meta_model(\"" << be.meta_model_name() << "\");" << std::endl;
ast.stream() << "    b.backend(\"" << be.backend_name() << "\");" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    physical::entities::backend r;" << std::endl;
ast.stream() << "    r.meta_name(b.build());" << std::endl;
            if (!be.directory_name().empty())
ast.stream() << "    r.directory_name(\"" << be.directory_name() << "\");" << std::endl;
            for(const auto& l : be.labels()) {
ast.stream() << "    r.labels().push_back(identification::entities::label(\"" << l.key() << "\", \"" << l.value() << "\"));" << std::endl;
            }

            if (!be.facets().empty()) {
ast.stream() << std::endl;
ast.stream() << "    const auto fct_inserter([&](const auto& fct) {" << std::endl;
ast.stream() << "        const auto id(fct.meta_name().id());" << std::endl;
ast.stream() << "        const auto pair(std::make_pair(id, fct));" << std::endl;
ast.stream() << "        const auto inserted(r.facets().insert(pair).second);" << std::endl;
ast.stream() << "        if (!inserted) {" << std::endl;
ast.stream() << "            using text::transforms::transformation_error;" << std::endl;
ast.stream() << "            const std::string duplicate_facet(\"Duplicate facet: \");" << std::endl;
ast.stream() << "            BOOST_LOG_SEV(lg, error) << duplicate_facet << id;" << std::endl;
ast.stream() << "            BOOST_THROW_EXCEPTION(transformation_error(duplicate_facet + id.value()));" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << "    });" << std::endl;
ast.stream() << std::endl;
                for (const auto& n : be.facets()) {
                    // Bit of a hack: facets work as namespaces.
ast.stream() << "    fct_inserter(" << n.simple() << "::" << n.simple() << "_factory::make());" << std::endl;
                }
            }

            if (!be.archetype_kinds().empty()) {
ast.stream() << std::endl;
ast.stream() << "    const auto ak_inserter([&](const auto& ak) {" << std::endl;
ast.stream() << "        const auto pair(std::make_pair(ak.id(), ak));" << std::endl;
ast.stream() << "        const auto inserted(r.archetype_kinds().insert(pair).second);" << std::endl;
ast.stream() << "        if (!inserted) {" << std::endl;
ast.stream() << "            using text::transforms::transformation_error;" << std::endl;
ast.stream() << "            const std::string duplicate_facet(\"Duplicate archetype kind: \");" << std::endl;
ast.stream() << "            BOOST_LOG_SEV(lg, error) << duplicate_facet << ak.id();" << std::endl;
ast.stream() << "            BOOST_THROW_EXCEPTION(transformation_error(duplicate_facet + ak.id()));" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << "    });" << std::endl;
                for (const auto& n : be.archetype_kinds()) {
ast.stream() << "    ak_inserter(" << n.simple() << "_factory::make());" << std::endl;
                }
            }

            if (!be.parts().empty()) {
ast.stream() << std::endl;
ast.stream() << "    const auto part_inserter([&](const auto& part) {" << std::endl;
ast.stream() << "        const auto id(part.meta_name().id());" << std::endl;
ast.stream() << "        const auto pair(std::make_pair(id, part));" << std::endl;
ast.stream() << "        const auto inserted(r.parts().insert(pair).second);" << std::endl;
ast.stream() << "        if (!inserted) {" << std::endl;
ast.stream() << "            using text::transforms::transformation_error;" << std::endl;
ast.stream() << "            const std::string duplicate_facet(\"Duplicate part: \");" << std::endl;
ast.stream() << "            BOOST_LOG_SEV(lg, error) << duplicate_facet << id;" << std::endl;
ast.stream() << "            BOOST_THROW_EXCEPTION(transformation_error(duplicate_facet + id.value()));" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << "    });" << std::endl;
                for (const auto& n : be.parts()) {
ast.stream() << "    part_inserter(" << n.simple() << "_factory::make());" << std::endl;
                }
            }
ast.stream() << "    return r;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
        } // snf
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);

}
}

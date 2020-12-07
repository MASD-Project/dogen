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
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/physical/helper.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/types/helper_class_implementation_factory_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/helper_class_implementation_factory_factory.hpp"

namespace dogen::text::cpp::transforms::types {
namespace {

const std::string transform_id("text.cpp.transforms.types.helper_class_implementation_factory_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& helper_class_implementation_factory_transform::static_archetype() {
    static auto r(helper_class_implementation_factory_factory::make());
    return r;
}

const physical::entities::archetype& helper_class_implementation_factory_transform::archetype() const {
    return static_archetype();
}

void helper_class_implementation_factory_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "helper class implementation",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);
    assistant ast(ctx, lps, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    const auto& hlp(ast.as<logical::entities::physical::helper>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(hlp));
        {
            const auto ns(ast.make_namespaces(hlp.name(),
                    false/*detect_model_name*/));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            const auto sn(hlp.name().simple() + "_factory");
ast.stream() << std::endl;
ast.stream() << "physical::entities::helper " << sn << "::make() {" << std::endl;
ast.stream() << "    physical::entities::helper r;" << std::endl;
ast.stream() << "    using pmnf = identification::helpers::physical_meta_name_factory;" << std::endl;
ast.stream() << "    r.meta_name(pmnf::make(\"" << hlp.backend_name() << "\", \"" << hlp.facet_name() << "\", \"" << hlp.name().simple() << "\"));" << std::endl;
ast.stream() << "    // r.relations().status(physical::entities::relation_status::" << hlp.relations().status() << ");" << std::endl;
             if (!hlp.family().empty()) {
ast.stream() << "    r.family(\"" << hlp.family() << "\");" << std::endl;
             }

             if (!hlp.owning_formatters().empty() || !hlp.owning_facets().empty()) {
ast.stream() << "    using identification::entities::physical_meta_id;" << std::endl;
             }

             for (const auto& of : hlp.owning_formatters()) {
ast.stream() << "    r.owning_formatters().push_back(" << std::endl;
ast.stream() << "        physical_meta_id(\"" << of << "\"));" << std::endl;
             }



             for (const auto& of : hlp.owning_facets()) {
ast.stream() << "    r.owning_facets().push_back(" << std::endl;
ast.stream() << "        physical_meta_id(\"" << of << "\"));" << std::endl;
             }

             for(const auto& l : hlp.labels()) {
ast.stream() << "    r.labels().push_back(identification::entities::label(\"" << l.key() << "\", \"" << l.value() << "\"));" << std::endl;
            }

            for(const auto& cr : hlp.relations().constant()) {
ast.stream() << std::endl;
ast.stream() << "    r.relations().constant().push_back(" << std::endl;
ast.stream() << "        physical::entities::constant_relation(" << std::endl;
ast.stream() << "            \"" << cr.original_urn() << "\"," << std::endl;
ast.stream() << "            \"\"/*resolved_urn*/," << std::endl;
                if (cr.labels().empty()) {
ast.stream() << "            std::list<identification::entities::label> {}," << std::endl;
                } else {
ast.stream() << "            std::list<identification::entities::label> {" << std::endl;
                    utility::formatters::sequence_formatter sf(cr.labels().size());
                    // sf.prefix_configuration().first(": ").not_first("  ");
                    sf.postfix_configuration().not_last(",")/*.last("")*/;

                    for(const auto& l : cr.labels()) {
ast.stream() << "                identification::entities::label(\"" << l.key() << "\", \"" << l.value() << "\")" << sf.postfix() << std::endl;
                        sf.next();
                    }
ast.stream() << "            }," << std::endl;
                }
ast.stream() << "            \"" << cr.logical_model_element_id() << "\"" << std::endl;
ast.stream() << "        )" << std::endl;
ast.stream() << "    );" << std::endl;
            }

            for(const auto& vr : hlp.relations().variable()) {
ast.stream() << std::endl;
ast.stream() << "    r.relations().variable().push_back(" << std::endl;
ast.stream() << "        physical::entities::variable_relation(" << std::endl;
ast.stream() << "            \"" << vr.original_urn() << "\"," << std::endl;
ast.stream() << "            \"\"/*resolved_urn*/," << std::endl;
ast.stream() << "            physical::entities::variable_relation_type::" << vr.type() << std::endl;
ast.stream() << "        )" << std::endl;
ast.stream() << "    );" << std::endl;
            }
ast.stream() << std::endl;
ast.stream() << "    return r;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
        } // snf
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}
}

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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/test_data/traits.hpp"
#include "dogen.text.cpp/types/transforms/test_data/class_implementation_transform.hpp"
#include "dogen.text.cpp/types/transforms/test_data/class_implementation_factory.hpp"

namespace dogen::text::cpp::transforms::test_data {
namespace {

const std::string transform_id("text.cpp.transforms.test_data.class_implementation_transform");

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
    tracing::scoped_transform_tracer stp(lg, "class implementation",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, lps, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    const auto& o(ast.as<logical::entities::structural::object>(e));

    {
        const auto sn(o.name().simple());
        const auto qn(ast.get_qualified_name(o.name()));
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        if (!o.local_attributes().empty()) {
ast.stream() << "namespace {" << std::endl;
        ast.add_helper_methods(o.name().qualified().dot());
ast.stream() << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
        }

        {
            const auto ns(ast.make_namespaces(o.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));

            /*
             * Default constructor.
             */
            if (!o.is_parent()) {
ast.stream() << std::endl;
ast.stream() << sn << "_generator::" << sn << "_generator() : position_(0) { }" << std::endl;
            }

            /*
             * Populate method.
             */
            if (!o.is_immutable()) {
                bool no_args(o.local_attributes().empty() && o.parents().empty());
                if (no_args) {
ast.stream() << std::endl;
ast.stream() << "void " << sn << "_generator::" << std::endl;
ast.stream() << "populate(const unsigned int /*position*/, result_type& /*v*/) {" << std::endl;
                } else {
ast.stream() << std::endl;
ast.stream() << "void " << sn << "_generator::" << std::endl;
ast.stream() << "populate(const unsigned int position, result_type& v) {" << std::endl;
                }

                if (!o.parents().empty()) {
                    const auto& pn(o.parents().front());
                    const auto pqn(ast.get_qualified_name(pn));
ast.stream() << "    " << pqn << "_generator::populate(position, v);" << std::endl;
                }
                unsigned int i(0);
                for (const auto& attr : o.local_attributes()) {
ast.stream() << "    v." << attr.name().simple() << "(create_" << attr.parsed_type().qualified().identifiable() << "(position + " << i << "));" << std::endl;
                    ++i;
                }
ast.stream() << "}" << std::endl;
            }

            /*
             * Create method.
             */
            if (!o.is_parent()) {
                 const bool no_arg(o.all_attributes().empty());
ast.stream() << std::endl;
ast.stream() << sn << "_generator::result_type" << std::endl;
ast.stream() << sn << "_generator::create(const unsigned int" << (no_arg ? "/*position*/" : " position") << ") {" << std::endl;
                if (o.is_immutable()) {
ast.stream() << "    return " << sn << "(" << std::endl;
                    if (o.local_attributes().empty())
ast.stream() << std::endl;
                    else {
                        utility::formatters::sequence_formatter sf(o.local_attributes().size());
                        for (const auto& attr : o.local_attributes()) {
ast.stream() << "        create_" << attr.parsed_type().qualified().identifiable() << "(position + " << sf.current_position() << ")" << sf.postfix() << std::endl;
                            sf.next();
                        }
                    }
ast.stream() << "        );" << std::endl;
                } else {
ast.stream() << "    " << sn << " r;" << std::endl;
                    if (!o.all_attributes().empty())
ast.stream() << "    " << sn << "_generator::populate(position, r);" << std::endl;
ast.stream() << "    return r;" << std::endl;
                }
ast.stream() << "}" << std::endl;
            }

            /*
             * Create method ptr.
             */
ast.stream() << std::endl;
ast.stream() << sn << "_generator::result_type*" << std::endl;
ast.stream() << sn << "_generator::create_ptr(const unsigned int position) {" << std::endl;
            if (o.leaves().empty()) {
                if (o.is_immutable())
ast.stream() << "    return new " << sn << "(create(position));" << std::endl;
                else {
ast.stream() << "    " << sn << "* p = new " << sn << "();" << std::endl;
ast.stream() << "    " << sn << "_generator::populate(position, *p);" << std::endl;
ast.stream() << "    return p;" << std::endl;
                }
            } else {
                auto leaves(o.leaves());
                const auto front(leaves.front());
                leaves.pop_front();
                unsigned int i(0);
                const auto total(static_cast<unsigned int>(leaves.size()));
                for (const auto& l : leaves) {
ast.stream() << "    if ((position % " << total << ") == " << i++ << ")" << std::endl;
ast.stream() << "        return " << ast.get_qualified_name(l) << "_generator::create_ptr(position);" << std::endl;
                }
ast.stream() << "    return " << ast.get_qualified_name(front) << "_generator::create_ptr(position);" << std::endl;
            }
ast.stream() << "}" << std::endl;
            /*
             * Function operator
             */
             if (!o.is_parent()) {
ast.stream() << std::endl;
ast.stream() << sn << "_generator::result_type" << std::endl;
ast.stream() << sn << "_generator::operator()() {" << std::endl;
ast.stream() << "    return create(position_++);" << std::endl;
ast.stream() << "}" << std::endl;
            }
ast.stream() << std::endl;
        } // snf
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}
}

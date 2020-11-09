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
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/physical/helper.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/types/helper_class_header_transform_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/helper_class_header_transform_factory.hpp"

namespace dogen::text::cpp::transforms::types {
namespace {

const std::string transform_id("text.cpp.transforms.types.helper_class_header_transform_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& helper_class_header_transform_transform::static_archetype() {
    static auto r(helper_class_header_transform_factory::make());
    return r;
}

const physical::entities::archetype& helper_class_header_transform_transform::archetype() const {
    return static_archetype();
}

void helper_class_header_transform_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "types helper class header",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);
    assistant ast(ctx, e, archetype().meta_name(), true/*requires_header_guard*/, a);
    const auto& o(ast.as<logical::entities::physical::helper>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(o));
        {
            const auto ns(ast.make_namespaces(o.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            const auto sn(o.name().simple() + "_transform");
ast.stream() << std::endl;
ast.stream() << "class " << sn << " final : public helper_transform {" << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    std::string id() const override;" << std::endl;
ast.stream() << "    std::string family() const override;" << std::endl;
ast.stream() << "    std::list<std::string> owning_formatters() const override;" << std::endl;
ast.stream() << "    std::list<std::string> owning_facets() const override;" << std::endl;
ast.stream() << "    std::string helper_name() const override;" << std::endl;
ast.stream() << "    bool is_enabled(const assistant& a," << std::endl;
ast.stream() << "        const logical::entities::helper_properties& hc) const override;" << std::endl;
ast.stream() << "    void apply(assistant& a," << std::endl;
ast.stream() << "        const logical::entities::helper_properties& hc) const override;" << std::endl;
ast.stream() << "};" << std::endl;
ast.stream() << std::endl;
        } // snf
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);

}

}

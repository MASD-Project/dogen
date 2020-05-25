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
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/serialization/class_header_transform.hpp"

namespace dogen::text::cpp::transforms::serialization {
namespace {

const std::string transform_id("text.cpp.transforms.serialization.class_header_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& class_header_transform::static_archetype() {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::class_header_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_object_name().qualified().dot());
        return r;
    }());
    return r;
}

const physical::entities::archetype& class_header_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types class_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path class_header_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().qualified());
}

boost::filesystem::path class_header_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, archetype().meta_name().qualified());
}

std::list<std::string> class_header_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    using logical::entities::structural::object;
    const auto& o(assistant::as<object>(e));
    auto builder(f.make());
    builder.add(o.name(), types::traits::class_header_archetype_qn());

    using ic = inclusion_constants;
    builder.add(ic::boost::serialization::split_free());

    if (o.is_parent())
        builder.add(ic::boost::serialization::assume_abstract());

    if (!o.is_parent() && o.is_child())
        builder.add(ic::boost::type_traits::is_virtual_base_of());

    return builder.build();
}

void class_header_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, archetype().meta_name(), true/*requires_header_guard*/, a);
    const auto& o(ast.as<logical::entities::structural::object>(e));

    {
        const auto qn(ast.get_qualified_name(o.name()));
        auto sbf(ast.make_scoped_boilerplate_formatter(e));

        if (!o.is_parent() && !o.parents().empty()) {
            const auto& pn(o.parents().front());
            const auto pqn(ast.get_qualified_name(pn));
ast.stream() << "namespace boost {" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template<>struct" << std::endl;
ast.stream() << "is_virtual_base_of<" << std::endl;
ast.stream() << "    " << pqn << "," << std::endl;
ast.stream() << "    " << qn << std::endl;
ast.stream() << "> : public mpl::true_ {};" << std::endl;
ast.stream() << std::endl;
ast.stream() << "}" << std::endl;
        }
ast.stream() << std::endl;
ast.stream() << "BOOST_SERIALIZATION_SPLIT_FREE(" << qn << ")" << std::endl;
        if (o.is_parent()) {
ast.stream() << "BOOST_SERIALIZATION_ASSUME_ABSTRACT(" << qn << ")" << std::endl;
ast.stream() << std::endl;
        }
ast.stream() << "namespace boost {" << std::endl;
ast.stream() << "namespace serialization {" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template<typename Archive>" << std::endl;
ast.stream() << "void save(Archive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template<typename Archive>" << std::endl;
ast.stream() << "void load(Archive& ar, " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "} }" << std::endl;
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
}
}

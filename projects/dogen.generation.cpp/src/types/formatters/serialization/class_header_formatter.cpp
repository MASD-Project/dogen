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
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen.generation.cpp/types/formatters/serialization/traits.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/formatters/serialization/class_header_formatter.hpp"

namespace dogen::generation::cpp::formatters::serialization {

std::string class_header_formatter::static_id() {
    return traits::class_header_archetype();
}

std::string class_header_formatter::id() const {
    return static_id();
}

physical::entities::location
class_header_formatter::archetype_location() const {
    static physical::entities::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          class_header_formatter::static_id());
    return r;
}

const logical::entities::name& class_header_formatter::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_object_name());
    return r;
}

std::string class_header_formatter::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types class_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path class_header_formatter::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path class_header_formatter::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> class_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    using logical::entities::structural::object;
    const auto& o(assistant::as<object>(e));
    auto builder(f.make());
    builder.add(o.name(), types::traits::class_header_archetype());

    using ic = inclusion_constants;
    builder.add(ic::boost::serialization::split_free());

    if (o.is_parent())
        builder.add(ic::boost::serialization::assume_abstract());

    if (!o.is_parent() && o.is_child())
        builder.add(ic::boost::type_traits::is_virtual_base_of());

    return builder.build();
}

extraction::entities::artefact class_header_formatter::
format(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location(), true/*requires_header_guard*/);
    const auto& o(a.as<logical::entities::structural::object>(e));

    {
        const auto qn(a.get_qualified_name(o.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(e));

        if (!o.is_parent() && !o.parents().empty()) {
            const auto& pn(o.parents().front());
            const auto pqn(a.get_qualified_name(pn));
a.stream() << "namespace boost {" << std::endl;
a.stream() << std::endl;
a.stream() << "template<>struct" << std::endl;
a.stream() << "is_virtual_base_of<" << std::endl;
a.stream() << "    " << pqn << "," << std::endl;
a.stream() << "    " << qn << std::endl;
a.stream() << "> : public mpl::true_ {};" << std::endl;
a.stream() << std::endl;
a.stream() << "}" << std::endl;
        }
a.stream() << std::endl;
a.stream() << "BOOST_SERIALIZATION_SPLIT_FREE(" << qn << ")" << std::endl;
        if (o.is_parent()) {
a.stream() << "BOOST_SERIALIZATION_ASSUME_ABSTRACT(" << qn << ")" << std::endl;
a.stream() << std::endl;
        }
a.stream() << "namespace boost {" << std::endl;
a.stream() << "namespace serialization {" << std::endl;
a.stream() << std::endl;
a.stream() << "template<typename Archive>" << std::endl;
a.stream() << "void save(Archive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
a.stream() << "template<typename Archive>" << std::endl;
a.stream() << "void load(Archive& ar, " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
a.stream() << "} }" << std::endl;
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}
}

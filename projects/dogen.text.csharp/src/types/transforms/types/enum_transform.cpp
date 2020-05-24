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
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text.csharp/types/traits.hpp"
#include "dogen.text.csharp/types/transforms/types/traits.hpp"
#include "dogen.text.csharp/types/transforms/assistant.hpp"
#include "dogen.text.csharp/types/transforms/types/enum_transform.hpp"

namespace dogen::text::csharp::transforms::types {
const physical::entities::archetype& enum_transform::static_archetype() {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(csharp::traits::backend_sn(),
            traits::facet_sn(), traits::enum_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_enumeration_name().qualified().dot());
        return r;
    }());
    return r;
}

const physical::entities::archetype& enum_transform::archetype() const {
    return static_archetype();
}

boost::filesystem::path enum_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path(n, archetype().meta_name().qualified());
}

std::list<std::string> enum_transform::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

void enum_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, archetype().meta_name(), a);
    const auto& ye(ast.as<logical::entities::structural::enumeration>(archetype().meta_name().qualified(), e));
    {
        const auto sn(e.name().simple());
        const auto qn(ast.get_qualified_name(e.name()));
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
ast.stream() << "using System;" << std::endl;
ast.stream() << std::endl;
            const auto ns(ast.make_namespaces(e.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            ast.comment(e.documentation(), 1/*indent*/);
            if (ye.use_implementation_defined_underlying_element())
ast.stream() << "    public enum " << sn << std::endl;
            else
ast.stream() << "    public enum " << sn << " : " << ast.get_qualified_name(ye.underlying_element()) << std::endl;
ast.stream() << "    {" << std::endl;
            utility::formatters::sequence_formatter sf(ye.enumerators().size());
            for (const auto& en : ye.enumerators()) {
                if (ye.use_implementation_defined_enumerator_values())
ast.stream() << "        " << en.name().simple() << sf.postfix() << ast.comment_inline(en.documentation()) << std::endl;
                else
ast.stream() << "        " << en.name().simple() << " = " << en.value() << sf.postfix() << ast.comment_inline(en.documentation()) << std::endl;
                sf.next();
            }
ast.stream() << "    }" << std::endl;
        } // snf
    } // sbf
    ast.update_artefact();
}
}

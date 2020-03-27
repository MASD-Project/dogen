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
#include "dogen.physical/types/helpers/name_factory.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.csharp/types/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/types/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/assistant.hpp"
#include "dogen.m2t.csharp/types/transforms/types/enum_transform.hpp"

namespace dogen::m2t::csharp::transforms::types {

std::string enum_transform::static_id() {
    return traits::enum_archetype();
}

std::string enum_transform::id() const {
    return static_id();
}

physical::entities::name
enum_transform::physical_name() const {
    using physical::helpers::name_factory;
    static const auto r(name_factory::make(csharp::traits::backend_qn(),
        traits::facet_qn(), enum_transform::static_id()));
    return r;
}

const logical::entities::name& enum_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_enumeration_name());
    return r;
}

boost::filesystem::path enum_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path(n, static_id());
}

std::list<std::string> enum_transform::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

physical::entities::artefact enum_transform::
apply(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, physical_name().location());
    const auto& ye(a.as<logical::entities::structural::enumeration>(static_id(), e));
    {
        const auto sn(e.name().simple());
        const auto qn(a.get_qualified_name(e.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
a.stream() << "using System;" << std::endl;
a.stream() << std::endl;
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            a.comment(e.documentation(), 1/*indent*/);
            if (ye.use_implementation_defined_underlying_element())
a.stream() << "    public enum " << sn << std::endl;
            else
a.stream() << "    public enum " << sn << " : " << a.get_qualified_name(ye.underlying_element()) << std::endl;
a.stream() << "    {" << std::endl;
            m2t::formatters::sequence_formatter sf(ye.enumerators().size());
            for (const auto& en : ye.enumerators()) {
                if (ye.use_implementation_defined_enumerator_values())
a.stream() << "        " << en.name().simple() << sf.postfix() << a.comment_inline(en.documentation()) << std::endl;
                else
a.stream() << "        " << en.name().simple() << " = " << en.value() << sf.postfix() << a.comment_inline(en.documentation()) << std::endl;
                sf.next();
            }
a.stream() << "    }" << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}
}

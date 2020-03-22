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
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.csharp/types/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/types/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/assistant.hpp"
#include "dogen.m2t.csharp/types/transforms/types/exception_transform.hpp"

namespace dogen::m2t::csharp::transforms::types {

std::string exception_transform::static_id() {
    return traits::exception_archetype();
}

std::string exception_transform::id() const {
    return static_id();
}

physical::entities::location exception_transform::archetype_location() const {
    static physical::entities::location
        r(csharp::traits::backend(), traits::facet(),
          exception_transform::static_id());
    return r;
}

const logical::entities::name& exception_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_exception_name());
    return r;
}

boost::filesystem::path exception_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path(n, static_id());
}

std::list<std::string> exception_transform::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

physical::entities::artefact exception_transform::
format(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location());
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
a.stream() << "    public class " << sn << "  : Exception" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        public " << sn << "() { }" << std::endl;
a.stream() << "        public " << sn << "(string message) : base(message) { }" << std::endl;
a.stream() << "        public " << sn << "(string message, Exception inner) : base(message, inner) { }" << std::endl;
a.stream() << "    }" << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}
}

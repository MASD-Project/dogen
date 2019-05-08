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
#include "masd.dogen.generation.csharp/types/formatters/types/exception_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formatters/assistant.hpp"
#include "masd.dogen.generation.csharp/types/formatters/types/traits.hpp"
#include "masd.dogen.generation.csharp/types/traits.hpp"
#include "masd.dogen.generation/types/formatters/sequence_formatter.hpp"
#include "masd.dogen.coding/types/helpers/meta_name_factory.hpp"
#include "masd.dogen.coding/types/meta_model/structural/exception.hpp"

namespace masd::dogen::generation::csharp::formatters::types {

std::string exception_formatter::static_id() {
    return traits::exception_archetype();
}

std::string exception_formatter::id() const {
    return static_id();
}

archetypes::location exception_formatter::archetype_location() const {
    static archetypes::location
        r(csharp::traits::kernel(), csharp::traits::backend(),
          traits::facet(),
          exception_formatter::static_id());
    return r;
}

const coding::meta_model::name& exception_formatter::meta_name() const {
    using coding::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_exception_name());
    return r;
}

std::string exception_formatter::family() const {
    return csharp::traits::csharp_family();
}

boost::filesystem::path exception_formatter::full_path(
    const formattables::locator& l, const coding::meta_model::name& n) const {
    return l.make_full_path(n, static_id());
}

std::list<std::string> exception_formatter::
inclusion_dependencies(const coding::meta_model::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

extraction::meta_model::artefact exception_formatter::
format(const context& ctx, const coding::meta_model::element& e) const {
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

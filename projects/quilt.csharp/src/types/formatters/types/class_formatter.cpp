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
#include "dogen/quilt.csharp/types/formatters/types/class_formatter.hpp"
#include "dogen/quilt.csharp/types/formatters/assistant.hpp"
#include "dogen/quilt.csharp/types/traits.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/yarn/types/object.hpp"
#include <boost/make_shared.hpp>
#include <typeinfo>

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {
namespace types {

dogen::formatters::artefact class_formatter::format(const yarn::element& e) const {
    assistant a;
    const auto id(e.name().id());
    {
        const auto sn(e.name().simple());
        // const auto qn(a.get_qualified_name(e.name()));
        // auto sbf(a.make_scoped_boilerplate_formatter());
        {
            // const auto ns(a.make_namespaces(e.name()));
            // auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
            // a.comment(o.documentation());
a.stream() << "class " << sn << " {" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
        }
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}
} } } } }

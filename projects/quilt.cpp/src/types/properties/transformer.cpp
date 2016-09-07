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
#include <boost/pointer_cast.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/utility/io/shared_ptr_io.hpp"
#include "dogen/yarn/io/object_types_io.hpp"
#include "dogen/quilt.cpp/io/properties/formattable_io.hpp"
#include "dogen/quilt.cpp/types/properties/name_builder.hpp"
#include "dogen/quilt.cpp/types/properties/transformation_error.hpp"
#include "dogen/quilt.cpp/types/properties/transformer.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("quilt.cpp.transformer"));

const std::string empty;
const std::string namespace_separator("::");
const std::string concept_not_found("Concept not found in concept container: ");
const std::string cast_failure("Failed to cast type: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

void transformer::
populate_formattable_properties(const yarn::name& n, formattable& f) const {
    f.identity(n.id());
}

void transformer::populate_entity_properties(const yarn::name& n,
    const std::string& documentation, entity& e) const {

    populate_formattable_properties(n, e);

    e.name(n.simple());
    e.documentation(documentation);
    e.id(n.id());

    name_builder b;
    e.namespaces(b.namespace_list(n));

    std::list<std::string> ns(e.namespaces());
    ns.push_back(e.name());

    using boost::join;
    e.qualified_name(join(ns, namespace_separator));
}

std::shared_ptr<forward_declarations_info> transformer::
to_forward_declarations_info(const yarn::visitor& v) const {
    auto r(std::make_shared<forward_declarations_info>());
    populate_entity_properties(v.name(), v.documentation(), *r);
    return r;
}

std::shared_ptr<forward_declarations_info> transformer::
to_forward_declarations_info(const yarn::object& o) const {
    auto r(std::make_shared<forward_declarations_info>());
    populate_entity_properties(o.name(), o.documentation(), *r);
    return r;
}

std::shared_ptr<forward_declarations_info> transformer::
to_forward_declarations_info(const yarn::exception& e) const {
    auto r(std::make_shared<forward_declarations_info>());
    r->is_exception(true);
    populate_entity_properties(e.name(), e.documentation(), *r);
    return r;
}

std::shared_ptr<forward_declarations_info> transformer::
to_forward_declarations_info(const yarn::enumeration& e) const {
    auto r(std::make_shared<forward_declarations_info>());
    populate_entity_properties(e.name(), e.documentation(), *r);
    r->is_enum(true);
    r->enum_type("unsigned int"); // FIXME
    return r;
}

std::forward_list<std::shared_ptr<formattable> >
transformer::transform(const yarn::visitor& v) const {
    std::forward_list<std::shared_ptr<formattable> > r;
    r.push_front(to_forward_declarations_info(v));
    return r;
}

std::forward_list<std::shared_ptr<formattable> >
transformer::transform(const yarn::enumeration& e) const {
    std::forward_list<std::shared_ptr<formattable> > r;
    r.push_front(to_forward_declarations_info(e));
    return r;
}

std::forward_list<std::shared_ptr<formattable> > transformer::
transform(const yarn::object& o) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming object: "
                             << o.name().id();

    std::forward_list<std::shared_ptr<formattable> > r;
    r.push_front(to_forward_declarations_info(o));

    for (const auto& i : r)
        BOOST_LOG_SEV(lg, debug) << "Transformed object: " << *i;
    return r;
}

std::forward_list<std::shared_ptr<formattable> >
transformer::transform(const yarn::exception& e) const {
    std::forward_list<std::shared_ptr<formattable> > r;
    r.push_front(to_forward_declarations_info(e));
    return r;
}

} } } }

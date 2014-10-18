/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/cpp/types/flat_name_builder.hpp"
#include "dogen/cpp/types/transformer.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.transformer"));

}

namespace dogen {
namespace cpp {

transformer::transformer(const sml::model& m) : model_(m) { }

enumerator_info
transformer::to_enumerator_info(const sml::enumerator& e) const {
    enumerator_info r;
    r.name(e.name());
    r.value(e.value());
    r.documentation(e.documentation());
    return r;
}

std::shared_ptr<enum_info>
transformer::to_enum_info(const sml::enumeration& e) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming enumeration: " << e.name();

    auto r(std::make_shared<enum_info>());
    r->name(e.name().simple_name());
    r->documentation(e.documentation());
    r->type(e.underlying_type().simple_name());

    flat_name_builder b;
    r->namespaces(b.to_namespace_list(model_, e.name()));

    for (const auto& en : e.enumerators())
        r->enumerators().push_back(to_enumerator_info(en));

    BOOST_LOG_SEV(lg, debug) << "Transformed enumeration: " << e.name();

    return r;
}

std::shared_ptr<namespace_info> transformer::
to_namespace_info(const sml::module& m) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming module: " << m.name();

    auto r(std::make_shared<namespace_info>());
    r->documentation(m.documentation());

    flat_name_builder b;
    r->namespaces(b.to_namespace_list(model_, m.name()));

    BOOST_LOG_SEV(lg, debug) << "Transformed module: " << m.name();
    return r;
}

std::shared_ptr<entity>
transformer::transform(const sml::enumeration& e) const {
    return to_enum_info(e);
}

std::shared_ptr<entity> transformer::transform(const sml::module& m) const {
    return to_namespace_info(m);
}

} }

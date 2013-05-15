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
#include "dogen/cpp/types/transformation_error.hpp"
#include "dogen/cpp/types/transformer.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("cpp.transformer"));

}

namespace dogen {
namespace cpp {

std::list<std::string>
transformer::transform(const dogen::sml::qname& qn) const {
    std::list<std::string> r(qn.external_package_path());

    if (!qn.model_name().empty())
        r.push_back(qn.model_name());

    const std::list<std::string> pp(qn.package_path());
    r.insert(r.end(), pp.begin(), pp.end());

    if (qn.meta_type() == sml::meta_types::package)
        r.push_back(qn.type_name());

    return r;
}

enumerator_info transformer::transform(const sml::enumerator& e) const {
    enumerator_info r;
    r.name(e.name());
    r.value(e.value());
    r.documentation(r.documentation());
    return r;
}

enumeration_info transformer::transform(const sml::enumeration& e) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming enumeration: " << e.name();

    enumeration_info r;

    r.name(e.name().type_name());
    r.namespaces(transform(e.name()));
    r.documentation(e.documentation());

    for (const auto& en : e.enumerators())
        r.enumerators().push_back(transform(en));

    BOOST_LOG_SEV(lg, debug) << "Transformed enumeration: " << e.name();

    return r;
}

} }

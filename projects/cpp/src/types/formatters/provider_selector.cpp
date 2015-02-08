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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/object_types_io.hpp"
#include "dogen/cpp/types/formatters/selection_error.hpp"
#include "dogen/cpp/types/formatters/provider_selector.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formatters.provider_selector"));

const std::string unsupported_object_type("Object type is not supported: ");

}

namespace dogen {
namespace cpp {
namespace formatters {

provider_selector::provider_selector(const formatters::container& c) :
    regular_objects_(create_providers_for_regular_objects(c)) { }

std::forward_list<std::shared_ptr<formattables::provider_interface> >
provider_selector::
create_providers_for_regular_objects(const formatters::container& c) const {
    std::forward_list<std::shared_ptr<formattables::provider_interface> > r;

    for (const auto f : c.class_formatters()) {
        using pi = formattables::provider_interface;
        r.push_front(std::dynamic_pointer_cast<pi>(f));
    }

    return r;
}


const std::forward_list<std::shared_ptr<formattables::provider_interface> >&
provider_selector::
select_providers_for_object(const sml::object_types ot) const {
    switch(ot) {
    case sml::object_types::factory:
    case sml::object_types::user_defined_service:
    case sml::object_types::user_defined_value_object:
    case sml::object_types::entity:
    case sml::object_types::keyed_entity:
    case sml::object_types::versioned_key:
    case sml::object_types::unversioned_key:
    case sml::object_types::visitor:
        return regular_objects_;
        break;

    default:
        // FIXME
        BOOST_LOG_SEV(lg, error) << unsupported_object_type << ot;
        // BOOST_THROW_EXCEPTION(selection_error(unsupported_object_type +
        //         boost::lexical_cast<std::string>(ot)));
    };
    // FIXME
    return empty;
}

} } }

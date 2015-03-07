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
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/schema/io/value_types_io.hpp"
#include "dogen/dynamic/schema/types/text.hpp"
#include "dogen/dynamic/schema/types/boolean.hpp"
#include "dogen/dynamic/schema/types/building_error.hpp"
#include "dogen/dynamic/schema/types/text_collection.hpp"
#include "dogen/dynamic/schema/types/field_instance_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dynamic.schema.field_instance_factory"));

const std::string value_type_not_supported(
    "Value type is not supported by factory: ");
const std::string expected_at_most_one_element(
    "Expected at most one element");

}

namespace dogen {
namespace dynamic {
namespace schema {

field_instance_factory::field_instance_factory() : value_factory_() { }

void field_instance_factory::ensure_at_most_one_element(
    const std::list<std::string>& raw_values) const {

    if (raw_values.empty())
        return;

    const auto i(++raw_values.begin());
    if (i != raw_values.end()) {
        BOOST_LOG_SEV(lg, error) << expected_at_most_one_element;
        BOOST_THROW_EXCEPTION(building_error(expected_at_most_one_element));
    }
}

field_instance field_instance_factory::make(const field_definition& fd,
    const std::list<std::string>& v) const {
    field_instance r;

    switch (fd.type()) {
    case value_types::text:
        ensure_at_most_one_element(v);
        r.value(value_factory_.make_text(v.front()));
        break;

    case value_types::text_collection:
        r.value(value_factory_.make_text_collection(v));
        break;

    case value_types::boolean:
        ensure_at_most_one_element(v);
        r.value(value_factory_.make_boolean(v.front()));
        break;

    default:
        BOOST_LOG_SEV(lg, error) << value_type_not_supported << fd.type();
        BOOST_THROW_EXCEPTION(building_error(value_type_not_supported +
                boost::lexical_cast<std::string>(fd.type())));
    }
    return r;
}

} } }

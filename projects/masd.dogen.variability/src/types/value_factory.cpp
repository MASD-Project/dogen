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
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.variability/io/value_types_io.hpp"
#include "masd.dogen.variability/types/building_error.hpp"
#include "masd.dogen.variability/types/text.hpp"
#include "masd.dogen.variability/types/text_collection.hpp"
#include "masd.dogen.variability/types/boolean.hpp"
#include "masd.dogen.variability/types/number.hpp"
#include "masd.dogen.variability/types/key_value_pair.hpp"
#include "masd.dogen.variability/types/value_factory.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory("annotations.value_factory"));

const std::string invalid_numeric_value(
    "Invalid numeric value: ");
const std::string invalid_boolean_value(
    "Invalid boolean value: ");

const std::string value_type_not_supported(
    "Value type is not supported by factory: ");
const std::string expected_at_most_one_element(
    "Expected at most one element");

/**
 * @brief Provides support for "true" and "false" as Boolean values.
 */
class locale_bool {
public:
    locale_bool() {}
    locale_bool(bool data) : data(data) {}

public:
    operator bool() const { return data; }

    friend std::istream& operator>>(std::istream &s, locale_bool &b) {
        s >> std::boolalpha >> b.data;
        return s;
    }

private:
    bool data;
};

}

namespace masd::dogen::variability {

int value_factory::to_int(const std::string& s) const {
    try {
        return boost::lexical_cast<int>(s);
    } catch (const boost::bad_lexical_cast& /*e*/) {
        BOOST_LOG_SEV(lg, error) << invalid_numeric_value << s;
        BOOST_THROW_EXCEPTION(building_error(invalid_numeric_value + s));
    }
}

bool value_factory::to_bool(const std::string& s) const {
    try {
        return boost::lexical_cast<locale_bool>(s);
    } catch (const boost::bad_lexical_cast& /*e*/) {
        BOOST_LOG_SEV(lg, error) << invalid_boolean_value << s;
        BOOST_THROW_EXCEPTION(building_error(invalid_boolean_value + s));
    }
}

void value_factory::ensure_at_most_one_element(
    const std::list<std::string>& raw_values) const {

    if (raw_values.empty())
        return;

    const auto i(++raw_values.begin());
    if (i != raw_values.end()) {
        BOOST_LOG_SEV(lg, error) << expected_at_most_one_element;
        BOOST_THROW_EXCEPTION(building_error(expected_at_most_one_element));
    }
}

bool value_factory::is_collection(const value_types vt) const {
    return vt == value_types::text_collection;
}

boost::shared_ptr<value> value_factory::make_text(const std::string& v) const {
    return boost::make_shared<text>(v);
}

boost::shared_ptr<value> value_factory::make_text_collection(
    const std::list<std::string>& v) const {
    auto r(boost::make_shared<text_collection>(v));
    return r;
}

boost::shared_ptr<value>
value_factory::make_boolean(const std::string& v) const {
    return boost::make_shared<boolean>(to_bool(v));
}

boost::shared_ptr<value> value_factory::make_boolean(const bool v) const {
    return boost::make_shared<boolean>(v);
}

boost::shared_ptr<value>
value_factory::make_number(const std::string& v) const {
    return boost::make_shared<number>(to_int(v));
}

boost::shared_ptr<value> value_factory::make_number(const int v) const {
    return boost::make_shared<number>(v);
}

boost::shared_ptr<value> value_factory::
make_kvp(const std::unordered_map<std::string, std::string>& v) const {
    return boost::make_shared<key_value_pair>(v);
}

boost::shared_ptr<value> value_factory::make(const type& t,
    const std::list<std::string>& v) const {

    if (!is_collection(t.value_type()))
        ensure_at_most_one_element(v);

    switch (t.value_type()) {
    case value_types::text:
        return make_text(v.front());
    case value_types::text_collection:
        return make_text_collection(v);
    case value_types::boolean:
        return make_boolean(v.front());
    case value_types::number:
        return make_number(v.front());
    default:
        break;
    }

    BOOST_LOG_SEV(lg, error) << value_type_not_supported << t.value_type();
    BOOST_THROW_EXCEPTION(building_error(value_type_not_supported +
            boost::lexical_cast<std::string>(t.value_type())));
}

boost::shared_ptr<value> value_factory::make(const type& t,
    const std::unordered_map<std::string, std::string>& v) const {

    if (t.value_type() != value_types::key_value_pair) {
        BOOST_LOG_SEV(lg, error) << value_type_not_supported << t.value_type();
        BOOST_THROW_EXCEPTION(building_error(value_type_not_supported +
                boost::lexical_cast<std::string>(t.value_type())));
    }
    return make_kvp(v);
}

}

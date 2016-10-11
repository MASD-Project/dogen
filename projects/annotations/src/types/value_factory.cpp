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
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/io/value_types_io.hpp"
#include "dogen/annotations/types/building_error.hpp"
#include "dogen/annotations/types/text.hpp"
#include "dogen/annotations/types/text_collection.hpp"
#include "dogen/annotations/types/boolean.hpp"
#include "dogen/annotations/types/number.hpp"
#include "dogen/annotations/types/value_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("annotations.value_factory"));

const std::string invalid_numeric_value(
    "Invalid numeric value: ");
const std::string invalid_boolean_value(
    "Invalid boolean value: ");

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

namespace dogen {
namespace annotations {

int value_factory::to_int(const std::string& s) const {
    try {
        return boost::lexical_cast<int>(s);
    } catch (boost::bad_lexical_cast& e) {
        BOOST_LOG_SEV(lg, error) << invalid_numeric_value << s;
        BOOST_THROW_EXCEPTION(building_error(invalid_numeric_value + s));
    }
}

bool value_factory::to_bool(const std::string& s) const {
    try {
        return boost::lexical_cast<locale_bool>(s);
    } catch (boost::bad_lexical_cast& e) {
        BOOST_LOG_SEV(lg, error) << invalid_boolean_value << s;
        BOOST_THROW_EXCEPTION(building_error(invalid_boolean_value + s));
    }
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

} }

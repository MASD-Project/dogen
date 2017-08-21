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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/serialization/xml_helper.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/exception/utility_exception.hpp"
#include "dogen/yarn/io/meta_model/endomodel_io.hpp"
#include "dogen/yarn/serialization/meta_model/endomodel_ser.hpp"
#include "dogen/yarn/test/yarn_file_asserter.hpp"

namespace  {

using namespace dogen::utility::log;
logger lg(logger_factory("yarn.yarn_file_asserter"));

const std::string yarn_xml_extension(".xmlyarn");
const std::string file_is_not_assertable(
    "attempt to assert unsupported Yarn files");

}

namespace dogen {
namespace yarn {
namespace test {

bool yarn_file_asserter::is_assertable(boost::filesystem::path path) const {
    return (path.extension().string() == yarn_xml_extension);
}

meta_model::endomodel yarn_file_asserter::
read_xml(boost::filesystem::path path) const {
    using utility::serialization::xml_deserialize;
    return xml_deserialize<meta_model::endomodel>(path);
}

bool yarn_file_asserter::assert_file(boost::filesystem::path expected,
    boost::filesystem::path actual) const {

    if (!is_assertable(expected) || !is_assertable(actual)) {
        using utility::exception::exception;
        BOOST_THROW_EXCEPTION(exception(file_is_not_assertable));
    }

    const auto e(read_xml(expected));
    const auto a(read_xml(actual));

    if (e == a) {
        BOOST_LOG_SEV(lg, debug) << "Yarn file asserter: contents are equal.";
        return true;
    }

    BOOST_LOG_SEV(lg, error) << "Yarn file asserter: objects differ.";
    BOOST_LOG_SEV(lg, debug) << "expected: " << e;
    BOOST_LOG_SEV(lg, debug) << "actual: " << a;
    BOOST_LOG_SEV(lg, debug) << "diff -u " << expected.string() << " "
                             << actual.string();
    return false;
}

} } }

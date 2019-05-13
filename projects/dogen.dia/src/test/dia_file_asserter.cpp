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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/serialization/xml_helper.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.utility/types/exception/utility_exception.hpp"
#include "dogen.dia/serialization/diagram_ser.hpp"
#include "dogen.dia/io/diagram_io.hpp"
#include "dogen.dia/test/dia_file_asserter.hpp"

using namespace dogen::utility::log;

namespace {

logger lg(logger_factory("dia.dia_file_asserter"));

const std::string dia_xml_extension(".xmldia");
const std::string file_is_not_assertable(
    "attempt to assert unsupported Dia files");

}

namespace dogen::dia::test {

bool dia_file_asserter::is_assertable(boost::filesystem::path path) const {
    return (path.extension().string() == dia_xml_extension);
}

dia::diagram dia_file_asserter::read_xml(boost::filesystem::path path) const {
    using dogen::utility::serialization::xml_deserialize;
    return xml_deserialize<dia::diagram>(path);
}

bool dia_file_asserter::assert_file(boost::filesystem::path expected,
    boost::filesystem::path actual) const {

    if (!is_assertable(expected) || !is_assertable(actual)) {
        using dogen::utility::exception::exception;
        BOOST_THROW_EXCEPTION(exception(file_is_not_assertable));
    }

    const auto e(read_xml(expected));
    const auto a(read_xml(actual));

    if (e == a) {
        BOOST_LOG_SEV(lg, debug) << "Dia file asserter: contents are equal.";
        return true;
    }

    BOOST_LOG_SEV(lg, error) << "Dia file asserter: objects differ.";
    BOOST_LOG_SEV(lg, debug) << "expected: " << e;
    BOOST_LOG_SEV(lg, debug) << "actual: " << a;
    BOOST_LOG_SEV(lg, debug) << "diff -u " << expected.string()
                             << " " << actual.string();
    return false;
}

}

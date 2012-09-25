/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Dogen Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/serialization/xml_helper.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/exception/utility_exception.hpp"
#include "dogen/dia/serialization/diagram_ser.hpp"
#include "dogen/dia/io/diagram_io.hpp"
#include "dogen/dia/test/dia_file_asserter.hpp"

namespace  {

const std::string dia_xml_extension(".xmldia");
const std::string file_is_not_assertable(
    "attempt to assert unsupported Dia files");

}

namespace dogen {
namespace dia {
namespace test {

bool dia_file_asserter::is_assertable(boost::filesystem::path path) const {
    return (path.extension().string() == dia_xml_extension);
}

dia::diagram dia_file_asserter::read_xml(boost::filesystem::path path) const {
    using dogen::utility::serialization::xml_deserialize;
    return xml_deserialize<dia::diagram>(path);
}

bool dia_file_asserter::assert_file(boost::filesystem::path expected,
    boost::filesystem::path actual) const {

    if (!is_assertable(expected) || !is_assertable(actual))
        throw dogen::utility::exception::exception(file_is_not_assertable);


    const auto e(read_xml(expected));
    const auto a(read_xml(actual));

    using namespace dogen::utility::log;
    logger lg(logger_factory("dia_file_asserter"));

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

} } }

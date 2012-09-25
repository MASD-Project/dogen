/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/serialization/xml_helper.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/exception/utility_exception.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
#include "dogen/sml/test/sml_file_asserter.hpp"

namespace  {

const std::string sml_xml_extension(".xmlsml");
const std::string file_is_not_assertable(
    "attempt to assert unsupported SML files");

}

namespace dogen {
namespace sml {
namespace test {

bool sml_file_asserter::is_assertable(boost::filesystem::path path) const {
    return (path.extension().string() == sml_xml_extension);
}

sml::model sml_file_asserter::read_xml(boost::filesystem::path path) const {
    using utility::serialization::xml_deserialize;
    return xml_deserialize<sml::model>(path);
}

bool sml_file_asserter::assert_file(boost::filesystem::path expected,
    boost::filesystem::path actual) const {

    if (!is_assertable(expected) || !is_assertable(actual))
        throw utility::exception::exception(file_is_not_assertable);


    const auto e(read_xml(expected));
    const auto a(read_xml(actual));

    using namespace utility::log;
    logger lg(logger_factory("sml_file_asserter"));

    if (e == a) {
        BOOST_LOG_SEV(lg, debug) << "SML file asserter: contents are equal.";
        return true;
    }

    BOOST_LOG_SEV(lg, error) << "SML file asserter: objects differ.";
    BOOST_LOG_SEV(lg, debug) << "expected: " << e;
    BOOST_LOG_SEV(lg, debug) << "actual: " << a;
    BOOST_LOG_SEV(lg, debug) << "diff -u " << expected.string() << " "
                             << actual.string();
    return false;
}

} } }

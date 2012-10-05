/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/prototype/test_data/repository_factory.hpp"
#include "dogen/prototype/test_data/currency_td.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/prototype/io/versioned_key_io.hpp"
#include "dogen/prototype/io/unversioned_key_io.hpp"
#include "dogen/prototype/io/currency_io.hpp"
#include "dogen/prototype/io/repository_io.hpp"

namespace  {

const std::string test_module("prototype");
const std::string test_suite("streaming_spec");

}

BOOST_AUTO_TEST_SUITE(streaming)

BOOST_AUTO_TEST_CASE(test) {
    SETUP_TEST_LOG("test");
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()

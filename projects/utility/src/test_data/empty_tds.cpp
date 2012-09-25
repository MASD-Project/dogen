/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <string>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test_data/dia_sml.hpp"
#include "dogen/utility/test_data/resolver.hpp"
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/test_data/test_data.hpp"
#include "dogen/utility/test_data/empty_tds.hpp"

using boost::filesystem::path;

namespace {

const path data_set("empty_tds");

const path expected("empty_tds/expected");
const path actual_src("empty_tds/actual/src");
const path actual_include("empty_tds/actual/include");

const path actual("empty_tds/actual");

}

namespace dogen {
namespace utility {
namespace test_data {

path empty_tds::data_set() {
    return validating_resolver::resolve(::data_set);
}

path empty_tds::target() {
    using dogen::utility::test_data::dia_sml;
    return dia_sml::input_class_in_a_package_dia();
}

path empty_tds::expected() {
    return validating_resolver::resolve(::expected);
}
path empty_tds::actual_src() {
    return resolver::resolve(::actual_src);
}

path empty_tds::actual_include() {
    return resolver::resolve(::actual_include);
}

path empty_tds::actual() {
    return validating_resolver::resolve(::actual);
}

} } }

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
#include "dogen/utility/test_data/debug_dogen.hpp"

using boost::filesystem::path;

namespace {

const path data_set("debug_dogen");

const path expected("debug_dogen/expected");
const path actual_src("debug_dogen/actual/src");
const path actual_include("debug_dogen/actual/include");

const path actual("debug_dogen/actual");

}

namespace dogen {
namespace utility {
namespace test_data {

path debug_dogen::data_set() {
    return validating_resolver::resolve(::data_set);
}

path debug_dogen::target() {
    using dogen::utility::test_data::dia_sml;
    return dia_sml::input_class_in_a_package_dia();
}

path debug_dogen::expected() {
    return validating_resolver::resolve(::expected);
}
path debug_dogen::actual_src() {
    return resolver::resolve(::actual_src);
}

path debug_dogen::actual_include() {
    return resolver::resolve(::actual_include);
}

path debug_dogen::actual() {
    return validating_resolver::resolve(::actual);
}

} } }

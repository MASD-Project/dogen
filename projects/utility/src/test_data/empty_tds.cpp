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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
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

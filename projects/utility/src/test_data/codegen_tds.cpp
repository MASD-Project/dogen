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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seethe
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
#include "dogen/utility/test_data/resolver.hpp"
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/test_data/test_data.hpp"
#include "dogen/utility/test_data/codegen_tds.hpp"

using boost::filesystem::path;

namespace {

const std::string expected("/expected");
const std::string actual_src("/actual/src");
const std::string actual_include("/actual/include");
const std::string actual("/actual");

}

namespace dogen {
namespace utility {
namespace test_data {

codegen_tds::codegen_tds(boost::filesystem::path target)
    : target_(target), name_(target.stem().string()) { }

path codegen_tds::data_set() {
    return validating_resolver::resolve(name_);
}

path codegen_tds::target() {
    return target_;
}

path codegen_tds::expected() {
    return validating_resolver::resolve(name_ + ::expected);
}
path codegen_tds::actual_src() {
    return resolver::resolve(name_ + ::actual_src);
}

path codegen_tds::actual_include() {
    return resolver::resolve(name_ + ::actual_include);
}

path codegen_tds::actual() {
    return validating_resolver::resolve(name_ + ::actual);
}

} } }

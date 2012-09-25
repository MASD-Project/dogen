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

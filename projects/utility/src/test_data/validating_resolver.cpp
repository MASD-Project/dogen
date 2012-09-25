/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include "dogen/utility/filesystem/file_not_found.hpp"
#include "dogen/utility/test_data/resolver.hpp"
#include "dogen/utility/test_data/validating_resolver.hpp"

namespace dogen {
namespace utility {
namespace test_data {

boost::filesystem::path
validating_resolver::resolve(boost::filesystem::path relative) {
    boost::filesystem::path r(resolver::resolve(relative));
    if (boost::filesystem::exists(r))
        return r;

    using dogen::utility::filesystem::file_not_found;
    throw file_not_found(relative.string());
}

} } }

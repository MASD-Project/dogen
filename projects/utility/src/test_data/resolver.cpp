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
#include "dogen/utility/test_data/test_data_exception.hpp"
#include "dogen/utility/test_data/resolver.hpp"

namespace {

const std::string test_data_dir_not_found("Test data directory not found");
const std::string relative_path_to_td_dir("../test_data");

}

namespace dogen {
namespace utility {
namespace test_data {

boost::filesystem::path resolver::test_data_directory() {
    const boost::filesystem::path rel(relative_path_to_td_dir);
    const boost::filesystem::path abs(boost::filesystem::absolute(rel));

    if (!boost::filesystem::exists(abs))
    {
        using dogen::utility::test_data::exception;
        throw exception(test_data_dir_not_found + abs.string());
    }
    return abs;
}

boost::filesystem::path
resolver::resolve(boost::filesystem::path relative) {
    boost::filesystem::path r(test_data_directory());
    r /= relative;
    return r;
}

} } }

/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#ifndef DOGEN_YARN_TYPES_HELPERS_FILE_LINTER_HPP
#define DOGEN_YARN_TYPES_HELPERS_FILE_LINTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <set>
#include <list>
#include <vector>
#include <boost/filesystem/path.hpp>
#include "dogen/yarn/types/meta_model/text_model.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

class file_linter final {
private:
    /**
     * @brief Obtains a list of expected files for the supplied model.
     */
    static std::set<boost::filesystem::path>
    obtain_expected_files(const meta_model::text_model& tm);

    /**
     * @brief Returns all files in all managed directories.
     */
    static std::set<boost::filesystem::path> obtain_actual_files(
        const std::list<boost::filesystem::path>& managed_directories);


    /**
     * @brief Returns all files that are not expected.
     */
    static std::list<boost::filesystem::path> diff_expected_with_actual(
        const std::set<boost::filesystem::path>& expected,
        const std::set<boost::filesystem::path>& actual);

    /**
     * @brief Returns all files in the original list which do not
     * match any of the supplied ignore patterns.
     *
     * @pre Ignore patterns must be valid regular expressions.
     */
    static std::list<boost::filesystem::path>
    filter(const std::vector<std::string>& patterns,
        const std::list<boost::filesystem::path>& files);

public:
    static std::list<boost::filesystem::path>
    lint(const std::vector<std::string>& patterns,
        const meta_model::text_model& tm);
};

} } }

#endif

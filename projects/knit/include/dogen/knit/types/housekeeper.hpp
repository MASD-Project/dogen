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
#ifndef DOGEN_KNIT_TYPES_HOUSEKEEPER_HPP
#define DOGEN_KNIT_TYPES_HOUSEKEEPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <set>
#include <list>
#include <functional>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace knit {

/**
 * @brief Performs maintenance tasks on the files managed by knitter.
 *
 * The main responsibility of the housekeeper is to delete all the
 * extra files found in the directories managed by knitter, ignoring
 * those which match any of the regular expressions provided.
 */
class housekeeper {
public:
    typedef std::function<
    void(const std::list<boost::filesystem::path>&)> delete_fn;

public:
    housekeeper() = delete;
    housekeeper(const housekeeper&) = delete;
    ~housekeeper() = default;
    housekeeper(housekeeper&&) = default;
    housekeeper& operator=(const housekeeper&) = delete;

public:
    /**
     * @brief Initialise the housekeeper.
     *
     * @param ignore_patterns regular expressions for files to ignore
     * @param managed_directories directories to housekeep
     * @param expected_files files that should exist in managed directories.
     * @param fn function to execute when deleting files.
     */
    housekeeper(const std::list<std::string>& ignore_patterns,
        std::list<boost::filesystem::path> managed_directories,
        std::set<boost::filesystem::path> expected_files,
        delete_fn fn = nullptr);

private:
    /**
     * @brief Returns all files in all managed directories.
     */
    std::set<boost::filesystem::path> find_files_in_managed_directories() const;

    /**
     * @brief Remove files from list based on regular expressions
     * supplied on construction.
     */
    std::list<boost::filesystem::path>
    remove_ignores(const std::list<boost::filesystem::path>& files) const;

    /**
     * @brief Delete files from the filesystem.
     */
    void delete_files(const std::list<boost::filesystem::path>& files) const;

public:
    void tidy_up() const;

private:
    const std::list<std::string> ignore_patterns_;
    const std::list<boost::filesystem::path> managed_directories_;
    const std::set<boost::filesystem::path> expected_files_;
    delete_fn delete_fn_;
};

} }

#endif

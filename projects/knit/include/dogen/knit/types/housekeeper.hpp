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
#include <vector>
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
    typedef std::function<void (std::list<boost::filesystem::path>)> delete_fn;

public:
    housekeeper() = delete;
    housekeeper(const housekeeper&) = delete;
    ~housekeeper() = default;
    housekeeper(housekeeper&&) = default;
    housekeeper& operator=(const housekeeper&) = delete;

public:
    housekeeper(const std::vector<std::string>& ignore_patterns,
        std::vector<boost::filesystem::path> managed_directories,
        std::set<boost::filesystem::path> expected_files,
        delete_fn fn = nullptr);

private:
    void log_removing_file(boost::filesystem::path);

private:
    std::set<boost::filesystem::path>
    files_in_directory(boost::filesystem::path dir) const;
    std::set<boost::filesystem::path> find_actual_files() const;
    std::list<boost::filesystem::path>
    remove_ignores(std::list<boost::filesystem::path> files) const;
    void delete_files(std::list<boost::filesystem::path> files) const;

public:
    void tidy_up() const;

private:
    const std::vector<std::string> ignore_patterns_;
    const std::vector<boost::filesystem::path> managed_directories_;
    const std::set<boost::filesystem::path> expected_files_;
    delete_fn delete_fn_;
};

} }

#endif

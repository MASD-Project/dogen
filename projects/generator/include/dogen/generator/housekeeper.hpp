/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_HOUSEKEEPER_HPP
#define DOGEN_GENERATOR_HOUSEKEEPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <set>
#include <vector>
#include <functional>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace generator {

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
    housekeeper(std::vector<boost::filesystem::path> managed_directories,
        std::set<boost::filesystem::path> expected_files, bool verbose_,
        delete_fn fn = nullptr);

private:
    void log_removing_file(boost::filesystem::path);

private:
    std::set<boost::filesystem::path>
    files_in_directory(boost::filesystem::path dir) const;
    std::set<boost::filesystem::path> find_actual_files() const;
    void delete_files(std::list<boost::filesystem::path> files) const;

public:
    void tidy_up() const;

private:
    const std::vector<boost::filesystem::path> managed_directories_;
    const std::set<boost::filesystem::path> expected_files_;
    bool verbose_;
    delete_fn delete_fn_;
};

} }

#endif

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
#ifndef DOGEN_TEST_MODELS_NORTHWIND_TYPES_HYDRATOR_HPP
#define DOGEN_TEST_MODELS_NORTHWIND_TYPES_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <tuple>
#include <string>
#include <iosfwd>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include "dogen/test_models/northwind/types/repository.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

class hydrator final {
private:
    void populate_region(
        const std::unordered_map<std::string, std::string>& map,
        repository& rp) const;
    void populate_employees(
        const std::unordered_map<std::string, std::string>& map,
        repository& rp) const;

private:
    void log_tuple(
        const std::tuple<std::string, std::string, std::string>& t) const;

    std::tuple<std::string, std::string, std::string>
    section_insert_line(const std::string& s) const;

    void scrub_tuple(
        std::tuple<std::string, std::string, std::string>& t) const;

    std::unordered_map<std::string, std::string> map_keys_to_values(
        const std::string& keys, const std::string& values) const;

    void populate_repository(const std::string& entity,
        const std::unordered_map<std::string, std::string>& map,
        repository& rp) const;

private:
    repository read_stream(std::istream& s) const;

public:
    repository hydrate(std::istream& s) const;
    repository hydrate(const boost::filesystem::path& p) const;
};

} } }

#endif

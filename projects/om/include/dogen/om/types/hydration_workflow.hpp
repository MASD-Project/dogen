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
#ifndef DOGEN_OM_TYPES_HYDRATION_WORKFLOW_HPP
#define DOGEN_OM_TYPES_HYDRATION_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include "dogen/utility/filesystem/file.hpp"

namespace dogen {
namespace om {

/**
 * @brief Hydrates all files found in the input directories.
 */
template<typename Hydrator>
class hydration_workflow {
public:
    hydration_workflow() = default;
    hydration_workflow(const hydration_workflow&) = default;
    hydration_workflow(hydration_workflow&&) = default;
    ~hydration_workflow() = default;

private:
    /**
     * @brief Hydrate the file given by path p.
     */
    std::pair<std::string, typename Hydrator::value_type>
    hydrate(const boost::filesystem::path& p) {
        boost::filesystem::ifstream s(p);
        const auto value(hydrator_.hydrate(s));
        return std::make_pair(p.filename().generic_string(), value);
    }

public:
    hydration_workflow(const Hydrator& h) : hydrator_(h) { }

    /**
     * @brief Hydrates all files found on all the directories
     * supplied.
     */
    std::unordered_map<std::string, typename Hydrator::value_type>
    hydrate(const std::list<boost::filesystem::path>& dirs) {
        std::unordered_map<std::string, typename Hydrator::value_type> r;
        const auto files(dogen::utility::filesystem::find_files(dirs));
        for (const auto& f : files)
            r.insert(hydrate(f));
        return r;
    }

private:
    Hydrator hydrator_;
};

} }

#endif

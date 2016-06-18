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
#ifndef DOGEN_QUILT_CPP_TYPES_PROPERTIES_PATH_DERIVATIVES_FACTORY_HPP
#define DOGEN_QUILT_CPP_TYPES_PROPERTIES_PATH_DERIVATIVES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/config/types/cpp_options.hpp"
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/quilt.cpp/types/settings/path_settings.hpp"
#include "dogen/quilt.cpp/types/properties/path_derivatives.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

/**
 * @brief Generates the path derivatives for a given qualified name.
 */
class path_derivatives_factory {
public:
    path_derivatives_factory(
        const config::cpp_options& opts,
        const yarn::model& m,
        const std::unordered_map<std::string, settings::path_settings>& ps);

private:
    /**
     * @brief Builds a relative path from the top-level include
     * directory for the supplied qualified name.
     */
    boost::filesystem::path make_inclusion_path(
        const settings::path_settings& ps, const yarn::name& n) const;

    /**
     * @brief Builds an absolute path for the supplied qualified name.
     */
    boost::filesystem::path make_file_path(
        const settings::path_settings& ps,
        const boost::filesystem::path& inclusion_path,
        const yarn::name& n) const;

    /**
     * @brief Converts a relative path to an inclusion directive.
     */
    std::string to_inclusion_directive(const boost::filesystem::path& p) const;

    /**
     * @brief Converts a relative path to a header file into a C++
     * header guard name.
     */
    std::string to_header_guard_name(const boost::filesystem::path& p) const;

public:
    /**
     * @brief Generate path derivatives.
     */
    std::unordered_map<std::string, path_derivatives>
    make(const yarn::name& n) const;

private:
    const config::cpp_options& options_;
    const yarn::model& model_;
    const std::unordered_map<std::string, settings::path_settings>&
    path_settings_;
};

} } } }

#endif

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
#ifndef DOGEN_KNIT_TYPES_BACKENDS_CPP_BACKEND_HPP
#define DOGEN_KNIT_TYPES_BACKENDS_CPP_BACKEND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/cpp/types/formattables/project.hpp"
#include "dogen/knit/types/backends/backend_interface.hpp"

namespace dogen {
namespace knit {
namespace backends {

class cpp_backend : public backend_interface {
public:
    cpp_backend() = default;
    cpp_backend(const cpp_backend&) = default;
    cpp_backend(cpp_backend&&) = default;
    cpp_backend& operator=(const cpp_backend&) = default;

public:
    virtual ~cpp_backend() noexcept;

private:
    /**
     * @brief Creates the c++ project.
     */
    cpp::formattables::project
    create_project(const config::knitting_options& o,
        const sml::model& model) const;

    /**
     * @brief Formats the project into files.
     */
    std::forward_list<formatters::file>
    format_files(const config::knitting_options& o,
        const cpp::formattables::project& p) const;

    /**
     * @brief Generates files with the new-world formatters
     */
    std::forward_list<formatters::file>
    format_files(const config::knitting_options& o,
        const dynamic::repository& rp,
        const sml::model& m) const;

    /**
     * @brief Overrides the old-world files with the new-world
     * versions.
     */
    std::forward_list<formatters::file> override_legacy_files(
        const std::forward_list<formatters::file>& old_world,
        const std::forward_list<formatters::file>& new_world) const;

public:
    std::forward_list<boost::filesystem::path>
    managed_directories(const config::knitting_options& o,
        const sml::model& m) const override;

    std::forward_list<formatters::file> generate(
        const config::knitting_options& o,
        const dynamic::repository& rp,
        const sml::model& m) override;
};

} } }

#endif

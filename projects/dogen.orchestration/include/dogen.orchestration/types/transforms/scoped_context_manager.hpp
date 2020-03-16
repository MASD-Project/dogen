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
#ifndef DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_SCOPED_CONTEXT_MANAGER_HPP
#define DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_SCOPED_CONTEXT_MANAGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen/types/configuration.hpp"
#include "dogen.orchestration/types/transforms/context.hpp"

namespace dogen::orchestration::transforms {

/**
 * @brief Manages the overall context.
 */
class scoped_context_manager final {
public:
    scoped_context_manager(const configuration& cfg,
        const std::string& activity,
        const boost::filesystem::path& output_directory);
    ~scoped_context_manager();

public:
    const transforms::context& context() const;

private:
    const transforms::context context_;
};

/**
 * @brief Manages just the injection context.
 */
class scoped_injection_context_manager final {
public:
    scoped_injection_context_manager(const configuration& cfg,
        const std::string& activity);
    ~scoped_injection_context_manager();

public:
    const injection::transforms::context& context() const;

private:
    const injection::transforms::context context_;
};

}

#endif

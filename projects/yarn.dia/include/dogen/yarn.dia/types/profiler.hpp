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
#ifndef DOGEN_YARN_DIA_TYPES_PROFILER_HPP
#define DOGEN_YARN_DIA_TYPES_PROFILER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/yarn.dia/types/object_types.hpp"
#include "dogen/yarn.dia/types/profile.hpp"
#include "dogen/yarn.dia/types/processed_object_fwd.hpp"

namespace dogen {
namespace yarn {
namespace dia {

/**
 * @brief Generates a @ref profile of the processed object.
 */
class profiler {
public:
    profiler() = default;
    profiler(const profiler&) = delete;
    profiler(profiler&&) = default;

private:
    /**
     * @brief Given a string with a valid dia object type, updates the
     * processed object type flags.
     */
    void process_object_type(profile& o, const object_types ot) const;

    /**
     * @brief Given a string with a valid stereotype, updates the
     * profile's stereotype flags.
     */
    void process_stereotype(profile& o, const std::string& s) const;

    void post_process(profile& o) const;

public:
    /**
     * @brief Perform the profiling.
     */
    profile generate(const processed_object& o);
};

} } }

#endif

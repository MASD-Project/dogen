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
#ifndef DOGEN_DIA_TO_SML_TYPES_PROFILER_HPP
#define DOGEN_DIA_TO_SML_TYPES_PROFILER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/dia_to_sml/types/object_types.hpp"
#include "dogen/dia_to_sml/types/profile.hpp"
#include "dogen/dia_to_sml/types/processed_object_fwd.hpp"

namespace dogen {
namespace dia_to_sml {

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

public:
    /**
     * @brief Perform the profiling.
     */
    profile generate(const processed_object& o);
};

} }

#endif

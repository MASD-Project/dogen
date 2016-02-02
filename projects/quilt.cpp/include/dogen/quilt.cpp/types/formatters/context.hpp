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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_CONTEXT_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/quilt.cpp/types/settings/bundle.hpp"
#include "dogen/quilt.cpp/types/settings/helper_settings.hpp"
#include "dogen/quilt.cpp/types/formattables/formatter_properties.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

/**
 * @brief Supplies additional information required for formatting.
 */
class context final {
public:
    context(
        const settings::bundle& bundle,
        const std::unordered_map<std::string,
        formattables::formatter_properties>& formatter_properties,
        const std::unordered_map<std::string,
        settings::helper_settings>& helper_settings);

public:
    const settings::bundle& bundle() const;
    const std::unordered_map<std::string, formattables::formatter_properties>&
        formatter_properties() const;
    const std::unordered_map<std::string, settings::helper_settings>&
        helper_settings() const;

private:
    const settings::bundle& bundle_;
    const std::unordered_map<std::string, formattables::formatter_properties>&
        formatter_properties_;
    const std::unordered_map<std::string, settings::helper_settings>&
        helper_settings_;
};

} } } }

#endif

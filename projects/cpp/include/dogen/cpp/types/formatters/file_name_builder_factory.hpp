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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_FILE_NAME_BUILDER_FACTORY_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_FILE_NAME_BUILDER_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/sml/types/qname.hpp"
#include "dogen/cpp/types/settings/selector.hpp"
#include "dogen/cpp/types/formatters/file_name_builder.hpp"
#include "dogen/cpp/types/formatters/formatter_interface.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

/**
 * @brief Sets up a file name builder from settings.
 */
class file_name_builder_factory {
public:
    /**
     * @brief Set up the file name builder for a given formatter and
     * qualified name.
     */
    file_name_builder make(const settings::selector& s,
        const formatter_interface& f, const sml::qname qn) const;
};

} } }

#endif

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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_SERIALIZATION_FORWARD_DECLARATIONS_FORMATTER_STITCH_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_SERIALIZATION_FORWARD_DECLARATIONS_FORMATTER_STITCH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <ostream>
#include <boost/optional.hpp>
#include "dogen/formatters/types/general_settings.hpp"
#include "dogen/cpp/types/settings/formatter_settings.hpp"
#include "dogen/cpp/types/formattables/forward_declarations_info.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace serialization {

void forward_declarations_formatter_stitch(std::ostream& s,
    const boost::optional<dogen::formatters::general_settings>& gs,
    const settings::formatter_settings& fs,
    const formattables::forward_declarations_info& fd);

} } } }

#endif

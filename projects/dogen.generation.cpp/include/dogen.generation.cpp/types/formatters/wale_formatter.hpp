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
#ifndef DOGEN_GENERATION_CPP_TYPES_FORMATTERS_WALE_FORMATTER_HPP
#define DOGEN_GENERATION_CPP_TYPES_FORMATTERS_WALE_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.extraction/types/meta_model/artefact.hpp"
#include "dogen.logical/types/meta_model/element_fwd.hpp"
#include "dogen.generation.cpp/types/formattables/locator.hpp"
#include "dogen.generation.cpp/types/formatters/artefact_formatter_interface.hpp"

namespace dogen::generation::cpp::formatters {

class wale_formatter final {
private:
    bool is_header(const inclusion_support_types ist) const;

public:
    extraction::meta_model::artefact format(
        const formattables::locator& l,
        const artefact_formatter_interface& stock_formatter,
        const context& ctx, const logical::meta_model::element& e) const;
};

}

#endif

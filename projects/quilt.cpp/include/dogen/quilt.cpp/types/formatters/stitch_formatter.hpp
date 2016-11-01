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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_STITCH_FORMATTER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_STITCH_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/annotations/types/annotation_groups_factory.hpp"
#include "dogen/formatters/types/artefact.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/yarn/types/element_fwd.hpp"
#include "dogen/stitch/types/instantiator.hpp"
#include "dogen/quilt.cpp/types/formattables/artefact_properties.hpp"
#include "dogen/quilt.cpp/types/formatters/artefact_formatter_interface.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

class stitch_formatter final {
public:
    stitch_formatter(const annotations::type_repository& atrp,
        const annotations::annotation_groups_factory& af,
        const dogen::formatters::repository& frp);

private:
    bool is_header(const inclusion_support_types ist) const;

public:
    dogen::formatters::artefact
    format(const artefact_formatter_interface& stock_formatter,
        const context& ctx, const yarn::element& e,
        const bool generate_wale_kvps = false) const;

private:
    const stitch::instantiator instantiator_;
};

} } } }

#endif

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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTERS_STITCH_FORMATTER_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTERS_STITCH_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.annotations/types/annotation_factory.hpp"
#include "masd.dogen.annotations/types/annotation_expander.hpp"
#include "masd.dogen.extraction/types/meta_model/artefact.hpp"
#include "masd.dogen.coding/types/meta_model/element_fwd.hpp"
#include "masd.dogen.templating/types/stitch/instantiator.hpp"
#include "masd.dogen.generation.cpp/types/formattables/artefact_properties.hpp"
#include "masd.dogen.generation.cpp/types/formatters/artefact_formatter_interface.hpp"

namespace masd::dogen::generation::cpp::formatters {

class stitch_formatter final {
public:
    stitch_formatter(const annotations::type_repository& atrp,
        const annotations::annotation_factory& af,
        const annotations::annotation_expander& ae);

private:
    bool is_header(const inclusion_support_types ist) const;

public:
    extraction::meta_model::artefact
    format(const artefact_formatter_interface& stock_formatter,
        const context& ctx, const coding::meta_model::element& e) const;

private:
    const templating::stitch::instantiator instantiator_;
};

}

#endif

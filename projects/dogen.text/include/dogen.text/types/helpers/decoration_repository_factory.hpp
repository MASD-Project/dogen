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
#ifndef DOGEN_TEXT_TYPES_HELPERS_DECORATION_REPOSITORY_FACTORY_HPP
#define DOGEN_TEXT_TYPES_HELPERS_DECORATION_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.logical/types/entities/name.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/helpers/decoration_repository.hpp"
#include "dogen.text/types/entities/model.hpp"

namespace dogen::text::helpers {

class decoration_repository_factory final {
private:
    bool is_meta_element(const logical::entities::name& me,
        const logical::entities::element& e) const;

private:
    void handle_licence(
        const boost::shared_ptr<logical::entities::element> e,
        logical::helpers::decoration_repository& drp) const;
    void handle_generation_marker(
        const boost::shared_ptr<logical::entities::element> e,
        logical::helpers::decoration_repository& drp) const;

    /**
     * @brief Organises all modelines by modeline group and by
     * technical space.
     */
    void handle_modeline_group(
        const boost::shared_ptr<logical::entities::element> e,
        logical::helpers::decoration_repository& drp) const;

public:
    logical::helpers::decoration_repository
    make(const entities::model& m) const;
};

}

#endif

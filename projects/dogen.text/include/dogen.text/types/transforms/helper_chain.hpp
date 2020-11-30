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
#ifndef DOGEN_TEXT_TYPES_TRANSFORMS_HELPER_CHAIN_HPP
#define DOGEN_TEXT_TYPES_TRANSFORMS_HELPER_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <ostream>
#include <boost/shared_ptr.hpp>
#include "dogen.physical/types/entities/model.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.text/types/transforms/registrar.hpp"

namespace dogen::text::transforms {

class helper_chain final {
public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static text::transforms::registrar& registrar();

    /**
     * @brief Physical model with meta-model properties.
     *
     * FIXME: big hack until we update the interfaces of the M2T
     * transforms.
     */
    static physical::entities::model* model_;

private:
    std::list<std::shared_ptr<transforms::helper_transform>>
    get_helpers(const physical::entities::artefact& a,
        const logical::entities::helper_properties& hp) const;

public:
    void apply(std::ostream& os, const logical::entities::element& e,
        const physical::entities::artefact& a);

private:
    static std::shared_ptr<text::transforms::registrar> registrar_;
};

}

#endif

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
#ifndef DOGEN_CPP_TYPES_ANNOTATIONS_ELEMENT_ANNOTATIONS_REPOSITORY_FACTORY_HPP
#define DOGEN_CPP_TYPES_ANNOTATIONS_ELEMENT_ANNOTATIONS_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/yarn/types/model.hpp"
#include "dogen/quilt.cpp/types/annotations/opaque_annotations_builder.hpp"
#include "dogen/quilt.cpp/types/annotations/element_annotations_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

/**
 * @brief Creates the element annotations repository.
 */
class element_annotations_repository_factory {
public:
    /**
     * @brief Create the element annotations repository.
     */
    element_annotations_repository make(const opaque_annotations_builder& osb,
        const yarn::model& m) const;
};

} } } }

#endif

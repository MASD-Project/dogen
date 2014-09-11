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
#ifndef DOGEN_SML_TYPES_META_DATA_SCOPED_REGISTRATION_HPP
#define DOGEN_SML_TYPES_META_DATA_SCOPED_REGISTRATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/sml/types/meta_data/workflow.hpp"

namespace dogen {
namespace sml {
namespace meta_data {

template<typename T>
class root_enricher_scoped_registration {
public:
    root_enricher_scoped_registration() {
        workflow::register_root_enricher(std::shared_ptr<T>(new T));
    }
};

template<typename T>
class ordinary_enricher_scoped_registration {
public:
    ordinary_enricher_scoped_registration() {
        workflow::register_ordinary_enricher(std::shared_ptr<T>(new T));
    }
};

} } }

#endif

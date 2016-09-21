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
#ifndef DOGEN_CPP_TYPES_ANNOTATIONS_OPAQUE_ANNOTATIONS_FACTORY_INTERFACE_HPP
#define DOGEN_CPP_TYPES_ANNOTATIONS_OPAQUE_ANNOTATIONS_FACTORY_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/shared_ptr.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/quilt.cpp/types/annotations/opaque_annotations.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

class opaque_annotations_factory_interface {
public:
    opaque_annotations_factory_interface() = default;
    opaque_annotations_factory_interface(
        const opaque_annotations_factory_interface&) = delete;
    opaque_annotations_factory_interface(
        opaque_annotations_factory_interface&&) = default;
    virtual ~opaque_annotations_factory_interface() noexcept = 0;

public:
    /**
     * @brief Key to use for the annotations produced by this factory.
     */
    virtual std::string annotations_key() const = 0;

    /**
     * @brief Sets up the factory for use.
     */
    virtual void setup(const dynamic::repository& rp) = 0;

    /**
     * @brief Produces the special annotations for this formatter.
     */
    virtual boost::shared_ptr<opaque_annotations>
    make(const dynamic::object& o) const = 0;
};

} } } }

#endif

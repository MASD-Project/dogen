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
#ifndef DOGEN_CPP_TYPES_ANNOTATIONS_OPAQUE_ANNOTATIONS_BUILDER_HPP
#define DOGEN_CPP_TYPES_ANNOTATIONS_OPAQUE_ANNOTATIONS_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/quilt.cpp/types/annotations/opaque_annotations.hpp"
#include "dogen/quilt.cpp/types/annotations/registrar.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

class opaque_annotations_builder {
public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static cpp::annotations::registrar& registrar();

public:
    explicit opaque_annotations_builder(const dynamic::repository& drp);

private:
    /**
     * @brief Sets up the builder.
     */
    void setup(const dynamic::repository& drp);

    /**
     * @brief Ensures the builder is in a valid state.
     */
    void validate() const;

public:
    /**
     * @brief Generates the opaque annotations.
     */
    std::unordered_map<std::string, boost::shared_ptr<opaque_annotations>>
    build(const dynamic::object& o) const;

private:
    static std::shared_ptr<cpp::annotations::registrar> registrar_;
};

} } } }

#endif

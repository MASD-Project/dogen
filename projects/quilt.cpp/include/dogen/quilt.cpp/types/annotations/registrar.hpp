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
#ifndef DOGEN_CPP_TYPES_ANNOTATIONS_REGISTRAR_HPP
#define DOGEN_CPP_TYPES_ANNOTATIONS_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <forward_list>
#include <boost/shared_ptr.hpp>
#include "dogen/quilt.cpp/types/annotations/opaque_annotations_factory_interface_fwd.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

/**
 * @brief Manages factory registration.
 */
class registrar final {
public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

public:
    /**
     * @brief Registers an opaque annotations factory.
     */
    void register_opaque_annotations_factory(
        boost::shared_ptr<opaque_annotations_factory_interface> f);

    /**
     * @brief Returns all registered opaque annotations factories.
     */
    const std::forward_list<
        boost::shared_ptr<opaque_annotations_factory_interface>
    >& opaque_annotations_factories() const;

private:
    std::forward_list<
        boost::shared_ptr<opaque_annotations_factory_interface>
    > opaque_annotations_factories_;
};

} } } }

#endif

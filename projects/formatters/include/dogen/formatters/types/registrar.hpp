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
#ifndef DOGEN_FORMATTERS_TYPES_REGISTRAR_HPP
#define DOGEN_FORMATTERS_TYPES_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/shared_ptr.hpp>
#include "dogen/formatters/types/workflow.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Helper class to simplify the registration of transformer and
 * formatters into the workflow.
 *
 * To use it, just declare an instance in an unnamed namespace in the
 * translation unit of your formatter or transformer. Can also be done
 * in other places, but remember that the workflow is not thread-safe.
 */
template<typename RegistrableInterface>
class registrar {
public:
    registrar(const registrar&) = delete;
    registrar(registrar&&) = delete;
    ~registrar() noexcept = default;

public:
    /**
     * @brief Registers the interface with the workflow.
     */
    explicit registrar(boost::shared_ptr<RegistrableInterface> ri) {
        workflow::register_interface(ri);
    }
};

} }

#endif

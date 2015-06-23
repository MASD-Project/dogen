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
#ifndef DOGEN_CPP_TYPES_SETTINGS_OPAQUE_SETTINGS_BUILDER_HPP
#define DOGEN_CPP_TYPES_SETTINGS_OPAQUE_SETTINGS_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/cpp/types/settings/opaque_settings.hpp"
#include "dogen/cpp/types/settings/registrar.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class opaque_settings_builder {
public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static cpp::settings::registrar& registrar();

public:
    /**
     * @brief Sets up the builder.
     */
    void setup(const dynamic::repository& rp);

public:
    /**
     * @brief Ensures the builder is in a valid state.
     */
    void validate() const;

public:
    /**
     * @brief Generates the opaque settings.
     */
    std::unordered_map<std::string, boost::shared_ptr<opaque_settings>>
    build(const dynamic::object& o) const;

private:
    static std::shared_ptr<cpp::settings::registrar> registrar_;
};

} } }

#endif

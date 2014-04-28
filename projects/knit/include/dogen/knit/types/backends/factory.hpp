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
#ifndef DOGEN_KNIT_TYPES_BACKENDS_FACTORY_HPP
#define DOGEN_KNIT_TYPES_BACKENDS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/config/types/settings.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/knit/types/backends/backend.hpp"

namespace dogen {
namespace knit {
namespace backends {

class factory {
public:
    factory() = delete;
    factory(const factory&) = default;
    ~factory() = default;
    factory(factory&&) = default;
    factory& operator=(const factory&) = default;

public:
    typedef std::vector<backend::ptr> result_type;

public:
    factory(const sml::model& model, const config::settings& settings);

private:
    void log_cpp_backend_disabled() const;

public:
    result_type create() const;

private:
    const config::settings& settings_;
    const sml::model& model_;
};

} } }

#endif

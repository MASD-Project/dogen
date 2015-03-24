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

#include "dogen/config/types/knitting_options.hpp"
#include "dogen/knit/types/backends/backend.hpp"
#include "dogen/sml/types/model.hpp" // FIXME
#include "dogen/dynamic/schema/types/repository.hpp" // FIXME

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
    factory(const config::knitting_options& o,
        const dynamic::schema::repository& rp,
        const sml::model& model);

private:
    void log_cpp_backend_disabled() const;

public:
    result_type create() const;

private:
    const config::knitting_options& options_;
    const dynamic::schema::repository& repository_;
    const sml::model& model_;
};

} } }

#endif

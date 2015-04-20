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
#ifndef DOGEN_KNIT_TYPES_BACKENDS_BACKEND_INTERFACE_HPP
#define DOGEN_KNIT_TYPES_BACKENDS_BACKEND_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/formatters/types/file.hpp"
#include "dogen/config/types/knitting_options.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/dynamic/schema/types/repository.hpp" // FIXME

namespace dogen {
namespace knit {
namespace backends {

class backend_interface {
public:
    backend_interface(const backend_interface&) = default;
    backend_interface(backend_interface&&) = default;
    backend_interface& operator=(const backend_interface&) = default;

public:
    virtual ~backend_interface() noexcept = 0;

protected:
    backend_interface() = default;

public:
    /**
     * @brief Get all directories managed by this backend.
     */
    virtual std::forward_list<boost::filesystem::path>
    managed_directories(const config::knitting_options& o,
        const sml::model& m) const = 0;

    /**
     * @brief Generate code for this backend.
     */
    virtual std::forward_list<formatters::file> generate(
        const config::knitting_options& o,
        const dynamic::schema::repository& rp, const sml::model& m) = 0;
};

} } }

#endif

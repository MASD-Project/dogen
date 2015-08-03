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
#ifndef DOGEN_BACKEND_TYPES_WORKFLOW_HPP
#define DOGEN_BACKEND_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/config/types/knitting_options.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/tack/types/model.hpp"
#include "dogen/formatters/types/file.hpp"
#include "dogen/backend/types/backend_registrar.hpp"
#include "dogen/backend/types/backend_interface.hpp"

namespace dogen {
namespace backend {

/**
 * @brief Manages the entire backend workflow.
 */
class workflow {
public:
    workflow(const config::knitting_options& o,
        const dynamic::repository& rp);

public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static backend::backend_registrar& registrar();

    /**
     * @brief Returns all directories managed by all backends.
     */
    std::forward_list<boost::filesystem::path>
    managed_directories(const tack::model& m) const;

    /**
     * @brief Generates files for the supplied model using all
     * registered backends.
     */
    std::forward_list<formatters::file> execute(const tack::model& m) const;

private:
    static std::shared_ptr<backend::backend_registrar> registrar_;
    const config::knitting_options knitting_options_;
    const dynamic::repository& repository_;
};

} }

#endif

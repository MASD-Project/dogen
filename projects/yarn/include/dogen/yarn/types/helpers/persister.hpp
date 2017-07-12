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
#ifndef DOGEN_YARN_TYPES_HELPERS_PERSISTER_HPP
#define DOGEN_YARN_TYPES_HELPERS_PERSISTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen/yarn/types/meta_model/intermediate_model.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

/**
 * @brief Persists a model to a file.
 */
class persister {
public:
    /**
     * @brief Saves a model to the filesystem.
     *
     * @param m model to save.
     * @param p full path of the file.
     *
     * The format to use is inferred by the extension supplied. If the
     * extension supplied is not supported, an extension is thrown.
     */
    static void persist(const meta_model::intermediate_model& m,
        const boost::filesystem::path& p);
};

} } }

#endif

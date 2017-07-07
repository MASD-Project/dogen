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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_INITIAL_TARGET_CHAIN_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_INITIAL_TARGET_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/transforms/context.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

/**
 * @brief Obtains the target model from a source, as per the supplied
 * options and performs some initial pre-processing on it.
 */
class initial_target_chain final {
public:
    /**
     * @brief Checks that the supplied path is absolute.
     *
     * We require the target path supplied to us to be an absolute
     * path. This is because we perform calculations off of it such as
     * locating the reference models and so forth. The end-user is not
     * required to have supplied an absolute path, but someone above
     * us must be responsible for ensuring we receive an absolute
     * path.
     */
    static void ensure_target_path_is_absolute(
        const boost::filesystem::path& p);

public:
    static intermediate_model transform(const context& ctx);
};

} } }

#endif

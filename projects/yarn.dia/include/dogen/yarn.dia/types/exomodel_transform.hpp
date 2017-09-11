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
#ifndef DOGEN_YARN_DIA_TYPES_EXOMODEL_TRANSFORM_HPP
#define DOGEN_YARN_DIA_TYPES_EXOMODEL_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen/yarn/types/transforms/exomodel_transform_interface.hpp"

namespace dogen {
namespace yarn {
namespace dia {

class exomodel_transform final :
        public yarn::transforms::exomodel_transform_interface {
public:
    exomodel_transform() = default;
    ~exomodel_transform() noexcept;

public:
    std::string id() const override;
    yarn::transforms::exomodel_transform_types transform_types() const override;
    std::list<std::string> supported_extensions() const override;
    meta_model::exomodel
    transform(const transforms::context& ctx,
        const boost::filesystem::path& p) override;
    void transform(const transforms::context& ctx,
        const meta_model::exomodel& em,
        const boost::filesystem::path& p) override;
};

} } }

#endif

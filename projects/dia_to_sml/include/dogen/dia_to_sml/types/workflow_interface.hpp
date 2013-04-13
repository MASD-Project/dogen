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
#ifndef DOGEN_DIA_TO_SML_TYPES_WORKFLOW_INTERFACE_HPP
#define DOGEN_DIA_TO_SML_TYPES_WORKFLOW_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/dia/types/diagram_fwd.hpp"
#include "dogen/sml/types/model_fwd.hpp"

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Transform a dia diagram into an sml model.
 */
class workflow_interface {
public:
    workflow_interface() = default;
    workflow_interface(const workflow_interface&) = delete;
    workflow_interface(workflow_interface&&) = default;
    virtual ~workflow_interface() noexcept = 0;

public:
    /**
     * @brief Runs the transformation.
     */
    virtual sml::model execute(const dia::diagram& diagram,
        const std::string& model_name,
        const std::string& external_package_path,
        bool is_target) = 0;
};

} }

#endif

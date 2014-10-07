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
#ifndef DOGEN_FRONTEND_TYPES_DIA_FRONTEND_HPP
#define DOGEN_FRONTEND_TYPES_DIA_FRONTEND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/frontend/types/frontend_interface.hpp"

namespace dogen {
namespace frontend {

/**
 * @brief Frontend that reads Dia diagrams and generates partial SML
 * models.
 */
class dia_frontend final : public frontend_interface {
public:
    dia_frontend() = default;
    dia_frontend(const dia_frontend&) = delete;
    dia_frontend(dia_frontend&&) = default;
    virtual ~dia_frontend() noexcept;

public:
    std::string id() const override;
    std::list<std::string> supported_extensions() const override;
    sml::model generate(const input_descriptor& d,
        const frontend_settings& s) override;
};

} }

#endif

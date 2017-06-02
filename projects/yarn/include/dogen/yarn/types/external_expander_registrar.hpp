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
#ifndef DOGEN_YARN_TYPES_EXTERNAL_EXPANDER_REGISTRAR_HPP
#define DOGEN_YARN_TYPES_EXTERNAL_EXPANDER_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <memory>
#include "dogen/yarn/types/external_expander_interface.hpp"

namespace dogen {
namespace yarn {

class external_expander_registrar {
public:
    void register_external_expander(
        std::shared_ptr<const external_expander_interface> ee);

public:
    void validate() const;
    std::list<std::shared_ptr<const external_expander_interface>>
    external_expanders() const;

private:
    std::list<std::shared_ptr<const external_expander_interface>>
    external_expanders_;
};

/*
 * Helper method to register external expanders.
 */
template<typename ExternalExpander>
inline void register_external_expander(external_expander_registrar& rg) {
    auto ee(std::make_shared<ExternalExpander>());
    rg.register_external_expander(ee);
}

} }

#endif

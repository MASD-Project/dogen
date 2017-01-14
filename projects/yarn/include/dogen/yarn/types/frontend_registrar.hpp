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
#ifndef DOGEN_YARN_TYPES_FRONTEND_REGISTRAR_HPP
#define DOGEN_YARN_TYPES_FRONTEND_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <memory>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/yarn/types/frontend_interface.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Keeps track of all the available frontends.
 */
class frontend_registrar {
public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

    /*
     * @brief Registers a given frontend.
     *
     * @pre Frontend is not yet registered.
     */
    void register_frontend(std::shared_ptr<frontend_interface> fi);

    /**
     * @brief Returns the frontend that handles the supplied path.
     *
     * @pre A frontend must have been registered for this path.
     */
    frontend_interface& frontend_for_path(const boost::filesystem::path& p);

private:
    std::unordered_map<std::string, std::shared_ptr<frontend_interface>>
    frontends_;
};

/*
 * Helper method to register frontends.
 */
template<typename Frontend>
inline void register_frontend(frontend_registrar& rg) {
    auto fe(std::make_shared<Frontend>());
    rg.register_frontend(fe);
}

} }

#endif

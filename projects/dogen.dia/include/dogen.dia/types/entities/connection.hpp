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
#ifndef DOGEN_DIA_TYPES_ENTITIES_CONNECTION_HPP
#define DOGEN_DIA_TYPES_ENTITIES_CONNECTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::dia::entities {

/**
 * @brief Connection between entities in a Dia diagram.
 */
class connection final {
public:
    connection() = default;
    connection(const connection&) = default;
    connection(connection&&) = default;
    ~connection() = default;

public:
    connection(
        const std::string& handle,
        const std::string& to,
        const std::string& connection_slot);

public:
    /**
     * @brief Internal handle for the connection.
     */
    /**@{*/
    const std::string& handle() const;
    std::string& handle();
    void handle(const std::string& v);
    void handle(const std::string&& v);
    /**@}*/

    /**
     * @brief Object we're connected to.
     */
    /**@{*/
    const std::string& to() const;
    std::string& to();
    void to(const std::string& v);
    void to(const std::string&& v);
    /**@}*/

    /**
     * @brief Number of the connection slot we're connected to.
     *
     * This is known in Dia as a connection but to avoid confusion between the class and the slot concepts,
     * we renamed it.
     */
    /**@{*/
    const std::string& connection_slot() const;
    std::string& connection_slot();
    void connection_slot(const std::string& v);
    void connection_slot(const std::string&& v);
    /**@}*/

public:
    bool operator==(const connection& rhs) const;
    bool operator!=(const connection& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(connection& other) noexcept;
    connection& operator=(connection other);

private:
    std::string handle_;
    std::string to_;
    std::string connection_slot_;
};

}

namespace std {

template<>
inline void swap(
    dogen::dia::entities::connection& lhs,
    dogen::dia::entities::connection& rhs) {
    lhs.swap(rhs);
}

}

#endif

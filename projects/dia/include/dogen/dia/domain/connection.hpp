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
#ifndef DOGEN_DIA_DOMAIN_CONNECTION_HPP
#define DOGEN_DIA_DOMAIN_CONNECTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace dia {

namespace serialization { namespace detail { class connection_serializer; } }

/**
 * @brief Connection between entities in a Dia diagram.
 */
class connection {
public:
    connection() = default;
    connection(const connection&) = default;
    connection(connection&&) = default;
    ~connection() = default;
    connection& operator=(const connection&) = default;

private:
    friend class dogen::dia::serialization::detail::connection_serializer;

public:
    connection(const std::string& handle, const std::string& to,
        const std::string& connection_slot)
        : handle_(handle), to_(to), connection_slot_(connection_slot) { }

public:
    /**
     * @brief Internal handle for the connection
     */
    /**@{*/
    std::string handle() const { return(handle_); }
    void handle(const std::string& value) { handle_ = value; }
    /**@}*/

    /**
     * @brief Object we're connected to.
     */
    /**@{*/
    std::string to() const { return(to_); }
    void to(const std::string& value) { to_ = value; }
    /**@}*/

    /**
     * @brief Number of the connection slot we're connected to.
     *
     * This is known in Dia as a connection but to avoid confusion
     * between the class and the slot concepts, we renamed it.
     */
    /**@{*/
    std::string connection_slot() const { return(connection_slot_); }
    void connection_slot(const std::string& value) { connection_slot_ = value; }
    /**@}*/


public:
    bool operator==(const dogen::dia::connection& value) const {
        return
            handle_ == value.handle() &&
            to_ == value.to() &&
            connection_slot_ == value.connection_slot();
    }

    bool operator!=(const dogen::dia::connection& value) const {
        return(!this->operator==(value));
    }

private:
    std::string handle_;
    std::string to_;
    std::string connection_slot_;
};

} }

#endif

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
#include <sstream>
#include <boost/uuid/detail/sha1.hpp>
#include "dogen.utility/types/hash/sha1_hash.hpp"

namespace dogen::utility::hash {

std::string sha1_hash(const std::string& s) {
    boost::uuids::detail::sha1 sha1;
    char hash[20];
    sha1.process_bytes(s.c_str(), s.size());
    unsigned int digest[5];
    sha1.get_digest(digest);

    for(int i = 0; i < 5; ++i) {
        const char* tmp = reinterpret_cast<char*>(digest);

        hash[i*4] = tmp[i*4+3];
        hash[i*4+1] = tmp[i*4+2];
        hash[i*4+2] = tmp[i*4+1];
        hash[i*4+3] = tmp[i*4];
    }

    std::ostringstream ss;
    ss << std::hex;
    for(int i = 0; i < 20; ++i) {
        ss << ((hash[i] & 0x000000F0) >> 4)
           <<  (hash[i] & 0x0000000F);
    }
    return ss.str();
}

}

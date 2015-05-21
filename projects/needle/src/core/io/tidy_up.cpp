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
#include <boost/algorithm/string.hpp>
#include "dogen/needle/core/io/tidy_up.hpp"

namespace  {

const std::string windows_new_line("\r\n");
const std::string linux_new_line("\n");
const std::string quote("\"");

const std::string safe_new_line("<new_line>");
const std::string safe_quote("<quote>");

}

namespace dogen {
namespace needle {
namespace core {
namespace io {

std::string tidy_up_copy(std::string s) {
    boost::replace_all(s, windows_new_line, safe_new_line);
    boost::replace_all(s, linux_new_line, safe_new_line);
    boost::replace_all(s, quote, safe_quote);
    return s;
}

} } } }

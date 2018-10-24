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
#ifndef MASD_DOGEN_TEMPLATING_TYPES_WALE_KEY_EXTRACTOR_HPP
#define MASD_DOGEN_TEMPLATING_TYPES_WALE_KEY_EXTRACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <locale>
#include <unordered_set>

namespace masd::dogen::templating::wale {

class key_extractor final {
public:
    key_extractor() = default;

private:
    void check_first_char(const char c) const;
    void check_char(const char c) const;

public:
    std::unordered_set<std::string> extract(const std::string& s) const;

private:
    std::locale locale_;
};

}

#endif

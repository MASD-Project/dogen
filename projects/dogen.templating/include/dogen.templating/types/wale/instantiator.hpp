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
#ifndef DOGEN_TEMPLATING_TYPES_WALE_INSTANTIATOR_HPP
#define DOGEN_TEMPLATING_TYPES_WALE_INSTANTIATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen.templating/types/wale/text_template.hpp"

namespace dogen::templating::wale {

/**
 * @brief Instantiates wale templates by rendering them.
 */
class instantiator final {
private:
    std::string
    read_content(const boost::filesystem::path& template_path) const;

    std::unordered_set<std::string>
    get_expected_keys(const std::string& s) const;

    std::string format(const text_template& tt) const;

    void validate(const text_template& tt) const;

public:
    std::string instantiate(const std::string& template_content,
        const std::unordered_map<std::string, std::string>& kvps) const;

    std::string instantiate(const boost::filesystem::path& template_path,
        const std::unordered_map<std::string, std::string>& kvps) const;
};

}

#endif

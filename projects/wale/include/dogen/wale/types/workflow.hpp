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
#ifndef DOGEN_WALE_TYPES_WORKFLOW_HPP
#define DOGEN_WALE_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/wale/types/properties.hpp"
#include "dogen/wale/types/text_template.hpp"

namespace dogen {
namespace wale {

class workflow final {
private:
    properties make_properties(const annotations::type_repository& atrp,
        const annotations::annotation& a) const;
    properties make_properties(const boost::filesystem::path& template_path,
        const std::unordered_map<std::string, std::string>& kvps) const;

    boost::filesystem::path
    resolve_path(const boost::filesystem::path& p) const;

    std::string
    read_content(const boost::filesystem::path& template_path) const;

    void update_actual_kvps(text_template& tt) const;

    std::string format(const text_template& tt) const;

    void validate(const text_template& tt) const;

    std::string execute(const properties& props) const;

public:
    bool can_execute(const annotations::annotation& a) const;
    std::string execute(const annotations::type_repository& atrp,
        const annotations::annotation& a) const;
    std::string execute(const boost::filesystem::path& template_path,
        const std::unordered_map<std::string, std::string>& kvps) const;
};

} }

#endif

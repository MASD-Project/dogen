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
#ifndef DOGEN_CODEC_TYPES_HELPERS_REFERENCES_RESOLVER_HPP
#define DOGEN_CODEC_TYPES_HELPERS_REFERENCES_RESOLVER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <boost/filesystem/path.hpp>

namespace dogen::codec::helpers {

/**
 * @brief Resolves a set of references to concrete paths to models.
 */
class references_resolver final {
private:
    /**
     * @brief Removes any duplicates that may exist in the list of directories.
     */
    const std::list<boost::filesystem::path> deduplicate_directories(
        const std::list<boost::filesystem::path> directories);

public:
    references_resolver(
        const std::list<std::string>& extensions,
        const std::list<boost::filesystem::path>& dirs);

public:
    boost::filesystem::path resolve(const std::string& ref) const;

    std::list<boost::filesystem::path>
    resolve(const std::list<std::string>& refs) const;

private:
    const std::list<std::string> extensions_;
    const std::list<boost::filesystem::path> directories_;
};

}

#endif

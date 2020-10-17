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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_PATH_PROPERTIES_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_PATH_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>

namespace dogen::physical::entities {

class path_properties final {
public:
    path_properties() = default;
    path_properties(const path_properties&) = default;
    ~path_properties() = default;

public:
    path_properties(path_properties&& rhs);

public:
    path_properties(
        const boost::filesystem::path& file_path,
        const std::string& header_guard,
        const std::list<std::string>& inclusion_dependencies,
        const std::string& primary_inclusion_directive,
        const std::list<std::string>& secondary_inclusion_directives);

public:
    /**
     * @brief Full path to the file corresponding to this artefact.
     */
    /**@{*/
    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief C++ header guard for this artefact, if any,
     */
    /**@{*/
    const std::string& header_guard() const;
    std::string& header_guard();
    void header_guard(const std::string& v);
    void header_guard(const std::string&& v);
    /**@}*/

    /**
     * @brief C++ Inlusion dependencies for this artefact.
     */
    /**@{*/
    const std::list<std::string>& inclusion_dependencies() const;
    std::list<std::string>& inclusion_dependencies();
    void inclusion_dependencies(const std::list<std::string>& v);
    void inclusion_dependencies(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief The main inclusion directive needed for this element.
     */
    /**@{*/
    const std::string& primary_inclusion_directive() const;
    std::string& primary_inclusion_directive();
    void primary_inclusion_directive(const std::string& v);
    void primary_inclusion_directive(const std::string&& v);
    /**@}*/

    /**
     * @brief Any other directives that are also needed for this element.
     */
    /**@{*/
    const std::list<std::string>& secondary_inclusion_directives() const;
    std::list<std::string>& secondary_inclusion_directives();
    void secondary_inclusion_directives(const std::list<std::string>& v);
    void secondary_inclusion_directives(const std::list<std::string>&& v);
    /**@}*/

public:
    bool operator==(const path_properties& rhs) const;
    bool operator!=(const path_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(path_properties& other) noexcept;
    path_properties& operator=(path_properties other);

private:
    boost::filesystem::path file_path_;
    std::string header_guard_;
    std::list<std::string> inclusion_dependencies_;
    std::string primary_inclusion_directive_;
    std::list<std::string> secondary_inclusion_directives_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::path_properties& lhs,
    dogen::physical::entities::path_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif

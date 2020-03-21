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
#ifndef DOGEN_M2T_CPP_TYPES_FORMATTABLES_ARTEFACT_PROPERTIES_HPP
#define DOGEN_M2T_CPP_TYPES_FORMATTABLES_ARTEFACT_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>

namespace dogen::m2t::cpp::formattables {

class artefact_properties final {
public:
    artefact_properties() = default;
    artefact_properties(const artefact_properties&) = default;
    ~artefact_properties() = default;

public:
    artefact_properties(artefact_properties&& rhs);

public:
    artefact_properties(
        const boost::filesystem::path& file_path,
        const std::string& header_guard,
        const std::list<std::string>& inclusion_dependencies);

public:
    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);

    const std::string& header_guard() const;
    std::string& header_guard();
    void header_guard(const std::string& v);
    void header_guard(const std::string&& v);

    const std::list<std::string>& inclusion_dependencies() const;
    std::list<std::string>& inclusion_dependencies();
    void inclusion_dependencies(const std::list<std::string>& v);
    void inclusion_dependencies(const std::list<std::string>&& v);

public:
    bool operator==(const artefact_properties& rhs) const;
    bool operator!=(const artefact_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(artefact_properties& other) noexcept;
    artefact_properties& operator=(artefact_properties other);

private:
    boost::filesystem::path file_path_;
    std::string header_guard_;
    std::list<std::string> inclusion_dependencies_;
};

}

namespace std {

template<>
inline void swap(
    dogen::m2t::cpp::formattables::artefact_properties& lhs,
    dogen::m2t::cpp::formattables::artefact_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif

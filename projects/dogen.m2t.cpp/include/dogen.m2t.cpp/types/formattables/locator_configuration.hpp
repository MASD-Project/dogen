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
#ifndef DOGEN_M2T_CPP_TYPES_FORMATTABLES_LOCATOR_CONFIGURATION_HPP
#define DOGEN_M2T_CPP_TYPES_FORMATTABLES_LOCATOR_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.m2t.cpp/types/formattables/locator_facet_configuration.hpp"
#include "dogen.m2t.cpp/types/formattables/locator_archetype_configuration.hpp"

namespace dogen::m2t::cpp::formattables {

class locator_configuration final {
public:
    locator_configuration(const locator_configuration&) = default;
    locator_configuration(locator_configuration&&) = default;
    ~locator_configuration() = default;

public:
    locator_configuration();

public:
    locator_configuration(
        const std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_facet_configuration>& facet_configurations,
        const std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_archetype_configuration>& archetype_configurations,
        const std::string& include_directory_name,
        const std::string& source_directory_name,
        const bool disable_facet_directories,
        const std::string& header_file_extension,
        const std::string& implementation_file_extension,
        const std::string& backend_directory_name,
        const std::string& tests_directory_name,
        const std::string& templates_directory_name,
        const std::string& templates_file_extension);

public:
    const std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_facet_configuration>& facet_configurations() const;
    std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_facet_configuration>& facet_configurations();
    void facet_configurations(const std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_facet_configuration>& v);
    void facet_configurations(const std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_facet_configuration>&& v);

    const std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_archetype_configuration>& archetype_configurations() const;
    std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_archetype_configuration>& archetype_configurations();
    void archetype_configurations(const std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_archetype_configuration>& v);
    void archetype_configurations(const std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_archetype_configuration>&& v);

    const std::string& include_directory_name() const;
    std::string& include_directory_name();
    void include_directory_name(const std::string& v);
    void include_directory_name(const std::string&& v);

    const std::string& source_directory_name() const;
    std::string& source_directory_name();
    void source_directory_name(const std::string& v);
    void source_directory_name(const std::string&& v);

    bool disable_facet_directories() const;
    void disable_facet_directories(const bool v);

    const std::string& header_file_extension() const;
    std::string& header_file_extension();
    void header_file_extension(const std::string& v);
    void header_file_extension(const std::string&& v);

    const std::string& implementation_file_extension() const;
    std::string& implementation_file_extension();
    void implementation_file_extension(const std::string& v);
    void implementation_file_extension(const std::string&& v);

    const std::string& backend_directory_name() const;
    std::string& backend_directory_name();
    void backend_directory_name(const std::string& v);
    void backend_directory_name(const std::string&& v);

    const std::string& tests_directory_name() const;
    std::string& tests_directory_name();
    void tests_directory_name(const std::string& v);
    void tests_directory_name(const std::string&& v);

    const std::string& templates_directory_name() const;
    std::string& templates_directory_name();
    void templates_directory_name(const std::string& v);
    void templates_directory_name(const std::string&& v);

    const std::string& templates_file_extension() const;
    std::string& templates_file_extension();
    void templates_file_extension(const std::string& v);
    void templates_file_extension(const std::string&& v);

public:
    bool operator==(const locator_configuration& rhs) const;
    bool operator!=(const locator_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(locator_configuration& other) noexcept;
    locator_configuration& operator=(locator_configuration other);

private:
    std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_facet_configuration> facet_configurations_;
    std::unordered_map<std::string, dogen::m2t::cpp::formattables::locator_archetype_configuration> archetype_configurations_;
    std::string include_directory_name_;
    std::string source_directory_name_;
    bool disable_facet_directories_;
    std::string header_file_extension_;
    std::string implementation_file_extension_;
    std::string backend_directory_name_;
    std::string tests_directory_name_;
    std::string templates_directory_name_;
    std::string templates_file_extension_;
};

}

namespace std {

template<>
inline void swap(
    dogen::m2t::cpp::formattables::locator_configuration& lhs,
    dogen::m2t::cpp::formattables::locator_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif

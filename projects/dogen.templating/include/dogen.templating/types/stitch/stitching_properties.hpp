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
#ifndef DOGEN_TEMPLATING_TYPES_STITCH_STITCHING_PROPERTIES_HPP
#define DOGEN_TEMPLATING_TYPES_STITCH_STITCHING_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/filesystem/path.hpp>

namespace dogen::templating::stitch {

class stitching_properties final {
public:
    stitching_properties() = default;
    stitching_properties(const stitching_properties&) = default;
    ~stitching_properties() = default;

public:
    stitching_properties(stitching_properties&& rhs);

public:
    stitching_properties(
        const std::string& stream_variable_name,
        const boost::filesystem::path& relative_output_directory,
        const std::list<std::string>& inclusion_dependencies,
        const std::list<std::string>& containing_namespaces,
        const std::string& wale_template,
        const std::unordered_map<std::string, std::string>& wale_kvps);

public:
    const std::string& stream_variable_name() const;
    std::string& stream_variable_name();
    void stream_variable_name(const std::string& v);
    void stream_variable_name(const std::string&& v);

    const boost::filesystem::path& relative_output_directory() const;
    boost::filesystem::path& relative_output_directory();
    void relative_output_directory(const boost::filesystem::path& v);
    void relative_output_directory(const boost::filesystem::path&& v);

    const std::list<std::string>& inclusion_dependencies() const;
    std::list<std::string>& inclusion_dependencies();
    void inclusion_dependencies(const std::list<std::string>& v);
    void inclusion_dependencies(const std::list<std::string>&& v);

    const std::list<std::string>& containing_namespaces() const;
    std::list<std::string>& containing_namespaces();
    void containing_namespaces(const std::list<std::string>& v);
    void containing_namespaces(const std::list<std::string>&& v);

    const std::string& wale_template() const;
    std::string& wale_template();
    void wale_template(const std::string& v);
    void wale_template(const std::string&& v);

    const std::unordered_map<std::string, std::string>& wale_kvps() const;
    std::unordered_map<std::string, std::string>& wale_kvps();
    void wale_kvps(const std::unordered_map<std::string, std::string>& v);
    void wale_kvps(const std::unordered_map<std::string, std::string>&& v);

public:
    bool operator==(const stitching_properties& rhs) const;
    bool operator!=(const stitching_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(stitching_properties& other) noexcept;
    stitching_properties& operator=(stitching_properties other);

private:
    std::string stream_variable_name_;
    boost::filesystem::path relative_output_directory_;
    std::list<std::string> inclusion_dependencies_;
    std::list<std::string> containing_namespaces_;
    std::string wale_template_;
    std::unordered_map<std::string, std::string> wale_kvps_;
};

}

namespace std {

template<>
inline void swap(
    dogen::templating::stitch::stitching_properties& lhs,
    dogen::templating::stitch::stitching_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif

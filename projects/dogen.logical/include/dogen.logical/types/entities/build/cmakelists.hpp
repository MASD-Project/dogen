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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_BUILD_CMAKELISTS_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_BUILD_CMAKELISTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/orm/odb_targets.hpp"

namespace dogen::logical::entities::build {

/**
 * @brief Represents build CMakeLists files.
 */
class cmakelists final : public dogen::logical::entities::element {
public:
    cmakelists() = default;
    cmakelists(const cmakelists&) = default;
    cmakelists(cmakelists&&) = default;

    virtual ~cmakelists() noexcept { }

public:
    cmakelists(
        const dogen::logical::entities::name& name,
        const std::string& documentation,
        const dogen::identification::entities::injection_provenance& provenance,
        const std::string& contained_by,
        const bool in_global_module,
        const dogen::logical::entities::stereotypes& stereotypes,
        const dogen::logical::entities::name& meta_name,
        const dogen::logical::entities::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::list<dogen::logical::entities::label>& labels,
        const dogen::logical::entities::generability_status generability_status,
        const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
        const std::string& include_directory_path,
        const std::string& source_directory_name,
        const std::string& header_file_extension,
        const std::string& implementation_file_extension,
        const dogen::logical::entities::orm::odb_targets& odb_targets,
        const std::string& tests_directory_name);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const std::string& include_directory_path() const;
    std::string& include_directory_path();
    void include_directory_path(const std::string& v);
    void include_directory_path(const std::string&& v);

    const std::string& source_directory_name() const;
    std::string& source_directory_name();
    void source_directory_name(const std::string& v);
    void source_directory_name(const std::string&& v);

    const std::string& header_file_extension() const;
    std::string& header_file_extension();
    void header_file_extension(const std::string& v);
    void header_file_extension(const std::string&& v);

    const std::string& implementation_file_extension() const;
    std::string& implementation_file_extension();
    void implementation_file_extension(const std::string& v);
    void implementation_file_extension(const std::string&& v);

    const dogen::logical::entities::orm::odb_targets& odb_targets() const;
    dogen::logical::entities::orm::odb_targets& odb_targets();
    void odb_targets(const dogen::logical::entities::orm::odb_targets& v);
    void odb_targets(const dogen::logical::entities::orm::odb_targets&& v);

    const std::string& tests_directory_name() const;
    std::string& tests_directory_name();
    void tests_directory_name(const std::string& v);
    void tests_directory_name(const std::string&& v);

public:
    bool operator==(const cmakelists& rhs) const;
    bool operator!=(const cmakelists& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(cmakelists& other) noexcept;
    cmakelists& operator=(cmakelists other);

private:
    std::string include_directory_path_;
    std::string source_directory_name_;
    std::string header_file_extension_;
    std::string implementation_file_extension_;
    dogen::logical::entities::orm::odb_targets odb_targets_;
    std::string tests_directory_name_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::build::cmakelists& lhs,
    dogen::logical::entities::build::cmakelists& rhs) {
    lhs.swap(rhs);
}

}

#endif

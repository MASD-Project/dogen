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
#ifndef DOGEN_GENERATION_CPP_TYPES_FABRIC_COMMON_ODB_OPTIONS_HPP
#define DOGEN_GENERATION_CPP_TYPES_FABRIC_COMMON_ODB_OPTIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.assets/types/meta_model/element.hpp"

namespace dogen::generation::cpp::fabric {

class common_odb_options final : public dogen::assets::meta_model::element {
public:
    common_odb_options() = default;
    common_odb_options(const common_odb_options&) = default;
    common_odb_options(common_odb_options&&) = default;

    virtual ~common_odb_options() noexcept { }

public:
    common_odb_options(
        const dogen::assets::meta_model::name& name,
        const std::string& documentation,
        const dogen::assets::meta_model::origin_types origin_type,
        const std::string& origin_sha1_hash,
        const std::string& origin_element_id,
        const std::string& contained_by,
        const bool in_global_module,
        const std::list<dogen::assets::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const dogen::assets::meta_model::name& meta_name,
        const dogen::assets::meta_model::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
        const bool is_element_extension,
        const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const std::unordered_map<dogen::assets::meta_model::technical_space, boost::optional<dogen::assets::meta_model::decoration::element_properties> >& decoration,
        const std::string& sql_name_case,
        const std::list<std::string>& databases);

public:
    using dogen::assets::meta_model::element::accept;

    virtual void accept(const dogen::assets::meta_model::element_visitor& v) const override;
    virtual void accept(dogen::assets::meta_model::element_visitor& v) const override;
    virtual void accept(const dogen::assets::meta_model::element_visitor& v) override;
    virtual void accept(dogen::assets::meta_model::element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const std::string& sql_name_case() const;
    std::string& sql_name_case();
    void sql_name_case(const std::string& v);
    void sql_name_case(const std::string&& v);

    const std::list<std::string>& databases() const;
    std::list<std::string>& databases();
    void databases(const std::list<std::string>& v);
    void databases(const std::list<std::string>&& v);

public:
    bool operator==(const common_odb_options& rhs) const;
    bool operator!=(const common_odb_options& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::assets::meta_model::element& other) const override;

public:
    void swap(common_odb_options& other) noexcept;
    common_odb_options& operator=(common_odb_options other);

private:
    std::string sql_name_case_;
    std::list<std::string> databases_;
};

}

namespace std {

template<>
inline void swap(
    dogen::generation::cpp::fabric::common_odb_options& lhs,
    dogen::generation::cpp::fabric::common_odb_options& rhs) {
    lhs.swap(rhs);
}

}

#endif

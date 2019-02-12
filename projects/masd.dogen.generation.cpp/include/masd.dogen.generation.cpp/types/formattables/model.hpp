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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_MODEL_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/optional.hpp>
#include "masd.dogen.coding/types/meta_model/name.hpp"
#include "masd.dogen.coding/types/meta_model/generation_properties.hpp"
#include "masd.dogen.generation.cpp/types/formattables/formattable.hpp"
#include "masd.dogen.generation.cpp/types/formattables/cpp_standards.hpp"
#include "masd.dogen.generation.cpp/types/formattables/facet_properties.hpp"
#include "masd.dogen.generation.cpp/types/formattables/streaming_properties.hpp"

namespace masd::dogen::generation::cpp::formattables {

class model final {
public:
    model(const model&) = default;
    ~model() = default;

public:
    model();

public:
    model(model&& rhs);

public:
    model(
        const masd::dogen::coding::meta_model::name& name,
        const std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::streaming_properties>& streaming_properties,
        const std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::formattable>& formattables,
        const std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::facet_properties>& facet_properties,
        const masd::dogen::generation::cpp::formattables::cpp_standards cpp_standard,
        const std::list<std::string>& odb_databases,
        const std::string& odb_sql_name_case,
        const std::list<std::string>& project_items,
        const boost::optional<masd::dogen::coding::meta_model::generation_properties>& generation_properties);

public:
    const masd::dogen::coding::meta_model::name& name() const;
    masd::dogen::coding::meta_model::name& name();
    void name(const masd::dogen::coding::meta_model::name& v);
    void name(const masd::dogen::coding::meta_model::name&& v);

    const std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::streaming_properties>& streaming_properties() const;
    std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::streaming_properties>& streaming_properties();
    void streaming_properties(const std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::streaming_properties>& v);
    void streaming_properties(const std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::streaming_properties>&& v);

    const std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::formattable>& formattables() const;
    std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::formattable>& formattables();
    void formattables(const std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::formattable>& v);
    void formattables(const std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::formattable>&& v);

    const std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::facet_properties>& facet_properties() const;
    std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::facet_properties>& facet_properties();
    void facet_properties(const std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::facet_properties>& v);
    void facet_properties(const std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::facet_properties>&& v);

    masd::dogen::generation::cpp::formattables::cpp_standards cpp_standard() const;
    void cpp_standard(const masd::dogen::generation::cpp::formattables::cpp_standards v);

    const std::list<std::string>& odb_databases() const;
    std::list<std::string>& odb_databases();
    void odb_databases(const std::list<std::string>& v);
    void odb_databases(const std::list<std::string>&& v);

    const std::string& odb_sql_name_case() const;
    std::string& odb_sql_name_case();
    void odb_sql_name_case(const std::string& v);
    void odb_sql_name_case(const std::string&& v);

    const std::list<std::string>& project_items() const;
    std::list<std::string>& project_items();
    void project_items(const std::list<std::string>& v);
    void project_items(const std::list<std::string>&& v);

    const boost::optional<masd::dogen::coding::meta_model::generation_properties>& generation_properties() const;
    boost::optional<masd::dogen::coding::meta_model::generation_properties>& generation_properties();
    void generation_properties(const boost::optional<masd::dogen::coding::meta_model::generation_properties>& v);
    void generation_properties(const boost::optional<masd::dogen::coding::meta_model::generation_properties>&& v);

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    masd::dogen::coding::meta_model::name name_;
    std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::streaming_properties> streaming_properties_;
    std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::formattable> formattables_;
    std::unordered_map<std::string, masd::dogen::generation::cpp::formattables::facet_properties> facet_properties_;
    masd::dogen::generation::cpp::formattables::cpp_standards cpp_standard_;
    std::list<std::string> odb_databases_;
    std::string odb_sql_name_case_;
    std::list<std::string> project_items_;
    boost::optional<masd::dogen::coding::meta_model::generation_properties> generation_properties_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::generation::cpp::formattables::model& lhs,
    masd::dogen::generation::cpp::formattables::model& rhs) {
    lhs.swap(rhs);
}

}

#endif

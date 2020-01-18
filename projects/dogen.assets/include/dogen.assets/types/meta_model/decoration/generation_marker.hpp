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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_DECORATION_GENERATION_MARKER_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_DECORATION_GENERATION_MARKER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.assets/types/meta_model/element.hpp"

namespace dogen::assets::meta_model::decoration {

/**
 * @brief Properties of the "generation marker" to add to generated files.
 *
 * These are also known as "location strings".
 */
class generation_marker final : public dogen::assets::meta_model::element {
public:
    generation_marker(const generation_marker&) = default;
    generation_marker(generation_marker&&) = default;

public:
    generation_marker();

    virtual ~generation_marker() noexcept { }

public:
    generation_marker(
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
        const boost::optional<dogen::assets::meta_model::decoration::element_properties>& decoration,
        const bool add_date_time,
        const bool add_dogen_version,
        const bool add_model_to_text_transform_details,
        const bool add_warning,
        const bool add_origin_sha1_hash,
        const std::string& message);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief If true, the location strings will include the date and time of generation.
     *
     * This is not recomended for models that are generated often as it will trigger
     * rebuilds for no good reason.
     */
    /**@{*/
    bool add_date_time() const;
    void add_date_time(const bool v);
    /**@}*/

    /**
     * @brief If true, adds the version of dogen used to generate the code.
     */
    /**@{*/
    bool add_dogen_version() const;
    void add_dogen_version(const bool v);
    /**@}*/

    /**
     * @brief If true, adds information about the transform used to generate the file.
     */
    /**@{*/
    bool add_model_to_text_transform_details() const;
    void add_model_to_text_transform_details(const bool v);
    /**@}*/

    /**
     * @brief If true, warns users that the file was code-generated.
     */
    /**@{*/
    bool add_warning() const;
    void add_warning(const bool v);
    /**@}*/

    /**
     * @brief If true, adds the SHA1 hash of the original model to the marker.
     */
    /**@{*/
    bool add_origin_sha1_hash() const;
    void add_origin_sha1_hash(const bool v);
    /**@}*/

    /**
     * @brief Custom message to add to each generated file.
     */
    /**@{*/
    const std::string& message() const;
    std::string& message();
    void message(const std::string& v);
    void message(const std::string&& v);
    /**@}*/

public:
    bool operator==(const generation_marker& rhs) const;
    bool operator!=(const generation_marker& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::assets::meta_model::element& other) const override;

public:
    void swap(generation_marker& other) noexcept;
    generation_marker& operator=(generation_marker other);

private:
    bool add_date_time_;
    bool add_dogen_version_;
    bool add_model_to_text_transform_details_;
    bool add_warning_;
    bool add_origin_sha1_hash_;
    std::string message_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::decoration::generation_marker& lhs,
    dogen::assets::meta_model::decoration::generation_marker& rhs) {
    lhs.swap(rhs);
}

}

#endif

/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_HELPER_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_HELPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen.physical/types/entities/relations.hpp"
#include "dogen.identification/types/entities/label.hpp"
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.physical/serialization/entities/helper_fwd_ser.hpp"
#include "dogen.identification/types/entities/physical_meta_name.hpp"

namespace dogen::physical::entities {

class helper final {
public:
    helper(const helper&) = default;
    helper(helper&&) = default;
    ~helper() = default;

public:
    helper();

public:
    helper(
        const std::string& description,
        const dogen::identification::entities::physical_meta_name& meta_name,
        const std::list<dogen::identification::entities::label>& labels,
        const std::list<std::string>& depends,
        const std::list<std::string>& generates,
        const std::string& generated_by,
        const dogen::identification::entities::technical_space technical_space,
        const dogen::physical::entities::relations& relations,
        const dogen::identification::entities::physical_meta_id& part,
        const std::string& family,
        const std::list<dogen::identification::entities::physical_meta_id>& owning_formatters,
        const std::list<dogen::identification::entities::physical_meta_id>& owning_facets);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::physical::entities::helper& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::physical::entities::helper& v, unsigned int version);

public:
    /**
     * @brief Human readable description of the entity.
     */
    /**@{*/
    const std::string& description() const;
    std::string& description();
    void description(const std::string& v);
    void description(const std::string&& v);
    /**@}*/

    /**
     * @brief Meta-name for this meta-element.
     */
    /**@{*/
    const dogen::identification::entities::physical_meta_name& meta_name() const;
    dogen::identification::entities::physical_meta_name& meta_name();
    void meta_name(const dogen::identification::entities::physical_meta_name& v);
    void meta_name(const dogen::identification::entities::physical_meta_name&& v);
    /**@}*/

    /**
     * @brief All labels associated with this element.
     */
    /**@{*/
    const std::list<dogen::identification::entities::label>& labels() const;
    std::list<dogen::identification::entities::label>& labels();
    void labels(const std::list<dogen::identification::entities::label>& v);
    void labels(const std::list<dogen::identification::entities::label>&& v);
    /**@}*/

    /**
     * @brief List of meta-elements this meta-element depends upon, if any.
     */
    /**@{*/
    const std::list<std::string>& depends() const;
    std::list<std::string>& depends();
    void depends(const std::list<std::string>& v);
    void depends(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief List of meta-elements this meta-element is used to generate, if any.
     */
    /**@{*/
    const std::list<std::string>& generates() const;
    std::list<std::string>& generates();
    void generates(const std::list<std::string>& v);
    void generates(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Meta-element used to generate this meta-element, if any.
     */
    /**@{*/
    const std::string& generated_by() const;
    std::string& generated_by();
    void generated_by(const std::string& v);
    void generated_by(const std::string&& v);
    /**@}*/

    /**
     * @brief Technical space to which this physical element belongs to.
     */
    /**@{*/
    dogen::identification::entities::technical_space technical_space() const;
    void technical_space(const dogen::identification::entities::technical_space v);
    /**@}*/

    /**
     * @brief Properties of this helper with regards to relations.
     */
    /**@{*/
    const dogen::physical::entities::relations& relations() const;
    dogen::physical::entities::relations& relations();
    void relations(const dogen::physical::entities::relations& v);
    void relations(const dogen::physical::entities::relations&& v);
    /**@}*/

    /**
     * @brief Part in which we are located.
     */
    /**@{*/
    const dogen::identification::entities::physical_meta_id& part() const;
    dogen::identification::entities::physical_meta_id& part();
    void part(const dogen::identification::entities::physical_meta_id& v);
    void part(const dogen::identification::entities::physical_meta_id&& v);
    /**@}*/

    const std::string& family() const;
    std::string& family();
    void family(const std::string& v);
    void family(const std::string&& v);

    const std::list<dogen::identification::entities::physical_meta_id>& owning_formatters() const;
    std::list<dogen::identification::entities::physical_meta_id>& owning_formatters();
    void owning_formatters(const std::list<dogen::identification::entities::physical_meta_id>& v);
    void owning_formatters(const std::list<dogen::identification::entities::physical_meta_id>&& v);

    const std::list<dogen::identification::entities::physical_meta_id>& owning_facets() const;
    std::list<dogen::identification::entities::physical_meta_id>& owning_facets();
    void owning_facets(const std::list<dogen::identification::entities::physical_meta_id>& v);
    void owning_facets(const std::list<dogen::identification::entities::physical_meta_id>&& v);

public:
    bool operator==(const helper& rhs) const;
    bool operator!=(const helper& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(helper& other) noexcept;
    helper& operator=(helper other);

private:
    std::string description_;
    dogen::identification::entities::physical_meta_name meta_name_;
    std::list<dogen::identification::entities::label> labels_;
    std::list<std::string> depends_;
    std::list<std::string> generates_;
    std::string generated_by_;
    dogen::identification::entities::technical_space technical_space_;
    dogen::physical::entities::relations relations_;
    dogen::identification::entities::physical_meta_id part_;
    std::string family_;
    std::list<dogen::identification::entities::physical_meta_id> owning_formatters_;
    std::list<dogen::identification::entities::physical_meta_id> owning_facets_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::helper& lhs,
    dogen::physical::entities::helper& rhs) {
    lhs.swap(rhs);
}

}

#endif

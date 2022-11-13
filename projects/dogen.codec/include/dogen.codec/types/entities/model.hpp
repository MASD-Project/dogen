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
#ifndef DOGEN_CODEC_TYPES_ENTITIES_MODEL_HPP
#define DOGEN_CODEC_TYPES_ENTITIES_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <boost/shared_ptr.hpp>
#include "dogen.codec/types/entities/comment.hpp"
#include "dogen.codec/types/entities/element.hpp"
#include "dogen.identification/types/entities/name.hpp"
#include "dogen.identification/types/entities/stereotype.hpp"
#include "dogen.identification/types/entities/tagged_value.hpp"
#include "dogen.variability/types/entities/configuration_fwd.hpp"
#include "dogen.identification/types/entities/codec_provenance.hpp"

namespace dogen::codec::entities {

/**
 * @brief Represents an external model.
 */
class model final {
public:
    model() = default;
    model(const model&) = default;
    model(model&&) = default;
    ~model() = default;

public:
    model(
        const std::list<dogen::identification::entities::tagged_value>& tagged_values,
        const std::list<dogen::identification::entities::stereotype>& stereotypes,
        const std::list<dogen::identification::entities::stereotype>& templates,
        const std::list<dogen::identification::entities::stereotype>& configurations,
        const dogen::identification::entities::name& name,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const dogen::identification::entities::codec_provenance& provenance,
        const std::list<dogen::identification::entities::tagged_value>& tagged_values_overrides,
        const dogen::codec::entities::comment& comment,
        const std::list<dogen::codec::entities::element>& elements,
        const std::string& input_technical_space,
        const std::list<std::string>& references,
        const std::unordered_set<std::string>& processed_variability_overrides);

public:
    const std::list<dogen::identification::entities::tagged_value>& tagged_values() const;
    std::list<dogen::identification::entities::tagged_value>& tagged_values();
    void tagged_values(const std::list<dogen::identification::entities::tagged_value>& v);
    void tagged_values(const std::list<dogen::identification::entities::tagged_value>&& v);

    const std::list<dogen::identification::entities::stereotype>& stereotypes() const;
    std::list<dogen::identification::entities::stereotype>& stereotypes();
    void stereotypes(const std::list<dogen::identification::entities::stereotype>& v);
    void stereotypes(const std::list<dogen::identification::entities::stereotype>&& v);

    const std::list<dogen::identification::entities::stereotype>& templates() const;
    std::list<dogen::identification::entities::stereotype>& templates();
    void templates(const std::list<dogen::identification::entities::stereotype>& v);
    void templates(const std::list<dogen::identification::entities::stereotype>&& v);

    const std::list<dogen::identification::entities::stereotype>& configurations() const;
    std::list<dogen::identification::entities::stereotype>& configurations();
    void configurations(const std::list<dogen::identification::entities::stereotype>& v);
    void configurations(const std::list<dogen::identification::entities::stereotype>&& v);

    /**
     * @brief Name of the codec element.
     */
    /**@{*/
    const dogen::identification::entities::name& name() const;
    dogen::identification::entities::name& name();
    void name(const dogen::identification::entities::name& v);
    void name(const dogen::identification::entities::name&& v);
    /**@}*/

    /**
     * @brief Configuration for this element.
     */
    /**@{*/
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration() const;
    boost::shared_ptr<dogen::variability::entities::configuration>& configuration();
    void configuration(const boost::shared_ptr<dogen::variability::entities::configuration>& v);
    void configuration(const boost::shared_ptr<dogen::variability::entities::configuration>&& v);
    /**@}*/

    /**
     * @brief Provenance details of this codec element.
     */
    /**@{*/
    const dogen::identification::entities::codec_provenance& provenance() const;
    dogen::identification::entities::codec_provenance& provenance();
    void provenance(const dogen::identification::entities::codec_provenance& v);
    void provenance(const dogen::identification::entities::codec_provenance&& v);
    /**@}*/

    /**
     * @brief Meta-data sourced externally that can be used to override meta-data in model.
     */
    /**@{*/
    const std::list<dogen::identification::entities::tagged_value>& tagged_values_overrides() const;
    std::list<dogen::identification::entities::tagged_value>& tagged_values_overrides();
    void tagged_values_overrides(const std::list<dogen::identification::entities::tagged_value>& v);
    void tagged_values_overrides(const std::list<dogen::identification::entities::tagged_value>&& v);
    /**@}*/

    /**
     * @brief Properties associated with the codec comment.
     */
    /**@{*/
    const dogen::codec::entities::comment& comment() const;
    dogen::codec::entities::comment& comment();
    void comment(const dogen::codec::entities::comment& v);
    void comment(const dogen::codec::entities::comment&& v);
    /**@}*/

    const std::list<dogen::codec::entities::element>& elements() const;
    std::list<dogen::codec::entities::element>& elements();
    void elements(const std::list<dogen::codec::entities::element>& v);
    void elements(const std::list<dogen::codec::entities::element>&& v);

    /**
     * @brief Technical space to which the model belongs, within the codec space.
     */
    /**@{*/
    const std::string& input_technical_space() const;
    std::string& input_technical_space();
    void input_technical_space(const std::string& v);
    void input_technical_space(const std::string&& v);
    /**@}*/

    const std::list<std::string>& references() const;
    std::list<std::string>& references();
    void references(const std::list<std::string>& v);
    void references(const std::list<std::string>&& v);

    /**
     * @brief All the variability overrides that were processed by this model.
     */
    /**@{*/
    const std::unordered_set<std::string>& processed_variability_overrides() const;
    std::unordered_set<std::string>& processed_variability_overrides();
    void processed_variability_overrides(const std::unordered_set<std::string>& v);
    void processed_variability_overrides(const std::unordered_set<std::string>&& v);
    /**@}*/

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    std::list<dogen::identification::entities::tagged_value> tagged_values_;
    std::list<dogen::identification::entities::stereotype> stereotypes_;
    std::list<dogen::identification::entities::stereotype> templates_;
    std::list<dogen::identification::entities::stereotype> configurations_;
    dogen::identification::entities::name name_;
    boost::shared_ptr<dogen::variability::entities::configuration> configuration_;
    dogen::identification::entities::codec_provenance provenance_;
    std::list<dogen::identification::entities::tagged_value> tagged_values_overrides_;
    dogen::codec::entities::comment comment_;
    std::list<dogen::codec::entities::element> elements_;
    std::string input_technical_space_;
    std::list<std::string> references_;
    std::unordered_set<std::string> processed_variability_overrides_;
};

}

namespace std {

template<>
inline void swap(
    dogen::codec::entities::model& lhs,
    dogen::codec::entities::model& rhs) {
    lhs.swap(rhs);
}

}

#endif

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
#ifndef DOGEN_INJECTION_TYPES_ENTITIES_MODEL_HPP
#define DOGEN_INJECTION_TYPES_ENTITIES_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <boost/shared_ptr.hpp>
#include "dogen.injection/types/entities/element.hpp"
#include "dogen.identification/types/entities/name.hpp"
#include "dogen.variability/types/entities/configuration_fwd.hpp"
#include "dogen.identification/types/entities/injection_provenance.hpp"

namespace dogen::injection::entities {

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
        const std::list<std::pair<std::string, std::string> >& tagged_values,
        const std::list<std::pair<std::string, std::string> >& tagged_values_overrides,
        const std::list<std::string>& stereotypes,
        const std::string& documentation,
        const dogen::identification::entities::name& name,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const dogen::identification::entities::injection_provenance& provenance,
        const std::list<dogen::injection::entities::element>& elements,
        const std::string& input_technical_space,
        const std::list<std::string>& references,
        const std::unordered_set<std::string>& processed_variability_overrides);

public:
    const std::list<std::pair<std::string, std::string> >& tagged_values() const;
    std::list<std::pair<std::string, std::string> >& tagged_values();
    void tagged_values(const std::list<std::pair<std::string, std::string> >& v);
    void tagged_values(const std::list<std::pair<std::string, std::string> >&& v);

    /**
     * @brief Meta-data sourced externally that can be used to override meta-data in model.
     */
    /**@{*/
    const std::list<std::pair<std::string, std::string> >& tagged_values_overrides() const;
    std::list<std::pair<std::string, std::string> >& tagged_values_overrides();
    void tagged_values_overrides(const std::list<std::pair<std::string, std::string> >& v);
    void tagged_values_overrides(const std::list<std::pair<std::string, std::string> >&& v);
    /**@}*/

    const std::list<std::string>& stereotypes() const;
    std::list<std::string>& stereotypes();
    void stereotypes(const std::list<std::string>& v);
    void stereotypes(const std::list<std::string>&& v);

    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the technical space in question, e.g. Doxygen for C++, JavaDoc for Java, etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the injection element.
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
     * @brief Provenance details of this injection element.
     */
    /**@{*/
    const dogen::identification::entities::injection_provenance& provenance() const;
    dogen::identification::entities::injection_provenance& provenance();
    void provenance(const dogen::identification::entities::injection_provenance& v);
    void provenance(const dogen::identification::entities::injection_provenance&& v);
    /**@}*/

    const std::list<dogen::injection::entities::element>& elements() const;
    std::list<dogen::injection::entities::element>& elements();
    void elements(const std::list<dogen::injection::entities::element>& v);
    void elements(const std::list<dogen::injection::entities::element>&& v);

    /**
     * @brief Technical space to which the model belongs, within the injection space.
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
    std::list<std::pair<std::string, std::string> > tagged_values_;
    std::list<std::pair<std::string, std::string> > tagged_values_overrides_;
    std::list<std::string> stereotypes_;
    std::string documentation_;
    dogen::identification::entities::name name_;
    boost::shared_ptr<dogen::variability::entities::configuration> configuration_;
    dogen::identification::entities::injection_provenance provenance_;
    std::list<dogen::injection::entities::element> elements_;
    std::string input_technical_space_;
    std::list<std::string> references_;
    std::unordered_set<std::string> processed_variability_overrides_;
};

}

namespace std {

template<>
inline void swap(
    dogen::injection::entities::model& lhs,
    dogen::injection::entities::model& rhs) {
    lhs.swap(rhs);
}

}

#endif

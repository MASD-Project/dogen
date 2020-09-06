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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_ARCHETYPE_TEXT_TEMPLATING_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_ARCHETYPE_TEXT_TEMPLATING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/entities/physical/relations.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.variability/types/entities/configuration_fwd.hpp"

namespace dogen::logical::entities::physical {

/**
 * @brief Contains all the properties related to the generation of archetypes themselves.
 */
class archetype_text_templating final {
public:
    archetype_text_templating() = default;
    archetype_text_templating(const archetype_text_templating&) = default;
    ~archetype_text_templating() = default;

public:
    archetype_text_templating(archetype_text_templating&& rhs);

public:
    archetype_text_templating(
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::string& stitch_template_content,
        const boost::optional<dogen::identification::entities::logical_name>& wale_template,
        const std::string& wale_template_content,
        const std::string& rendered_stitch_template,
        const dogen::logical::entities::physical::relations& relations);

public:
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
     * @brief Content of the stitch template associated with this archetype, if any exists.
     */
    /**@{*/
    const std::string& stitch_template_content() const;
    std::string& stitch_template_content();
    void stitch_template_content(const std::string& v);
    void stitch_template_content(const std::string&& v);
    /**@}*/

    /**
     * @brief Parsed name of the wale template linked to this archetype, if any.
     */
    /**@{*/
    const boost::optional<dogen::identification::entities::logical_name>& wale_template() const;
    boost::optional<dogen::identification::entities::logical_name>& wale_template();
    void wale_template(const boost::optional<dogen::identification::entities::logical_name>& v);
    void wale_template(const boost::optional<dogen::identification::entities::logical_name>&& v);
    /**@}*/

    /**
     * @brief Content of the wale template associated with this archetype, if any exists.
     */
    /**@{*/
    const std::string& wale_template_content() const;
    std::string& wale_template_content();
    void wale_template_content(const std::string& v);
    void wale_template_content(const std::string&& v);
    /**@}*/

    /**
     * @brief Contains the result of the stitch template after rendering.
     */
    /**@{*/
    const std::string& rendered_stitch_template() const;
    std::string& rendered_stitch_template();
    void rendered_stitch_template(const std::string& v);
    void rendered_stitch_template(const std::string&& v);
    /**@}*/

    /**
     * @brief Relation information for this archetype.
     */
    /**@{*/
    const dogen::logical::entities::physical::relations& relations() const;
    dogen::logical::entities::physical::relations& relations();
    void relations(const dogen::logical::entities::physical::relations& v);
    void relations(const dogen::logical::entities::physical::relations&& v);
    /**@}*/

public:
    bool operator==(const archetype_text_templating& rhs) const;
    bool operator!=(const archetype_text_templating& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(archetype_text_templating& other) noexcept;
    archetype_text_templating& operator=(archetype_text_templating other);

private:
    boost::shared_ptr<dogen::variability::entities::configuration> configuration_;
    std::string stitch_template_content_;
    boost::optional<dogen::identification::entities::logical_name> wale_template_;
    std::string wale_template_content_;
    std::string rendered_stitch_template_;
    dogen::logical::entities::physical::relations relations_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::physical::archetype_text_templating& lhs,
    dogen::logical::entities::physical::archetype_text_templating& rhs) {
    lhs.swap(rhs);
}

}

#endif

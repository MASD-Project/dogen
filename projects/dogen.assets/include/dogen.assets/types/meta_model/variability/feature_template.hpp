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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_FEATURE_TEMPLATE_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_FEATURE_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.archetypes/types/location.hpp"
#include "dogen.assets/types/meta_model/name.hpp"
#include "dogen.assets/types/meta_model/name_tree.hpp"
#include "dogen.variability/types/meta_model/value_type.hpp"
#include "dogen.variability/types/meta_model/binding_point.hpp"
#include "dogen.variability/types/meta_model/template_kind.hpp"
#include "dogen.variability/types/meta_model/configuration_fwd.hpp"

namespace dogen::assets::meta_model::variability {

class feature_template final {
public:
    feature_template(const feature_template&) = default;
    feature_template(feature_template&&) = default;
    ~feature_template() = default;

public:
    feature_template();

public:
    feature_template(
        const std::string& documentation,
        const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
        const dogen::assets::meta_model::name& name,
        const std::string& key,
        const std::string& identifiable_key,
        const std::string& unparsed_type,
        const std::string& mapped_type,
        const dogen::assets::meta_model::name_tree& parsed_type,
        const std::string& value,
        const dogen::variability::meta_model::value_type value_type,
        const dogen::archetypes::location& location,
        const dogen::variability::meta_model::binding_point binding_point,
        const dogen::variability::meta_model::template_kind template_kind,
        const bool is_optional,
        const bool requires_optionality);

public:
    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the technical space in question, e.g. Doxygen for C++, JavaDoc for Java,
     * etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Configuration for this element.
     */
    /**@{*/
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration() const;
    boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration();
    void configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>& v);
    void configuration(const boost::shared_ptr<dogen::variability::meta_model::configuration>&& v);
    /**@}*/

    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const dogen::assets::meta_model::name& name() const;
    dogen::assets::meta_model::name& name();
    void name(const dogen::assets::meta_model::name& v);
    void name(const dogen::assets::meta_model::name&& v);
    /**@}*/

    /**
     * @brief Identifier of the feature template, as will be seen by the end user.
     */
    /**@{*/
    const std::string& key() const;
    std::string& key();
    void key(const std::string& v);
    void key(const std::string&& v);
    /**@}*/

    /**
     * @brief Post-processed key, suitable for use as an identifier.
     */
    /**@{*/
    const std::string& identifiable_key() const;
    std::string& identifiable_key();
    void identifiable_key(const std::string& v);
    void identifiable_key(const std::string&& v);
    /**@}*/

    /**
     * @brief Type of the static configuration field, as read out from original model.
     *
     * This is the type before mapping and parsing.
     */
    /**@{*/
    const std::string& unparsed_type() const;
    std::string& unparsed_type();
    void unparsed_type(const std::string& v);
    void unparsed_type(const std::string&& v);
    /**@}*/

    /**
     * @brief Unparsed type, after mapping has taken place.
     */
    /**@{*/
    const std::string& mapped_type() const;
    std::string& mapped_type();
    void mapped_type(const std::string& v);
    void mapped_type(const std::string&& v);
    /**@}*/

    /**
     * @brief Mapped type, after parsing has taken place.
     */
    /**@{*/
    const dogen::assets::meta_model::name_tree& parsed_type() const;
    dogen::assets::meta_model::name_tree& parsed_type();
    void parsed_type(const dogen::assets::meta_model::name_tree& v);
    void parsed_type(const dogen::assets::meta_model::name_tree&& v);
    /**@}*/

    /**
     * @brief String representing the default value set on the model.
     */
    /**@{*/
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);
    /**@}*/

    /**
     * @brief Type of the value pointed to by the feature.
     */
    /**@{*/
    dogen::variability::meta_model::value_type value_type() const;
    void value_type(const dogen::variability::meta_model::value_type v);
    /**@}*/

    /**
     * @brief Archetype location coordinates for the feature template to expand into.
     */
    /**@{*/
    const dogen::archetypes::location& location() const;
    dogen::archetypes::location& location();
    void location(const dogen::archetypes::location& v);
    void location(const dogen::archetypes::location&& v);
    /**@}*/

    /**
     * @brief Where the feature will bind when instantiated in a model.
     */
    /**@{*/
    dogen::variability::meta_model::binding_point binding_point() const;
    void binding_point(const dogen::variability::meta_model::binding_point v);
    /**@}*/

    /**
     * @brief Kind of template expansion to perform for this feature template.
     */
    /**@{*/
    dogen::variability::meta_model::template_kind template_kind() const;
    void template_kind(const dogen::variability::meta_model::template_kind v);
    /**@}*/

    /**
     * @brief If true, the feature generated by the feature template is optional.
     */
    /**@{*/
    bool is_optional() const;
    void is_optional(const bool v);
    /**@}*/

    /**
     * @brief If true, the feature's static configuration will have an optional type.
     *
     * This is only required if the feature template is optional and has no default value.
     */
    /**@{*/
    bool requires_optionality() const;
    void requires_optionality(const bool v);
    /**@}*/

public:
    bool operator==(const feature_template& rhs) const;
    bool operator!=(const feature_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(feature_template& other) noexcept;
    feature_template& operator=(feature_template other);

private:
    std::string documentation_;
    boost::shared_ptr<dogen::variability::meta_model::configuration> configuration_;
    dogen::assets::meta_model::name name_;
    std::string key_;
    std::string identifiable_key_;
    std::string unparsed_type_;
    std::string mapped_type_;
    dogen::assets::meta_model::name_tree parsed_type_;
    std::string value_;
    dogen::variability::meta_model::value_type value_type_;
    dogen::archetypes::location location_;
    dogen::variability::meta_model::binding_point binding_point_;
    dogen::variability::meta_model::template_kind template_kind_;
    bool is_optional_;
    bool requires_optionality_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::variability::feature_template& lhs,
    dogen::assets::meta_model::variability::feature_template& rhs) {
    lhs.swap(rhs);
}

}

#endif

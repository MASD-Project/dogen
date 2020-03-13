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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_ABSTRACT_FEATURE_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_ABSTRACT_FEATURE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen.assets/types/meta_model/name.hpp"
#include "dogen.assets/types/meta_model/name_tree.hpp"
#include "dogen.variability/types/meta_model/value_type.hpp"
#include "dogen.variability/types/meta_model/binding_point.hpp"
#include "dogen.variability/types/meta_model/configuration_fwd.hpp"

namespace dogen::assets::meta_model::variability {

/**
 * @brief Contains all of the common attributes between features and feature templates.
 */
class abstract_feature {
public:
    abstract_feature(const abstract_feature&) = default;

public:
    abstract_feature();

    virtual ~abstract_feature() noexcept = 0;

public:
    abstract_feature(abstract_feature&& rhs);

public:
    abstract_feature(
        const std::string& documentation,
        const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
        const dogen::assets::meta_model::name& name,
        const std::string& original_key,
        const std::string& key,
        const std::string& identifiable_key,
        const std::string& unparsed_type,
        const std::string& mapped_type,
        const dogen::assets::meta_model::name_tree& parsed_type,
        const std::string& value,
        const dogen::variability::meta_model::value_type value_type,
        const boost::optional<dogen::variability::meta_model::binding_point>& binding_point,
        const bool is_optional,
        const bool requires_optionality);

public:
    virtual void to_stream(std::ostream& s) const;

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
     * @brief Key as it was originally provided by the user.
     */
    /**@{*/
    const std::string& original_key() const;
    std::string& original_key();
    void original_key(const std::string& v);
    void original_key(const std::string&& v);
    /**@}*/

    /**
     * @brief Identifier of the feature, as will be seen by the end user.
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
     * @brief Override binding point for this feature.
     *
     * If the default binding point is supplied for a bundle, the features cannot
     * supply individual binding points. Conversely, if not supplied, they must supply
     * their individual binding points.
     */
    /**@{*/
    const boost::optional<dogen::variability::meta_model::binding_point>& binding_point() const;
    boost::optional<dogen::variability::meta_model::binding_point>& binding_point();
    void binding_point(const boost::optional<dogen::variability::meta_model::binding_point>& v);
    void binding_point(const boost::optional<dogen::variability::meta_model::binding_point>&& v);
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

protected:
    bool compare(const abstract_feature& rhs) const;
public:
    virtual bool equals(const abstract_feature& other) const = 0;

protected:
    void swap(abstract_feature& other) noexcept;

private:
    std::string documentation_;
    boost::shared_ptr<dogen::variability::meta_model::configuration> configuration_;
    dogen::assets::meta_model::name name_;
    std::string original_key_;
    std::string key_;
    std::string identifiable_key_;
    std::string unparsed_type_;
    std::string mapped_type_;
    dogen::assets::meta_model::name_tree parsed_type_;
    std::string value_;
    dogen::variability::meta_model::value_type value_type_;
    boost::optional<dogen::variability::meta_model::binding_point> binding_point_;
    bool is_optional_;
    bool requires_optionality_;
};

inline abstract_feature::~abstract_feature() noexcept { }

inline bool operator==(const abstract_feature& lhs, const abstract_feature& rhs) {
    return lhs.equals(rhs);
}

}

#endif

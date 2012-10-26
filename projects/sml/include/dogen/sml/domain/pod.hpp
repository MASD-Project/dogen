/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_SML_DOMAIN_POD_HPP
#define DOGEN_SML_DOMAIN_POD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <vector>
#include <iosfwd>
#include <utility>
#include <boost/optional.hpp>
#include "dogen/sml/domain/category_types.hpp"
#include "dogen/sml/domain/property.hpp"
#include "dogen/sml/domain/qualified_name.hpp"

namespace dogen {
namespace sml {

class pod_serializer;

/**
 * @brief Represents a namespace.
 */
class pod {
public:
    pod(const pod&) = default;
    pod& operator=(const pod&) = default;
    ~pod() = default;

private:
    friend class pod_serializer;

public:
    pod() : generate_(false), is_parent_(false),
            category_type_(category_types::invalid) { }

    /**
     * @brief Initialises the pod.
     *
     * @param name qualified name of the pod.
     * @param properties list of properties for the pod.
     * @param parent_name qualified name for the pod's parent, if the
     * pod has one.
     * @param generate Whether this pod should be code generated or
     * not.
     * @param is_parent If true, this pod is the parent of another pod
     * in this model.
     * @param category_type Whether the type is user defined or one of
     * the well known system types.
     * @param documentation the documentation for the pod
     */
    pod(qualified_name name,
        std::vector<dogen::sml::property> properties,
        boost::optional<qualified_name> parent_name, bool generate,
        bool is_parent, category_types category_type,
        const std::string& documentation)
        : name_(name), properties_(properties), parent_name_(parent_name),
          generate_(generate), is_parent_(is_parent),
          category_type_(category_type), documentation_(documentation) { }

    pod(pod&& rhs) : name_(std::move(rhs.name_)),
                     properties_(std::move(rhs.properties_)),
                     parent_name_(std::move(rhs.parent_name_)),
                     generate_(std::move(rhs.generate_)),
                     is_parent_(std::move(rhs.is_parent_)),
                     category_type_(std::move(rhs.category_type_)),
                     documentation_(std::move(rhs.documentation_)) { }

public:
    /**
     * @brief Qualified name for the type.
     */
    /**@{*/
    qualified_name name() const { return name_; }
    void name(qualified_name value) { name_ = value; }
    /**@}*/

    /**@{*/
    /**
     * @brief Identifier for the list of properties
     */
    /**@{*/
    std::vector<dogen::sml::property> properties() const { return properties_; }
    void properties(std::vector<dogen::sml::property> properties) {
        properties_ = properties; }
    /**@}*/

    /**
     * @brief Qualified name for the pod's parent, if the pod has one.
     */
    /**@{*/
    boost::optional<qualified_name> parent_name() const { return parent_name_; }
    void parent_name(boost::optional<qualified_name> value) {
        parent_name_ = value;
    }
    /**@}*/

    /**
     * @brief Returns true if this pod is to be code generated, false
     * otherwise.
     */
    /**@{*/
    bool generate() const { return generate_; }
    void generate(bool value) { generate_ = value; }
    /**@}*/

    /**
     * @brief True if this class is the parent of one or more classes,
     * false otherwise.
     */
    /**@{*/
    bool is_parent() const { return is_parent_; }
    void is_parent(bool value) { is_parent_ = value; }
    /**@}*/

    /**
     * @brief Category of this type - whether its system or user
     * defined.
     */
    /**@{*/
    sml::category_types category_type() const { return category_type_; }
    void category_type(sml::category_types value) { category_type_ = value; }
    /**@}*/

    /**
     * @brief Doxygen documentation for the type.
     */
    /**@{*/
    std::string documentation() const { return documentation_; }
    void documentation(const std::string& value) { documentation_ = value; }
    /**@}*/

public:
    void to_stream(std::ostream& stream) const;

public:
    bool operator==(const pod& rhs) const;

    bool operator!=(const pod& rhs) const {
        return(!this->operator==(rhs));
    }

private:
    qualified_name name_;
    std::vector<dogen::sml::property> properties_;
    boost::optional<qualified_name> parent_name_;
    bool generate_;
    bool is_parent_;
    sml::category_types category_type_;
    std::string documentation_;
};

} }

#endif

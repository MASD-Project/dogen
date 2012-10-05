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
    pod() = default;
    pod(const pod&) = default;
    pod& operator=(const pod&) = default;
    ~pod() = default;

private:
    friend class pod_serializer;

public:
    /**
     * @brief Initialises the pod.
     *
     * @param name qualified name of the pod.
     * @param properties list of properties for the pod.
     * @param parent_name qualified name for the pod's parent, if the
     * pod has one.
     * @param generate Whether this pod should be code generated or not.
     */
    pod(qualified_name name,
        std::vector<dogen::sml::property> properties,
        boost::optional<qualified_name> parent_name, bool generate)
        : name_(name), properties_(properties), parent_name_(parent_name),
          generate_(generate) { }

    pod(pod&& rhs) : name_(std::move(rhs.name_)),
                     properties_(std::move(rhs.properties_)),
                     parent_name_(std::move(rhs.parent_name_)),
                     generate_(std::move(rhs.generate_)) { }

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
     * @brief Returns true if this pod should be code generated, false
     * otherwise.
     */
    /**@{*/
    bool generate() const { return generate_; }
    void generate(bool value) { generate_ = value; }
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
};

} }

#endif

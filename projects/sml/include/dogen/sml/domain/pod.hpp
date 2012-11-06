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
            category_type_(category_types::invalid),
            number_of_type_arguments_(0),
            is_sequence_container_(false),
            is_associative_container_(false),
            is_smart_pointer_(false),
            is_cacheable_(false) { }

    /**
     * @brief Initialises the pod.
     *
     * @param name qualified name of the pod.
     * @param properties list of properties for the pod.
     * @param parent_name qualified name for the pod's parent, if the
     * pod has one.
     * @param original_parent_name qualified name for the root of the
     * inheritance tree, if the pod is part of one.
     * @param generate Whether this pod should be code generated or
     * not.
     * @param is_parent If true, this pod is the parent of another pod
     * in this model.
     * @param leaves All concrete types which are indirectly or
     * directly derived from this type
     * @param category_type Whether the type is user defined or one of
     * the well known system types.
     * @param documentation the documentation for the pod
     * @param number_of_type_arguments If the type is a generic type,
     * how many arguments does it expect.
     * @param is_sequence_container If true the pod is a sequence
     * container type, false otherwise.
     * @param is_associative_container If true the pod is a sequence
     * container type, false otherwise.
     * @param is_smart_pointer If true the pod represents a smart
     * pointer, false otherwise.
     * @param is_cacheable If true the pod requires cache support
     */
    pod(qualified_name name,
        std::vector<dogen::sml::property> properties,
        boost::optional<qualified_name> parent_name,
        boost::optional<qualified_name> original_parent_name,
        std::list<qualified_name> leaves, bool generate,
        bool is_parent, category_types category_type,
        const std::string& documentation,
        const unsigned int number_of_type_arguments, bool is_sequence_container,
        bool is_associative_container, bool is_smart_pointer, bool is_cacheable)
        : name_(name), properties_(properties), parent_name_(parent_name),
          original_parent_name_(original_parent_name), leaves_(leaves),
          generate_(generate), is_parent_(is_parent),
          category_type_(category_type), documentation_(documentation),
          number_of_type_arguments_(number_of_type_arguments),
          is_sequence_container_(is_sequence_container),
          is_associative_container_(is_associative_container),
          is_smart_pointer_(is_smart_pointer), is_cacheable_(is_cacheable) { }

    pod(pod&& rhs) : name_(std::move(rhs.name_)),
                     properties_(std::move(rhs.properties_)),
                     parent_name_(std::move(rhs.parent_name_)),
                     original_parent_name_(
                         std::move(rhs.original_parent_name_)),
                     leaves_(std::move(rhs.leaves_)),
                     generate_(std::move(rhs.generate_)),
                     is_parent_(std::move(rhs.is_parent_)),
                     category_type_(std::move(rhs.category_type_)),
                     documentation_(std::move(rhs.documentation_)),
                     number_of_type_arguments_(
                         std::move(rhs.number_of_type_arguments_)),
                     is_sequence_container_(
                         std::move(rhs.is_sequence_container_)),
                     is_associative_container_(
                         std::move(rhs.is_associative_container_)),
                     is_smart_pointer_(
                         std::move(rhs.is_smart_pointer_)),
                     is_cacheable_(rhs.is_cacheable_) { }

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
     * @brief Qualified name for the root of the inheritance
     * hierarchy, if the pod is part of one.
     */
    /**@{*/
    boost::optional<qualified_name> original_parent_name() const {
        return original_parent_name_;
    }
    void original_parent_name(boost::optional<qualified_name> v) {
        original_parent_name_ = v;
    }
    /**@}*/

    /**
     * @brief All concrete types which are indirectly or directly
     * derived from this type
     */
    /**@{*/
    std::list<qualified_name> leaves() const { return leaves_; }
    void leaves(std::list<qualified_name> v) { leaves_ = v; }
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

    /**
     * @brief How many type arguments does this type have
     */
    /**@{*/
    unsigned int number_of_type_arguments() const {
        return number_of_type_arguments_;
    }
    void number_of_type_arguments(const unsigned int v) {
        number_of_type_arguments_ = v;
    }
    /**@}*/

    /**
     * @brief If true the pod is a sequence container type, false otherwise.
     */
    /**@{*/
    bool is_sequence_container() const { return is_sequence_container_; }
    void is_sequence_container(const bool v) { is_sequence_container_ = v; }
    /**@}*/

    /**
     * @brief If true the pod is an associative container type, false otherwise.
     */
    /**@{*/
    bool is_associative_container() const { return is_associative_container_; }
    void is_associative_container(const bool v) { is_associative_container_ = v; }
    /**@}*/

    /**
     * @brief If true the pod is a smart pointer, false otherwise.
     */
    /**@{*/
    bool is_smart_pointer() const { return is_smart_pointer_; }
    void is_smart_pointer(const bool v) { is_smart_pointer_ = v; }
    /**@}*/

    /**
     * @brief If true the pod requires cache support.
     */
    /**@{*/
    bool is_cacheable() const { return is_cacheable_; }
    void is_cacheable(const bool v) { is_cacheable_ = v; }
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
    boost::optional<qualified_name> original_parent_name_;
    std::list<qualified_name> leaves_;
    bool generate_;
    bool is_parent_;
    sml::category_types category_type_;
    std::string documentation_;
    unsigned int number_of_type_arguments_;
    bool is_sequence_container_;
    bool is_associative_container_;
    bool is_smart_pointer_;
    bool is_cacheable_;
};

} }

#endif

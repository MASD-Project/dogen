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
#ifndef DOGEN_SML_DOMAIN_MODEL_HPP
#define DOGEN_SML_DOMAIN_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "dogen/sml/domain/qualified_name.hpp"
#include "dogen/sml/hash/qualified_name_hash.hpp"
#include "dogen/sml/domain/primitive.hpp"
#include "dogen/sml/domain/enumeration.hpp"
#include "dogen/sml/domain/exception.hpp"
#include "dogen/sml/domain/package.hpp"
#include "dogen/sml/domain/pod.hpp"
#include "dogen/sml/domain/reference.hpp"

namespace dogen {
namespace sml {

class model_serializer;

/**
 * @brief Represents a domain model.
 */
class model {
public:
    model(const model&) = default;
    ~model() = default;
    model(model&&) = default;
    model& operator=(const model&) = default;

private:
    friend class model_serializer;

public:
    model() : is_system_(false) { }

    /**
     * @brief Initialises the structure.
     *
     * @param name name of the domain model.
     * @param packages packages contained in the model.
     * @param pods pods contained in the model.
     * @param primitives primitives contained in the model.
     * @param enumerations enumerations contained in the model.
     * @param exceptions exceptions contained in the model.
     * @param external_package_path Path of packages that contain this
     * model
     * @param is_system If true this is a system model, false
     * otherwise
     * @param dependencies All other models this model depends on
     * @param leaves All concrete types which have a parent
     */
    model(std::string name,
        std::unordered_map<qualified_name, package> packages,
        std::unordered_map<qualified_name, pod> pods,
        std::unordered_map<qualified_name, primitive> primitives,
        std::unordered_map<qualified_name, enumeration> enumerations,
        std::unordered_map<qualified_name, exception> exceptions,
        std::list<std::string> external_package_path,
        bool is_system,
        std::unordered_map<std::string, reference> dependencies,
        std::unordered_set<qualified_name> leaves) :
        name_(name), packages_(packages), pods_(pods),
        primitives_(primitives), enumerations_(enumerations),
        exceptions_(exceptions), external_package_path_(external_package_path),
        is_system_(is_system), dependencies_(dependencies), leaves_(leaves) { }

public:
    /**
     * @brief Name of the domain model.
     *
     * Must not contain spaces or any special character as its used to
     * name folders in the file-system.
     */
    /**@{*/
    std::string name() const { return name_; }
    void name(std::string value) { name_ = value; }
    /**@}*/

    /**
     * @brief Packages contained in the model.
     */
    /**@{*/
    std::unordered_map<qualified_name, package> packages() const {
        return packages_;
    }

    void packages(std::unordered_map<qualified_name, package> packages) {
        packages_ = packages;
    }
    /**@}*/

    /**
     * @brief Pods contained in the model.
     */
    /**@{*/
    std::unordered_map<qualified_name, pod> pods() const { return pods_; }
    void pods(std::unordered_map<qualified_name, pod> pods) {
        pods_ = pods;
    }
    /**@}*/

    /**
     * @brief Primitives contained in the model.
     */
    /**@{*/
    std::unordered_map<qualified_name, primitive> primitives() const {
        return primitives_;
    }
    void primitives(std::unordered_map<qualified_name, primitive> primitives) {
        primitives_ = primitives;
    }
    /**@}*/

    /**
     * @brief Enumerations contained in the model.
     */
    /**@{*/
    std::unordered_map<qualified_name, enumeration> enumerations() const {
        return enumerations_;
    }
    void enumerations(std::unordered_map<qualified_name, enumeration> v) {
        enumerations_ = v;
    }
    /**@}*/

    /**
     * @brief Exceptions contained in the model.
     */
    /**@{*/
    std::unordered_map<qualified_name, exception> exceptions() const {
        return exceptions_;
    }
    void exceptions(std::unordered_map<qualified_name, exception> v) {
        exceptions_ = v;
    }
    /**@}*/

    /**
     * @brief Path of packages that contain this model.
     */
    std::list<std::string> external_package_path() const {
        return(external_package_path_);
    }
    void external_package_path(std::list<std::string> value) {
        external_package_path_ = value;
    }

    /**
     * @brief Name of the database schema this model belongs to, if
     * any.
     */
    /**@{*/
    std::string schema_name() const { return schema_name_; }
    void schema_name(std::string value) { schema_name_ = value; }
    /**@}*/

    /**
     * @brief If true, the model is a system model such as STL, boost,
     * etc. If false, it is a user generated model.
     *
     * System models are a way to expose third party code into Dogen
     * so that we can make use of these types. They need to be
     * hand-coded in, because they require changes to the formatters.
     *
     * User models are regular Dogen models, normally made using Dia.
     */
    /**@{*/
    bool is_system() const { return is_system_; }
    void is_system(bool value) { is_system_ = value; }
    /**@}*/

    /**
     * @brief All other models that this model depends on - both
     * system and user defined.
     */
    /**@{*/
    std::unordered_map<std::string, reference> dependencies() const {
        return dependencies_;
    }
    void dependencies(std::unordered_map<std::string, reference> value) {
        dependencies_ = value;
    }
    /**@}*/

    /**
     * @brief All leaf types in this model.
     *
     * Leaves are types concrete types which have a parent.
     */
    /**@{*/
    std::unordered_set<qualified_name> leaves() const {
        return leaves_;
    }
    void leaves(std::unordered_set<qualified_name> value) {
        leaves_ = value;
    }
    /**@}*/

public:
    void to_stream(std::ostream& stream) const;

public:
    bool operator==(const model& rhs) const;

    bool operator!=(const model& rhs) const {
        return(!this->operator==(rhs));
    }

private:
    std::string name_;
    std::unordered_map<qualified_name, package> packages_;
    std::unordered_map<qualified_name, pod> pods_;
    std::unordered_map<qualified_name, primitive> primitives_;
    std::unordered_map<qualified_name, enumeration> enumerations_;
    std::unordered_map<qualified_name, exception> exceptions_;
    std::list<std::string> external_package_path_;
    std::string schema_name_;
    bool is_system_;
    std::unordered_map<std::string, reference> dependencies_;
    std::unordered_set<qualified_name> leaves_;
};

} }

#endif

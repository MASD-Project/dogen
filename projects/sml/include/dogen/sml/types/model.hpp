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
#ifndef DOGEN_SML_TYPES_MODEL_HPP
#define DOGEN_SML_TYPES_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "dogen/sml/hash/qualified_name_hash.hpp"
#include "dogen/sml/serialization/model_fwd_ser.hpp"
#include "dogen/sml/types/enumeration.hpp"
#include "dogen/sml/types/exception.hpp"
#include "dogen/sml/types/package.hpp"
#include "dogen/sml/types/pod.hpp"
#include "dogen/sml/types/primitive.hpp"
#include "dogen/sml/types/qualified_name.hpp"
#include "dogen/sml/types/reference.hpp"

namespace dogen {
namespace sml {

/*
 * @brief Represents a domain model.
 */
class model final {
public:
    model(const model&) = default;
    model(model&&) = default;
    ~model() = default;

public:
    model();

public:
    model(
        const std::string& name,
        const std::unordered_map<dogen::sml::qualified_name, dogen::sml::package>& packages,
        const std::unordered_map<dogen::sml::qualified_name, dogen::sml::pod>& pods,
        const std::unordered_map<dogen::sml::qualified_name, dogen::sml::primitive>& primitives,
        const std::unordered_map<dogen::sml::qualified_name, dogen::sml::enumeration>& enumerations,
        const std::unordered_map<dogen::sml::qualified_name, dogen::sml::exception>& exceptions,
        const std::list<std::string>& external_package_path,
        const std::string& schema_name,
        const bool is_system,
        const std::unordered_map<std::string, dogen::sml::reference>& dependencies,
        const std::unordered_set<dogen::sml::qualified_name>& leaves);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, model& v, unsigned int version);

public:
    /*
     * @brief Name of the domain model.
     *
     * Must not contain spaces or any special character as its used to
     * name folders in the file-system.
     */
    /**@{*/
    std::string name() const {
        return name_;
    }

    void name(const std::string& v) {
        name_ = v;
    }
    /**@}*/

    /*
     * @brief Packages contained in the model.
     */
    /**@{*/
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::package> packages() const {
        return packages_;
    }

    void packages(const std::unordered_map<dogen::sml::qualified_name, dogen::sml::package>& v) {
        packages_ = v;
    }
    /**@}*/

    /*
     * @brief Pods contained in the model.
     */
    /**@{*/
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::pod> pods() const {
        return pods_;
    }

    void pods(const std::unordered_map<dogen::sml::qualified_name, dogen::sml::pod>& v) {
        pods_ = v;
    }
    /**@}*/

    /*
     * @brief Primitives contained in the model.
     */
    /**@{*/
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::primitive> primitives() const {
        return primitives_;
    }

    void primitives(const std::unordered_map<dogen::sml::qualified_name, dogen::sml::primitive>& v) {
        primitives_ = v;
    }
    /**@}*/

    /*
     * @brief Enumerations contained in the model.
     */
    /**@{*/
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::enumeration> enumerations() const {
        return enumerations_;
    }

    void enumerations(const std::unordered_map<dogen::sml::qualified_name, dogen::sml::enumeration>& v) {
        enumerations_ = v;
    }
    /**@}*/

    /*
     * @brief Exceptions contained in the model.
     */
    /**@{*/
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::exception> exceptions() const {
        return exceptions_;
    }

    void exceptions(const std::unordered_map<dogen::sml::qualified_name, dogen::sml::exception>& v) {
        exceptions_ = v;
    }
    /**@}*/

    /*
     * @brief Path of packages that contain this model.
     */
    /**@{*/
    std::list<std::string> external_package_path() const {
        return external_package_path_;
    }

    void external_package_path(const std::list<std::string>& v) {
        external_package_path_ = v;
    }
    /**@}*/

    /*
     * @brief Name of the database schema this model belongs to, if any.
     */
    /**@{*/
    std::string schema_name() const {
        return schema_name_;
    }

    void schema_name(const std::string& v) {
        schema_name_ = v;
    }
    /**@}*/

    /*
     * @brief If true, the model is a system model such as STL, boost, etc. If false, it is a user generated model.
     *
     * System models are a way to expose third party code into Dogen
     * so that we can make use of these types. They need to be
     * hand-coded in, because they require changes to the formatters.
     *
     * User models are regular Dogen models, normally made using Dia.
     */
    /**@{*/
    bool is_system() const {
        return is_system_;
    }

    void is_system(const bool v) {
        is_system_ = v;
    }
    /**@}*/

    /*
     * @brief All other models that this model depends on - both system and user defined.
     */
    /**@{*/
    std::unordered_map<std::string, dogen::sml::reference> dependencies() const {
        return dependencies_;
    }

    void dependencies(const std::unordered_map<std::string, dogen::sml::reference>& v) {
        dependencies_ = v;
    }
    /**@}*/

    /*
     * @brief All leaf types in this model.
     *
     * Leaves are types concrete types which have a parent.
     */
    /**@{*/
    std::unordered_set<dogen::sml::qualified_name> leaves() const {
        return leaves_;
    }

    void leaves(const std::unordered_set<dogen::sml::qualified_name>& v) {
        leaves_ = v;
    }
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
    std::string name_;
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::package> packages_;
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::pod> pods_;
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::primitive> primitives_;
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::enumeration> enumerations_;
    std::unordered_map<dogen::sml::qualified_name, dogen::sml::exception> exceptions_;
    std::list<std::string> external_package_path_;
    std::string schema_name_;
    bool is_system_;
    std::unordered_map<std::string, dogen::sml::reference> dependencies_;
    std::unordered_set<dogen::sml::qualified_name> leaves_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::model& lhs,
    dogen::sml::model& rhs) {
    lhs.swap(rhs);
}

}

#endif

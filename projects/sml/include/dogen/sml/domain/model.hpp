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
 * You should have received a copy of the GNU General PublicLicense
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
#include "dogen/sml/domain/qualified_name.hpp"
#include "dogen/sml/hash/qualified_name_hash.hpp"
#include "dogen/sml/domain/primitive.hpp"
#include "dogen/sml/domain/package.hpp"
#include "dogen/sml/domain/pod.hpp"

namespace dogen {
namespace sml {

class model_serializer;

/**
 * @brief Represents a domain model.
 */
class model {
public:
    model() = default;
    model(const model&) = default;
    ~model() = default;
    model(model&&) = default;
    model& operator=(const model&) = default;

private:
    friend class model_serializer;

public:
    /**
     * @brief Initialises the structure.
     *
     * @param name name of the domain model.
     * @param packages packages contained in the model.
     * @param pods pods contained in the model.
     * @param primitives primitives contained in the model.
     * @param external_package_path Path of packages that contain this
     * model
     */
    model(std::string name,
        std::unordered_map<qualified_name, package> packages,
        std::unordered_map<qualified_name, pod> pods,
        std::unordered_map<qualified_name, primitive> primitives,
        std::list<std::string> external_package_path) :
        name_(name), packages_(packages), pods_(pods),
        primitives_(primitives),
        external_package_path_(external_package_path) { }

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
    std::list<std::string> external_package_path_;
    std::string schema_name_;
};

} }

#endif

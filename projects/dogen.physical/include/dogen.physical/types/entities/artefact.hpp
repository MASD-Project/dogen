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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_ARTEFACT_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_ARTEFACT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.physical/types/entities/name.hpp"
#include "dogen.physical/types/entities/meta_name.hpp"
#include "dogen.physical/types/entities/operation.hpp"
#include "dogen.physical/types/entities/logical_name.hpp"
#include "dogen.physical/types/entities/artefact_properties.hpp"
#include "dogen.variability/types/entities/configuration_fwd.hpp"
#include "dogen.physical/types/entities/enablement_properties.hpp"

namespace dogen::physical::entities {

/**
 * @brief Represents an entity in physical space.
 */
class artefact final {
public:
    artefact(const artefact&) = default;
    artefact(artefact&&) = default;
    ~artefact() = default;

public:
    artefact();

public:
    artefact(
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::string& origin_sha1_hash,
        const dogen::physical::entities::logical_name& logical_name,
        const dogen::physical::entities::meta_name& physical_meta_name,
        const dogen::physical::entities::name& name,
        const std::string& content,
        const bool enabled,
        const bool overwrite,
        const std::unordered_map<std::string, boost::filesystem::path>& relative_paths,
        const std::vector<boost::filesystem::path>& dependencies,
        const std::list<std::string>& relations,
        const std::string& unified_diff,
        const dogen::physical::entities::operation& operation,
        const dogen::physical::entities::artefact_properties& artefact_properties,
        const dogen::physical::entities::enablement_properties& enablement_properties);

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
     * @brief SHA1 hash of the original model that contained the element.
     */
    /**@{*/
    const std::string& origin_sha1_hash() const;
    std::string& origin_sha1_hash();
    void origin_sha1_hash(const std::string& v);
    void origin_sha1_hash(const std::string&& v);
    /**@}*/

    /**
     * @brief Logical model details of the element that originated this physical element.
     */
    /**@{*/
    const dogen::physical::entities::logical_name& logical_name() const;
    dogen::physical::entities::logical_name& logical_name();
    void logical_name(const dogen::physical::entities::logical_name& v);
    void logical_name(const dogen::physical::entities::logical_name&& v);
    /**@}*/

    /**
     * @brief Physical model details of the meta-element that originated this element.
     */
    /**@{*/
    const dogen::physical::entities::meta_name& physical_meta_name() const;
    dogen::physical::entities::meta_name& physical_meta_name();
    void physical_meta_name(const dogen::physical::entities::meta_name& v);
    void physical_meta_name(const dogen::physical::entities::meta_name&& v);
    /**@}*/

    /**
     * @brief Name of the physical element.
     */
    /**@{*/
    const dogen::physical::entities::name& name() const;
    dogen::physical::entities::name& name();
    void name(const dogen::physical::entities::name& v);
    void name(const dogen::physical::entities::name&& v);
    /**@}*/

    /**
     * @brief Content of the file.
     */
    /**@{*/
    const std::string& content() const;
    std::string& content();
    void content(const std::string& v);
    void content(const std::string&& v);
    /**@}*/

    bool enabled() const;
    void enabled(const bool v);

    bool overwrite() const;
    void overwrite(const bool v);

    /**
     * @brief Paths relative to the path ID that keys the container.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::filesystem::path>& relative_paths() const;
    std::unordered_map<std::string, boost::filesystem::path>& relative_paths();
    void relative_paths(const std::unordered_map<std::string, boost::filesystem::path>& v);
    void relative_paths(const std::unordered_map<std::string, boost::filesystem::path>&& v);
    /**@}*/

    /**
     * @brief Files in the project directory that this file depends on, but which are not generated.
     */
    /**@{*/
    const std::vector<boost::filesystem::path>& dependencies() const;
    std::vector<boost::filesystem::path>& dependencies();
    void dependencies(const std::vector<boost::filesystem::path>& v);
    void dependencies(const std::vector<boost::filesystem::path>&& v);
    /**@}*/

    /**
     * @brief Artefacts that this artefact depends on.
     *
     * The format used is dependent on the technical space the artefact belongs to.
     */
    /**@{*/
    const std::list<std::string>& relations() const;
    std::list<std::string>& relations();
    void relations(const std::list<std::string>& v);
    void relations(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Unified diff between the in-memory artefact and the file in the filesystem.
     */
    /**@{*/
    const std::string& unified_diff() const;
    std::string& unified_diff();
    void unified_diff(const std::string& v);
    void unified_diff(const std::string&& v);
    /**@}*/

    const dogen::physical::entities::operation& operation() const;
    dogen::physical::entities::operation& operation();
    void operation(const dogen::physical::entities::operation& v);
    void operation(const dogen::physical::entities::operation&& v);

    const dogen::physical::entities::artefact_properties& artefact_properties() const;
    dogen::physical::entities::artefact_properties& artefact_properties();
    void artefact_properties(const dogen::physical::entities::artefact_properties& v);
    void artefact_properties(const dogen::physical::entities::artefact_properties&& v);

    const dogen::physical::entities::enablement_properties& enablement_properties() const;
    dogen::physical::entities::enablement_properties& enablement_properties();
    void enablement_properties(const dogen::physical::entities::enablement_properties& v);
    void enablement_properties(const dogen::physical::entities::enablement_properties&& v);

public:
    bool operator==(const artefact& rhs) const;
    bool operator!=(const artefact& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(artefact& other) noexcept;
    artefact& operator=(artefact other);

private:
    boost::shared_ptr<dogen::variability::entities::configuration> configuration_;
    std::string origin_sha1_hash_;
    dogen::physical::entities::logical_name logical_name_;
    dogen::physical::entities::meta_name physical_meta_name_;
    dogen::physical::entities::name name_;
    std::string content_;
    bool enabled_;
    bool overwrite_;
    std::unordered_map<std::string, boost::filesystem::path> relative_paths_;
    std::vector<boost::filesystem::path> dependencies_;
    std::list<std::string> relations_;
    std::string unified_diff_;
    dogen::physical::entities::operation operation_;
    dogen::physical::entities::artefact_properties artefact_properties_;
    dogen::physical::entities::enablement_properties enablement_properties_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::artefact& lhs,
    dogen::physical::entities::artefact& rhs) {
    lhs.swap(rhs);
}

}

#endif

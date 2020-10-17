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

#include <string>
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.physical/types/entities/operation.hpp"
#include "dogen.physical/types/entities/path_properties.hpp"
#include "dogen.physical/types/entities/formatting_styles.hpp"
#include "dogen.identification/types/entities/physical_name.hpp"
#include "dogen.variability/types/entities/configuration_fwd.hpp"
#include "dogen.physical/types/entities/enablement_properties.hpp"
#include "dogen.identification/types/entities/logical_provenance.hpp"
#include "dogen.identification/types/entities/physical_meta_name.hpp"

namespace dogen::physical::entities {

/**
 * @brief Represents an entity in physical space.
 */
class artefact final {
public:
    artefact(const artefact&) = default;
    ~artefact() = default;

public:
    artefact();

public:
    artefact(artefact&& rhs);

public:
    artefact(
        const dogen::identification::entities::physical_meta_name& meta_name,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const dogen::identification::entities::logical_provenance& provenance,
        const dogen::identification::entities::physical_name& name,
        const boost::filesystem::path& file_path,
        const std::string& content,
        const dogen::physical::entities::path_properties& path_properties,
        const std::vector<boost::filesystem::path>& dependencies,
        const std::string& unified_diff,
        const dogen::physical::entities::operation& operation,
        const dogen::physical::entities::enablement_properties& enablement_properties,
        const dogen::physical::entities::formatting_styles formatting_style,
        const std::string& formatting_input);

public:
    /**
     * @brief Meta-name for this meta-element.
     */
    /**@{*/
    const dogen::identification::entities::physical_meta_name& meta_name() const;
    dogen::identification::entities::physical_meta_name& meta_name();
    void meta_name(const dogen::identification::entities::physical_meta_name& v);
    void meta_name(const dogen::identification::entities::physical_meta_name&& v);
    /**@}*/

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
     * @brief Details of the provenance of this model element.
     */
    /**@{*/
    const dogen::identification::entities::logical_provenance& provenance() const;
    dogen::identification::entities::logical_provenance& provenance();
    void provenance(const dogen::identification::entities::logical_provenance& v);
    void provenance(const dogen::identification::entities::logical_provenance&& v);
    /**@}*/

    /**
     * @brief Name of the physical element.
     */
    /**@{*/
    const dogen::identification::entities::physical_name& name() const;
    dogen::identification::entities::physical_name& name();
    void name(const dogen::identification::entities::physical_name& v);
    void name(const dogen::identification::entities::physical_name&& v);
    /**@}*/

    /**
     * @brief Full path to the file corresponding to this artefact.
     */
    /**@{*/
    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Textual content of the artefact.
     */
    /**@{*/
    const std::string& content() const;
    std::string& content();
    void content(const std::string& v);
    void content(const std::string&& v);
    /**@}*/

    /**
     * @brief Properties related to paths in the filesystem.
     */
    /**@{*/
    const dogen::physical::entities::path_properties& path_properties() const;
    dogen::physical::entities::path_properties& path_properties();
    void path_properties(const dogen::physical::entities::path_properties& v);
    void path_properties(const dogen::physical::entities::path_properties&& v);
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
     * @brief Unified diff between the in-memory artefact and the file in the filesystem.
     */
    /**@{*/
    const std::string& unified_diff() const;
    std::string& unified_diff();
    void unified_diff(const std::string& v);
    void unified_diff(const std::string&& v);
    /**@}*/

    /**
     * @brief Operation to be applied to this artefact.
     */
    /**@{*/
    const dogen::physical::entities::operation& operation() const;
    dogen::physical::entities::operation& operation();
    void operation(const dogen::physical::entities::operation& v);
    void operation(const dogen::physical::entities::operation&& v);
    /**@}*/

    /**
     * @brief Stores the properties related to the enablement, as read out from configuration.
     */
    /**@{*/
    const dogen::physical::entities::enablement_properties& enablement_properties() const;
    dogen::physical::entities::enablement_properties& enablement_properties();
    void enablement_properties(const dogen::physical::entities::enablement_properties& v);
    void enablement_properties(const dogen::physical::entities::enablement_properties&& v);
    /**@}*/

    /**
     * @brief What type of M2T transform to use in order to generate the artefact's content.
     */
    /**@{*/
    dogen::physical::entities::formatting_styles formatting_style() const;
    void formatting_style(const dogen::physical::entities::formatting_styles v);
    /**@}*/

    /**
     * @brief Template used as input in order to generate the artefact's content, if any.
     */
    /**@{*/
    const std::string& formatting_input() const;
    std::string& formatting_input();
    void formatting_input(const std::string& v);
    void formatting_input(const std::string&& v);
    /**@}*/

public:
    bool operator==(const artefact& rhs) const;
    bool operator!=(const artefact& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(artefact& other) noexcept;
    artefact& operator=(artefact other);

private:
    dogen::identification::entities::physical_meta_name meta_name_;
    boost::shared_ptr<dogen::variability::entities::configuration> configuration_;
    dogen::identification::entities::logical_provenance provenance_;
    dogen::identification::entities::physical_name name_;
    boost::filesystem::path file_path_;
    std::string content_;
    dogen::physical::entities::path_properties path_properties_;
    std::vector<boost::filesystem::path> dependencies_;
    std::string unified_diff_;
    dogen::physical::entities::operation operation_;
    dogen::physical::entities::enablement_properties enablement_properties_;
    dogen::physical::entities::formatting_styles formatting_style_;
    std::string formatting_input_;
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

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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_MODEL_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/types/entities/model_type.hpp"
#include "dogen.logical/types/entities/aspect_properties.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.logical/types/entities/assistant_properties.hpp"
#include "dogen.logical/types/entities/orm/model_properties.hpp"
#include "dogen.logical/types/entities/streaming_properties.hpp"
#include "dogen.identification/hash/entities/logical_id_hash.hpp"
#include "dogen.logical/types/entities/structural/module_fwd.hpp"
#include "dogen.identification/types/entities/logical_meta_id.hpp"
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.logical/types/entities/orm/element_repository.hpp"
#include "dogen.identification/hash/entities/logical_name_hash.hpp"
#include "dogen.identification/types/entities/codec_provenance.hpp"
#include "dogen.identification/types/entities/logical_meta_name.hpp"
#include "dogen.logical/types/entities/build/element_repository.hpp"
#include "dogen.identification/hash/entities/logical_meta_id_hash.hpp"
#include "dogen.identification/hash/entities/technical_space_hash.hpp"
#include "dogen.logical/types/entities/mapping/element_repository.hpp"
#include "dogen.logical/types/entities/physical/element_repository.hpp"
#include "dogen.logical/types/entities/decoration/element_repository.hpp"
#include "dogen.logical/types/entities/structural/element_repository.hpp"
#include "dogen.logical/types/entities/templating/element_repository.hpp"
#include "dogen.identification/types/entities/technical_space_version.hpp"
#include "dogen.logical/types/entities/variability/element_repository.hpp"
#include "dogen.logical/types/entities/serialization/element_repository.hpp"
#include "dogen.logical/types/entities/visual_studio/element_repository.hpp"

namespace dogen::logical::entities {

/**
 * @brief Intermediate representation of a masd model.
 */
class model final {
public:
    model(const model&) = default;
    ~model() = default;

public:
    model();

public:
    model(model&& rhs);

public:
    model(
        const dogen::identification::entities::logical_name& name,
        const dogen::identification::entities::logical_meta_name& meta_name,
        const dogen::identification::entities::codec_provenance& provenance,
        const std::unordered_map<dogen::identification::entities::logical_name, dogen::identification::entities::model_type>& references,
        const std::unordered_set<dogen::identification::entities::logical_name>& leaves,
        const boost::shared_ptr<dogen::logical::entities::structural::module>& root_module,
        const dogen::identification::entities::technical_space input_technical_space,
        const std::list<dogen::identification::entities::technical_space>& output_technical_spaces,
        const std::unordered_set<dogen::identification::entities::technical_space>& all_technical_spaces,
        const boost::optional<dogen::logical::entities::orm::model_properties>& orm_properties,
        const dogen::logical::entities::structural::element_repository& structural_elements,
        const dogen::logical::entities::decoration::element_repository& decoration_elements,
        const dogen::logical::entities::variability::element_repository& variability_elements,
        const dogen::logical::entities::mapping::element_repository& mapping_elements,
        const dogen::logical::entities::templating::element_repository& templating_elements,
        const dogen::logical::entities::serialization::element_repository& serialization_elements,
        const dogen::logical::entities::visual_studio::element_repository& visual_studio_elements,
        const dogen::logical::entities::orm::element_repository& orm_elements,
        const dogen::logical::entities::build::element_repository& build_elements,
        const dogen::logical::entities::physical::element_repository& physical_elements,
        const std::unordered_map<dogen::identification::entities::logical_meta_id, dogen::identification::entities::logical_meta_name>& meta_names,
        const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::streaming_properties>& streaming_properties,
        const dogen::identification::entities::technical_space_version technical_space_version,
        const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::aspect_properties>& aspect_properties,
        const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::assistant_properties>& assistant_properties,
        const std::list<std::string>& project_items);

public:
    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const dogen::identification::entities::logical_name& name() const;
    dogen::identification::entities::logical_name& name();
    void name(const dogen::identification::entities::logical_name& v);
    void name(const dogen::identification::entities::logical_name&& v);
    /**@}*/

    /**
     * @brief Name of the element in the meta-model that this instance conforms to.
     */
    /**@{*/
    const dogen::identification::entities::logical_meta_name& meta_name() const;
    dogen::identification::entities::logical_meta_name& meta_name();
    void meta_name(const dogen::identification::entities::logical_meta_name& v);
    void meta_name(const dogen::identification::entities::logical_meta_name&& v);
    /**@}*/

    /**
     * @brief Details of the provenance of this model element.
     */
    /**@{*/
    const dogen::identification::entities::codec_provenance& provenance() const;
    dogen::identification::entities::codec_provenance& provenance();
    void provenance(const dogen::identification::entities::codec_provenance& v);
    void provenance(const dogen::identification::entities::codec_provenance&& v);
    /**@}*/

    /**
     * @brief All other intermediate models that this model depends on, mapped to their
     * origin.
     */
    /**@{*/
    const std::unordered_map<dogen::identification::entities::logical_name, dogen::identification::entities::model_type>& references() const;
    std::unordered_map<dogen::identification::entities::logical_name, dogen::identification::entities::model_type>& references();
    void references(const std::unordered_map<dogen::identification::entities::logical_name, dogen::identification::entities::model_type>& v);
    void references(const std::unordered_map<dogen::identification::entities::logical_name, dogen::identification::entities::model_type>&& v);
    /**@}*/

    /**
     * @brief All leaf types in this model.
     *
     * Leaves are types concrete types which have a parent.
     */
    /**@{*/
    const std::unordered_set<dogen::identification::entities::logical_name>& leaves() const;
    std::unordered_set<dogen::identification::entities::logical_name>& leaves();
    void leaves(const std::unordered_set<dogen::identification::entities::logical_name>& v);
    void leaves(const std::unordered_set<dogen::identification::entities::logical_name>&& v);
    /**@}*/

    const boost::shared_ptr<dogen::logical::entities::structural::module>& root_module() const;
    boost::shared_ptr<dogen::logical::entities::structural::module>& root_module();
    void root_module(const boost::shared_ptr<dogen::logical::entities::structural::module>& v);
    void root_module(const boost::shared_ptr<dogen::logical::entities::structural::module>&& v);

    /**
     * @brief Technical space in which this model was written.
     */
    /**@{*/
    dogen::identification::entities::technical_space input_technical_space() const;
    void input_technical_space(const dogen::identification::entities::technical_space v);
    /**@}*/

    /**
     * @brief Technical spaces into which to extract the final model.
     */
    /**@{*/
    const std::list<dogen::identification::entities::technical_space>& output_technical_spaces() const;
    std::list<dogen::identification::entities::technical_space>& output_technical_spaces();
    void output_technical_spaces(const std::list<dogen::identification::entities::technical_space>& v);
    void output_technical_spaces(const std::list<dogen::identification::entities::technical_space>&& v);
    /**@}*/

    /**
     * @brief Set of all technical concrete spaces involved in generating this model.
     *
     * Includes the primary technical space (e.g. the output technical space) as well as
     * all of the secondary technical spaces. Does not include any abstract technical
     * spaces.
     */
    /**@{*/
    const std::unordered_set<dogen::identification::entities::technical_space>& all_technical_spaces() const;
    std::unordered_set<dogen::identification::entities::technical_space>& all_technical_spaces();
    void all_technical_spaces(const std::unordered_set<dogen::identification::entities::technical_space>& v);
    void all_technical_spaces(const std::unordered_set<dogen::identification::entities::technical_space>&& v);
    /**@}*/

    const boost::optional<dogen::logical::entities::orm::model_properties>& orm_properties() const;
    boost::optional<dogen::logical::entities::orm::model_properties>& orm_properties();
    void orm_properties(const boost::optional<dogen::logical::entities::orm::model_properties>& v);
    void orm_properties(const boost::optional<dogen::logical::entities::orm::model_properties>&& v);

    /**
     * @brief All structural elements in this model.
     */
    /**@{*/
    const dogen::logical::entities::structural::element_repository& structural_elements() const;
    dogen::logical::entities::structural::element_repository& structural_elements();
    void structural_elements(const dogen::logical::entities::structural::element_repository& v);
    void structural_elements(const dogen::logical::entities::structural::element_repository&& v);
    /**@}*/

    /**
     * @brief All decoration elements in this model.
     */
    /**@{*/
    const dogen::logical::entities::decoration::element_repository& decoration_elements() const;
    dogen::logical::entities::decoration::element_repository& decoration_elements();
    void decoration_elements(const dogen::logical::entities::decoration::element_repository& v);
    void decoration_elements(const dogen::logical::entities::decoration::element_repository&& v);
    /**@}*/

    /**
     * @brief All variability elements in this model.
     */
    /**@{*/
    const dogen::logical::entities::variability::element_repository& variability_elements() const;
    dogen::logical::entities::variability::element_repository& variability_elements();
    void variability_elements(const dogen::logical::entities::variability::element_repository& v);
    void variability_elements(const dogen::logical::entities::variability::element_repository&& v);
    /**@}*/

    /**
     * @brief Model elements related to element mapping.
     */
    /**@{*/
    const dogen::logical::entities::mapping::element_repository& mapping_elements() const;
    dogen::logical::entities::mapping::element_repository& mapping_elements();
    void mapping_elements(const dogen::logical::entities::mapping::element_repository& v);
    void mapping_elements(const dogen::logical::entities::mapping::element_repository&& v);
    /**@}*/

    /**
     * @brief Elements related to text templates.
     */
    /**@{*/
    const dogen::logical::entities::templating::element_repository& templating_elements() const;
    dogen::logical::entities::templating::element_repository& templating_elements();
    void templating_elements(const dogen::logical::entities::templating::element_repository& v);
    void templating_elements(const dogen::logical::entities::templating::element_repository&& v);
    /**@}*/

    /**
     * @brief Elements related to serialization.
     */
    /**@{*/
    const dogen::logical::entities::serialization::element_repository& serialization_elements() const;
    dogen::logical::entities::serialization::element_repository& serialization_elements();
    void serialization_elements(const dogen::logical::entities::serialization::element_repository& v);
    void serialization_elements(const dogen::logical::entities::serialization::element_repository&& v);
    /**@}*/

    const dogen::logical::entities::visual_studio::element_repository& visual_studio_elements() const;
    dogen::logical::entities::visual_studio::element_repository& visual_studio_elements();
    void visual_studio_elements(const dogen::logical::entities::visual_studio::element_repository& v);
    void visual_studio_elements(const dogen::logical::entities::visual_studio::element_repository&& v);

    const dogen::logical::entities::orm::element_repository& orm_elements() const;
    dogen::logical::entities::orm::element_repository& orm_elements();
    void orm_elements(const dogen::logical::entities::orm::element_repository& v);
    void orm_elements(const dogen::logical::entities::orm::element_repository&& v);

    const dogen::logical::entities::build::element_repository& build_elements() const;
    dogen::logical::entities::build::element_repository& build_elements();
    void build_elements(const dogen::logical::entities::build::element_repository& v);
    void build_elements(const dogen::logical::entities::build::element_repository&& v);

    const dogen::logical::entities::physical::element_repository& physical_elements() const;
    dogen::logical::entities::physical::element_repository& physical_elements();
    void physical_elements(const dogen::logical::entities::physical::element_repository& v);
    void physical_elements(const dogen::logical::entities::physical::element_repository&& v);

    /**
     * @brief All meta-names by qualified name.
     */
    /**@{*/
    const std::unordered_map<dogen::identification::entities::logical_meta_id, dogen::identification::entities::logical_meta_name>& meta_names() const;
    std::unordered_map<dogen::identification::entities::logical_meta_id, dogen::identification::entities::logical_meta_name>& meta_names();
    void meta_names(const std::unordered_map<dogen::identification::entities::logical_meta_id, dogen::identification::entities::logical_meta_name>& v);
    void meta_names(const std::unordered_map<dogen::identification::entities::logical_meta_id, dogen::identification::entities::logical_meta_name>&& v);
    /**@}*/

    const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::streaming_properties>& streaming_properties() const;
    std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::streaming_properties>& streaming_properties();
    void streaming_properties(const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::streaming_properties>& v);
    void streaming_properties(const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::streaming_properties>&& v);

    /**
     * @brief Version of the technical space we are targeting.
     */
    /**@{*/
    dogen::identification::entities::technical_space_version technical_space_version() const;
    void technical_space_version(const dogen::identification::entities::technical_space_version v);
    /**@}*/

    const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::aspect_properties>& aspect_properties() const;
    std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::aspect_properties>& aspect_properties();
    void aspect_properties(const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::aspect_properties>& v);
    void aspect_properties(const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::aspect_properties>&& v);

    const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::assistant_properties>& assistant_properties() const;
    std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::assistant_properties>& assistant_properties();
    void assistant_properties(const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::assistant_properties>& v);
    void assistant_properties(const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::assistant_properties>&& v);

    const std::list<std::string>& project_items() const;
    std::list<std::string>& project_items();
    void project_items(const std::list<std::string>& v);
    void project_items(const std::list<std::string>&& v);

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    dogen::identification::entities::logical_name name_;
    dogen::identification::entities::logical_meta_name meta_name_;
    dogen::identification::entities::codec_provenance provenance_;
    std::unordered_map<dogen::identification::entities::logical_name, dogen::identification::entities::model_type> references_;
    std::unordered_set<dogen::identification::entities::logical_name> leaves_;
    boost::shared_ptr<dogen::logical::entities::structural::module> root_module_;
    dogen::identification::entities::technical_space input_technical_space_;
    std::list<dogen::identification::entities::technical_space> output_technical_spaces_;
    std::unordered_set<dogen::identification::entities::technical_space> all_technical_spaces_;
    boost::optional<dogen::logical::entities::orm::model_properties> orm_properties_;
    dogen::logical::entities::structural::element_repository structural_elements_;
    dogen::logical::entities::decoration::element_repository decoration_elements_;
    dogen::logical::entities::variability::element_repository variability_elements_;
    dogen::logical::entities::mapping::element_repository mapping_elements_;
    dogen::logical::entities::templating::element_repository templating_elements_;
    dogen::logical::entities::serialization::element_repository serialization_elements_;
    dogen::logical::entities::visual_studio::element_repository visual_studio_elements_;
    dogen::logical::entities::orm::element_repository orm_elements_;
    dogen::logical::entities::build::element_repository build_elements_;
    dogen::logical::entities::physical::element_repository physical_elements_;
    std::unordered_map<dogen::identification::entities::logical_meta_id, dogen::identification::entities::logical_meta_name> meta_names_;
    std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::streaming_properties> streaming_properties_;
    dogen::identification::entities::technical_space_version technical_space_version_;
    std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::aspect_properties> aspect_properties_;
    std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::assistant_properties> assistant_properties_;
    std::list<std::string> project_items_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::model& lhs,
    dogen::logical::entities::model& rhs) {
    lhs.swap(rhs);
}

}

#endif

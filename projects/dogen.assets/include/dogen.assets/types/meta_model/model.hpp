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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_MODEL_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_MODEL_HPP

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
#include "dogen.assets/types/meta_model/name.hpp"
#include "dogen.assets/hash/meta_model/name_hash.hpp"
#include "dogen.assets/types/meta_model/origin_types.hpp"
#include "dogen.assets/types/meta_model/technical_space.hpp"
#include "dogen.assets/types/meta_model/orm/model_properties.hpp"
#include "dogen.assets/types/meta_model/extraction_properties.hpp"
#include "dogen.assets/types/meta_model/structural/module_fwd.hpp"
#include "dogen.assets/types/meta_model/build/element_repository.hpp"
#include "dogen.assets/types/meta_model/mapping/element_repository.hpp"
#include "dogen.assets/types/meta_model/decoration/element_repository.hpp"
#include "dogen.assets/types/meta_model/structural/element_repository.hpp"
#include "dogen.assets/types/meta_model/templating/element_repository.hpp"
#include "dogen.assets/types/meta_model/variability/element_repository.hpp"
#include "dogen.assets/types/meta_model/serialization/element_repository.hpp"

namespace dogen::assets::meta_model {

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
        const dogen::assets::meta_model::name& name,
        const dogen::assets::meta_model::name& meta_name,
        const dogen::assets::meta_model::origin_types origin_type,
        const std::string& origin_sha1_hash,
        const std::string& origin_element_id,
        const std::unordered_map<dogen::assets::meta_model::name, dogen::assets::meta_model::origin_types>& references,
        const std::unordered_set<dogen::assets::meta_model::name>& leaves,
        const boost::shared_ptr<dogen::assets::meta_model::structural::module>& root_module,
        const dogen::assets::meta_model::technical_space input_technical_space,
        const std::list<dogen::assets::meta_model::technical_space>& output_technical_spaces,
        const boost::optional<dogen::assets::meta_model::orm::model_properties>& orm_properties,
        const dogen::assets::meta_model::extraction_properties& extraction_properties,
        const dogen::assets::meta_model::structural::element_repository& structural_elements,
        const dogen::assets::meta_model::decoration::element_repository& decoration_elements,
        const dogen::assets::meta_model::variability::element_repository& variability_elements,
        const dogen::assets::meta_model::mapping::element_repository& mapping_elements,
        const dogen::assets::meta_model::templating::element_repository& templating_elements,
        const dogen::assets::meta_model::serialization::element_repository& serialization_elements,
        const dogen::assets::meta_model::build::element_repository& build_elements);

public:
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
     * @brief Name of the element in the meta-model that this instance conforms to.
     */
    /**@{*/
    const dogen::assets::meta_model::name& meta_name() const;
    dogen::assets::meta_model::name& meta_name();
    void meta_name(const dogen::assets::meta_model::name& v);
    void meta_name(const dogen::assets::meta_model::name&& v);
    /**@}*/

    /**
     * @brief How was this model element originated.
     */
    /**@{*/
    dogen::assets::meta_model::origin_types origin_type() const;
    void origin_type(const dogen::assets::meta_model::origin_types v);
    /**@}*/

    /**
     * @brief SHA1 key of the original injection model.
     */
    /**@{*/
    const std::string& origin_sha1_hash() const;
    std::string& origin_sha1_hash();
    void origin_sha1_hash(const std::string& v);
    void origin_sha1_hash(const std::string&& v);
    /**@}*/

    /**
     * @brief Unique identifier within the originan injection model for this modeling element.
     */
    /**@{*/
    const std::string& origin_element_id() const;
    std::string& origin_element_id();
    void origin_element_id(const std::string& v);
    void origin_element_id(const std::string&& v);
    /**@}*/

    /**
     * @brief All other intermediate models that this model depends on, mapped to their
     * origin.
     */
    /**@{*/
    const std::unordered_map<dogen::assets::meta_model::name, dogen::assets::meta_model::origin_types>& references() const;
    std::unordered_map<dogen::assets::meta_model::name, dogen::assets::meta_model::origin_types>& references();
    void references(const std::unordered_map<dogen::assets::meta_model::name, dogen::assets::meta_model::origin_types>& v);
    void references(const std::unordered_map<dogen::assets::meta_model::name, dogen::assets::meta_model::origin_types>&& v);
    /**@}*/

    /**
     * @brief All leaf types in this model.
     *
     * Leaves are types concrete types which have a parent.
     */
    /**@{*/
    const std::unordered_set<dogen::assets::meta_model::name>& leaves() const;
    std::unordered_set<dogen::assets::meta_model::name>& leaves();
    void leaves(const std::unordered_set<dogen::assets::meta_model::name>& v);
    void leaves(const std::unordered_set<dogen::assets::meta_model::name>&& v);
    /**@}*/

    const boost::shared_ptr<dogen::assets::meta_model::structural::module>& root_module() const;
    boost::shared_ptr<dogen::assets::meta_model::structural::module>& root_module();
    void root_module(const boost::shared_ptr<dogen::assets::meta_model::structural::module>& v);
    void root_module(const boost::shared_ptr<dogen::assets::meta_model::structural::module>&& v);

    /**
     * @brief Technical space in which this model was written.
     */
    /**@{*/
    dogen::assets::meta_model::technical_space input_technical_space() const;
    void input_technical_space(const dogen::assets::meta_model::technical_space v);
    /**@}*/

    /**
     * @brief Technical spaces into which to extract the final model.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::technical_space>& output_technical_spaces() const;
    std::list<dogen::assets::meta_model::technical_space>& output_technical_spaces();
    void output_technical_spaces(const std::list<dogen::assets::meta_model::technical_space>& v);
    void output_technical_spaces(const std::list<dogen::assets::meta_model::technical_space>&& v);
    /**@}*/

    const boost::optional<dogen::assets::meta_model::orm::model_properties>& orm_properties() const;
    boost::optional<dogen::assets::meta_model::orm::model_properties>& orm_properties();
    void orm_properties(const boost::optional<dogen::assets::meta_model::orm::model_properties>& v);
    void orm_properties(const boost::optional<dogen::assets::meta_model::orm::model_properties>&& v);

    const dogen::assets::meta_model::extraction_properties& extraction_properties() const;
    dogen::assets::meta_model::extraction_properties& extraction_properties();
    void extraction_properties(const dogen::assets::meta_model::extraction_properties& v);
    void extraction_properties(const dogen::assets::meta_model::extraction_properties&& v);

    /**
     * @brief All structural elements in this model.
     */
    /**@{*/
    const dogen::assets::meta_model::structural::element_repository& structural_elements() const;
    dogen::assets::meta_model::structural::element_repository& structural_elements();
    void structural_elements(const dogen::assets::meta_model::structural::element_repository& v);
    void structural_elements(const dogen::assets::meta_model::structural::element_repository&& v);
    /**@}*/

    /**
     * @brief All decoration elements in this model.
     */
    /**@{*/
    const dogen::assets::meta_model::decoration::element_repository& decoration_elements() const;
    dogen::assets::meta_model::decoration::element_repository& decoration_elements();
    void decoration_elements(const dogen::assets::meta_model::decoration::element_repository& v);
    void decoration_elements(const dogen::assets::meta_model::decoration::element_repository&& v);
    /**@}*/

    /**
     * @brief All variability elements in this model.
     */
    /**@{*/
    const dogen::assets::meta_model::variability::element_repository& variability_elements() const;
    dogen::assets::meta_model::variability::element_repository& variability_elements();
    void variability_elements(const dogen::assets::meta_model::variability::element_repository& v);
    void variability_elements(const dogen::assets::meta_model::variability::element_repository&& v);
    /**@}*/

    /**
     * @brief Model elements related to element mapping.
     */
    /**@{*/
    const dogen::assets::meta_model::mapping::element_repository& mapping_elements() const;
    dogen::assets::meta_model::mapping::element_repository& mapping_elements();
    void mapping_elements(const dogen::assets::meta_model::mapping::element_repository& v);
    void mapping_elements(const dogen::assets::meta_model::mapping::element_repository&& v);
    /**@}*/

    /**
     * @brief Elements related to text templates.
     */
    /**@{*/
    const dogen::assets::meta_model::templating::element_repository& templating_elements() const;
    dogen::assets::meta_model::templating::element_repository& templating_elements();
    void templating_elements(const dogen::assets::meta_model::templating::element_repository& v);
    void templating_elements(const dogen::assets::meta_model::templating::element_repository&& v);
    /**@}*/

    /**
     * @brief Elements related to serialization.
     */
    /**@{*/
    const dogen::assets::meta_model::serialization::element_repository& serialization_elements() const;
    dogen::assets::meta_model::serialization::element_repository& serialization_elements();
    void serialization_elements(const dogen::assets::meta_model::serialization::element_repository& v);
    void serialization_elements(const dogen::assets::meta_model::serialization::element_repository&& v);
    /**@}*/

    const dogen::assets::meta_model::build::element_repository& build_elements() const;
    dogen::assets::meta_model::build::element_repository& build_elements();
    void build_elements(const dogen::assets::meta_model::build::element_repository& v);
    void build_elements(const dogen::assets::meta_model::build::element_repository&& v);

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    dogen::assets::meta_model::name name_;
    dogen::assets::meta_model::name meta_name_;
    dogen::assets::meta_model::origin_types origin_type_;
    std::string origin_sha1_hash_;
    std::string origin_element_id_;
    std::unordered_map<dogen::assets::meta_model::name, dogen::assets::meta_model::origin_types> references_;
    std::unordered_set<dogen::assets::meta_model::name> leaves_;
    boost::shared_ptr<dogen::assets::meta_model::structural::module> root_module_;
    dogen::assets::meta_model::technical_space input_technical_space_;
    std::list<dogen::assets::meta_model::technical_space> output_technical_spaces_;
    boost::optional<dogen::assets::meta_model::orm::model_properties> orm_properties_;
    dogen::assets::meta_model::extraction_properties extraction_properties_;
    dogen::assets::meta_model::structural::element_repository structural_elements_;
    dogen::assets::meta_model::decoration::element_repository decoration_elements_;
    dogen::assets::meta_model::variability::element_repository variability_elements_;
    dogen::assets::meta_model::mapping::element_repository mapping_elements_;
    dogen::assets::meta_model::templating::element_repository templating_elements_;
    dogen::assets::meta_model::serialization::element_repository serialization_elements_;
    dogen::assets::meta_model::build::element_repository build_elements_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::model& lhs,
    dogen::assets::meta_model::model& rhs) {
    lhs.swap(rhs);
}

}

#endif

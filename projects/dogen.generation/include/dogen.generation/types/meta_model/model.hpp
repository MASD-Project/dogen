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
#ifndef DOGEN_GENERATION_TYPES_META_MODEL_MODEL_HPP
#define DOGEN_GENERATION_TYPES_META_MODEL_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/meta_model/name.hpp"
#include "dogen.logical/hash/meta_model/name_hash.hpp"
#include "dogen.logical/types/meta_model/element_fwd.hpp"
#include "dogen.logical/types/meta_model/origin_types.hpp"
#include "dogen.logical/types/meta_model/technical_space.hpp"
#include "dogen.logical/hash/meta_model/technical_space_hash.hpp"
#include "dogen.generation/types/meta_model/element_archetype.hpp"
#include "dogen.logical/types/meta_model/orm/model_properties.hpp"
#include "dogen.generation/types/meta_model/locator_properties.hpp"
#include "dogen.logical/types/meta_model/extraction_properties.hpp"
#include "dogen.logical/types/meta_model/structural/module_fwd.hpp"
#include "dogen.generation/hash/meta_model/element_archetype_hash.hpp"
#include "dogen.generation/types/meta_model/global_archetype_location_properties.hpp"

namespace dogen::generation::meta_model {

/**
 * @brief Yarn model.
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
        const dogen::logical::meta_model::name& name,
        const dogen::logical::meta_model::name& meta_name,
        const std::string& origin_sha1_hash,
        const std::string& origin_element_id,
        const std::unordered_map<dogen::logical::meta_model::name, dogen::logical::meta_model::origin_types>& references,
        const std::unordered_set<dogen::logical::meta_model::name>& leaves,
        const std::vector<boost::shared_ptr<dogen::logical::meta_model::element> >& elements,
        const boost::shared_ptr<dogen::logical::meta_model::structural::module>& root_module,
        const std::unordered_set<std::string>& module_ids,
        const bool has_generatable_types,
        const dogen::logical::meta_model::technical_space input_technical_space,
        const dogen::logical::meta_model::technical_space output_technical_space,
        const std::unordered_set<dogen::logical::meta_model::technical_space>& all_technical_spaces,
        const boost::optional<dogen::logical::meta_model::orm::model_properties>& orm_properties,
        const std::unordered_set<dogen::generation::meta_model::element_archetype>& enabled_archetype_for_element,
        const dogen::generation::meta_model::locator_properties& locator_properties,
        const dogen::generation::meta_model::global_archetype_location_properties& global_archetype_location_properties,
        const dogen::logical::meta_model::extraction_properties& extraction_properties);

public:
    const dogen::logical::meta_model::name& name() const;
    dogen::logical::meta_model::name& name();
    void name(const dogen::logical::meta_model::name& v);
    void name(const dogen::logical::meta_model::name&& v);

    const dogen::logical::meta_model::name& meta_name() const;
    dogen::logical::meta_model::name& meta_name();
    void meta_name(const dogen::logical::meta_model::name& v);
    void meta_name(const dogen::logical::meta_model::name&& v);

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
     * @brief All other models that this model depends on, mapped to their origin.
     */
    /**@{*/
    const std::unordered_map<dogen::logical::meta_model::name, dogen::logical::meta_model::origin_types>& references() const;
    std::unordered_map<dogen::logical::meta_model::name, dogen::logical::meta_model::origin_types>& references();
    void references(const std::unordered_map<dogen::logical::meta_model::name, dogen::logical::meta_model::origin_types>& v);
    void references(const std::unordered_map<dogen::logical::meta_model::name, dogen::logical::meta_model::origin_types>&& v);
    /**@}*/

    /**
     * @brief All leaf types in this model.
     *
     * Leaves are types concrete types which have a parent.
     */
    /**@{*/
    const std::unordered_set<dogen::logical::meta_model::name>& leaves() const;
    std::unordered_set<dogen::logical::meta_model::name>& leaves();
    void leaves(const std::unordered_set<dogen::logical::meta_model::name>& v);
    void leaves(const std::unordered_set<dogen::logical::meta_model::name>&& v);
    /**@}*/

    const std::vector<boost::shared_ptr<dogen::logical::meta_model::element> >& elements() const;
    std::vector<boost::shared_ptr<dogen::logical::meta_model::element> >& elements();
    void elements(const std::vector<boost::shared_ptr<dogen::logical::meta_model::element> >& v);
    void elements(const std::vector<boost::shared_ptr<dogen::logical::meta_model::element> >&& v);

    /**
     * @brief The module that represents the model.
     */
    /**@{*/
    const boost::shared_ptr<dogen::logical::meta_model::structural::module>& root_module() const;
    boost::shared_ptr<dogen::logical::meta_model::structural::module>& root_module();
    void root_module(const boost::shared_ptr<dogen::logical::meta_model::structural::module>& v);
    void root_module(const boost::shared_ptr<dogen::logical::meta_model::structural::module>&& v);
    /**@}*/

    /**
     * @brief IDs of all of the model elements which are modules.
     */
    /**@{*/
    const std::unordered_set<std::string>& module_ids() const;
    std::unordered_set<std::string>& module_ids();
    void module_ids(const std::unordered_set<std::string>& v);
    void module_ids(const std::unordered_set<std::string>&& v);
    /**@}*/

    /**
     * @brief If true the intermediate model has at least one generable type, false otherwise.
     */
    /**@{*/
    bool has_generatable_types() const;
    void has_generatable_types(const bool v);
    /**@}*/

    /**
     * @brief Technical space which this model used originally.
     */
    /**@{*/
    dogen::logical::meta_model::technical_space input_technical_space() const;
    void input_technical_space(const dogen::logical::meta_model::technical_space v);
    /**@}*/

    /**
     * @brief Technical space into which to output the model.
     */
    /**@{*/
    dogen::logical::meta_model::technical_space output_technical_space() const;
    void output_technical_space(const dogen::logical::meta_model::technical_space v);
    /**@}*/

    /**
     * @brief Set of all technical concrete spaces involved in generating this model.
     *
     * Includes the primary technical space (e.g. the output technical space) as well as
     * all of the secondary technical spaces. Does not include any abstract technical
     * spaces.
     */
    /**@{*/
    const std::unordered_set<dogen::logical::meta_model::technical_space>& all_technical_spaces() const;
    std::unordered_set<dogen::logical::meta_model::technical_space>& all_technical_spaces();
    void all_technical_spaces(const std::unordered_set<dogen::logical::meta_model::technical_space>& v);
    void all_technical_spaces(const std::unordered_set<dogen::logical::meta_model::technical_space>&& v);
    /**@}*/

    const boost::optional<dogen::logical::meta_model::orm::model_properties>& orm_properties() const;
    boost::optional<dogen::logical::meta_model::orm::model_properties>& orm_properties();
    void orm_properties(const boost::optional<dogen::logical::meta_model::orm::model_properties>& v);
    void orm_properties(const boost::optional<dogen::logical::meta_model::orm::model_properties>&& v);

    const std::unordered_set<dogen::generation::meta_model::element_archetype>& enabled_archetype_for_element() const;
    std::unordered_set<dogen::generation::meta_model::element_archetype>& enabled_archetype_for_element();
    void enabled_archetype_for_element(const std::unordered_set<dogen::generation::meta_model::element_archetype>& v);
    void enabled_archetype_for_element(const std::unordered_set<dogen::generation::meta_model::element_archetype>&& v);

    const dogen::generation::meta_model::locator_properties& locator_properties() const;
    dogen::generation::meta_model::locator_properties& locator_properties();
    void locator_properties(const dogen::generation::meta_model::locator_properties& v);
    void locator_properties(const dogen::generation::meta_model::locator_properties&& v);

    const dogen::generation::meta_model::global_archetype_location_properties& global_archetype_location_properties() const;
    dogen::generation::meta_model::global_archetype_location_properties& global_archetype_location_properties();
    void global_archetype_location_properties(const dogen::generation::meta_model::global_archetype_location_properties& v);
    void global_archetype_location_properties(const dogen::generation::meta_model::global_archetype_location_properties&& v);

    const dogen::logical::meta_model::extraction_properties& extraction_properties() const;
    dogen::logical::meta_model::extraction_properties& extraction_properties();
    void extraction_properties(const dogen::logical::meta_model::extraction_properties& v);
    void extraction_properties(const dogen::logical::meta_model::extraction_properties&& v);

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    dogen::logical::meta_model::name name_;
    dogen::logical::meta_model::name meta_name_;
    std::string origin_sha1_hash_;
    std::string origin_element_id_;
    std::unordered_map<dogen::logical::meta_model::name, dogen::logical::meta_model::origin_types> references_;
    std::unordered_set<dogen::logical::meta_model::name> leaves_;
    std::vector<boost::shared_ptr<dogen::logical::meta_model::element> > elements_;
    boost::shared_ptr<dogen::logical::meta_model::structural::module> root_module_;
    std::unordered_set<std::string> module_ids_;
    bool has_generatable_types_;
    dogen::logical::meta_model::technical_space input_technical_space_;
    dogen::logical::meta_model::technical_space output_technical_space_;
    std::unordered_set<dogen::logical::meta_model::technical_space> all_technical_spaces_;
    boost::optional<dogen::logical::meta_model::orm::model_properties> orm_properties_;
    std::unordered_set<dogen::generation::meta_model::element_archetype> enabled_archetype_for_element_;
    dogen::generation::meta_model::locator_properties locator_properties_;
    dogen::generation::meta_model::global_archetype_location_properties global_archetype_location_properties_;
    dogen::logical::meta_model::extraction_properties extraction_properties_;
};

}

namespace std {

template<>
inline void swap(
    dogen::generation::meta_model::model& lhs,
    dogen::generation::meta_model::model& rhs) {
    lhs.swap(rhs);
}

}

#endif

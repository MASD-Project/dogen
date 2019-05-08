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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_MODEL_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_MODEL_HPP

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
#include "masd.dogen.coding/types/meta_model/name.hpp"
#include "masd.dogen.coding/hash/meta_model/name_hash.hpp"
#include "masd.dogen.coding/types/meta_model/origin_types.hpp"
#include "masd.dogen.coding/types/meta_model/technical_space.hpp"
#include "masd.dogen.coding/types/meta_model/orm/model_properties.hpp"
#include "masd.dogen.coding/types/meta_model/extraction_properties.hpp"
#include "masd.dogen.coding/types/meta_model/structural/module_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/structural/object_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/decoration/licence_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/structural/builtin_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/structural/visitor_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/decoration/modeline_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/structural/exception_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/structural/primitive_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/structural/enumeration_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/decoration/modeline_group_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/structural/object_template_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/decoration/generation_marker_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/variability/profile_template_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/variability/feature_template_group_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/variability/feature_template_group_registrar_fwd.hpp"

namespace masd::dogen::coding::meta_model {

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
        const masd::dogen::coding::meta_model::name& name,
        const masd::dogen::coding::meta_model::name& meta_name,
        const masd::dogen::coding::meta_model::origin_types origin_type,
        const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& references,
        const std::unordered_set<masd::dogen::coding::meta_model::name>& leaves,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::module> >& modules,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object_template> >& object_templates,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::builtin> >& builtins,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::enumeration> >& enumerations,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::primitive> >& primitives,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object> >& objects,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::exception> >& exceptions,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::visitor> >& visitors,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline_group> >& modeline_groups,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline> >& modelines,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::licence> >& licences,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::generation_marker> >& generation_markers,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> >& variability_profile_templates,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> >& variability_feature_template_groups,
        const boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group_registrar>& variability_feature_template_group_registrar,
        const boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>& root_module,
        const masd::dogen::coding::meta_model::technical_space input_technical_space,
        const std::list<masd::dogen::coding::meta_model::technical_space>& output_technical_spaces,
        const boost::optional<masd::dogen::coding::meta_model::orm::model_properties>& orm_properties,
        const masd::dogen::coding::meta_model::extraction_properties& extraction_properties);

public:
    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const masd::dogen::coding::meta_model::name& name() const;
    masd::dogen::coding::meta_model::name& name();
    void name(const masd::dogen::coding::meta_model::name& v);
    void name(const masd::dogen::coding::meta_model::name&& v);
    /**@}*/

    /**
     * @brief Name of the element in the meta-model that this instance conforms to.
     */
    /**@{*/
    const masd::dogen::coding::meta_model::name& meta_name() const;
    masd::dogen::coding::meta_model::name& meta_name();
    void meta_name(const masd::dogen::coding::meta_model::name& v);
    void meta_name(const masd::dogen::coding::meta_model::name&& v);
    /**@}*/

    /**
     * @brief How was this model element originated.
     */
    /**@{*/
    masd::dogen::coding::meta_model::origin_types origin_type() const;
    void origin_type(const masd::dogen::coding::meta_model::origin_types v);
    /**@}*/

    /**
     * @brief All other intermediate models that this model depends on, mapped to their
     * origin.
     */
    /**@{*/
    const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& references() const;
    std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& references();
    void references(const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& v);
    void references(const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>&& v);
    /**@}*/

    /**
     * @brief All leaf types in this model.
     *
     * Leaves are types concrete types which have a parent.
     */
    /**@{*/
    const std::unordered_set<masd::dogen::coding::meta_model::name>& leaves() const;
    std::unordered_set<masd::dogen::coding::meta_model::name>& leaves();
    void leaves(const std::unordered_set<masd::dogen::coding::meta_model::name>& v);
    void leaves(const std::unordered_set<masd::dogen::coding::meta_model::name>&& v);
    /**@}*/

    /**
     * @brief Modules contained in the model.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::module> >& modules() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::module> >& modules();
    void modules(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::module> >& v);
    void modules(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::module> >&& v);
    /**@}*/

    /**
     * @brief All the object templates available in this model.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object_template> >& object_templates() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object_template> >& object_templates();
    void object_templates(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object_template> >& v);
    void object_templates(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object_template> >&& v);
    /**@}*/

    /**
     * @brief All built-ins contained in this model.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::builtin> >& builtins() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::builtin> >& builtins();
    void builtins(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::builtin> >& v);
    void builtins(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::builtin> >&& v);
    /**@}*/

    /**
     * @brief All enumerations contained in this model.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::enumeration> >& enumerations() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::enumeration> >& enumerations();
    void enumerations(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::enumeration> >& v);
    void enumerations(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::enumeration> >&& v);
    /**@}*/

    /**
     * @brief All primitives in this model.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::primitive> >& primitives() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::primitive> >& primitives();
    void primitives(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::primitive> >& v);
    void primitives(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::primitive> >&& v);
    /**@}*/

    /**
     * @brief All objects contained in this model.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object> >& objects() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object> >& objects();
    void objects(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object> >& v);
    void objects(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object> >&& v);
    /**@}*/

    /**
     * @brief All exceptions in this model.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::exception> >& exceptions() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::exception> >& exceptions();
    void exceptions(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::exception> >& v);
    void exceptions(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::exception> >&& v);
    /**@}*/

    /**
     * @brief All visitors in this model.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::visitor> >& visitors() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::visitor> >& visitors();
    void visitors(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::visitor> >& v);
    void visitors(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::visitor> >&& v);
    /**@}*/

    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline_group> >& modeline_groups() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline_group> >& modeline_groups();
    void modeline_groups(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline_group> >& v);
    void modeline_groups(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline_group> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline> >& modelines() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline> >& modelines();
    void modelines(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline> >& v);
    void modelines(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::licence> >& licences() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::licence> >& licences();
    void licences(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::licence> >& v);
    void licences(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::licence> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::generation_marker> >& generation_markers() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::generation_marker> >& generation_markers();
    void generation_markers(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::generation_marker> >& v);
    void generation_markers(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::generation_marker> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> >& variability_profile_templates() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> >& variability_profile_templates();
    void variability_profile_templates(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> >& v);
    void variability_profile_templates(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> >& variability_feature_template_groups() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> >& variability_feature_template_groups();
    void variability_feature_template_groups(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> >& v);
    void variability_feature_template_groups(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> >&& v);

    const boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group_registrar>& variability_feature_template_group_registrar() const;
    boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group_registrar>& variability_feature_template_group_registrar();
    void variability_feature_template_group_registrar(const boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group_registrar>& v);
    void variability_feature_template_group_registrar(const boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group_registrar>&& v);

    const boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>& root_module() const;
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>& root_module();
    void root_module(const boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>& v);
    void root_module(const boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>&& v);

    /**
     * @brief Technical space in which this model was written.
     */
    /**@{*/
    masd::dogen::coding::meta_model::technical_space input_technical_space() const;
    void input_technical_space(const masd::dogen::coding::meta_model::technical_space v);
    /**@}*/

    /**
     * @brief Technical spaces into which to extract the final model.
     */
    /**@{*/
    const std::list<masd::dogen::coding::meta_model::technical_space>& output_technical_spaces() const;
    std::list<masd::dogen::coding::meta_model::technical_space>& output_technical_spaces();
    void output_technical_spaces(const std::list<masd::dogen::coding::meta_model::technical_space>& v);
    void output_technical_spaces(const std::list<masd::dogen::coding::meta_model::technical_space>&& v);
    /**@}*/

    const boost::optional<masd::dogen::coding::meta_model::orm::model_properties>& orm_properties() const;
    boost::optional<masd::dogen::coding::meta_model::orm::model_properties>& orm_properties();
    void orm_properties(const boost::optional<masd::dogen::coding::meta_model::orm::model_properties>& v);
    void orm_properties(const boost::optional<masd::dogen::coding::meta_model::orm::model_properties>&& v);

    const masd::dogen::coding::meta_model::extraction_properties& extraction_properties() const;
    masd::dogen::coding::meta_model::extraction_properties& extraction_properties();
    void extraction_properties(const masd::dogen::coding::meta_model::extraction_properties& v);
    void extraction_properties(const masd::dogen::coding::meta_model::extraction_properties&& v);

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    masd::dogen::coding::meta_model::name name_;
    masd::dogen::coding::meta_model::name meta_name_;
    masd::dogen::coding::meta_model::origin_types origin_type_;
    std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types> references_;
    std::unordered_set<masd::dogen::coding::meta_model::name> leaves_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::module> > modules_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object_template> > object_templates_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::builtin> > builtins_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::enumeration> > enumerations_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::primitive> > primitives_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object> > objects_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::exception> > exceptions_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::visitor> > visitors_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline_group> > modeline_groups_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline> > modelines_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::licence> > licences_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::generation_marker> > generation_markers_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> > variability_profile_templates_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> > variability_feature_template_groups_;
    boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group_registrar> variability_feature_template_group_registrar_;
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::module> root_module_;
    masd::dogen::coding::meta_model::technical_space input_technical_space_;
    std::list<masd::dogen::coding::meta_model::technical_space> output_technical_spaces_;
    boost::optional<masd::dogen::coding::meta_model::orm::model_properties> orm_properties_;
    masd::dogen::coding::meta_model::extraction_properties extraction_properties_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::model& lhs,
    masd::dogen::coding::meta_model::model& rhs) {
    lhs.swap(rhs);
}

}

#endif

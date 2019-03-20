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
#include "masd.dogen.coding/types/meta_model/model.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/builtin.hpp"
#include "masd.dogen.coding/types/meta_model/visitor.hpp"
#include "masd.dogen.coding/types/meta_model/exception.hpp"
#include "masd.dogen.coding/types/meta_model/primitive.hpp"
#include "masd.dogen.coding/types/meta_model/enumeration.hpp"
#include "masd.dogen.coding/types/meta_model/object_template.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::coding::meta_model::module>& lhs,
const boost::shared_ptr<masd::dogen::coding::meta_model::module>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::coding::meta_model::object_template>& lhs,
const boost::shared_ptr<masd::dogen::coding::meta_model::object_template>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::coding::meta_model::builtin>& lhs,
const boost::shared_ptr<masd::dogen::coding::meta_model::builtin>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::coding::meta_model::enumeration>& lhs,
const boost::shared_ptr<masd::dogen::coding::meta_model::enumeration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::coding::meta_model::primitive>& lhs,
const boost::shared_ptr<masd::dogen::coding::meta_model::primitive>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::coding::meta_model::object>& lhs,
const boost::shared_ptr<masd::dogen::coding::meta_model::object>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::coding::meta_model::exception>& lhs,
const boost::shared_ptr<masd::dogen::coding::meta_model::exception>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::coding::meta_model::visitor>& lhs,
const boost::shared_ptr<masd::dogen::coding::meta_model::visitor>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace masd::dogen::coding::meta_model {

model::model()
    : origin_type_(static_cast<masd::dogen::coding::meta_model::origin_types>(0)),
      input_language_(static_cast<masd::dogen::coding::meta_model::languages>(0)) { }

model::model(model&& rhs)
    : name_(std::move(rhs.name_)),
      meta_name_(std::move(rhs.meta_name_)),
      origin_type_(std::move(rhs.origin_type_)),
      references_(std::move(rhs.references_)),
      leaves_(std::move(rhs.leaves_)),
      modules_(std::move(rhs.modules_)),
      object_templates_(std::move(rhs.object_templates_)),
      builtins_(std::move(rhs.builtins_)),
      enumerations_(std::move(rhs.enumerations_)),
      primitives_(std::move(rhs.primitives_)),
      objects_(std::move(rhs.objects_)),
      exceptions_(std::move(rhs.exceptions_)),
      visitors_(std::move(rhs.visitors_)),
      modeline_groups_(std::move(rhs.modeline_groups_)),
      licences_(std::move(rhs.licences_)),
      generation_markers_(std::move(rhs.generation_markers_)),
      root_module_(std::move(rhs.root_module_)),
      input_language_(std::move(rhs.input_language_)),
      output_languages_(std::move(rhs.output_languages_)),
      orm_properties_(std::move(rhs.orm_properties_)),
      extraction_properties_(std::move(rhs.extraction_properties_)) { }

model::model(
    const masd::dogen::coding::meta_model::name& name,
    const masd::dogen::coding::meta_model::name& meta_name,
    const masd::dogen::coding::meta_model::origin_types origin_type,
    const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& references,
    const std::unordered_set<masd::dogen::coding::meta_model::name>& leaves,
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::module> >& modules,
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object_template> >& object_templates,
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::builtin> >& builtins,
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::enumeration> >& enumerations,
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::primitive> >& primitives,
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object> >& objects,
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::exception> >& exceptions,
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::visitor> >& visitors,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::modeline_group>& modeline_groups,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::licence>& licences,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::generation_marker>& generation_markers,
    const boost::shared_ptr<masd::dogen::coding::meta_model::module>& root_module,
    const masd::dogen::coding::meta_model::languages input_language,
    const std::list<masd::dogen::coding::meta_model::languages>& output_languages,
    const boost::optional<masd::dogen::coding::meta_model::orm_model_properties>& orm_properties,
    const masd::dogen::coding::meta_model::extraction_properties& extraction_properties)
    : name_(name),
      meta_name_(meta_name),
      origin_type_(origin_type),
      references_(references),
      leaves_(leaves),
      modules_(modules),
      object_templates_(object_templates),
      builtins_(builtins),
      enumerations_(enumerations),
      primitives_(primitives),
      objects_(objects),
      exceptions_(exceptions),
      visitors_(visitors),
      modeline_groups_(modeline_groups),
      licences_(licences),
      generation_markers_(generation_markers),
      root_module_(root_module),
      input_language_(input_language),
      output_languages_(output_languages),
      orm_properties_(orm_properties),
      extraction_properties_(extraction_properties) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(meta_name_, other.meta_name_);
    swap(origin_type_, other.origin_type_);
    swap(references_, other.references_);
    swap(leaves_, other.leaves_);
    swap(modules_, other.modules_);
    swap(object_templates_, other.object_templates_);
    swap(builtins_, other.builtins_);
    swap(enumerations_, other.enumerations_);
    swap(primitives_, other.primitives_);
    swap(objects_, other.objects_);
    swap(exceptions_, other.exceptions_);
    swap(visitors_, other.visitors_);
    swap(modeline_groups_, other.modeline_groups_);
    swap(licences_, other.licences_);
    swap(generation_markers_, other.generation_markers_);
    swap(root_module_, other.root_module_);
    swap(input_language_, other.input_language_);
    swap(output_languages_, other.output_languages_);
    swap(orm_properties_, other.orm_properties_);
    swap(extraction_properties_, other.extraction_properties_);
}

bool model::operator==(const model& rhs) const {
    return name_ == rhs.name_ &&
        meta_name_ == rhs.meta_name_ &&
        origin_type_ == rhs.origin_type_ &&
        references_ == rhs.references_ &&
        leaves_ == rhs.leaves_ &&
        modules_ == rhs.modules_ &&
        object_templates_ == rhs.object_templates_ &&
        builtins_ == rhs.builtins_ &&
        enumerations_ == rhs.enumerations_ &&
        primitives_ == rhs.primitives_ &&
        objects_ == rhs.objects_ &&
        exceptions_ == rhs.exceptions_ &&
        visitors_ == rhs.visitors_ &&
        modeline_groups_ == rhs.modeline_groups_ &&
        licences_ == rhs.licences_ &&
        generation_markers_ == rhs.generation_markers_ &&
        root_module_ == rhs.root_module_ &&
        input_language_ == rhs.input_language_ &&
        output_languages_ == rhs.output_languages_ &&
        orm_properties_ == rhs.orm_properties_ &&
        extraction_properties_ == rhs.extraction_properties_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const masd::dogen::coding::meta_model::name& model::name() const {
    return name_;
}

masd::dogen::coding::meta_model::name& model::name() {
    return name_;
}

void model::name(const masd::dogen::coding::meta_model::name& v) {
    name_ = v;
}

void model::name(const masd::dogen::coding::meta_model::name&& v) {
    name_ = std::move(v);
}

const masd::dogen::coding::meta_model::name& model::meta_name() const {
    return meta_name_;
}

masd::dogen::coding::meta_model::name& model::meta_name() {
    return meta_name_;
}

void model::meta_name(const masd::dogen::coding::meta_model::name& v) {
    meta_name_ = v;
}

void model::meta_name(const masd::dogen::coding::meta_model::name&& v) {
    meta_name_ = std::move(v);
}

masd::dogen::coding::meta_model::origin_types model::origin_type() const {
    return origin_type_;
}

void model::origin_type(const masd::dogen::coding::meta_model::origin_types v) {
    origin_type_ = v;
}

const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& model::references() const {
    return references_;
}

std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& model::references() {
    return references_;
}

void model::references(const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>& v) {
    references_ = v;
}

void model::references(const std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types>&& v) {
    references_ = std::move(v);
}

const std::unordered_set<masd::dogen::coding::meta_model::name>& model::leaves() const {
    return leaves_;
}

std::unordered_set<masd::dogen::coding::meta_model::name>& model::leaves() {
    return leaves_;
}

void model::leaves(const std::unordered_set<masd::dogen::coding::meta_model::name>& v) {
    leaves_ = v;
}

void model::leaves(const std::unordered_set<masd::dogen::coding::meta_model::name>&& v) {
    leaves_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::module> >& model::modules() const {
    return modules_;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::module> >& model::modules() {
    return modules_;
}

void model::modules(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::module> >& v) {
    modules_ = v;
}

void model::modules(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::module> >&& v) {
    modules_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object_template> >& model::object_templates() const {
    return object_templates_;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object_template> >& model::object_templates() {
    return object_templates_;
}

void model::object_templates(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object_template> >& v) {
    object_templates_ = v;
}

void model::object_templates(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object_template> >&& v) {
    object_templates_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::builtin> >& model::builtins() const {
    return builtins_;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::builtin> >& model::builtins() {
    return builtins_;
}

void model::builtins(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::builtin> >& v) {
    builtins_ = v;
}

void model::builtins(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::builtin> >&& v) {
    builtins_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::enumeration> >& model::enumerations() const {
    return enumerations_;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::enumeration> >& model::enumerations() {
    return enumerations_;
}

void model::enumerations(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::enumeration> >& v) {
    enumerations_ = v;
}

void model::enumerations(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::enumeration> >&& v) {
    enumerations_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::primitive> >& model::primitives() const {
    return primitives_;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::primitive> >& model::primitives() {
    return primitives_;
}

void model::primitives(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::primitive> >& v) {
    primitives_ = v;
}

void model::primitives(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::primitive> >&& v) {
    primitives_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object> >& model::objects() const {
    return objects_;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object> >& model::objects() {
    return objects_;
}

void model::objects(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object> >& v) {
    objects_ = v;
}

void model::objects(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object> >&& v) {
    objects_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::exception> >& model::exceptions() const {
    return exceptions_;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::exception> >& model::exceptions() {
    return exceptions_;
}

void model::exceptions(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::exception> >& v) {
    exceptions_ = v;
}

void model::exceptions(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::exception> >&& v) {
    exceptions_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::visitor> >& model::visitors() const {
    return visitors_;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::visitor> >& model::visitors() {
    return visitors_;
}

void model::visitors(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::visitor> >& v) {
    visitors_ = v;
}

void model::visitors(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::visitor> >&& v) {
    visitors_ = std::move(v);
}

const std::unordered_map<std::string, masd::dogen::coding::meta_model::modeline_group>& model::modeline_groups() const {
    return modeline_groups_;
}

std::unordered_map<std::string, masd::dogen::coding::meta_model::modeline_group>& model::modeline_groups() {
    return modeline_groups_;
}

void model::modeline_groups(const std::unordered_map<std::string, masd::dogen::coding::meta_model::modeline_group>& v) {
    modeline_groups_ = v;
}

void model::modeline_groups(const std::unordered_map<std::string, masd::dogen::coding::meta_model::modeline_group>&& v) {
    modeline_groups_ = std::move(v);
}

const std::unordered_map<std::string, masd::dogen::coding::meta_model::licence>& model::licences() const {
    return licences_;
}

std::unordered_map<std::string, masd::dogen::coding::meta_model::licence>& model::licences() {
    return licences_;
}

void model::licences(const std::unordered_map<std::string, masd::dogen::coding::meta_model::licence>& v) {
    licences_ = v;
}

void model::licences(const std::unordered_map<std::string, masd::dogen::coding::meta_model::licence>&& v) {
    licences_ = std::move(v);
}

const std::unordered_map<std::string, masd::dogen::coding::meta_model::generation_marker>& model::generation_markers() const {
    return generation_markers_;
}

std::unordered_map<std::string, masd::dogen::coding::meta_model::generation_marker>& model::generation_markers() {
    return generation_markers_;
}

void model::generation_markers(const std::unordered_map<std::string, masd::dogen::coding::meta_model::generation_marker>& v) {
    generation_markers_ = v;
}

void model::generation_markers(const std::unordered_map<std::string, masd::dogen::coding::meta_model::generation_marker>&& v) {
    generation_markers_ = std::move(v);
}

const boost::shared_ptr<masd::dogen::coding::meta_model::module>& model::root_module() const {
    return root_module_;
}

boost::shared_ptr<masd::dogen::coding::meta_model::module>& model::root_module() {
    return root_module_;
}

void model::root_module(const boost::shared_ptr<masd::dogen::coding::meta_model::module>& v) {
    root_module_ = v;
}

void model::root_module(const boost::shared_ptr<masd::dogen::coding::meta_model::module>&& v) {
    root_module_ = std::move(v);
}

masd::dogen::coding::meta_model::languages model::input_language() const {
    return input_language_;
}

void model::input_language(const masd::dogen::coding::meta_model::languages v) {
    input_language_ = v;
}

const std::list<masd::dogen::coding::meta_model::languages>& model::output_languages() const {
    return output_languages_;
}

std::list<masd::dogen::coding::meta_model::languages>& model::output_languages() {
    return output_languages_;
}

void model::output_languages(const std::list<masd::dogen::coding::meta_model::languages>& v) {
    output_languages_ = v;
}

void model::output_languages(const std::list<masd::dogen::coding::meta_model::languages>&& v) {
    output_languages_ = std::move(v);
}

const boost::optional<masd::dogen::coding::meta_model::orm_model_properties>& model::orm_properties() const {
    return orm_properties_;
}

boost::optional<masd::dogen::coding::meta_model::orm_model_properties>& model::orm_properties() {
    return orm_properties_;
}

void model::orm_properties(const boost::optional<masd::dogen::coding::meta_model::orm_model_properties>& v) {
    orm_properties_ = v;
}

void model::orm_properties(const boost::optional<masd::dogen::coding::meta_model::orm_model_properties>&& v) {
    orm_properties_ = std::move(v);
}

const masd::dogen::coding::meta_model::extraction_properties& model::extraction_properties() const {
    return extraction_properties_;
}

masd::dogen::coding::meta_model::extraction_properties& model::extraction_properties() {
    return extraction_properties_;
}

void model::extraction_properties(const masd::dogen::coding::meta_model::extraction_properties& v) {
    extraction_properties_ = v;
}

void model::extraction_properties(const masd::dogen::coding::meta_model::extraction_properties&& v) {
    extraction_properties_ = std::move(v);
}

}

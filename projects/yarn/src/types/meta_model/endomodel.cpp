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
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/concept.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/visitor.hpp"
#include "dogen/yarn/types/meta_model/endomodel.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::meta_model::module>& lhs,
const boost::shared_ptr<dogen::yarn::meta_model::module>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::meta_model::concept>& lhs,
const boost::shared_ptr<dogen::yarn::meta_model::concept>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::meta_model::builtin>& lhs,
const boost::shared_ptr<dogen::yarn::meta_model::builtin>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::meta_model::enumeration>& lhs,
const boost::shared_ptr<dogen::yarn::meta_model::enumeration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::meta_model::primitive>& lhs,
const boost::shared_ptr<dogen::yarn::meta_model::primitive>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::meta_model::object>& lhs,
const boost::shared_ptr<dogen::yarn::meta_model::object>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::meta_model::exception>& lhs,
const boost::shared_ptr<dogen::yarn::meta_model::exception>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::meta_model::visitor>& lhs,
const boost::shared_ptr<dogen::yarn::meta_model::visitor>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::meta_model::element>& lhs,
const boost::shared_ptr<dogen::yarn::meta_model::element>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

endomodel::endomodel()
    : origin_type_(static_cast<dogen::yarn::meta_model::origin_types>(0)),
      has_generatable_types_(static_cast<bool>(0)),
      input_language_(static_cast<dogen::yarn::meta_model::languages>(0)) { }

endomodel::endomodel(endomodel&& rhs)
    : name_(std::move(rhs.name_)),
      meta_name_(std::move(rhs.meta_name_)),
      origin_type_(std::move(rhs.origin_type_)),
      references_(std::move(rhs.references_)),
      leaves_(std::move(rhs.leaves_)),
      modules_(std::move(rhs.modules_)),
      concepts_(std::move(rhs.concepts_)),
      builtins_(std::move(rhs.builtins_)),
      enumerations_(std::move(rhs.enumerations_)),
      primitives_(std::move(rhs.primitives_)),
      objects_(std::move(rhs.objects_)),
      exceptions_(std::move(rhs.exceptions_)),
      visitors_(std::move(rhs.visitors_)),
      injected_elements_(std::move(rhs.injected_elements_)),
      has_generatable_types_(std::move(rhs.has_generatable_types_)),
      root_module_(std::move(rhs.root_module_)),
      input_language_(std::move(rhs.input_language_)),
      output_languages_(std::move(rhs.output_languages_)),
      orm_properties_(std::move(rhs.orm_properties_)),
      facet_properties_(std::move(rhs.facet_properties_)) { }

endomodel::endomodel(
    const dogen::yarn::meta_model::name& name,
    const dogen::yarn::meta_model::name& meta_name,
    const dogen::yarn::meta_model::origin_types origin_type,
    const std::unordered_map<dogen::yarn::meta_model::name, dogen::yarn::meta_model::origin_types>& references,
    const std::unordered_set<dogen::yarn::meta_model::name>& leaves,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::module> >& modules,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::concept> >& concepts,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::builtin> >& builtins,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::enumeration> >& enumerations,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::primitive> >& primitives,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::object> >& objects,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::exception> >& exceptions,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::visitor> >& visitors,
    const std::list<boost::shared_ptr<dogen::yarn::meta_model::element> >& injected_elements,
    const bool has_generatable_types,
    const boost::shared_ptr<dogen::yarn::meta_model::module>& root_module,
    const dogen::yarn::meta_model::languages input_language,
    const std::list<dogen::yarn::meta_model::languages>& output_languages,
    const boost::optional<dogen::yarn::meta_model::orm_model_properties>& orm_properties,
    const std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties>& facet_properties)
    : name_(name),
      meta_name_(meta_name),
      origin_type_(origin_type),
      references_(references),
      leaves_(leaves),
      modules_(modules),
      concepts_(concepts),
      builtins_(builtins),
      enumerations_(enumerations),
      primitives_(primitives),
      objects_(objects),
      exceptions_(exceptions),
      visitors_(visitors),
      injected_elements_(injected_elements),
      has_generatable_types_(has_generatable_types),
      root_module_(root_module),
      input_language_(input_language),
      output_languages_(output_languages),
      orm_properties_(orm_properties),
      facet_properties_(facet_properties) { }

void endomodel::swap(endomodel& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(meta_name_, other.meta_name_);
    swap(origin_type_, other.origin_type_);
    swap(references_, other.references_);
    swap(leaves_, other.leaves_);
    swap(modules_, other.modules_);
    swap(concepts_, other.concepts_);
    swap(builtins_, other.builtins_);
    swap(enumerations_, other.enumerations_);
    swap(primitives_, other.primitives_);
    swap(objects_, other.objects_);
    swap(exceptions_, other.exceptions_);
    swap(visitors_, other.visitors_);
    swap(injected_elements_, other.injected_elements_);
    swap(has_generatable_types_, other.has_generatable_types_);
    swap(root_module_, other.root_module_);
    swap(input_language_, other.input_language_);
    swap(output_languages_, other.output_languages_);
    swap(orm_properties_, other.orm_properties_);
    swap(facet_properties_, other.facet_properties_);
}

bool endomodel::operator==(const endomodel& rhs) const {
    return name_ == rhs.name_ &&
        meta_name_ == rhs.meta_name_ &&
        origin_type_ == rhs.origin_type_ &&
        references_ == rhs.references_ &&
        leaves_ == rhs.leaves_ &&
        modules_ == rhs.modules_ &&
        concepts_ == rhs.concepts_ &&
        builtins_ == rhs.builtins_ &&
        enumerations_ == rhs.enumerations_ &&
        primitives_ == rhs.primitives_ &&
        objects_ == rhs.objects_ &&
        exceptions_ == rhs.exceptions_ &&
        visitors_ == rhs.visitors_ &&
        injected_elements_ == rhs.injected_elements_ &&
        has_generatable_types_ == rhs.has_generatable_types_ &&
        root_module_ == rhs.root_module_ &&
        input_language_ == rhs.input_language_ &&
        output_languages_ == rhs.output_languages_ &&
        orm_properties_ == rhs.orm_properties_ &&
        facet_properties_ == rhs.facet_properties_;
}

endomodel& endomodel::operator=(endomodel other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::yarn::meta_model::name& endomodel::name() const {
    return name_;
}

dogen::yarn::meta_model::name& endomodel::name() {
    return name_;
}

void endomodel::name(const dogen::yarn::meta_model::name& v) {
    name_ = v;
}

void endomodel::name(const dogen::yarn::meta_model::name&& v) {
    name_ = std::move(v);
}

const dogen::yarn::meta_model::name& endomodel::meta_name() const {
    return meta_name_;
}

dogen::yarn::meta_model::name& endomodel::meta_name() {
    return meta_name_;
}

void endomodel::meta_name(const dogen::yarn::meta_model::name& v) {
    meta_name_ = v;
}

void endomodel::meta_name(const dogen::yarn::meta_model::name&& v) {
    meta_name_ = std::move(v);
}

dogen::yarn::meta_model::origin_types endomodel::origin_type() const {
    return origin_type_;
}

void endomodel::origin_type(const dogen::yarn::meta_model::origin_types v) {
    origin_type_ = v;
}

const std::unordered_map<dogen::yarn::meta_model::name, dogen::yarn::meta_model::origin_types>& endomodel::references() const {
    return references_;
}

std::unordered_map<dogen::yarn::meta_model::name, dogen::yarn::meta_model::origin_types>& endomodel::references() {
    return references_;
}

void endomodel::references(const std::unordered_map<dogen::yarn::meta_model::name, dogen::yarn::meta_model::origin_types>& v) {
    references_ = v;
}

void endomodel::references(const std::unordered_map<dogen::yarn::meta_model::name, dogen::yarn::meta_model::origin_types>&& v) {
    references_ = std::move(v);
}

const std::unordered_set<dogen::yarn::meta_model::name>& endomodel::leaves() const {
    return leaves_;
}

std::unordered_set<dogen::yarn::meta_model::name>& endomodel::leaves() {
    return leaves_;
}

void endomodel::leaves(const std::unordered_set<dogen::yarn::meta_model::name>& v) {
    leaves_ = v;
}

void endomodel::leaves(const std::unordered_set<dogen::yarn::meta_model::name>&& v) {
    leaves_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::module> >& endomodel::modules() const {
    return modules_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::module> >& endomodel::modules() {
    return modules_;
}

void endomodel::modules(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::module> >& v) {
    modules_ = v;
}

void endomodel::modules(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::module> >&& v) {
    modules_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::concept> >& endomodel::concepts() const {
    return concepts_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::concept> >& endomodel::concepts() {
    return concepts_;
}

void endomodel::concepts(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::concept> >& v) {
    concepts_ = v;
}

void endomodel::concepts(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::concept> >&& v) {
    concepts_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::builtin> >& endomodel::builtins() const {
    return builtins_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::builtin> >& endomodel::builtins() {
    return builtins_;
}

void endomodel::builtins(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::builtin> >& v) {
    builtins_ = v;
}

void endomodel::builtins(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::builtin> >&& v) {
    builtins_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::enumeration> >& endomodel::enumerations() const {
    return enumerations_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::enumeration> >& endomodel::enumerations() {
    return enumerations_;
}

void endomodel::enumerations(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::enumeration> >& v) {
    enumerations_ = v;
}

void endomodel::enumerations(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::enumeration> >&& v) {
    enumerations_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::primitive> >& endomodel::primitives() const {
    return primitives_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::primitive> >& endomodel::primitives() {
    return primitives_;
}

void endomodel::primitives(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::primitive> >& v) {
    primitives_ = v;
}

void endomodel::primitives(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::primitive> >&& v) {
    primitives_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::object> >& endomodel::objects() const {
    return objects_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::object> >& endomodel::objects() {
    return objects_;
}

void endomodel::objects(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::object> >& v) {
    objects_ = v;
}

void endomodel::objects(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::object> >&& v) {
    objects_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::exception> >& endomodel::exceptions() const {
    return exceptions_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::exception> >& endomodel::exceptions() {
    return exceptions_;
}

void endomodel::exceptions(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::exception> >& v) {
    exceptions_ = v;
}

void endomodel::exceptions(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::exception> >&& v) {
    exceptions_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::visitor> >& endomodel::visitors() const {
    return visitors_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::visitor> >& endomodel::visitors() {
    return visitors_;
}

void endomodel::visitors(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::visitor> >& v) {
    visitors_ = v;
}

void endomodel::visitors(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::meta_model::visitor> >&& v) {
    visitors_ = std::move(v);
}

const std::list<boost::shared_ptr<dogen::yarn::meta_model::element> >& endomodel::injected_elements() const {
    return injected_elements_;
}

std::list<boost::shared_ptr<dogen::yarn::meta_model::element> >& endomodel::injected_elements() {
    return injected_elements_;
}

void endomodel::injected_elements(const std::list<boost::shared_ptr<dogen::yarn::meta_model::element> >& v) {
    injected_elements_ = v;
}

void endomodel::injected_elements(const std::list<boost::shared_ptr<dogen::yarn::meta_model::element> >&& v) {
    injected_elements_ = std::move(v);
}

bool endomodel::has_generatable_types() const {
    return has_generatable_types_;
}

void endomodel::has_generatable_types(const bool v) {
    has_generatable_types_ = v;
}

const boost::shared_ptr<dogen::yarn::meta_model::module>& endomodel::root_module() const {
    return root_module_;
}

boost::shared_ptr<dogen::yarn::meta_model::module>& endomodel::root_module() {
    return root_module_;
}

void endomodel::root_module(const boost::shared_ptr<dogen::yarn::meta_model::module>& v) {
    root_module_ = v;
}

void endomodel::root_module(const boost::shared_ptr<dogen::yarn::meta_model::module>&& v) {
    root_module_ = std::move(v);
}

dogen::yarn::meta_model::languages endomodel::input_language() const {
    return input_language_;
}

void endomodel::input_language(const dogen::yarn::meta_model::languages v) {
    input_language_ = v;
}

const std::list<dogen::yarn::meta_model::languages>& endomodel::output_languages() const {
    return output_languages_;
}

std::list<dogen::yarn::meta_model::languages>& endomodel::output_languages() {
    return output_languages_;
}

void endomodel::output_languages(const std::list<dogen::yarn::meta_model::languages>& v) {
    output_languages_ = v;
}

void endomodel::output_languages(const std::list<dogen::yarn::meta_model::languages>&& v) {
    output_languages_ = std::move(v);
}

const boost::optional<dogen::yarn::meta_model::orm_model_properties>& endomodel::orm_properties() const {
    return orm_properties_;
}

boost::optional<dogen::yarn::meta_model::orm_model_properties>& endomodel::orm_properties() {
    return orm_properties_;
}

void endomodel::orm_properties(const boost::optional<dogen::yarn::meta_model::orm_model_properties>& v) {
    orm_properties_ = v;
}

void endomodel::orm_properties(const boost::optional<dogen::yarn::meta_model::orm_model_properties>&& v) {
    orm_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties>& endomodel::facet_properties() const {
    return facet_properties_;
}

std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties>& endomodel::facet_properties() {
    return facet_properties_;
}

void endomodel::facet_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties>& v) {
    facet_properties_ = v;
}

void endomodel::facet_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties>&& v) {
    facet_properties_ = std::move(v);
}

} } }

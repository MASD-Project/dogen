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
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::element>& lhs,
const boost::shared_ptr<dogen::yarn::element>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace yarn {

intermediate_model::intermediate_model()
    : origin_type_(static_cast<dogen::yarn::origin_types>(0)),
      has_generatable_types_(static_cast<bool>(0)),
      input_language_(static_cast<dogen::yarn::languages>(0)) { }

intermediate_model::intermediate_model(intermediate_model&& rhs)
    : name_(std::move(rhs.name_)),
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
      scribble_groups_(std::move(rhs.scribble_groups_)),
      orm_configuration_(std::move(rhs.orm_configuration_)) { }

intermediate_model::intermediate_model(
    const dogen::yarn::name& name,
    const dogen::yarn::origin_types origin_type,
    const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& references,
    const std::unordered_set<dogen::yarn::name>& leaves,
    const std::unordered_map<std::string, dogen::yarn::module>& modules,
    const std::unordered_map<std::string, dogen::yarn::concept>& concepts,
    const std::unordered_map<std::string, dogen::yarn::builtin>& builtins,
    const std::unordered_map<std::string, dogen::yarn::enumeration>& enumerations,
    const std::unordered_map<std::string, dogen::yarn::primitive>& primitives,
    const std::unordered_map<std::string, dogen::yarn::object>& objects,
    const std::unordered_map<std::string, dogen::yarn::exception>& exceptions,
    const std::unordered_map<std::string, dogen::yarn::visitor>& visitors,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> >& injected_elements,
    const bool has_generatable_types,
    const dogen::yarn::module& root_module,
    const dogen::yarn::languages input_language,
    const std::list<dogen::yarn::languages>& output_languages,
    const std::unordered_map<std::string, dogen::annotations::scribble_group>& scribble_groups,
    const boost::optional<dogen::yarn::orm_model_configuration>& orm_configuration)
    : name_(name),
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
      scribble_groups_(scribble_groups),
      orm_configuration_(orm_configuration) { }

void intermediate_model::swap(intermediate_model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
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
    swap(scribble_groups_, other.scribble_groups_);
    swap(orm_configuration_, other.orm_configuration_);
}

bool intermediate_model::operator==(const intermediate_model& rhs) const {
    return name_ == rhs.name_ &&
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
        scribble_groups_ == rhs.scribble_groups_ &&
        orm_configuration_ == rhs.orm_configuration_;
}

intermediate_model& intermediate_model::operator=(intermediate_model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::yarn::name& intermediate_model::name() const {
    return name_;
}

dogen::yarn::name& intermediate_model::name() {
    return name_;
}

void intermediate_model::name(const dogen::yarn::name& v) {
    name_ = v;
}

void intermediate_model::name(const dogen::yarn::name&& v) {
    name_ = std::move(v);
}

dogen::yarn::origin_types intermediate_model::origin_type() const {
    return origin_type_;
}

void intermediate_model::origin_type(const dogen::yarn::origin_types v) {
    origin_type_ = v;
}

const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& intermediate_model::references() const {
    return references_;
}

std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& intermediate_model::references() {
    return references_;
}

void intermediate_model::references(const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& v) {
    references_ = v;
}

void intermediate_model::references(const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>&& v) {
    references_ = std::move(v);
}

const std::unordered_set<dogen::yarn::name>& intermediate_model::leaves() const {
    return leaves_;
}

std::unordered_set<dogen::yarn::name>& intermediate_model::leaves() {
    return leaves_;
}

void intermediate_model::leaves(const std::unordered_set<dogen::yarn::name>& v) {
    leaves_ = v;
}

void intermediate_model::leaves(const std::unordered_set<dogen::yarn::name>&& v) {
    leaves_ = std::move(v);
}

const std::unordered_map<std::string, dogen::yarn::module>& intermediate_model::modules() const {
    return modules_;
}

std::unordered_map<std::string, dogen::yarn::module>& intermediate_model::modules() {
    return modules_;
}

void intermediate_model::modules(const std::unordered_map<std::string, dogen::yarn::module>& v) {
    modules_ = v;
}

void intermediate_model::modules(const std::unordered_map<std::string, dogen::yarn::module>&& v) {
    modules_ = std::move(v);
}

const std::unordered_map<std::string, dogen::yarn::concept>& intermediate_model::concepts() const {
    return concepts_;
}

std::unordered_map<std::string, dogen::yarn::concept>& intermediate_model::concepts() {
    return concepts_;
}

void intermediate_model::concepts(const std::unordered_map<std::string, dogen::yarn::concept>& v) {
    concepts_ = v;
}

void intermediate_model::concepts(const std::unordered_map<std::string, dogen::yarn::concept>&& v) {
    concepts_ = std::move(v);
}

const std::unordered_map<std::string, dogen::yarn::builtin>& intermediate_model::builtins() const {
    return builtins_;
}

std::unordered_map<std::string, dogen::yarn::builtin>& intermediate_model::builtins() {
    return builtins_;
}

void intermediate_model::builtins(const std::unordered_map<std::string, dogen::yarn::builtin>& v) {
    builtins_ = v;
}

void intermediate_model::builtins(const std::unordered_map<std::string, dogen::yarn::builtin>&& v) {
    builtins_ = std::move(v);
}

const std::unordered_map<std::string, dogen::yarn::enumeration>& intermediate_model::enumerations() const {
    return enumerations_;
}

std::unordered_map<std::string, dogen::yarn::enumeration>& intermediate_model::enumerations() {
    return enumerations_;
}

void intermediate_model::enumerations(const std::unordered_map<std::string, dogen::yarn::enumeration>& v) {
    enumerations_ = v;
}

void intermediate_model::enumerations(const std::unordered_map<std::string, dogen::yarn::enumeration>&& v) {
    enumerations_ = std::move(v);
}

const std::unordered_map<std::string, dogen::yarn::primitive>& intermediate_model::primitives() const {
    return primitives_;
}

std::unordered_map<std::string, dogen::yarn::primitive>& intermediate_model::primitives() {
    return primitives_;
}

void intermediate_model::primitives(const std::unordered_map<std::string, dogen::yarn::primitive>& v) {
    primitives_ = v;
}

void intermediate_model::primitives(const std::unordered_map<std::string, dogen::yarn::primitive>&& v) {
    primitives_ = std::move(v);
}

const std::unordered_map<std::string, dogen::yarn::object>& intermediate_model::objects() const {
    return objects_;
}

std::unordered_map<std::string, dogen::yarn::object>& intermediate_model::objects() {
    return objects_;
}

void intermediate_model::objects(const std::unordered_map<std::string, dogen::yarn::object>& v) {
    objects_ = v;
}

void intermediate_model::objects(const std::unordered_map<std::string, dogen::yarn::object>&& v) {
    objects_ = std::move(v);
}

const std::unordered_map<std::string, dogen::yarn::exception>& intermediate_model::exceptions() const {
    return exceptions_;
}

std::unordered_map<std::string, dogen::yarn::exception>& intermediate_model::exceptions() {
    return exceptions_;
}

void intermediate_model::exceptions(const std::unordered_map<std::string, dogen::yarn::exception>& v) {
    exceptions_ = v;
}

void intermediate_model::exceptions(const std::unordered_map<std::string, dogen::yarn::exception>&& v) {
    exceptions_ = std::move(v);
}

const std::unordered_map<std::string, dogen::yarn::visitor>& intermediate_model::visitors() const {
    return visitors_;
}

std::unordered_map<std::string, dogen::yarn::visitor>& intermediate_model::visitors() {
    return visitors_;
}

void intermediate_model::visitors(const std::unordered_map<std::string, dogen::yarn::visitor>& v) {
    visitors_ = v;
}

void intermediate_model::visitors(const std::unordered_map<std::string, dogen::yarn::visitor>&& v) {
    visitors_ = std::move(v);
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> >& intermediate_model::injected_elements() const {
    return injected_elements_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> >& intermediate_model::injected_elements() {
    return injected_elements_;
}

void intermediate_model::injected_elements(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> >& v) {
    injected_elements_ = v;
}

void intermediate_model::injected_elements(const std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> >&& v) {
    injected_elements_ = std::move(v);
}

bool intermediate_model::has_generatable_types() const {
    return has_generatable_types_;
}

void intermediate_model::has_generatable_types(const bool v) {
    has_generatable_types_ = v;
}

const dogen::yarn::module& intermediate_model::root_module() const {
    return root_module_;
}

dogen::yarn::module& intermediate_model::root_module() {
    return root_module_;
}

void intermediate_model::root_module(const dogen::yarn::module& v) {
    root_module_ = v;
}

void intermediate_model::root_module(const dogen::yarn::module&& v) {
    root_module_ = std::move(v);
}

dogen::yarn::languages intermediate_model::input_language() const {
    return input_language_;
}

void intermediate_model::input_language(const dogen::yarn::languages v) {
    input_language_ = v;
}

const std::list<dogen::yarn::languages>& intermediate_model::output_languages() const {
    return output_languages_;
}

std::list<dogen::yarn::languages>& intermediate_model::output_languages() {
    return output_languages_;
}

void intermediate_model::output_languages(const std::list<dogen::yarn::languages>& v) {
    output_languages_ = v;
}

void intermediate_model::output_languages(const std::list<dogen::yarn::languages>&& v) {
    output_languages_ = std::move(v);
}

const std::unordered_map<std::string, dogen::annotations::scribble_group>& intermediate_model::scribble_groups() const {
    return scribble_groups_;
}

std::unordered_map<std::string, dogen::annotations::scribble_group>& intermediate_model::scribble_groups() {
    return scribble_groups_;
}

void intermediate_model::scribble_groups(const std::unordered_map<std::string, dogen::annotations::scribble_group>& v) {
    scribble_groups_ = v;
}

void intermediate_model::scribble_groups(const std::unordered_map<std::string, dogen::annotations::scribble_group>&& v) {
    scribble_groups_ = std::move(v);
}

const boost::optional<dogen::yarn::orm_model_configuration>& intermediate_model::orm_configuration() const {
    return orm_configuration_;
}

boost::optional<dogen::yarn::orm_model_configuration>& intermediate_model::orm_configuration() {
    return orm_configuration_;
}

void intermediate_model::orm_configuration(const boost::optional<dogen::yarn::orm_model_configuration>& v) {
    orm_configuration_ = v;
}

void intermediate_model::orm_configuration(const boost::optional<dogen::yarn::orm_model_configuration>&& v) {
    orm_configuration_ = std::move(v);
}

} }

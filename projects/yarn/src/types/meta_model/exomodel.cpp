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
#include "dogen/yarn/types/meta_model/exomodel.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/types/meta_model/object_template.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::meta_model::module>& lhs,
const boost::shared_ptr<dogen::yarn::meta_model::module>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::meta_model::object_template>& lhs,
const boost::shared_ptr<dogen::yarn::meta_model::object_template>& rhs) {
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

namespace dogen {
namespace yarn {
namespace meta_model {

exomodel::exomodel(
    const dogen::yarn::meta_model::name& name,
    const dogen::yarn::meta_model::name& meta_name,
    const std::string& documentation,
    const std::vector<dogen::yarn::meta_model::well_known_stereotypes>& well_known_stereotypes,
    const std::vector<std::string>& stereotypes,
    const std::list<std::pair<std::string, std::string> >& tagged_values,
    const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > >& modules,
    const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> > >& object_templates,
    const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> > >& builtins,
    const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> > >& enumerations,
    const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> > >& primitives,
    const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> > >& objects,
    const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> > >& exceptions,
    const std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> >& root_module,
    const std::string& new_name,
    const std::list<dogen::yarn::meta_model::exoelement>& elements)
    : name_(name),
      meta_name_(meta_name),
      documentation_(documentation),
      well_known_stereotypes_(well_known_stereotypes),
      stereotypes_(stereotypes),
      tagged_values_(tagged_values),
      modules_(modules),
      object_templates_(object_templates),
      builtins_(builtins),
      enumerations_(enumerations),
      primitives_(primitives),
      objects_(objects),
      exceptions_(exceptions),
      root_module_(root_module),
      new_name_(new_name),
      elements_(elements) { }

void exomodel::swap(exomodel& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(meta_name_, other.meta_name_);
    swap(documentation_, other.documentation_);
    swap(well_known_stereotypes_, other.well_known_stereotypes_);
    swap(stereotypes_, other.stereotypes_);
    swap(tagged_values_, other.tagged_values_);
    swap(modules_, other.modules_);
    swap(object_templates_, other.object_templates_);
    swap(builtins_, other.builtins_);
    swap(enumerations_, other.enumerations_);
    swap(primitives_, other.primitives_);
    swap(objects_, other.objects_);
    swap(exceptions_, other.exceptions_);
    swap(root_module_, other.root_module_);
    swap(new_name_, other.new_name_);
    swap(elements_, other.elements_);
}

bool exomodel::operator==(const exomodel& rhs) const {
    return name_ == rhs.name_ &&
        meta_name_ == rhs.meta_name_ &&
        documentation_ == rhs.documentation_ &&
        well_known_stereotypes_ == rhs.well_known_stereotypes_ &&
        stereotypes_ == rhs.stereotypes_ &&
        tagged_values_ == rhs.tagged_values_ &&
        modules_ == rhs.modules_ &&
        object_templates_ == rhs.object_templates_ &&
        builtins_ == rhs.builtins_ &&
        enumerations_ == rhs.enumerations_ &&
        primitives_ == rhs.primitives_ &&
        objects_ == rhs.objects_ &&
        exceptions_ == rhs.exceptions_ &&
        root_module_ == rhs.root_module_ &&
        new_name_ == rhs.new_name_ &&
        elements_ == rhs.elements_;
}

exomodel& exomodel::operator=(exomodel other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::yarn::meta_model::name& exomodel::name() const {
    return name_;
}

dogen::yarn::meta_model::name& exomodel::name() {
    return name_;
}

void exomodel::name(const dogen::yarn::meta_model::name& v) {
    name_ = v;
}

void exomodel::name(const dogen::yarn::meta_model::name&& v) {
    name_ = std::move(v);
}

const dogen::yarn::meta_model::name& exomodel::meta_name() const {
    return meta_name_;
}

dogen::yarn::meta_model::name& exomodel::meta_name() {
    return meta_name_;
}

void exomodel::meta_name(const dogen::yarn::meta_model::name& v) {
    meta_name_ = v;
}

void exomodel::meta_name(const dogen::yarn::meta_model::name&& v) {
    meta_name_ = std::move(v);
}

const std::string& exomodel::documentation() const {
    return documentation_;
}

std::string& exomodel::documentation() {
    return documentation_;
}

void exomodel::documentation(const std::string& v) {
    documentation_ = v;
}

void exomodel::documentation(const std::string&& v) {
    documentation_ = std::move(v);
}

const std::vector<dogen::yarn::meta_model::well_known_stereotypes>& exomodel::well_known_stereotypes() const {
    return well_known_stereotypes_;
}

std::vector<dogen::yarn::meta_model::well_known_stereotypes>& exomodel::well_known_stereotypes() {
    return well_known_stereotypes_;
}

void exomodel::well_known_stereotypes(const std::vector<dogen::yarn::meta_model::well_known_stereotypes>& v) {
    well_known_stereotypes_ = v;
}

void exomodel::well_known_stereotypes(const std::vector<dogen::yarn::meta_model::well_known_stereotypes>&& v) {
    well_known_stereotypes_ = std::move(v);
}

const std::vector<std::string>& exomodel::stereotypes() const {
    return stereotypes_;
}

std::vector<std::string>& exomodel::stereotypes() {
    return stereotypes_;
}

void exomodel::stereotypes(const std::vector<std::string>& v) {
    stereotypes_ = v;
}

void exomodel::stereotypes(const std::vector<std::string>&& v) {
    stereotypes_ = std::move(v);
}

const std::list<std::pair<std::string, std::string> >& exomodel::tagged_values() const {
    return tagged_values_;
}

std::list<std::pair<std::string, std::string> >& exomodel::tagged_values() {
    return tagged_values_;
}

void exomodel::tagged_values(const std::list<std::pair<std::string, std::string> >& v) {
    tagged_values_ = v;
}

void exomodel::tagged_values(const std::list<std::pair<std::string, std::string> >&& v) {
    tagged_values_ = std::move(v);
}

const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > >& exomodel::modules() const {
    return modules_;
}

std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > >& exomodel::modules() {
    return modules_;
}

void exomodel::modules(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > >& v) {
    modules_ = v;
}

void exomodel::modules(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > >&& v) {
    modules_ = std::move(v);
}

const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> > >& exomodel::object_templates() const {
    return object_templates_;
}

std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> > >& exomodel::object_templates() {
    return object_templates_;
}

void exomodel::object_templates(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> > >& v) {
    object_templates_ = v;
}

void exomodel::object_templates(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> > >&& v) {
    object_templates_ = std::move(v);
}

const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> > >& exomodel::builtins() const {
    return builtins_;
}

std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> > >& exomodel::builtins() {
    return builtins_;
}

void exomodel::builtins(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> > >& v) {
    builtins_ = v;
}

void exomodel::builtins(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> > >&& v) {
    builtins_ = std::move(v);
}

const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> > >& exomodel::enumerations() const {
    return enumerations_;
}

std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> > >& exomodel::enumerations() {
    return enumerations_;
}

void exomodel::enumerations(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> > >& v) {
    enumerations_ = v;
}

void exomodel::enumerations(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> > >&& v) {
    enumerations_ = std::move(v);
}

const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> > >& exomodel::primitives() const {
    return primitives_;
}

std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> > >& exomodel::primitives() {
    return primitives_;
}

void exomodel::primitives(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> > >& v) {
    primitives_ = v;
}

void exomodel::primitives(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> > >&& v) {
    primitives_ = std::move(v);
}

const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> > >& exomodel::objects() const {
    return objects_;
}

std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> > >& exomodel::objects() {
    return objects_;
}

void exomodel::objects(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> > >& v) {
    objects_ = v;
}

void exomodel::objects(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> > >&& v) {
    objects_ = std::move(v);
}

const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> > >& exomodel::exceptions() const {
    return exceptions_;
}

std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> > >& exomodel::exceptions() {
    return exceptions_;
}

void exomodel::exceptions(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> > >& v) {
    exceptions_ = v;
}

void exomodel::exceptions(const std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> > >&& v) {
    exceptions_ = std::move(v);
}

const std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> >& exomodel::root_module() const {
    return root_module_;
}

std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> >& exomodel::root_module() {
    return root_module_;
}

void exomodel::root_module(const std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> >& v) {
    root_module_ = v;
}

void exomodel::root_module(const std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> >&& v) {
    root_module_ = std::move(v);
}

const std::string& exomodel::new_name() const {
    return new_name_;
}

std::string& exomodel::new_name() {
    return new_name_;
}

void exomodel::new_name(const std::string& v) {
    new_name_ = v;
}

void exomodel::new_name(const std::string&& v) {
    new_name_ = std::move(v);
}

const std::list<dogen::yarn::meta_model::exoelement>& exomodel::elements() const {
    return elements_;
}

std::list<dogen::yarn::meta_model::exoelement>& exomodel::elements() {
    return elements_;
}

void exomodel::elements(const std::list<dogen::yarn::meta_model::exoelement>& v) {
    elements_ = v;
}

void exomodel::elements(const std::list<dogen::yarn::meta_model::exoelement>&& v) {
    elements_ = std::move(v);
}

} } }

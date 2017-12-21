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
#include <ostream>
#include <boost/io/ios_state.hpp>
#include "dogen.modeling/io/meta_model/name_io.hpp"
#include "dogen.modeling/io/meta_model/element_io.hpp"
#include "dogen.modeling/io/meta_model/enumerator_io.hpp"
#include "dogen.modeling/types/meta_model/enumeration.hpp"
#include "dogen.modeling/types/meta_model/element_visitor.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<dogen::modeling::meta_model::enumerator>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace modeling {
namespace meta_model {

enumeration::enumeration()
    : use_implementation_defined_underlying_element_(static_cast<bool>(0)),
      use_implementation_defined_enumerator_values_(static_cast<bool>(0)),
      add_invalid_enumerator_(static_cast<bool>(0)) { }

enumeration::enumeration(
    const dogen::modeling::meta_model::name& name,
    const std::string& documentation,
    const dogen::annotations::annotation& annotation,
    const dogen::modeling::meta_model::origin_types origin_type,
    const boost::optional<dogen::modeling::meta_model::name>& contained_by,
    const bool in_global_module,
    const std::list<dogen::modeling::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::modeling::meta_model::name& meta_name,
    const bool is_element_extension,
    const dogen::formatting::decoration_properties& decoration_properties,
    const std::unordered_map<std::string, dogen::modeling::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::modeling::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const dogen::modeling::meta_model::name& underlying_element,
    const std::vector<dogen::modeling::meta_model::enumerator>& enumerators,
    const bool use_implementation_defined_underlying_element,
    const bool use_implementation_defined_enumerator_values,
    const bool add_invalid_enumerator)
    : dogen::modeling::meta_model::element(
      name,
      documentation,
      annotation,
      origin_type,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      is_element_extension,
      decoration_properties,
      artefact_properties,
      archetype_location_properties),
      underlying_element_(underlying_element),
      enumerators_(enumerators),
      use_implementation_defined_underlying_element_(use_implementation_defined_underlying_element),
      use_implementation_defined_enumerator_values_(use_implementation_defined_enumerator_values),
      add_invalid_enumerator_(add_invalid_enumerator) { }

void enumeration::accept(const element_visitor& v) const {
    v.visit(*this);
}

void enumeration::accept(element_visitor& v) const {
    v.visit(*this);
    }

void enumeration::accept(const element_visitor& v) {
    v.visit(*this);
}

void enumeration::accept(element_visitor& v) {
    v.visit(*this);
}

void enumeration::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::modeling::meta_model::enumeration\"" << ", "
      << "\"__parent_0__\": ";
    dogen::modeling::meta_model::element::to_stream(s);
    s << ", "
      << "\"underlying_element\": " << underlying_element_ << ", "
      << "\"enumerators\": " << enumerators_ << ", "
      << "\"use_implementation_defined_underlying_element\": " << use_implementation_defined_underlying_element_ << ", "
      << "\"use_implementation_defined_enumerator_values\": " << use_implementation_defined_enumerator_values_ << ", "
      << "\"add_invalid_enumerator\": " << add_invalid_enumerator_
      << " }";
}

void enumeration::swap(enumeration& other) noexcept {
    dogen::modeling::meta_model::element::swap(other);

    using std::swap;
    swap(underlying_element_, other.underlying_element_);
    swap(enumerators_, other.enumerators_);
    swap(use_implementation_defined_underlying_element_, other.use_implementation_defined_underlying_element_);
    swap(use_implementation_defined_enumerator_values_, other.use_implementation_defined_enumerator_values_);
    swap(add_invalid_enumerator_, other.add_invalid_enumerator_);
}

bool enumeration::equals(const dogen::modeling::meta_model::element& other) const {
    const enumeration* const p(dynamic_cast<const enumeration* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool enumeration::operator==(const enumeration& rhs) const {
    return dogen::modeling::meta_model::element::compare(rhs) &&
        underlying_element_ == rhs.underlying_element_ &&
        enumerators_ == rhs.enumerators_ &&
        use_implementation_defined_underlying_element_ == rhs.use_implementation_defined_underlying_element_ &&
        use_implementation_defined_enumerator_values_ == rhs.use_implementation_defined_enumerator_values_ &&
        add_invalid_enumerator_ == rhs.add_invalid_enumerator_;
}

enumeration& enumeration::operator=(enumeration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::modeling::meta_model::name& enumeration::underlying_element() const {
    return underlying_element_;
}

dogen::modeling::meta_model::name& enumeration::underlying_element() {
    return underlying_element_;
}

void enumeration::underlying_element(const dogen::modeling::meta_model::name& v) {
    underlying_element_ = v;
}

void enumeration::underlying_element(const dogen::modeling::meta_model::name&& v) {
    underlying_element_ = std::move(v);
}

const std::vector<dogen::modeling::meta_model::enumerator>& enumeration::enumerators() const {
    return enumerators_;
}

std::vector<dogen::modeling::meta_model::enumerator>& enumeration::enumerators() {
    return enumerators_;
}

void enumeration::enumerators(const std::vector<dogen::modeling::meta_model::enumerator>& v) {
    enumerators_ = v;
}

void enumeration::enumerators(const std::vector<dogen::modeling::meta_model::enumerator>&& v) {
    enumerators_ = std::move(v);
}

bool enumeration::use_implementation_defined_underlying_element() const {
    return use_implementation_defined_underlying_element_;
}

void enumeration::use_implementation_defined_underlying_element(const bool v) {
    use_implementation_defined_underlying_element_ = v;
}

bool enumeration::use_implementation_defined_enumerator_values() const {
    return use_implementation_defined_enumerator_values_;
}

void enumeration::use_implementation_defined_enumerator_values(const bool v) {
    use_implementation_defined_enumerator_values_ = v;
}

bool enumeration::add_invalid_enumerator() const {
    return add_invalid_enumerator_;
}

void enumeration::add_invalid_enumerator(const bool v) {
    add_invalid_enumerator_ = v;
}

} } }

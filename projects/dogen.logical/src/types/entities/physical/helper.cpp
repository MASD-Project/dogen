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
#include <boost/algorithm/string.hpp>
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/physical/helper.hpp"
#include "dogen.identification/io/entities/technical_space_io.hpp"
#include "dogen.logical/io/entities/physical/text_templating_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace dogen::logical::entities::physical {

helper::helper()
    : major_technical_space_(static_cast<dogen::identification::entities::technical_space>(0)) { }

helper::helper(
    const dogen::identification::entities::logical_name& name,
    const std::string& documentation,
    const dogen::identification::entities::codec_provenance& provenance,
    const dogen::identification::entities::logical_id& contained_by,
    const bool in_global_module,
    const dogen::logical::entities::stereotypes& stereotypes,
    const dogen::identification::entities::logical_meta_name& meta_name,
    const dogen::identification::entities::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::list<dogen::identification::entities::label>& labels,
    const dogen::logical::entities::generability_status generability_status,
    const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const std::list<dogen::logical::entities::helper_properties>& helper_properties,
    const std::string& id,
    const dogen::identification::entities::technical_space major_technical_space,
    const std::string& part_id,
    const std::string& backend_name,
    const std::string& facet_name,
    const std::string& family,
    const std::list<std::string>& owning_formatters,
    const std::list<std::string>& owning_facets,
    const std::string& helper_name,
    const dogen::logical::entities::physical::text_templating& text_templating)
    : dogen::logical::entities::element(
      name,
      documentation,
      provenance,
      contained_by,
      in_global_module,
      stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      labels,
      generability_status,
      decoration,
      helper_properties),
      id_(id),
      major_technical_space_(major_technical_space),
      part_id_(part_id),
      backend_name_(backend_name),
      facet_name_(facet_name),
      family_(family),
      owning_formatters_(owning_formatters),
      owning_facets_(owning_facets),
      helper_name_(helper_name),
      text_templating_(text_templating) { }

void helper::accept(const element_visitor& v) const {
    v.visit(*this);
}

void helper::accept(element_visitor& v) const {
    v.visit(*this);
    }

void helper::accept(const element_visitor& v) {
    v.visit(*this);
}

void helper::accept(element_visitor& v) {
    v.visit(*this);
}

void helper::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::physical::helper\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"id\": " << "\"" << tidy_up_string(id_) << "\"" << ", "
      << "\"major_technical_space\": " << major_technical_space_ << ", "
      << "\"part_id\": " << "\"" << tidy_up_string(part_id_) << "\"" << ", "
      << "\"backend_name\": " << "\"" << tidy_up_string(backend_name_) << "\"" << ", "
      << "\"facet_name\": " << "\"" << tidy_up_string(facet_name_) << "\"" << ", "
      << "\"family\": " << "\"" << tidy_up_string(family_) << "\"" << ", "
      << "\"owning_formatters\": " << owning_formatters_ << ", "
      << "\"owning_facets\": " << owning_facets_ << ", "
      << "\"helper_name\": " << "\"" << tidy_up_string(helper_name_) << "\"" << ", "
      << "\"text_templating\": " << text_templating_
      << " }";
}

void helper::swap(helper& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(id_, other.id_);
    swap(major_technical_space_, other.major_technical_space_);
    swap(part_id_, other.part_id_);
    swap(backend_name_, other.backend_name_);
    swap(facet_name_, other.facet_name_);
    swap(family_, other.family_);
    swap(owning_formatters_, other.owning_formatters_);
    swap(owning_facets_, other.owning_facets_);
    swap(helper_name_, other.helper_name_);
    swap(text_templating_, other.text_templating_);
}

bool helper::equals(const dogen::logical::entities::element& other) const {
    const helper* const p(dynamic_cast<const helper* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool helper::operator==(const helper& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        id_ == rhs.id_ &&
        major_technical_space_ == rhs.major_technical_space_ &&
        part_id_ == rhs.part_id_ &&
        backend_name_ == rhs.backend_name_ &&
        facet_name_ == rhs.facet_name_ &&
        family_ == rhs.family_ &&
        owning_formatters_ == rhs.owning_formatters_ &&
        owning_facets_ == rhs.owning_facets_ &&
        helper_name_ == rhs.helper_name_ &&
        text_templating_ == rhs.text_templating_;
}

helper& helper::operator=(helper other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& helper::id() const {
    return id_;
}

std::string& helper::id() {
    return id_;
}

void helper::id(const std::string& v) {
    id_ = v;
}

void helper::id(const std::string&& v) {
    id_ = std::move(v);
}

dogen::identification::entities::technical_space helper::major_technical_space() const {
    return major_technical_space_;
}

void helper::major_technical_space(const dogen::identification::entities::technical_space v) {
    major_technical_space_ = v;
}

const std::string& helper::part_id() const {
    return part_id_;
}

std::string& helper::part_id() {
    return part_id_;
}

void helper::part_id(const std::string& v) {
    part_id_ = v;
}

void helper::part_id(const std::string&& v) {
    part_id_ = std::move(v);
}

const std::string& helper::backend_name() const {
    return backend_name_;
}

std::string& helper::backend_name() {
    return backend_name_;
}

void helper::backend_name(const std::string& v) {
    backend_name_ = v;
}

void helper::backend_name(const std::string&& v) {
    backend_name_ = std::move(v);
}

const std::string& helper::facet_name() const {
    return facet_name_;
}

std::string& helper::facet_name() {
    return facet_name_;
}

void helper::facet_name(const std::string& v) {
    facet_name_ = v;
}

void helper::facet_name(const std::string&& v) {
    facet_name_ = std::move(v);
}

const std::string& helper::family() const {
    return family_;
}

std::string& helper::family() {
    return family_;
}

void helper::family(const std::string& v) {
    family_ = v;
}

void helper::family(const std::string&& v) {
    family_ = std::move(v);
}

const std::list<std::string>& helper::owning_formatters() const {
    return owning_formatters_;
}

std::list<std::string>& helper::owning_formatters() {
    return owning_formatters_;
}

void helper::owning_formatters(const std::list<std::string>& v) {
    owning_formatters_ = v;
}

void helper::owning_formatters(const std::list<std::string>&& v) {
    owning_formatters_ = std::move(v);
}

const std::list<std::string>& helper::owning_facets() const {
    return owning_facets_;
}

std::list<std::string>& helper::owning_facets() {
    return owning_facets_;
}

void helper::owning_facets(const std::list<std::string>& v) {
    owning_facets_ = v;
}

void helper::owning_facets(const std::list<std::string>&& v) {
    owning_facets_ = std::move(v);
}

const std::string& helper::helper_name() const {
    return helper_name_;
}

std::string& helper::helper_name() {
    return helper_name_;
}

void helper::helper_name(const std::string& v) {
    helper_name_ = v;
}

void helper::helper_name(const std::string&& v) {
    helper_name_ = std::move(v);
}

const dogen::logical::entities::physical::text_templating& helper::text_templating() const {
    return text_templating_;
}

dogen::logical::entities::physical::text_templating& helper::text_templating() {
    return text_templating_;
}

void helper::text_templating(const dogen::logical::entities::physical::text_templating& v) {
    text_templating_ = v;
}

void helper::text_templating(const dogen::logical::entities::physical::text_templating&& v) {
    text_templating_ = std::move(v);
}

}

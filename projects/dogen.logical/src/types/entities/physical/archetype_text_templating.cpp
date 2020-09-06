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
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.logical/types/entities/physical/archetype_text_templating.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::entities::configuration>& lhs,
const boost::shared_ptr<dogen::variability::entities::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::logical::entities::physical {

archetype_text_templating::archetype_text_templating(archetype_text_templating&& rhs)
    : configuration_(std::move(rhs.configuration_)),
      stitch_template_content_(std::move(rhs.stitch_template_content_)),
      wale_template_(std::move(rhs.wale_template_)),
      wale_template_content_(std::move(rhs.wale_template_content_)),
      rendered_stitch_template_(std::move(rhs.rendered_stitch_template_)),
      relations_(std::move(rhs.relations_)) { }

archetype_text_templating::archetype_text_templating(
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::string& stitch_template_content,
    const boost::optional<dogen::identification::entities::logical_name>& wale_template,
    const std::string& wale_template_content,
    const std::string& rendered_stitch_template,
    const dogen::logical::entities::physical::relations& relations)
    : configuration_(configuration),
      stitch_template_content_(stitch_template_content),
      wale_template_(wale_template),
      wale_template_content_(wale_template_content),
      rendered_stitch_template_(rendered_stitch_template),
      relations_(relations) { }

void archetype_text_templating::swap(archetype_text_templating& other) noexcept {
    using std::swap;
    swap(configuration_, other.configuration_);
    swap(stitch_template_content_, other.stitch_template_content_);
    swap(wale_template_, other.wale_template_);
    swap(wale_template_content_, other.wale_template_content_);
    swap(rendered_stitch_template_, other.rendered_stitch_template_);
    swap(relations_, other.relations_);
}

bool archetype_text_templating::operator==(const archetype_text_templating& rhs) const {
    return configuration_ == rhs.configuration_ &&
        stitch_template_content_ == rhs.stitch_template_content_ &&
        wale_template_ == rhs.wale_template_ &&
        wale_template_content_ == rhs.wale_template_content_ &&
        rendered_stitch_template_ == rhs.rendered_stitch_template_ &&
        relations_ == rhs.relations_;
}

archetype_text_templating& archetype_text_templating::operator=(archetype_text_templating other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<dogen::variability::entities::configuration>& archetype_text_templating::configuration() const {
    return configuration_;
}

boost::shared_ptr<dogen::variability::entities::configuration>& archetype_text_templating::configuration() {
    return configuration_;
}

void archetype_text_templating::configuration(const boost::shared_ptr<dogen::variability::entities::configuration>& v) {
    configuration_ = v;
}

void archetype_text_templating::configuration(const boost::shared_ptr<dogen::variability::entities::configuration>&& v) {
    configuration_ = std::move(v);
}

const std::string& archetype_text_templating::stitch_template_content() const {
    return stitch_template_content_;
}

std::string& archetype_text_templating::stitch_template_content() {
    return stitch_template_content_;
}

void archetype_text_templating::stitch_template_content(const std::string& v) {
    stitch_template_content_ = v;
}

void archetype_text_templating::stitch_template_content(const std::string&& v) {
    stitch_template_content_ = std::move(v);
}

const boost::optional<dogen::identification::entities::logical_name>& archetype_text_templating::wale_template() const {
    return wale_template_;
}

boost::optional<dogen::identification::entities::logical_name>& archetype_text_templating::wale_template() {
    return wale_template_;
}

void archetype_text_templating::wale_template(const boost::optional<dogen::identification::entities::logical_name>& v) {
    wale_template_ = v;
}

void archetype_text_templating::wale_template(const boost::optional<dogen::identification::entities::logical_name>&& v) {
    wale_template_ = std::move(v);
}

const std::string& archetype_text_templating::wale_template_content() const {
    return wale_template_content_;
}

std::string& archetype_text_templating::wale_template_content() {
    return wale_template_content_;
}

void archetype_text_templating::wale_template_content(const std::string& v) {
    wale_template_content_ = v;
}

void archetype_text_templating::wale_template_content(const std::string&& v) {
    wale_template_content_ = std::move(v);
}

const std::string& archetype_text_templating::rendered_stitch_template() const {
    return rendered_stitch_template_;
}

std::string& archetype_text_templating::rendered_stitch_template() {
    return rendered_stitch_template_;
}

void archetype_text_templating::rendered_stitch_template(const std::string& v) {
    rendered_stitch_template_ = v;
}

void archetype_text_templating::rendered_stitch_template(const std::string&& v) {
    rendered_stitch_template_ = std::move(v);
}

const dogen::logical::entities::physical::relations& archetype_text_templating::relations() const {
    return relations_;
}

dogen::logical::entities::physical::relations& archetype_text_templating::relations() {
    return relations_;
}

void archetype_text_templating::relations(const dogen::logical::entities::physical::relations& v) {
    relations_ = v;
}

void archetype_text_templating::relations(const dogen::logical::entities::physical::relations&& v) {
    relations_ = std::move(v);
}

}

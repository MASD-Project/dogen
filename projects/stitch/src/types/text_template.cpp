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
#include "dogen/stitch/types/text_template.hpp"

namespace dogen {
namespace stitch {

text_template::text_template(text_template&& rhs)
    : template_path_(std::move(rhs.template_path_)),
      output_path_(std::move(rhs.output_path_)),
      scribble_group_(std::move(rhs.scribble_group_)),
      properties_(std::move(rhs.properties_)),
      lines_(std::move(rhs.lines_)) { }

text_template::text_template(
    const boost::filesystem::path& template_path,
    const boost::filesystem::path& output_path,
    const dogen::annotations::scribble_group& scribble_group,
    const dogen::stitch::properties& properties,
    const std::list<dogen::stitch::line>& lines)
    : template_path_(template_path),
      output_path_(output_path),
      scribble_group_(scribble_group),
      properties_(properties),
      lines_(lines) { }

void text_template::swap(text_template& other) noexcept {
    using std::swap;
    swap(template_path_, other.template_path_);
    swap(output_path_, other.output_path_);
    swap(scribble_group_, other.scribble_group_);
    swap(properties_, other.properties_);
    swap(lines_, other.lines_);
}

bool text_template::operator==(const text_template& rhs) const {
    return template_path_ == rhs.template_path_ &&
        output_path_ == rhs.output_path_ &&
        scribble_group_ == rhs.scribble_group_ &&
        properties_ == rhs.properties_ &&
        lines_ == rhs.lines_;
}

text_template& text_template::operator=(text_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& text_template::template_path() const {
    return template_path_;
}

boost::filesystem::path& text_template::template_path() {
    return template_path_;
}

void text_template::template_path(const boost::filesystem::path& v) {
    template_path_ = v;
}

void text_template::template_path(const boost::filesystem::path&& v) {
    template_path_ = std::move(v);
}

const boost::filesystem::path& text_template::output_path() const {
    return output_path_;
}

boost::filesystem::path& text_template::output_path() {
    return output_path_;
}

void text_template::output_path(const boost::filesystem::path& v) {
    output_path_ = v;
}

void text_template::output_path(const boost::filesystem::path&& v) {
    output_path_ = std::move(v);
}

const dogen::annotations::scribble_group& text_template::scribble_group() const {
    return scribble_group_;
}

dogen::annotations::scribble_group& text_template::scribble_group() {
    return scribble_group_;
}

void text_template::scribble_group(const dogen::annotations::scribble_group& v) {
    scribble_group_ = v;
}

void text_template::scribble_group(const dogen::annotations::scribble_group&& v) {
    scribble_group_ = std::move(v);
}

const dogen::stitch::properties& text_template::properties() const {
    return properties_;
}

dogen::stitch::properties& text_template::properties() {
    return properties_;
}

void text_template::properties(const dogen::stitch::properties& v) {
    properties_ = v;
}

void text_template::properties(const dogen::stitch::properties&& v) {
    properties_ = std::move(v);
}

const std::list<dogen::stitch::line>& text_template::lines() const {
    return lines_;
}

std::list<dogen::stitch::line>& text_template::lines() {
    return lines_;
}

void text_template::lines(const std::list<dogen::stitch::line>& v) {
    lines_ = v;
}

void text_template::lines(const std::list<dogen::stitch::line>&& v) {
    lines_ = std::move(v);
}

} }

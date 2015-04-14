/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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

text_template::text_template(
    const dogen::stitch::settings_bundle& settings,
    const dogen::dynamic::schema::object& extensions,
    const std::list<boost::variant<dogen::stitch::mixed_content_block, dogen::stitch::scriptlet_block> >& content)
    : settings_(settings),
      extensions_(extensions),
      content_(content) { }

void text_template::swap(text_template& other) noexcept {
    using std::swap;
    swap(settings_, other.settings_);
    swap(extensions_, other.extensions_);
    swap(content_, other.content_);
}

bool text_template::operator==(const text_template& rhs) const {
    return settings_ == rhs.settings_ &&
        extensions_ == rhs.extensions_ &&
        content_ == rhs.content_;
}

text_template& text_template::operator=(text_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::stitch::settings_bundle& text_template::settings() const {
    return settings_;
}

dogen::stitch::settings_bundle& text_template::settings() {
    return settings_;
}

void text_template::settings(const dogen::stitch::settings_bundle& v) {
    settings_ = v;
}

void text_template::settings(const dogen::stitch::settings_bundle&& v) {
    settings_ = std::move(v);
}

const dogen::dynamic::schema::object& text_template::extensions() const {
    return extensions_;
}

dogen::dynamic::schema::object& text_template::extensions() {
    return extensions_;
}

void text_template::extensions(const dogen::dynamic::schema::object& v) {
    extensions_ = v;
}

void text_template::extensions(const dogen::dynamic::schema::object&& v) {
    extensions_ = std::move(v);
}

const std::list<boost::variant<dogen::stitch::mixed_content_block, dogen::stitch::scriptlet_block> >& text_template::content() const {
    return content_;
}

std::list<boost::variant<dogen::stitch::mixed_content_block, dogen::stitch::scriptlet_block> >& text_template::content() {
    return content_;
}

void text_template::content(const std::list<boost::variant<dogen::stitch::mixed_content_block, dogen::stitch::scriptlet_block> >& v) {
    content_ = v;
}

void text_template::content(const std::list<boost::variant<dogen::stitch::mixed_content_block, dogen::stitch::scriptlet_block> >&& v) {
    content_ = std::move(v);
}

} }
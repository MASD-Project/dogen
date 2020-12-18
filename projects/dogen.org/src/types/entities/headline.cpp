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
#include "dogen.org/types/entities/headline.hpp"

namespace dogen::org::entities {

headline::headline()
    : level_(static_cast<unsigned int>(0)) { }

headline::headline(
    const std::list<dogen::org::entities::affiliated_keyword>& affiliated_keywords,
    const std::list<dogen::org::entities::drawer>& drawers,
    const dogen::org::entities::section& section,
    const std::list<dogen::org::entities::headline>& headlines,
    const unsigned int level,
    const dogen::org::entities::priority_cookie& priority,
    const std::string& title,
    const std::list<dogen::org::entities::tag>& tags,
    const dogen::org::entities::todo_keyword& todo_keyword)
    : affiliated_keywords_(affiliated_keywords),
      drawers_(drawers),
      section_(section),
      headlines_(headlines),
      level_(level),
      priority_(priority),
      title_(title),
      tags_(tags),
      todo_keyword_(todo_keyword) { }

void headline::swap(headline& other) noexcept {
    using std::swap;
    swap(affiliated_keywords_, other.affiliated_keywords_);
    swap(drawers_, other.drawers_);
    swap(section_, other.section_);
    swap(headlines_, other.headlines_);
    swap(level_, other.level_);
    swap(priority_, other.priority_);
    swap(title_, other.title_);
    swap(tags_, other.tags_);
    swap(todo_keyword_, other.todo_keyword_);
}

bool headline::operator==(const headline& rhs) const {
    return affiliated_keywords_ == rhs.affiliated_keywords_ &&
        drawers_ == rhs.drawers_ &&
        section_ == rhs.section_ &&
        headlines_ == rhs.headlines_ &&
        level_ == rhs.level_ &&
        priority_ == rhs.priority_ &&
        title_ == rhs.title_ &&
        tags_ == rhs.tags_ &&
        todo_keyword_ == rhs.todo_keyword_;
}

headline& headline::operator=(headline other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::org::entities::affiliated_keyword>& headline::affiliated_keywords() const {
    return affiliated_keywords_;
}

std::list<dogen::org::entities::affiliated_keyword>& headline::affiliated_keywords() {
    return affiliated_keywords_;
}

void headline::affiliated_keywords(const std::list<dogen::org::entities::affiliated_keyword>& v) {
    affiliated_keywords_ = v;
}

void headline::affiliated_keywords(const std::list<dogen::org::entities::affiliated_keyword>&& v) {
    affiliated_keywords_ = std::move(v);
}

const std::list<dogen::org::entities::drawer>& headline::drawers() const {
    return drawers_;
}

std::list<dogen::org::entities::drawer>& headline::drawers() {
    return drawers_;
}

void headline::drawers(const std::list<dogen::org::entities::drawer>& v) {
    drawers_ = v;
}

void headline::drawers(const std::list<dogen::org::entities::drawer>&& v) {
    drawers_ = std::move(v);
}

const dogen::org::entities::section& headline::section() const {
    return section_;
}

dogen::org::entities::section& headline::section() {
    return section_;
}

void headline::section(const dogen::org::entities::section& v) {
    section_ = v;
}

void headline::section(const dogen::org::entities::section&& v) {
    section_ = std::move(v);
}

const std::list<dogen::org::entities::headline>& headline::headlines() const {
    return headlines_;
}

std::list<dogen::org::entities::headline>& headline::headlines() {
    return headlines_;
}

void headline::headlines(const std::list<dogen::org::entities::headline>& v) {
    headlines_ = v;
}

void headline::headlines(const std::list<dogen::org::entities::headline>&& v) {
    headlines_ = std::move(v);
}

unsigned int headline::level() const {
    return level_;
}

void headline::level(const unsigned int v) {
    level_ = v;
}

const dogen::org::entities::priority_cookie& headline::priority() const {
    return priority_;
}

dogen::org::entities::priority_cookie& headline::priority() {
    return priority_;
}

void headline::priority(const dogen::org::entities::priority_cookie& v) {
    priority_ = v;
}

void headline::priority(const dogen::org::entities::priority_cookie&& v) {
    priority_ = std::move(v);
}

const std::string& headline::title() const {
    return title_;
}

std::string& headline::title() {
    return title_;
}

void headline::title(const std::string& v) {
    title_ = v;
}

void headline::title(const std::string&& v) {
    title_ = std::move(v);
}

const std::list<dogen::org::entities::tag>& headline::tags() const {
    return tags_;
}

std::list<dogen::org::entities::tag>& headline::tags() {
    return tags_;
}

void headline::tags(const std::list<dogen::org::entities::tag>& v) {
    tags_ = v;
}

void headline::tags(const std::list<dogen::org::entities::tag>&& v) {
    tags_ = std::move(v);
}

const dogen::org::entities::todo_keyword& headline::todo_keyword() const {
    return todo_keyword_;
}

dogen::org::entities::todo_keyword& headline::todo_keyword() {
    return todo_keyword_;
}

void headline::todo_keyword(const dogen::org::entities::todo_keyword& v) {
    todo_keyword_ = v;
}

void headline::todo_keyword(const dogen::org::entities::todo_keyword&& v) {
    todo_keyword_ = std::move(v);
}

}

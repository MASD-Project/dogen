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
#include "dogen/quilt.cpp/types/fabric/odb_target.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

odb_target::odb_target(
    const std::string& name,
    const std::string& comment,
    const std::string& output_directory,
    const std::string& pragmas_file,
    const std::string& types_file,
    const std::list<std::pair<std::string, std::string> >& move_parameters,
    const std::string& common_odb_options,
    const std::string& object_odb_options)
    : name_(name),
      comment_(comment),
      output_directory_(output_directory),
      pragmas_file_(pragmas_file),
      types_file_(types_file),
      move_parameters_(move_parameters),
      common_odb_options_(common_odb_options),
      object_odb_options_(object_odb_options) { }

void odb_target::swap(odb_target& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(comment_, other.comment_);
    swap(output_directory_, other.output_directory_);
    swap(pragmas_file_, other.pragmas_file_);
    swap(types_file_, other.types_file_);
    swap(move_parameters_, other.move_parameters_);
    swap(common_odb_options_, other.common_odb_options_);
    swap(object_odb_options_, other.object_odb_options_);
}

bool odb_target::operator==(const odb_target& rhs) const {
    return name_ == rhs.name_ &&
        comment_ == rhs.comment_ &&
        output_directory_ == rhs.output_directory_ &&
        pragmas_file_ == rhs.pragmas_file_ &&
        types_file_ == rhs.types_file_ &&
        move_parameters_ == rhs.move_parameters_ &&
        common_odb_options_ == rhs.common_odb_options_ &&
        object_odb_options_ == rhs.object_odb_options_;
}

odb_target& odb_target::operator=(odb_target other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& odb_target::name() const {
    return name_;
}

std::string& odb_target::name() {
    return name_;
}

void odb_target::name(const std::string& v) {
    name_ = v;
}

void odb_target::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& odb_target::comment() const {
    return comment_;
}

std::string& odb_target::comment() {
    return comment_;
}

void odb_target::comment(const std::string& v) {
    comment_ = v;
}

void odb_target::comment(const std::string&& v) {
    comment_ = std::move(v);
}

const std::string& odb_target::output_directory() const {
    return output_directory_;
}

std::string& odb_target::output_directory() {
    return output_directory_;
}

void odb_target::output_directory(const std::string& v) {
    output_directory_ = v;
}

void odb_target::output_directory(const std::string&& v) {
    output_directory_ = std::move(v);
}

const std::string& odb_target::pragmas_file() const {
    return pragmas_file_;
}

std::string& odb_target::pragmas_file() {
    return pragmas_file_;
}

void odb_target::pragmas_file(const std::string& v) {
    pragmas_file_ = v;
}

void odb_target::pragmas_file(const std::string&& v) {
    pragmas_file_ = std::move(v);
}

const std::string& odb_target::types_file() const {
    return types_file_;
}

std::string& odb_target::types_file() {
    return types_file_;
}

void odb_target::types_file(const std::string& v) {
    types_file_ = v;
}

void odb_target::types_file(const std::string&& v) {
    types_file_ = std::move(v);
}

const std::list<std::pair<std::string, std::string> >& odb_target::move_parameters() const {
    return move_parameters_;
}

std::list<std::pair<std::string, std::string> >& odb_target::move_parameters() {
    return move_parameters_;
}

void odb_target::move_parameters(const std::list<std::pair<std::string, std::string> >& v) {
    move_parameters_ = v;
}

void odb_target::move_parameters(const std::list<std::pair<std::string, std::string> >&& v) {
    move_parameters_ = std::move(v);
}

const std::string& odb_target::common_odb_options() const {
    return common_odb_options_;
}

std::string& odb_target::common_odb_options() {
    return common_odb_options_;
}

void odb_target::common_odb_options(const std::string& v) {
    common_odb_options_ = v;
}

void odb_target::common_odb_options(const std::string&& v) {
    common_odb_options_ = std::move(v);
}

const std::string& odb_target::object_odb_options() const {
    return object_odb_options_;
}

std::string& odb_target::object_odb_options() {
    return object_odb_options_;
}

void odb_target::object_odb_options(const std::string& v) {
    object_odb_options_ = v;
}

void odb_target::object_odb_options(const std::string&& v) {
    object_odb_options_ = std::move(v);
}

} } } }

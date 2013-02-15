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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/sml/io/nested_qname_io.hpp"
#include "dogen/sml/types/nested_qname_builder.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("nested_qualified_name_builder"));

}

namespace dogen {
namespace sml {

nested_qualified_name_builder::nested_qualified_name_builder(
    const std::unordered_set<std::string>& packages,
    const std::list<std::string>& external_package_path,
    const std::string& model_name)
    : packages_(packages), external_package_path_(external_package_path),
      model_name_(model_name), root_(new node), current_(root_) {

    BOOST_LOG_SEV(lg, debug) << "Initialised with settings:"
                             << " packages: " << packages
                             << " external_package_path: "
                             << external_package_path
                             << " model_name: " << model_name;

}

void nested_qualified_name_builder::add_name(const std::string& n) {
    BOOST_LOG_SEV(lg, debug) << "pushing back name: " << n;
    names_.push_back(n);
}

void nested_qualified_name_builder::add_primitive(const std::string& n) {
    BOOST_LOG_SEV(lg, debug) << "pushing back primitive :" << n;
    auto qn(current_->data());
    qn.type_name(n);
    current_->data(qn);
}

void nested_qualified_name_builder::finish_current_node() {
    BOOST_LOG_SEV(lg, debug) << "finishing current node. names: "
                             << names_;

    qname qn(current_->data());
    if (names_.empty())
        return;

    if (names_.size() == 1) {
        qn.type_name(names_.front());
        names_.clear();
        BOOST_LOG_SEV(lg, debug) << "type name: " << qn.type_name();
        current_->data(qn);
        return;
    }

    const auto i(packages_.find(names_.front()));
    if (i != packages_.end()) {
        qn.model_name(model_name_);
        BOOST_LOG_SEV(lg, debug) << "model name: " << model_name_;
    } else {
        BOOST_LOG_SEV(lg, debug) << "model name: " << names_.front();
        qn.model_name(names_.front());
        names_.pop_front();
    }

    qn.type_name(names_.back());
    BOOST_LOG_SEV(lg, debug) << "type name: " << qn.type_name();

    names_.pop_back();
    qn.package_path(names_);
    BOOST_LOG_SEV(lg, debug) << "package path: " << qn.package_path();

    names_.clear();
    current_->data(qn);
}

void nested_qualified_name_builder::start_children() {
    BOOST_LOG_SEV(lg, debug) << "starting children";

    finish_current_node();
    boost::shared_ptr<node> tmp(new node);
    tmp->parent(current_);
    auto c(current_->children());
    c.push_back(tmp);
    current_->children(c);
    current_ = tmp;
}

void nested_qualified_name_builder::next_child() {
    BOOST_LOG_SEV(lg, debug) << "next child";

    finish_current_node();
    current_ = current_->parent();
    boost::shared_ptr<node> tmp(new node);
    tmp->parent(current_);

    auto c(current_->children());
    c.push_back(tmp);
    current_->children(c);
    current_ = tmp;
}

void nested_qualified_name_builder::end_children() {
    BOOST_LOG_SEV(lg, debug) << "ending children";

    finish_current_node();
    current_ = current_->parent();
}

void nested_qualified_name_builder::
build_node(nested_qname& qn, boost::shared_ptr<node> node) {
    BOOST_LOG_SEV(lg, debug) << "bulding node: "
                             << node->data().model_name()
                             << " "
                             << node->data().type_name();

    qn.type(node->data());
    std::list<nested_qname> children;
    for (const auto c : node->children()) {
        nested_qname cqn;
        build_node(cqn, c);
        children.push_back(cqn);
    }
    qn.children(children);
}

nested_qname nested_qualified_name_builder::build() {
    BOOST_LOG_SEV(lg, debug) << "started build";

    finish_current_node();
    nested_qname r;
    build_node(r, root_);

    BOOST_LOG_SEV(lg, debug) << "finished build. Final name: " << r;

    return r;
}

} }

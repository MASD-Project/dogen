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
#include "dogen/tack/io/nested_name_io.hpp"
#include "dogen/tack/types/nested_name_builder.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("tack.nested_name_builder"));

}

namespace dogen {
namespace tack {

nested_name_builder::nested_name_builder(
    const std::unordered_set<std::string>& modules,
    const std::list<std::string>& external_module_path,
    const std::string& model_name)
    : modules_(modules), external_module_path_(external_module_path),
      model_name_(model_name), root_(new node) {

    current_ = root_; // try to fix valgrind warnings

    BOOST_LOG_SEV(lg, debug) << "Initialised with settings:"
                             << " modules: " << modules
                             << " external_module_path: "
                             << external_module_path
                             << " model_name: " << model_name;

}

void nested_name_builder::add_name(const std::string& s) {
    BOOST_LOG_SEV(lg, debug) << "pushing back name: " << s;
    names_.push_back(s);
}

void nested_name_builder::add_primitive(const std::string& s) {
    BOOST_LOG_SEV(lg, debug) << "pushing back primitive :" << s;
    auto n(current_->data());
    n.simple(s);
    current_->data(n);
}

void nested_name_builder::finish_current_node() {
    BOOST_LOG_SEV(lg, debug) << "finishing current node. names: "
                             << names_;

    name n(current_->data());
    if (names_.empty())
        return;

    if (names_.size() == 1) {
        n.simple(names_.front());
        names_.clear();
        BOOST_LOG_SEV(lg, debug) << "simple name: " << n.simple();
        current_->data(n);
        return;
    }

    const auto i(modules_.find(names_.front()));
    if (i != modules_.end()) {
        n.location().original_model_name(model_name_);
        BOOST_LOG_SEV(lg, debug) << "model name: " << model_name_;
    } else {
        BOOST_LOG_SEV(lg, debug) << "model name: " << names_.front();
        n.location().original_model_name(names_.front());
        names_.pop_front();
    }

    n.simple(names_.back());
    BOOST_LOG_SEV(lg, debug) << "simple name: " << n.simple();

    names_.pop_back();
    n.location().internal_module_path(names_);
    BOOST_LOG_SEV(lg, debug) << "internal module path: "
                             << n.location().internal_module_path();

    names_.clear();
    current_->data(n);
}

void nested_name_builder::start_children() {
    BOOST_LOG_SEV(lg, debug) << "starting children";

    finish_current_node();
    boost::shared_ptr<node> tmp(new node);
    tmp->parent(current_);
    auto c(current_->children());
    c.push_back(tmp);
    current_->children(c);
    current_ = tmp;
}

void nested_name_builder::next_child() {
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

void nested_name_builder::end_children() {
    BOOST_LOG_SEV(lg, debug) << "ending children";

    finish_current_node();
    current_ = current_->parent();
}

void nested_name_builder::
build_node(nested_name& n, boost::shared_ptr<node> node) {
    BOOST_LOG_SEV(lg, debug) << "bulding node: "
                             << node->data().location().original_model_name()
                             << " "
                             << node->data().simple();

    n.type(node->data());
    std::list<nested_name> children;
    for (const auto c : node->children()) {
        nested_name cn;
        build_node(cn, c);
        children.push_back(cn);
    }
    n.children(children);
}

nested_name nested_name_builder::build() {
    BOOST_LOG_SEV(lg, debug) << "started build";

    finish_current_node();
    nested_name r;
    build_node(r, root_);

    BOOST_LOG_SEV(lg, debug) << "finished build. Final name: " << r;

    return r;
}

} }

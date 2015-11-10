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
#include <boost/make_shared.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/io/location_io.hpp"
#include "dogen/yarn/io/nested_name_io.hpp"
#include "dogen/yarn/types/name_builder.hpp"
#include "dogen/yarn/types/nested_name_builder.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("yarn.nested_name_builder"));

}

namespace dogen {
namespace yarn {

nested_name_builder::nested_name_builder(
    const std::unordered_set<std::string>& top_level_modules,
    const location& model_location)
    : top_level_modules_(top_level_modules),
      model_location_(model_location),
      root_(new node) {

    current_ = root_;
    BOOST_LOG_SEV(lg, debug) << "Initialised with settings:";
    BOOST_LOG_SEV(lg, debug) << " modules: " << top_level_modules_;
    BOOST_LOG_SEV(lg, debug) << " location: " << model_location_;
}

void nested_name_builder::add_name(const std::string& s) {
    BOOST_LOG_SEV(lg, debug) << "pushing back name: " << s;
    names_.push_back(s);
}

void nested_name_builder::add_primitive(const std::string& s) {
    BOOST_LOG_SEV(lg, debug) << "pushing back primitive :" << s;

    name_builder b;
    b.compute_qualifed_name(false);
    b.simple_name(s);
    current_->data(b.build());
}

void nested_name_builder::finish_current_node() {
    BOOST_LOG_SEV(lg, debug) << "finishing current node. names: " << names_;

    if (names_.empty())
        return;

    /*
     * Setup the name builder. We must not yet compute the qualified
     * name as we do not know if we have a fully formed name.
     */
    name_builder b;
    b.compute_qualifed_name(false);

    /*
     * If we have a single name, we are either referencing a type
     * defined in the global namespace (possibly in a different
     * model), or a type defined at the top-level in this model. As we
     * cannot tell the difference, we must fill in just the simple
     * name and let the resolver handle it properly later on.
     */
    const auto front(names_.front());
    if (names_.size() == 1) {
        b.simple_name(front);
        current_->data(b.build());
        names_.clear();
        BOOST_LOG_SEV(lg, debug) << "simple name: " << front;
        return;
    }

    /*
     * Check to see if the first name matches a top-level module in
     * this model. If it does, we must be referencing a type in a
     * module in the current model. If it does not, we are referencing
     * a type on a different model, and this is the foreign model
     * name.
     */
    const auto i(top_level_modules_.find(front));
    if (i != top_level_modules_.end()) {
        b.model_name(model_location_);
        BOOST_LOG_SEV(lg, debug) << "found module in current model: " << front;
    } else {
        BOOST_LOG_SEV(lg, debug) << "foreign model name: " << front;
        b.model_name(front);
        names_.pop_front(); // consume the foreign model name.
    }

    /*
     * The back of the list must now be the type's simple name.
     */
    const auto back(names_.back());
    b.simple_name(back);
    BOOST_LOG_SEV(lg, debug) << "simple name: " << back;
    names_.pop_back(); // consume the simple name

    if (!names_.empty()) {
        /*
         * Whatever is left, if anything, must be a path to non-top-level
         * modules defined within the model.
         */
        b.internal_module_path(names_);
        BOOST_LOG_SEV(lg, debug) << "internal module path: " << names_;
        names_.clear(); // consume internal modules
    }
    current_->data(b.build());
}

void nested_name_builder::start_children() {
    BOOST_LOG_SEV(lg, debug) << "starting children";

    finish_current_node();

    /*
     * Create a child node, link it up to its parent, link the parent
     * to the child and then make the child the current node.
     */
    auto child(boost::make_shared<node>());
    child->parent(current_);
    current_->children().push_back(child);
    current_ = child;
}

void nested_name_builder::next_child() {
    BOOST_LOG_SEV(lg, debug) << "next child";

    finish_current_node();

    /*
     * We are currently sitting on a child node. We first need to move
     * back up to the parent; then add a new child node, link it to
     * the parent and link the parent to the child; finally, make the
     * new child the current node.
     */
    current_ = current_->parent();
    auto child(boost::make_shared<node>());
    child->parent(current_);
    current_->children().push_back(child);
    current_ = child;
}

void nested_name_builder::end_children() {
    BOOST_LOG_SEV(lg, debug) << "ending children";

    finish_current_node();

    /*
     * All the children have been done, so move back up to the parent.
     */
    current_ = current_->parent();
}

void nested_name_builder::
build_node(nested_name& n, boost::shared_ptr<node> node) {
    BOOST_LOG_SEV(lg, debug) << "bulding node: " << node->data();

    n.type(node->data());
    std::list<nested_name> children;
    for (const auto c : node->children()) {
        nested_name cnn;
        build_node(cnn, c);
        children.push_back(cnn);
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

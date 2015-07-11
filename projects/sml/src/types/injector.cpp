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
#include <memory>
#include <functional>
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/types/type_visitor.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/sml/types/injection_error.hpp"
#include "dogen/sml/types/injector.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("sml.injector"));

const std::string empty;
const std::string merged("merged_");
const std::string xml_extension(".xml");
const std::string text_extension(".txt");
const std::string binary_extension(".bin");
const std::string dia_model("dia");
const std::string sml_model("sml");
const std::string visitor_name("visitor");
const std::string extract_name("extract");
const std::string uint_name("unsigned int");
const std::string id_name("id");
const std::string version_name("version");
const std::string visitor_argument_name("v");
const std::string extractor_argument_name("e");
const std::string visitor_doc("Visitor for ");
const std::string visit_operation_doc("Accept visits for type ");
const std::string global_module_doc("Module that represents the global scope.");
const std::string empty_identity(
    "Identity must have at least one attribute: ");
const std::string duplicate_qname(
    "Attempt to add object with a name that already exists in model: ");
const std::string zero_leaves("Type marked as visitable but has no leaves: ");
const std::string leaf_not_found("Could not find leaf object: ");
const std::string model_already_has_global_module(
    "Found a global module in model: ");

}

namespace dogen {
namespace sml {

template<typename AssociativeContainerOfContainable>
inline void add_containing_module_to_non_contained_entities(
    const qname& container_qn, AssociativeContainerOfContainable& c) {
    for (auto& pair : c) {
        auto& s(pair.second);
        if (!s.containing_module())
            s.containing_module(container_qn);
    }
}

class injector::context {
public:
    context(sml::model& m) : model_(m) { }

public:
    sml::model& model() { return model_; }

private:
    sml::model& model_;
};

bool injector::insert(const object& o) {
    const auto i(context_->model().objects().insert(
            std::make_pair(o.name(), o)));

    return i.second;
}

object injector::
create_visitor(const object& o, const std::list<qname>& leaves) const {
    qname qn;
    qn.simple_name(o.name().simple_name() + "_" + visitor_name);
    qn.model_name(o.name().model_name());
    qn.module_path(o.name().module_path());
    qn.external_module_path(o.name().external_module_path());

    BOOST_LOG_SEV(lg, debug) << "Creating visitor: "
                             << string_converter::convert(qn);

    object r;
    r.name(qn);
    r.is_final(true);
    r.generation_type(o.generation_type());
    r.origin_type(origin_types::system);
    r.object_type(object_types::visitor);
    r.documentation(visitor_doc + o.name().simple_name());

    for (const auto& l : leaves)
        r.relationships()[relationship_types::visits].push_back(l);

    BOOST_LOG_SEV(lg, debug) << "Created visitor: "
                             << string_converter::convert(qn);
    return r;
}

void injector::inject_visited_by(object& root, const std::list<qname>& leaves,
    const qname& visitor) const {

    root.relationships()[relationship_types::visited_by].push_back(visitor);

    for (const auto& l : leaves) {
        auto i(context_->model().objects().find(l));
        if (i == context_->model().objects().end()) {
            const auto n(string_converter::convert(l));
            BOOST_LOG_SEV(lg, error) << leaf_not_found << n;
            BOOST_THROW_EXCEPTION(injection_error(leaf_not_found + n));
        }

        auto& leaf(i->second);
        leaf.relationships()[relationship_types::visited_by].push_back(visitor);
    }
}

void injector::inject_visitors() {
    BOOST_LOG_SEV(lg, debug) << "Injecting visitors.";

    std::list<object> visitors;
    for (auto& pair : context_->model().objects()) {
        auto& o(pair.second);

        if (!o.is_visitable())
            continue;

        const auto i(o.relationships().find(relationship_types::leaves));
        const bool has_leaves(i != o.relationships().end() &&
            !i->second.empty());

        if (!has_leaves) {
            const auto n(string_converter::convert(o.name()));
            BOOST_LOG_SEV(lg, error) << zero_leaves << n;
            BOOST_THROW_EXCEPTION(injection_error(zero_leaves + n));
        }

        const auto v(create_visitor(o, i->second));
        visitors.push_back(v);
        inject_visited_by(o, i->second, v.name());
    }

    for (const auto v : visitors) {
        BOOST_LOG_SEV(lg, debug) << "Adding visitor: "
                                 << string_converter::convert(v.name());

        if (!insert(v)) {
            const auto n(string_converter::convert(v.name()));
            BOOST_LOG_SEV(lg, error) << duplicate_qname << n;
            BOOST_THROW_EXCEPTION(injection_error(duplicate_qname + n));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Done injecting visitors.";
}

void injector::inject_global_module() {
    qname qn;

    auto& model(context_->model());
    const auto i(model.modules().find(qn));
    if (i != model.modules().end()) {
        const auto n(string_converter::convert(model.name()));
        BOOST_LOG_SEV(lg, error) << model_already_has_global_module << n;
        BOOST_THROW_EXCEPTION(injection_error(
                model_already_has_global_module + n));
    }

    add_containing_module_to_non_contained_entities(qn, model.modules());
    add_containing_module_to_non_contained_entities(qn, model.concepts());
    add_containing_module_to_non_contained_entities(qn, model.primitives());
    add_containing_module_to_non_contained_entities(qn, model.enumerations());
    add_containing_module_to_non_contained_entities(qn, model.objects());

    module global_module;
    global_module.name(qn);
    global_module.generation_type(generation_types::no_generation);
    global_module.origin_type(origin_types::system);
    global_module.documentation(global_module_doc);
    model.modules().insert(std::make_pair(qn, global_module));
}

void injector::inject(model& m) {
    context_ = std::unique_ptr<context>(new context(m));
    inject_visitors();
    inject_global_module();
    context_ = std::unique_ptr<context>();
}

} }

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
const std::string key_extractor_name("key_extractor");
const std::string visitor_name("visitor");
const std::string versioned_name("versioned_key");
const std::string unversioned_name("unversioned_key");
const std::string extract_name("extract");
const std::string uint_name("unsigned int");
const std::string id_name("id");
const std::string version_name("version");
const std::string visitor_argument_name("v");
const std::string extractor_argument_name("e");
const std::string visitor_doc("Visitor for ");
const std::string key_extractor_doc("Extracts keys for type ");
const std::string visit_operation_doc("Accept visits for type ");
const std::string unversioned_key_doc("Unversioned key for ");
const std::string versioned_key_doc("Versioned key for ");
const std::string versioned_property_doc("Object instance's version.");
const std::string global_module_doc("Module that represents the global scope.");
const std::string empty_identity(
    "Identity must have at least one attribute: ");
const std::string duplicate_qname(
    "Attempt to add object with a name that already exists in model: ");
const std::string zero_leaves("Type marked as visitable but has no leaves: ");
const std::string unversioned_key_not_found(
    "Object is an entity but has no unversioned key: ");
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

object injector::create_key(const qname& qn, const generation_types gt,
    const std::list<property>& properties, const bool versioned) const {

    qname kqn;
    kqn.simple_name(qn.simple_name() + "_" +
        (versioned ? versioned_name : unversioned_name));
    kqn.model_name(qn.model_name());
    kqn.module_path(qn.module_path());
    kqn.external_module_path(qn.external_module_path());

    object r;
    r.name(kqn);
    r.generation_type(gt);
    r.origin_type(origin_types::system);

    const auto vk(object_types::versioned_key);
    const auto uvk(object_types::unversioned_key);
    r.object_type(versioned ? vk : uvk);

    const auto doc(versioned ? versioned_key_doc : unversioned_key_doc);
    r.documentation(doc + qn.simple_name());
    r.local_properties(properties);

    if (versioned)
        inject_version(r);

    BOOST_LOG_SEV(lg, debug) << "Created key: "
                             << sml::string_converter::convert(kqn);
    return r;
}

object injector::create_versioned_key(const qname& qn,
    const generation_types gt, const std::list<property>& properties) const {
    return create_key(qn, gt, properties, true);
}

object injector::create_unversioned_key(const qname& qn,
    const generation_types gt, const std::list<property>& properties) const {
    return create_key(qn, gt, properties, false);
}

object injector::create_key_extractor(const object& ke) const {
    object r;
    qname qn;
    qn.simple_name(ke.name().simple_name() + "_" + key_extractor_name);
    qn.model_name(ke.name().model_name());
    qn.module_path(ke.name().module_path());
    qn.external_module_path(ke.name().external_module_path());

    BOOST_LOG_SEV(lg, debug) << "Creating extractor: "
                             << sml::string_converter::convert(qn);

    r.name(qn);
    r.generation_type(ke.generation_type());
    r.origin_type(origin_types::system);
    r.object_type(object_types::key_extractor);
    r.documentation(visitor_doc + ke.name().simple_name());

    // FIXME: create these methods with correct names
    parameter p;
    p.name(extractor_argument_name);

    nested_qname nqn;
    const auto i(ke.relationships().find(relationship_types::unversioned_keys));
    if (i == ke.relationships().end() || i->second.size() != 1) {
        const auto n(sml::string_converter::convert(ke.name()));
        BOOST_LOG_SEV(lg, error) << unversioned_key_not_found << n;
        BOOST_THROW_EXCEPTION(injection_error(unversioned_key_not_found + n));
    }
    nqn.type(i->second.front());
    p.type(nqn);

    operation opuv;
    opuv.name(unversioned_name);
    opuv.parameters().push_back(p);
    opuv.documentation(key_extractor_doc + ke.name().simple_name());
    r.operations().push_back(opuv);

    BOOST_LOG_SEV(lg, debug) << "Created extractor: "
                             << sml::string_converter::convert(qn);
    return r;
}

void injector::inject_keys() {
    BOOST_LOG_SEV(lg, debug) << "Injecting keys.";

    std::list<object> objects;
    for (auto& pair : context_->model().objects()) {
        const auto qn(pair.first);
        auto& o(pair.second);

        BOOST_LOG_SEV(lg, debug) << "Visiting: "
                                 << sml::string_converter::convert(qn);
        if (o.object_type() != object_types::keyed_entity)
            continue;

        if (o.identity().empty()) {
            const auto n(sml::string_converter::convert(qn));
            BOOST_LOG_SEV(lg, error) << empty_identity << n;

            BOOST_THROW_EXCEPTION(injection_error(empty_identity + n));
        }
        BOOST_LOG_SEV(lg, debug) << "Attributes in identity operation: "
                                 << o.identity().size();

        const auto gt(o.generation_type());
        const auto uvk(create_unversioned_key(qn, gt, o.identity()));
        objects.push_back(uvk);
        o.relationships()[relationship_types::unversioned_keys].push_back(
            uvk.name());

        if (o.is_versioned()) {
            auto vk(create_versioned_key(qn, gt, o.identity()));
            o.relationships()[relationship_types::versioned_keys].push_back(
                vk.name());
            objects.push_back(vk);
        }

        // FIXME
        // objects.push_back(create_key_extractor(ke));
    }

    for (const auto& o : objects) {
        if (!insert(o)) {
            const auto n(sml::string_converter::convert(o.name()));
            BOOST_LOG_SEV(lg, error) << duplicate_qname << n;
            BOOST_THROW_EXCEPTION(injection_error(duplicate_qname + n));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Done injecting keys. Total: "
                             << objects.size();
}

void injector::inject_version(object& p) const {
    BOOST_LOG_SEV(lg, debug) << "Injecting version property to type: "
                             << sml::string_converter::convert(p.name());

    qname qn;
    qn.simple_name(uint_name);

    nested_qname nqn;
    nqn.type(qn);

    property v;
    v.name(version_name);
    v.type(nqn);
    v.documentation(versioned_property_doc);

    p.local_properties().push_back(v);
}

void injector::inject_version() {
    BOOST_LOG_SEV(lg, debug) << "Injecting version property on all types.";

    for (auto& pair : context_->model().objects()) {
        auto& o(pair.second);

        if (o.is_versioned())
            inject_version(o);
    }

    BOOST_LOG_SEV(lg, debug) << "Done injecting version property on all types.";
}

object injector::
create_visitor(const object& o, const std::list<qname>& leaves) const {
    object r;
    qname qn;
    qn.simple_name(o.name().simple_name() + "_" + visitor_name);
    qn.model_name(o.name().model_name());
    qn.module_path(o.name().module_path());
    qn.external_module_path(o.name().external_module_path());

    BOOST_LOG_SEV(lg, debug) << "Creating visitor: "
                             << sml::string_converter::convert(qn);

    r.name(qn);
    r.generation_type(o.generation_type());
    r.origin_type(origin_types::system);
    r.object_type(object_types::visitor);
    r.documentation(visitor_doc + o.name().simple_name());

    for (const auto& l : leaves)
        r.relationships()[relationship_types::visits].push_back(l);

    BOOST_LOG_SEV(lg, debug) << "Created visitor: "
                             << sml::string_converter::convert(qn);
    return r;
}

void injector::inject_visited_by(object& root, const std::list<qname>& leaves,
    const qname& visitor) const {

    root.relationships()[relationship_types::visited_by].push_back(visitor);

    for (const auto& l : leaves) {
        auto i(context_->model().objects().find(l));
        if (i == context_->model().objects().end()) {
            const auto n(sml::string_converter::convert(l));
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
            const auto n(sml::string_converter::convert(o.name()));
            BOOST_LOG_SEV(lg, error) << zero_leaves << n;
            BOOST_THROW_EXCEPTION(injection_error(zero_leaves + n));
        }

        const auto v(create_visitor(o, i->second));
        visitors.push_back(v);
        inject_visited_by(o, i->second, v.name());
    }

    for (const auto v : visitors) {
        BOOST_LOG_SEV(lg, debug) << "Adding visitor: "
                                 << sml::string_converter::convert(v.name());

        if (!insert(v)) {
            const auto n(sml::string_converter::convert(v.name()));
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
        const auto n(sml::string_converter::convert(model.name()));
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
    global_module.type(module_types::global);
    model.modules().insert(std::make_pair(qn, global_module));
}

void injector::inject(model& m) {
    context_ = std::unique_ptr<context>(new context(m));
    inject_version();
    inject_keys();
    inject_visitors();
    inject_global_module();
    context_ = std::unique_ptr<context>();
}

} }

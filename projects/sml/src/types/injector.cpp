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
#include <boost/make_shared.hpp>
#include "dogen/sml/types/value_object.hpp"
#include "dogen/sml/types/keyed_entity.hpp"
#include "dogen/sml/types/service.hpp"
#include "dogen/sml/types/factory.hpp"
#include "dogen/sml/types/repository.hpp"
#include "dogen/sml/types/entity.hpp"
#include "dogen/sml/types/keyed_entity.hpp"
#include "dogen/sml/types/type_visitor.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/io/qname_io.hpp"
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
const std::string versioned_name("versioned_key");
const std::string unversioned_name("unversioned_key");
const std::string uint_name("unsigned int");
const std::string id_name("id");
const std::string version_name("version");
const std::string visitor_doc("Visitor for ");
const std::string visit_operation_doc("Accept visits for type ");
const std::string unversioned_key_doc("Unversioned key for ");
const std::string versioned_key_doc("Versioned key for ");
const std::string versioned_property_doc("Object instance's version.");
const std::string empty_identity(
    "Identity must have at least one attribute: ");
const std::string duplicate_qname(
    "Attempt to add object with a name that already exists in model: ");
const std::string zero_leaves("Type marked as visitable but has no leaves: ");

class keyed_entity_visitor : public dogen::sml::type_visitor {
public:
    typedef std::function<void(dogen::sml::keyed_entity&)> function_type;

public:
    explicit keyed_entity_visitor(const function_type& fn) : fn_(fn) {}
    ~keyed_entity_visitor() noexcept { }

public:
    using type_visitor::visit;
    virtual void visit(dogen::sml::keyed_entity& ke) override { fn_(ke); }

private:
    function_type fn_;
};

}

namespace dogen {
namespace sml {

boost::shared_ptr<abstract_object> injector::create_key(const qname& qn,
    const generation_types gt, const std::list<property>& properties,
    const bool versioned) const {

    qname kqn;
    kqn.simple_name(qn.simple_name() + "_" +
        (versioned ? versioned_name : unversioned_name));
    kqn.model_name(qn.model_name());
    kqn.module_path(qn.module_path());
    kqn.external_module_path(qn.external_module_path());

    auto r(boost::make_shared<value_object>());
    r->name(kqn);
    r->generation_type(gt);
    const auto vk(value_object_types::versioned_key);
    const auto uvk(value_object_types::unversioned_key);
    r->type(versioned ? vk : uvk);

    const auto doc(versioned ? versioned_key_doc : unversioned_key_doc);
    r->documentation(doc + qn.simple_name());

    r->properties(properties);

    if (versioned)
        inject_version(*r);

    BOOST_LOG_SEV(lg, debug) << "Created key: " << kqn.simple_name();
    return r;
}

boost::shared_ptr<abstract_object> injector::
create_versioned_key(const qname& qn, const generation_types gt,
    const std::list<property>& properties) const {
    return create_key(qn, gt, properties, true);
}

boost::shared_ptr<abstract_object> injector::
create_unversioned_key(const qname& qn, const generation_types gt,
    const std::list<property>& properties) const {
    return create_key(qn, gt, properties, false);
}

void injector::inject_keys(model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Injecting keys.";

    std::list<boost::shared_ptr<abstract_object> > keys;
    const auto lambda([&](keyed_entity& ke) {
            if (ke.identity().empty()) {
                BOOST_LOG_SEV(lg, error) << empty_identity << ke.name();

                BOOST_THROW_EXCEPTION(
                    injection_error(empty_identity +
                        boost::lexical_cast<std::string>(ke.name())));
            }
            BOOST_LOG_SEV(lg, debug) << "Attributes in identity operation: "
                                     << ke.identity().size();

            const auto gt(ke.generation_type());
            const auto qn(ke.name());
            const auto uvk(create_unversioned_key(qn, gt, ke.identity()));
            keys.push_back(uvk);
            ke.unversioned_key(uvk->name());

            if (ke.is_versioned()) {
                auto vk(create_versioned_key(qn, gt, ke.identity()));
                ke.versioned_key(vk->name());
                keys.push_back(vk);
            }
        });

    keyed_entity_visitor v(lambda);
    for (auto& pair : m.objects()) {
        BOOST_LOG_SEV(lg, debug) << "Visiting: " << pair.first;
        pair.second->accept(v);
    }

    for (const auto& k : keys) {
        const auto i(m.objects().insert(std::make_pair(k->name(), k)));
        if (!i.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_qname << k->name();
            BOOST_THROW_EXCEPTION(injection_error(duplicate_qname +
                    boost::lexical_cast<std::string>(k->name())));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Done injecting keys. Total: " << keys.size();
}

void injector::inject_version(abstract_object& p) const {
    BOOST_LOG_SEV(lg, debug) << "Injecting version property to type: "
                             << p.name();

    qname qn;
    qn.simple_name(uint_name);

    nested_qname nqn;
    nqn.type(qn);

    property v;
    v.name(version_name);
    v.type(nqn);
    v.documentation(versioned_property_doc);

    p.properties().push_back(v);
}

void injector::inject_version(model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Injecting version property on all types.";

    for (auto& pair : m.objects()) {
        auto& ao(*pair.second);

        if (ao.is_versioned())
            inject_version(ao);
    }

    BOOST_LOG_SEV(lg, debug) << "Done injecting version property on all types.";
}

boost::shared_ptr<abstract_object>
injector::create_visitor(const abstract_object& ao) const {
    auto r(boost::make_shared<service>());
    qname qn;
    qn.simple_name(ao.name().simple_name() + "_" + visitor_name);
    qn.model_name(ao.name().model_name());
    qn.module_path(ao.name().module_path());
    qn.external_module_path(ao.name().external_module_path());

    BOOST_LOG_SEV(lg, debug) << "Creating visitor: " << qn.simple_name();

    r->name(qn);
    r->generation_type(ao.generation_type());
    r->type(service_types::visitor);
    r->documentation(visitor_doc + ao.name().simple_name());

    for (const auto& l : ao.leaves()) {
        operation op;
        op.name("visit");

        nested_qname nqn;
        nqn.type(l);
        op.arguments().push_back(nqn);
        op.documentation(visit_operation_doc + l.simple_name());
        r->operations().push_back(op);
    }

    BOOST_LOG_SEV(lg, debug) << "Created visitor: " << qn.simple_name();
    return r;
}

void injector::inject_visitors(model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Injecting visitors.";

    std::list<boost::shared_ptr<abstract_object> > visitors;
    for (auto& pair : m.objects()) {
        auto& ao(*pair.second);

        if (!ao.is_visitable())
            continue;

        if (ao.leaves().empty()) {
            BOOST_LOG_SEV(lg, error) << zero_leaves << ao.name();
            BOOST_THROW_EXCEPTION(injection_error(zero_leaves +
                    boost::lexical_cast<std::string>(ao.name())));
        }
        visitors.push_back(create_visitor(ao));
    }

    for (const auto v : visitors) {
        BOOST_LOG_SEV(lg, debug) << "Adding visitor: "
                                 << v->name().simple_name();

        const auto i(m.objects().insert(std::make_pair(v->name(), v)));

        if (!i.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_qname << v->name();
            BOOST_THROW_EXCEPTION(injection_error(duplicate_qname +
                    boost::lexical_cast<std::string>(v->name())));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Done injecting visitors.";
}

void injector::inject_key_extractors(model& ) const {
    
}

void injector::inject(model& m) const {
    inject_version(m);
    inject_keys(m);
    inject_visitors(m);
}

} }

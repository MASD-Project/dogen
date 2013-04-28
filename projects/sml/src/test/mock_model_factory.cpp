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
#include <sstream>
#include "dogen/sml/test/mock_model_factory.hpp"

namespace {

const std::string model_name_prefix("some_model_");
const std::string type_name_prefix("some_type_");
const std::string property_name_prefix("some_property_");

std::string type_name(unsigned int i) {
    std::ostringstream stream;
    stream << type_name_prefix << i;
    return stream.str();
}

std::string model_name(unsigned int i) {
    std::ostringstream stream;
    stream << model_name_prefix << i;
    return stream.str();
}

std::string property_name(unsigned int i) {
    std::ostringstream stream;
    stream << property_name_prefix << i;
    return stream.str();
}

dogen::sml::pod mock_pod(unsigned int i, std::string model_name) {
    dogen::sml::qname qn;
    qn.model_name(model_name);
    qn.type_name(type_name(i));
    qn.meta_type(dogen::sml::meta_types::pod);

    dogen::sml::pod r;
    r.name(qn);
    r.generation_type(dogen::sml::generation_types::full_generation);
    return r;
}

dogen::sml::pod mock_pod(unsigned int i) {
    return mock_pod(i, model_name(i));
}

}

namespace dogen {
namespace sml {
namespace test {

model mock_model_factory::build_single_pod_model(const unsigned int n) {
    pod p(mock_pod(n));
    model r;
    r.pods().insert(std::make_pair(p.name(), p));
    r.name(model_name(n));
    return r;
}

model mock_model_factory::build_multi_pod_model(const unsigned int n,
    const unsigned int pod_n) {

    model r;
    for (unsigned int i(0); i < pod_n; ++i) {
        const auto p(mock_pod(i, model_name(n)));
        r.pods().insert(std::make_pair(p.name(), p));
    }
    r.name(model_name(n));
    return r;
}

model mock_model_factory::pod_with_property() {
    using namespace dogen::sml;
    const std::string mn(model_name(0));
    pod pod0(mock_pod(0, mn));
    pod pod1(mock_pod(1, mn));

    property p;
    p.name(property_name(0));

    dogen::sml::qname qn;
    qn.type_name(pod1.name().type_name());
    qn.model_name(pod1.name().model_name());

    dogen::sml::nested_qname nqn;
    nqn.type(qn);
    p.type_name(nqn);
    pod0.properties().push_back(p);

    model r;
    r.pods().insert(std::make_pair(pod0.name(), pod0));
    r.pods().insert(std::make_pair(pod1.name(), pod1));
    r.name(mn);
    return r;
}

std::array<model, 2> mock_model_factory::
pod_with_property_type_in_different_model() {
    pod pod0(mock_pod(0));
    pod pod1(mock_pod(1));

    property p;
    p.name(property_name(0));

    dogen::sml::qname qn;
    qn.type_name(pod1.name().type_name());
    qn.model_name(pod1.name().model_name());

    dogen::sml::nested_qname nqn;
    nqn.type(qn);
    p.type_name(nqn);
    pod0.properties().push_back(p);

    model m0;
    m0.pods().insert(std::make_pair(pod0.name(), pod0));
    m0.name(model_name(0));

    model m1;
    m1.pods().insert(std::make_pair(pod1.name(), pod1));
    m1.name(model_name(1));

    return std::array<model, 2> {{ m0, m1 }};
}

model mock_model_factory::pod_with_missing_property_type() {
    pod pod0(mock_pod(0));
    pod pod1(mock_pod(1));

    property p;
    p.name(property_name(0));

    dogen::sml::qname qn;
    qn.type_name(pod1.name().type_name());
    qn.model_name(pod1.name().model_name());

    dogen::sml::nested_qname nqn;
    nqn.type(qn);
    p.type_name(nqn);
    pod0.properties().push_back(p);

    model r;
    r.pods().insert(std::make_pair(pod0.name(), pod0));
    r.name(model_name(0));
    return r;
}

model mock_model_factory::pod_with_parent_in_the_same_model() {
    const std::string mn(model_name(0));
    pod pod0(mock_pod(0, mn));
    pod pod1(mock_pod(1, mn));
    pod0.parent_name(pod1.name());

    model r;
    r.pods().insert(std::make_pair(pod0.name(), pod0));
    r.pods().insert(std::make_pair(pod1.name(), pod1));
    r.name(mn);
    return r;
}

std::array<model, 2> mock_model_factory::
pod_with_parent_in_different_models() {
    pod pod0(mock_pod(0));
    pod pod1(mock_pod(1));
    pod0.parent_name(pod1.name());

    model m0;
    m0.pods().insert(std::make_pair(pod0.name(), pod0));
    m0.name(model_name(0));

    model m1;
    m1.pods().insert(std::make_pair(pod1.name(), pod1));
    m1.name(model_name(1));

    return std::array<model, 2> {{ m0, m1 }};
}

model mock_model_factory::pod_with_third_degree_parent_in_same_model() {
    const std::string mn(model_name(0));
    pod pod0(mock_pod(0, mn));
    pod pod1(mock_pod(1, mn));
    pod pod2(mock_pod(2, mn));
    pod pod3(mock_pod(3, mn));

    pod0.parent_name(pod1.name());
    pod1.parent_name(pod2.name());
    pod2.parent_name(pod3.name());

    model r;
    r.pods().insert(std::make_pair(pod0.name(), pod0));
    r.pods().insert(std::make_pair(pod1.name(), pod1));
    r.pods().insert(std::make_pair(pod2.name(), pod2));
    r.pods().insert(std::make_pair(pod3.name(), pod3));
    r.name(mn);
    return r;
}

model mock_model_factory::pod_with_third_degree_parent_missing() {
    const std::string mn(model_name(0));
    pod pod0(mock_pod(0, mn));
    pod pod1(mock_pod(1, mn));
    pod pod2(mock_pod(2, mn));
    pod pod3(mock_pod(3, mn));

    pod0.parent_name(pod1.name());
    pod1.parent_name(pod2.name());
    pod2.parent_name(pod3.name());

    model r;
    r.pods().insert(std::make_pair(pod0.name(), pod0));
    r.pods().insert(std::make_pair(pod1.name(), pod1));
    r.pods().insert(std::make_pair(pod2.name(), pod2));
    r.name(mn);
    return r;
}

std::array<model, 4>
mock_model_factory::pod_with_third_degree_parent_in_different_models() {
    pod pod0(mock_pod(0));
    pod pod1(mock_pod(1));
    pod pod2(mock_pod(2));
    pod pod3(mock_pod(3));

    pod0.parent_name(pod1.name());
    pod1.parent_name(pod2.name());
    pod2.parent_name(pod3.name());

    model m0;
    m0.pods().insert(std::make_pair(pod0.name(), pod0));
    m0.name(model_name(0));

    model m1;
    m1.pods().insert(std::make_pair(pod1.name(), pod1));
    m1.name(model_name(1));

    model m2;
    m2.pods().insert(std::make_pair(pod2.name(), pod2));
    m2.name(model_name(2));

    model m3;
    m3.pods().insert(std::make_pair(pod3.name(), pod3));
    m3.name(model_name(3));

    return std::array<model, 4>{{ m0, m1, m2, m3 }};
}

std::array<model, 4> mock_model_factory::
pod_with_missing_third_degree_parent_in_different_models() {
    pod pod0(mock_pod(0));
    pod pod1(mock_pod(1));
    pod pod2(mock_pod(2));
    pod pod3(mock_pod(3));

    pod0.parent_name(pod1.name());
    pod1.parent_name(pod2.name());
    pod2.parent_name(pod3.name());

    model m0;
    m0.pods().insert(std::make_pair(pod0.name(), pod0));
    m0.name(model_name(0));

    model m1;
    m1.pods().insert(std::make_pair(pod1.name(), pod1));
    m1.name(model_name(1));

    model m2;
    m2.pods().insert(std::make_pair(pod2.name(), pod2));
    m2.name(model_name(2));

    return std::array<model, 4>{{ m0, m1, m2 }};
}

} } }

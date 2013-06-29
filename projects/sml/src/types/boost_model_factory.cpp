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
#include "dogen/sml/types/value_object.hpp"
#include "dogen/sml/types/boost_model_factory.hpp"

namespace {
const std::string model_name("boost");
const std::string shared_ptr_name("shared_ptr");
const std::string weak_ptr_name("weak_ptr");
const std::string scoped_ptr_name("scoped_ptr");
const std::string optional_name("optional");
const std::string variant_name("variant");
const std::string path_name("path");

const std::string asio_name("asio");
const std::string filesystem_name("filesystem");
const std::string io_service_name("io_service");
const std::string ip_name("ip");
const std::string tcp_name("tcp");
const std::string socket_name("socket");
const std::string acceptor_name("acceptor");

const std::string gregorian_name("gregorian");
const std::string date_name("date");
const std::string posix_time_name("posix_time");
const std::string ptime_name("ptime");
const std::string time_duration_name("time_duration");

}

namespace dogen {
namespace sml {

boost::shared_ptr<abstract_object>
boost_model_factory::create_value_object(const std::string& name,
    const std::list<std::string> &module_path, value_object_types t) {

    qname q;
    q.simple_name(name);
    q.meta_type(meta_types::value_object);
    q.model_name(model_name);
    q.module_path(module_path);

    std::unique_ptr<value_object> r(new value_object());
    r->name(q);
    r->generation_type(generation_types::no_generation);
    r->type(t);
    if (t == value_object_types::sequence_container)
        r->number_of_type_arguments(1);
    else if (t == value_object_types::associative_container)
        r->number_of_type_arguments(2);

    return boost::shared_ptr<abstract_object>(r.release());
}

module boost_model_factory::create_module(const std::string& name,
    const std::list<std::string>& module_path) {
    qname qn;
    qn.model_name(model_name);
    qn.simple_name(name);
    qn.module_path(module_path);

    module r;
    r.name(qn);

    return r;
}

model boost_model_factory::create() {
    using namespace sml;
    qname qn;
    qn.model_name(model_name);

    model r;
    r.name(qn);
    r.is_system(true);

    const auto pi([&](const std::string& name,
            const std::list<std::string>& module_path, value_object_types vot) {
            const auto vo(create_value_object(name, module_path, vot));
            r.objects().insert(std::make_pair(vo->name(), vo));
        });

    const auto gamma([&](std::string name,
            std::list<std::string> module_path) {
            const auto m(create_module(name, module_path));
            r.modules().insert(std::make_pair(m.name(), m));
        });

    std::list<std::string> module_path;
    pi(shared_ptr_name, module_path, value_object_types::smart_pointer);
    pi(weak_ptr_name, module_path, value_object_types::smart_pointer);
    pi(scoped_ptr_name, module_path, value_object_types::smart_pointer);
    pi(optional_name, module_path, value_object_types::plain);
    pi(variant_name, module_path, value_object_types::plain);

    gamma(asio_name, module_path);
    module_path.push_back(asio_name);
    pi(io_service_name, module_path, value_object_types::plain);

    gamma(ip_name, module_path);
    module_path.push_back(ip_name);

    gamma(tcp_name, module_path);
    module_path.push_back(tcp_name);

    pi(socket_name, module_path, value_object_types::plain);
    pi(acceptor_name, module_path, value_object_types::plain);

    module_path.clear();
    gamma(filesystem_name, module_path);
    module_path.push_back(filesystem_name);
    pi(path_name, module_path, value_object_types::plain);

    module_path.clear();
    gamma(gregorian_name, module_path);

    module_path.push_back(gregorian_name);
    pi(date_name, module_path, value_object_types::plain);

    module_path.clear();
    gamma(posix_time_name, module_path);

    module_path.push_back(posix_time_name);
    pi(ptime_name, module_path, value_object_types::plain);
    pi(time_duration_name, module_path, value_object_types::plain);

    return r;
}

} }

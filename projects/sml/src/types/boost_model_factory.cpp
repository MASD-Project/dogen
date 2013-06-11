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

pod boost_model_factory::create_pod(const std::string& name, pod_types pt,
    std::list<std::string> module_path) {
    qname q;
    q.type_name(name);
    q.meta_type(meta_types::pod);
    q.model_name(model_name);
    q.module_path(module_path);

    pod r;
    r.name(q);
    r.generation_type(generation_types::no_generation);
    if (pt == pod_types::sequence_container)
        r.number_of_type_arguments(1);
    else if (pt == pod_types::associative_container)
        r.number_of_type_arguments(2);

    r.pod_type(pt);
    return r;
}

module boost_model_factory::
create_module(const std::string& name, std::list<std::string> module_path) {
    qname qn;
    qn.model_name(model_name);
    qn.type_name(name);
    qn.module_path(module_path);

    module r;
    r.name(qn);

    return r;
}

model boost_model_factory::create() {
    using namespace sml;
    model r;
    r.name(model_name);
    r.is_system(true);

    const auto pi([&](std::string name, pod_types pt,
            std::list<std::string> module_path) {
            pod p(create_pod(name, pt, module_path));
            r.pods().insert(std::make_pair(p.name(), p));
        });

    const auto gamma([&](std::string name,
            std::list<std::string> module_path) {
            module p(create_module(name, module_path));
            r.modules().insert(std::make_pair(p.name(), p));
        });

    std::list<std::string> module_path;
    pi(shared_ptr_name, pod_types::smart_pointer, module_path);
    pi(weak_ptr_name, pod_types::smart_pointer, module_path);
    pi(scoped_ptr_name, pod_types::smart_pointer, module_path);
    pi(optional_name, pod_types::value, module_path);
    pi(variant_name, pod_types::value, module_path);

    gamma(asio_name, module_path);
    module_path.push_back(asio_name);
    pi(io_service_name, pod_types::value, module_path);

    gamma(ip_name, module_path);
    module_path.push_back(ip_name);

    gamma(tcp_name, module_path);
    module_path.push_back(tcp_name);

    pi(socket_name, pod_types::value, module_path);
    pi(acceptor_name, pod_types::value, module_path);

    module_path.clear();
    gamma(filesystem_name, module_path);
    module_path.push_back(filesystem_name);
    pi(path_name, pod_types::value, module_path);

    module_path.clear();
    gamma(gregorian_name, module_path);

    module_path.push_back(gregorian_name);
    pi(date_name, pod_types::value, module_path);

    module_path.clear();
    gamma(posix_time_name, module_path);

    module_path.push_back(posix_time_name);
    pi(ptime_name, pod_types::value, module_path);
    pi(time_duration_name, pod_types::value, module_path);

    return r;
}

} }

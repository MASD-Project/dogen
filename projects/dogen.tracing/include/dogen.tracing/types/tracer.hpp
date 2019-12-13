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
#ifndef DOGEN_TRACING_TYPES_TRACER_HPP
#define DOGEN_TRACING_TYPES_TRACER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <sstream>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "dogen.tracing/types/backend.hpp"
#include "dogen/types/configuration.hpp"
#include "dogen.tracing/types/backend_factory_registrar.hpp"

namespace dogen::tracing {

/**
 * @brief Handles all of the tracing-related work.
 */
class tracer final {
public:
    /**
     * @brief Registrar that keeps track of the available transforms.
     */
    static backend_factory_registrar& registrar();

public:
    tracer(const tracer&) = default;

public:
    explicit tracer(const configuration& cfg);

public:
    const boost::shared_ptr<tracing::backend> backend() const {
        return backend_;
    }

private:
    template<typename Ioable>
    std::string to_string(const Ioable& ioable) const {
        std::ostringstream s;
        s << ioable;
        return s.str();
    }

    static std::string generate_guid();

public:
    /**
     * @brief Writes an initial input to the filesystem.
     */
    template<typename Ioable>
    void add_initial_input(const std::string& input_id,
        const Ioable& input) const {
        if (backend_)
            backend_->start_tracing(input_id, to_string(input));
    }

    void add_references_graph(const std::string& root_vertex,
        const std::unordered_map<std::string, std::list<std::string>>&
        edges_per_model) const;

    void start_chain(const std::string& transform_id,
        const std::string& transform_instance_id) const;
    void start_chain(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id) const;

    template<typename Ioable>
    void start_chain(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id,
        const Ioable& input) const {
        if (backend_) {
            backend_->start_chain(transform_id, transform_instance_id,
                model_id, to_string(input));
        }
    }

    void start_transform(const std::string& transform_id,
        const std::string& transform_instance_id) const;

    void start_transform(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id) const;

    template<typename Ioable>
    void start_transform(const std::string& transform_id,
        const std::string& transform_instance_id,
        const std::string& model_id,
        const Ioable& input) const {
        if (backend_) {
            backend_->start_transform(transform_id, transform_instance_id,
                model_id, to_string(input));
        }
    }

    void end_chain(const std::string& transform_instance_id) const;

    template<typename Ioable>
    void end_chain(const std::string& transform_instance_id,
        const Ioable& output) const {
        if (backend_)
            backend_->end_chain(transform_instance_id, to_string(output));
    }

    void end_transform(const std::string& transform_instance_id) const;

    template<typename Ioable>
    void end_transform(const std::string& transform_instance_id,
        const Ioable& output) const {
        if (backend_)
            backend_->end_transform(transform_instance_id, to_string(output));
    }

    void end_tracing() const;

public:
    bool operator==(const tracer& rhs) const;

private:
    boost::shared_ptr<tracing::backend> backend_;
    static backend_factory_registrar registrar_;
};

/*
 * Helper method to register transforms.
 */
template<typename Transform>
inline void register_backend_factory() {
    auto t(boost::make_shared<Transform>());
    auto& rg(tracer::registrar());
    rg.register_backend_factory(t);
}

}

#endif

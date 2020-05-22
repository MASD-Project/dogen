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
#ifndef DOGEN_TRACING_TYPES_SCOPED_TRACER_HPP
#define DOGEN_TRACING_TYPES_SCOPED_TRACER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/tracer.hpp"

namespace dogen::tracing {

/**
 * @brief Top-level scoped tracer. Signals the end of the run.
 */
class scoped_tracer final {
public:
    scoped_tracer(const tracer& tp) : tracer_(tp) {}
    ~scoped_tracer() { tracer_.end_run(); }

private:
    const tracer& tracer_;
};

/**
 * @brief Scoped tracer for a transform chain.
 */
class scoped_chain_tracer final {
private:
    static std::string generate_guid();

public:
    scoped_chain_tracer(dogen::utility::log::logger& lg,
        const std::string& description, const std::string& id, const tracer& tp)
        : description_(description), lg_(lg), dismiss_(false), tracer_(tp),
          transform_id_(id), transform_instance_id_(generate_guid()) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << description << ".";
        tracer_.start_chain(id, transform_instance_id_);
    }

    scoped_chain_tracer(dogen::utility::log::logger& lg,
        const std::string& description, const std::string& id,
        const std::string& model_id, const tracer& tp)
        : description_(description), lg_(lg), dismiss_(false), tracer_(tp),
          model_id_(model_id), transform_id_(id),
          transform_instance_id_(generate_guid()) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << description << ".";
        tracer_.start_chain(id, transform_instance_id_, model_id_);
    }

    template<typename Input>
    scoped_chain_tracer(dogen::utility::log::logger& lg,
        const std::string& description, const std::string& id,
        const std::string& model_id, const tracer& tp, const Input& input)
        : description_(description), lg_(lg), dismiss_(false), tracer_(tp),
          model_id_(model_id), transform_id_(id),
          transform_instance_id_(generate_guid()) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << description
                                  << " [" << model_id_ << "]";
        tracer_.start_chain(id, transform_instance_id_, model_id_, input);
    }

    template<typename Output>
    void end_chain(const Output& output) {
        const auto& tid(transform_instance_id_);
        tracer_.end_chain(transform_id_, tid, model_id_, output);
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Finished " << description_ << ".";
        dismiss_ = true;
    }

    ~scoped_chain_tracer() {
        if (dismiss_)
            return;

        try {
            tracer_.end_chain(transform_id_, transform_instance_id_);
            using namespace dogen::utility::log;
            BOOST_LOG_SEV(lg_, debug) << "Finished " << description_<< ".";
        } catch (...) {}
    }

private:
    const std::string description_;
    dogen::utility::log::logger& lg_;
    bool dismiss_;
    const tracer& tracer_;
    const std::string model_id_;
    const std::string transform_id_;
    const std::string transform_instance_id_;
};

/**
 * @brief Scoped tracer for a regular transform.
 */
class scoped_transform_tracer final {
private:
    static std::string generate_guid();

public:
    scoped_transform_tracer(dogen::utility::log::logger& lg,
        const std::string& description, const std::string& id,
        const std::string& model_id, const tracer& tp)
        : description_(description), lg_(lg), dismiss_(false), tracer_(tp),
          model_id_(model_id), transform_id_(id),
          transform_instance_id_(generate_guid()) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << description << ". ";
        tracer_.start_transform(id, transform_instance_id_, model_id);
    }

    template<typename Input>
    scoped_transform_tracer(dogen::utility::log::logger& lg,
        const std::string& description, const std::string& id,
        const tracer& tp, const Input& input)
        : description_(description), lg_(lg), dismiss_(false), tracer_(tp),
          model_id_(), transform_id_(id),
          transform_instance_id_(generate_guid()) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << description << ". ";
        tracer_.start_transform(id, transform_instance_id_, "", input);
    }

    template<typename Input>
    scoped_transform_tracer(dogen::utility::log::logger& lg,
        const std::string& description, const std::string& id,
        const std::string& model_id, const tracer& tp, const Input& input)
        : description_(description), lg_(lg), dismiss_(false), tracer_(tp),
          model_id_(model_id), transform_id_(id),
          transform_instance_id_(generate_guid()) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << description
                                  << ". Model: " << model_id;
        tracer_.start_transform(id, transform_instance_id_, model_id, input);
    }

    template<typename Output>
    void end_transform(const Output& output) {
        const auto& tid(transform_instance_id_);
        tracer_.end_transform(transform_id_, tid, model_id_, output);
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Finished " << description_
                                  << ". Model: " << model_id_;
        dismiss_ = true;
    }

    ~scoped_transform_tracer() {
        if (dismiss_)
            return;

        try {
            tracer_.end_transform(transform_id_, transform_instance_id_);
            using namespace dogen::utility::log;
            BOOST_LOG_SEV(lg_, debug) << "Finished " << description_ << ".";
        } catch (...) {}
    }

private:
    const std::string description_;
    dogen::utility::log::logger& lg_;
    bool dismiss_;
    const tracer& tracer_;
    const std::string model_id_;
    const std::string transform_id_;
    const std::string transform_instance_id_;
};

}

#endif

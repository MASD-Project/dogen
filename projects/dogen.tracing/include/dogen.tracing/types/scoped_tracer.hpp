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

class scoped_chain_tracer final {
public:
    scoped_chain_tracer(dogen::utility::log::logger& lg,
        const std::string& description, const std::string& id, const tracer& tp)
        : description_(description), lg_(lg), dismiss_(false), tracer_(tp) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << description << ".";
        tracer_.start_chain(id);
    }

    scoped_chain_tracer(dogen::utility::log::logger& lg,
        const std::string& description, const std::string& id,
        const std::string& model_id, const tracer& tp)
        : description_(description), lg_(lg), dismiss_(false), tracer_(tp) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << description << ".";
        tracer_.start_chain(id, model_id);
    }

    template<typename Input>
    scoped_chain_tracer(dogen::utility::log::logger& lg,
        const std::string& description, const std::string& id,
        const std::string& model_id, const tracer& tp, const Input& input)
        : description_(description), lg_(lg), dismiss_(false), tracer_(tp) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << description
                                  << " [" << model_id << "]";
        tracer_.start_chain(id, model_id, input);
    }

    template<typename Output>
    void end_chain(const Output& output) {
        tracer_.end_chain(output);
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Finished " << description_ << ".";
        dismiss_ = true;
    }

    ~scoped_chain_tracer() {
        if (dismiss_)
            return;

        try {
            tracer_.end_chain();
            using namespace dogen::utility::log;
            BOOST_LOG_SEV(lg_, debug) << "Finished " << description_<< ".";
        } catch (...) {}
    }

private:
    const std::string description_;
    dogen::utility::log::logger& lg_;
    bool dismiss_;
    const tracer& tracer_;
};

class scoped_transform_tracer final {
public:
    scoped_transform_tracer(dogen::utility::log::logger& lg,
        const std::string& description, const std::string& id,
        const std::string& model_id, const tracer& tp)
        : description_(description), lg_(lg), dismiss_(false), tracer_(tp) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << description << ". ";
        tracer_.start_transform(id, model_id);
    }

    template<typename Input>
    scoped_transform_tracer(dogen::utility::log::logger& lg,
        const std::string& description, const std::string& id,
        const tracer& tp, const Input& input)
        : description_(description), lg_(lg), dismiss_(false), tracer_(tp) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << description << ". ";
        tracer_.start_transform(id, "", input);
    }

    template<typename Input>
    scoped_transform_tracer(dogen::utility::log::logger& lg,
        const std::string& description, const std::string& id,
        const std::string& model_id, const tracer& tp, const Input& input)
        : description_(description), lg_(lg), dismiss_(false), tracer_(tp) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << description
                                  << ". Model: " << model_id;
        tracer_.start_transform(id, model_id, input);
    }

    template<typename Output>
    void end_transform(const Output& output) {
        tracer_.end_transform(output);
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Finished " << description_ << ".";
        dismiss_ = true;
    }

    ~scoped_transform_tracer() {
        if (dismiss_)
            return;

        try {
            tracer_.end_transform();
            using namespace dogen::utility::log;
            BOOST_LOG_SEV(lg_, debug) << "Finished " << description_ << ".";
        } catch (...) {}
    }

private:
    const std::string description_;
    dogen::utility::log::logger& lg_;
    bool dismiss_;
    const tracer& tracer_;
};

}

#endif

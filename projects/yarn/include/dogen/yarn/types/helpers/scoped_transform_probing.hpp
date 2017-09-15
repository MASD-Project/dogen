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
#ifndef DOGEN_YARN_TYPES_HELPERS_SCOPED_TRANSFORM_PROBING_HPP
#define DOGEN_YARN_TYPES_HELPERS_SCOPED_TRANSFORM_PROBING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/helpers/transform_prober.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

class scoped_chain_probing final {
public:
    scoped_chain_probing(dogen::utility::log::logger& lg,
        const std::string& transform_description,
        const std::string& transform_id, const transform_prober& tp)
        : transform_description_(transform_description),
          lg_(lg), dismiss_(false), transform_prober_(tp) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << transform_description
                                  << ". ";
        transform_prober_.start_chain(transform_id);
    }

    scoped_chain_probing(dogen::utility::log::logger& lg,
        const std::string& transform_description,
        const std::string& transform_id, const std::string& model_id,
        const transform_prober& tp)
        : transform_description_(transform_description),
          lg_(lg), dismiss_(false), transform_prober_(tp) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << transform_description
                                  << ". ";
        transform_prober_.start_chain(transform_id, model_id);
    }

    template<typename Input>
    scoped_chain_probing(dogen::utility::log::logger& lg,
        const std::string& transform_description,
        const std::string& transform_id, const std::string& model_id,
        const transform_prober& tp, const Input& input)
        : transform_description_(transform_description),
          lg_(lg), dismiss_(false), transform_prober_(tp) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << transform_description
                                  << ". Model: " << model_id;
        transform_prober_.start_chain(transform_id, model_id, input);
    }

    template<typename Output>
    void end_chain(const Output& output) {
        transform_prober_.end_chain(output);
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Finished " << transform_description_
                                  << ".";
        dismiss_ = true;
    }

    ~scoped_chain_probing() {
        if (dismiss_)
            return;

        try {
            transform_prober_.end_chain();
            using namespace dogen::utility::log;
            BOOST_LOG_SEV(lg_, debug) << "Finished " << transform_description_
                                      << ".";
        } catch (...) {}
    }

private:
    const std::string transform_description_;
    dogen::utility::log::logger& lg_;
    bool dismiss_;
    const transform_prober& transform_prober_;
};

class scoped_transform_probing final {
public:
    scoped_transform_probing(dogen::utility::log::logger& lg,
        const std::string& transform_description,
        const std::string& transform_id, const std::string& model_id,
        const transform_prober& tp)
        : transform_description_(transform_description),
          lg_(lg), dismiss_(false), transform_prober_(tp) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << transform_description
                                  << ". ";
        transform_prober_.start_transform(transform_id, model_id);
    }

    template<typename Input>
    scoped_transform_probing(dogen::utility::log::logger& lg,
        const std::string& transform_description,
        const std::string& transform_id,
        const transform_prober& tp, const Input& input)
        : transform_description_(transform_description),
          lg_(lg), dismiss_(false), transform_prober_(tp) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << transform_description
                                  << ". ";
        transform_prober_.start_transform(transform_id, "", input);
    }

    template<typename Input>
    scoped_transform_probing(dogen::utility::log::logger& lg,
        const std::string& transform_description,
        const std::string& transform_id, const std::string& model_id,
        const transform_prober& tp, const Input& input)
        : transform_description_(transform_description),
          lg_(lg), dismiss_(false), transform_prober_(tp) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Started " << transform_description
                                  << ". Model: " << model_id;
        transform_prober_.start_transform(transform_id, model_id, input);
    }

    template<typename Output>
    void end_transform(const Output& output) {
        transform_prober_.end_transform(output);
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg_, debug) << "Finished " << transform_description_
                                  << ".";
        dismiss_ = true;
    }

    ~scoped_transform_probing() {
        if (dismiss_)
            return;

        try {
            transform_prober_.end_transform();
            using namespace dogen::utility::log;
            BOOST_LOG_SEV(lg_, debug) << "Finished " << transform_description_
                                      << ".";
        } catch (...) {}
    }

private:
    const std::string transform_description_;
    dogen::utility::log::logger& lg_;
    bool dismiss_;
    const transform_prober& transform_prober_;
};

} } }

#endif

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
#ifndef DOGEN_RELATIONAL_TYPES_TRACING_LOG_BACKEND_HPP
#define DOGEN_RELATIONAL_TYPES_TRACING_LOG_BACKEND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/detail/header.hpp>
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/pgsql/database.hxx>
#include <odb/schema-catalog.hxx>
#include "dogen.utility/types/log/severity_level.hpp"
#include "dogen/types/configuration.hpp"

namespace dogen::relational::tracing {

class log_backend final : public boost::log::sinks::
        basic_formatted_sink_backend<char,
                                     boost::log::sinks::concurrent_feeding> {
public:
    log_backend(const std::string& run_id, const database_configuration& dbcfg);

public:
    void consume(const boost::log::record_view& rv,
        const string_type& formatted_message);

private:
    const std::string run_id_;
    boost::shared_ptr<odb::pgsql::database> database_;
};

void create_relational_log_backend(const configuration& cfg,
    const utility::log::severity_level severity);

}

#endif

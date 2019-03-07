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
#ifndef MASD_DOGEN_EXTRACTION_TYPES_TRANSFORMS_CONTEXT_HPP
#define MASD_DOGEN_EXTRACTION_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.tracing/types/tracer_fwd.hpp"
#include "masd.dogen/types/diffing_configuration.hpp"
#include "masd.dogen/types/reporting_configuration.hpp"

namespace masd::dogen::extraction::transforms {

class context final {
public:
    context() = default;
    // context(const context&) = default;
    ~context() = default;

public:
    // context(context&& rhs);

public:
    context(
        const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer,
        const boost::optional<masd::dogen::diffing_configuration>& diffing_configuration,
        const boost::optional<masd::dogen::reporting_configuration>& reporting_configuration);

public:
    const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer() const;
    boost::shared_ptr<masd::dogen::tracing::tracer>& tracer();
    void tracer(const boost::shared_ptr<masd::dogen::tracing::tracer>& v);
    void tracer(const boost::shared_ptr<masd::dogen::tracing::tracer>&& v);

    const boost::optional<masd::dogen::diffing_configuration>& diffing_configuration() const;
    boost::optional<masd::dogen::diffing_configuration>& diffing_configuration();
    void diffing_configuration(const boost::optional<masd::dogen::diffing_configuration>& v);
    void diffing_configuration(const boost::optional<masd::dogen::diffing_configuration>&& v);

    const boost::optional<masd::dogen::reporting_configuration>& reporting_configuration() const;
    boost::optional<masd::dogen::reporting_configuration>& reporting_configuration();
    void reporting_configuration(const boost::optional<masd::dogen::reporting_configuration>& v);
    void reporting_configuration(const boost::optional<masd::dogen::reporting_configuration>&& v);

private:
    boost::shared_ptr<masd::dogen::tracing::tracer> tracer_;
    boost::optional<masd::dogen::diffing_configuration> diffing_configuration_;
    boost::optional<masd::dogen::reporting_configuration> reporting_configuration_;
};

}

#endif

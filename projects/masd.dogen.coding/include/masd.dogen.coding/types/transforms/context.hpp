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
#ifndef MASD_DOGEN_CODING_TYPES_TRANSFORMS_CONTEXT_HPP
#define MASD_DOGEN_CODING_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.tracing/types/tracer_fwd.hpp"
#include "masd.dogen.coding/types/transforms/options.hpp"
#include "masd.dogen.extraction/types/repository_fwd.hpp"
#include "masd.dogen.annotations/types/type_repository_fwd.hpp"
#include "masd.dogen.annotations/types/annotation_factory_fwd.hpp"
#include "masd.dogen.annotations/types/annotation_expander_fwd.hpp"
#include "masd.dogen.coding/types/helpers/mapping_set_repository_fwd.hpp"
#include "masd.dogen.annotations/types/archetype_location_repository_fwd.hpp"

namespace masd::dogen::coding::transforms {

/**
 *
 * Context for all coding transformations.
 *
 * Contains all of the external data required for the transformations
 * to execute. It's not ideal to have a huge "global" class, with lots
 * of unrelated state; however, over time, we found that a number of
 * arguments were being supplied across the call graph, resulting in a
 * lot of repetitive code. The context gathers together all of these.
 */
class context final {
public:
    context() = default;
    // context(const context&) = default;
    // context(context&&) = default;
    ~context() = default;

public:
    context(
        const std::vector<boost::filesystem::path>& data_directories,
        const masd::dogen::coding::transforms::options& transform_options,
        const boost::shared_ptr<masd::dogen::annotations::type_repository>& type_repository,
        const boost::shared_ptr<masd::dogen::annotations::archetype_location_repository>& archetype_location_repository,
        const boost::shared_ptr<masd::dogen::annotations::annotation_factory>& annotation_factory,
        const boost::shared_ptr<masd::dogen::annotations::annotation_expander>& annotation_expander,
        const boost::shared_ptr<masd::dogen::coding::helpers::mapping_set_repository>& mapping_repository,
        const boost::shared_ptr<masd::dogen::extraction::repository>& formatting_repository,
        const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer);

public:
    const std::vector<boost::filesystem::path>& data_directories() const;
    std::vector<boost::filesystem::path>& data_directories();
    void data_directories(const std::vector<boost::filesystem::path>& v);
    void data_directories(const std::vector<boost::filesystem::path>&& v);

    const masd::dogen::coding::transforms::options& transform_options() const;
    masd::dogen::coding::transforms::options& transform_options();
    void transform_options(const masd::dogen::coding::transforms::options& v);
    void transform_options(const masd::dogen::coding::transforms::options&& v);

    const boost::shared_ptr<masd::dogen::annotations::type_repository>& type_repository() const;
    boost::shared_ptr<masd::dogen::annotations::type_repository>& type_repository();
    void type_repository(const boost::shared_ptr<masd::dogen::annotations::type_repository>& v);
    void type_repository(const boost::shared_ptr<masd::dogen::annotations::type_repository>&& v);

    const boost::shared_ptr<masd::dogen::annotations::archetype_location_repository>& archetype_location_repository() const;
    boost::shared_ptr<masd::dogen::annotations::archetype_location_repository>& archetype_location_repository();
    void archetype_location_repository(const boost::shared_ptr<masd::dogen::annotations::archetype_location_repository>& v);
    void archetype_location_repository(const boost::shared_ptr<masd::dogen::annotations::archetype_location_repository>&& v);

    const boost::shared_ptr<masd::dogen::annotations::annotation_factory>& annotation_factory() const;
    boost::shared_ptr<masd::dogen::annotations::annotation_factory>& annotation_factory();
    void annotation_factory(const boost::shared_ptr<masd::dogen::annotations::annotation_factory>& v);
    void annotation_factory(const boost::shared_ptr<masd::dogen::annotations::annotation_factory>&& v);

    const boost::shared_ptr<masd::dogen::annotations::annotation_expander>& annotation_expander() const;
    boost::shared_ptr<masd::dogen::annotations::annotation_expander>& annotation_expander();
    void annotation_expander(const boost::shared_ptr<masd::dogen::annotations::annotation_expander>& v);
    void annotation_expander(const boost::shared_ptr<masd::dogen::annotations::annotation_expander>&& v);

    const boost::shared_ptr<masd::dogen::coding::helpers::mapping_set_repository>& mapping_repository() const;
    boost::shared_ptr<masd::dogen::coding::helpers::mapping_set_repository>& mapping_repository();
    void mapping_repository(const boost::shared_ptr<masd::dogen::coding::helpers::mapping_set_repository>& v);
    void mapping_repository(const boost::shared_ptr<masd::dogen::coding::helpers::mapping_set_repository>&& v);

    const boost::shared_ptr<masd::dogen::extraction::repository>& formatting_repository() const;
    boost::shared_ptr<masd::dogen::extraction::repository>& formatting_repository();
    void formatting_repository(const boost::shared_ptr<masd::dogen::extraction::repository>& v);
    void formatting_repository(const boost::shared_ptr<masd::dogen::extraction::repository>&& v);

    const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer() const;
    boost::shared_ptr<masd::dogen::tracing::tracer>& tracer();
    void tracer(const boost::shared_ptr<masd::dogen::tracing::tracer>& v);
    void tracer(const boost::shared_ptr<masd::dogen::tracing::tracer>&& v);

private:
    std::vector<boost::filesystem::path> data_directories_;
    masd::dogen::coding::transforms::options transform_options_;
    boost::shared_ptr<masd::dogen::annotations::type_repository> type_repository_;
    boost::shared_ptr<masd::dogen::annotations::archetype_location_repository> archetype_location_repository_;
    boost::shared_ptr<masd::dogen::annotations::annotation_factory> annotation_factory_;
    boost::shared_ptr<masd::dogen::annotations::annotation_expander> annotation_expander_;
    boost::shared_ptr<masd::dogen::coding::helpers::mapping_set_repository> mapping_repository_;
    boost::shared_ptr<masd::dogen::extraction::repository> formatting_repository_;
    boost::shared_ptr<masd::dogen::tracing::tracer> tracer_;
};

}

#endif

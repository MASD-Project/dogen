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
#ifndef MASD_DOGEN_GENERATION_TYPES_TRANSFORMS_CONTEXT_HPP
#define MASD_DOGEN_GENERATION_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.tracing/types/tracer_fwd.hpp"
#include "masd.dogen.extraction/types/repository_fwd.hpp"
#include "masd.dogen.annotations/types/type_repository_fwd.hpp"
#include "masd.dogen.annotations/types/annotation_factory_fwd.hpp"
#include "masd.dogen.annotations/types/annotation_expander_fwd.hpp"
#include "masd.dogen.annotations/types/archetype_location_repository_fwd.hpp"
#include "masd.dogen.generation/types/meta_model/intra_backend_segment_properties.hpp"

namespace masd::dogen::generation::transforms {

class context final {
public:
    context() = default;
    // context(const context&) = default;
    ~context() = default;

public:
    // context(context&& rhs);

public:
    context(
        const boost::shared_ptr<masd::dogen::annotations::type_repository>& type_repository,
        const boost::shared_ptr<masd::dogen::annotations::archetype_location_repository>& archetype_location_repository,
        const boost::shared_ptr<masd::dogen::annotations::annotation_factory>& annotation_factory,
        const boost::shared_ptr<masd::dogen::annotations::annotation_expander>& annotation_expander,
        const boost::shared_ptr<masd::dogen::extraction::repository>& formatting_repository,
        const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer,
        const std::unordered_map<std::string, masd::dogen::generation::meta_model::intra_backend_segment_properties>& intra_backend_segment_properties,
        const boost::filesystem::path& output_directory_path);

public:
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

    const boost::shared_ptr<masd::dogen::extraction::repository>& formatting_repository() const;
    boost::shared_ptr<masd::dogen::extraction::repository>& formatting_repository();
    void formatting_repository(const boost::shared_ptr<masd::dogen::extraction::repository>& v);
    void formatting_repository(const boost::shared_ptr<masd::dogen::extraction::repository>&& v);

    const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer() const;
    boost::shared_ptr<masd::dogen::tracing::tracer>& tracer();
    void tracer(const boost::shared_ptr<masd::dogen::tracing::tracer>& v);
    void tracer(const boost::shared_ptr<masd::dogen::tracing::tracer>&& v);

    const std::unordered_map<std::string, masd::dogen::generation::meta_model::intra_backend_segment_properties>& intra_backend_segment_properties() const;
    std::unordered_map<std::string, masd::dogen::generation::meta_model::intra_backend_segment_properties>& intra_backend_segment_properties();
    void intra_backend_segment_properties(const std::unordered_map<std::string, masd::dogen::generation::meta_model::intra_backend_segment_properties>& v);
    void intra_backend_segment_properties(const std::unordered_map<std::string, masd::dogen::generation::meta_model::intra_backend_segment_properties>&& v);

    /**
     * @brief FIXME: to be removed
     */
    /**@{*/
    const boost::filesystem::path& output_directory_path() const;
    boost::filesystem::path& output_directory_path();
    void output_directory_path(const boost::filesystem::path& v);
    void output_directory_path(const boost::filesystem::path&& v);
    /**@}*/

private:
    boost::shared_ptr<masd::dogen::annotations::type_repository> type_repository_;
    boost::shared_ptr<masd::dogen::annotations::archetype_location_repository> archetype_location_repository_;
    boost::shared_ptr<masd::dogen::annotations::annotation_factory> annotation_factory_;
    boost::shared_ptr<masd::dogen::annotations::annotation_expander> annotation_expander_;
    boost::shared_ptr<masd::dogen::extraction::repository> formatting_repository_;
    boost::shared_ptr<masd::dogen::tracing::tracer> tracer_;
    std::unordered_map<std::string, masd::dogen::generation::meta_model::intra_backend_segment_properties> intra_backend_segment_properties_;
    boost::filesystem::path output_directory_path_;
};

}

#endif

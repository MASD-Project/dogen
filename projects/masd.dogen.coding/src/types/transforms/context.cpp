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
#include "masd.dogen.coding/types/transforms/context.hpp"

namespace masd::dogen::coding::transforms {

context::context(
        const std::vector<boost::filesystem::path>& data_directories,
        const transforms::options& options,
        const annotations::archetype_location_repository& alrp,
        const annotations::type_repository& atrp,
        const helpers::mapping_set_repository& msrp,
        const masd::dogen::extraction::repository& frp,
        const probing::prober& prober,
        const std::unordered_map<std::string,
        meta_model::intra_backend_segment_properties>&
        intra_backend_segment_properties,
        const boost::shared_ptr<helpers::artefact_writer_interface> writer) :
    data_directories_(data_directories), options_(options),
    archetype_location_repository_(alrp), type_repository_(atrp),
    annotation_factory_(data_directories, archetype_location_repository_,
        type_repository_, options.compatibility_mode()),
    mapping_repository_(msrp), formatting_repository_(frp), prober_(prober),
    intra_backend_segment_properties_(intra_backend_segment_properties),
    writer_(writer) {}

context::~context() {
    prober_.end_probing();
}

const std::vector<boost::filesystem::path>& context::data_directories() const {
    return data_directories_;
}

const options& context::transform_options() const {
    return options_;
}

const annotations::archetype_location_repository&
context::archetype_location_repository() const {
    return archetype_location_repository_;
}

const annotations::type_repository& context::type_repository() const {
    return type_repository_;
}

const annotations::annotation_factory& context::annotation_factory() const {
    return annotation_factory_;
}

const helpers::mapping_set_repository& context::mapping_repository() const {
    return mapping_repository_;
}

const masd::dogen::extraction::repository& context::formatting_repository() const {
    return formatting_repository_;
}

const probing::prober& context::prober() const {
    return prober_;
}

const std::unordered_map<std::string,
                         meta_model::intra_backend_segment_properties>&
context::intra_backend_segment_properties() const {
    return intra_backend_segment_properties_;
}

const helpers::artefact_writer_interface& context::artefact_writer() const {
    return *writer_;
}

}

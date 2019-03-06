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
#include "masd.dogen.tracing/types/tracer.hpp"
#include "masd.dogen.extraction/types/repository.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.annotations/types/type_repository.hpp"
#include "masd.dogen.annotations/types/annotation_factory.hpp"
#include "masd.dogen.annotations/types/annotation_expander.hpp"
#include "masd.dogen.coding/types/helpers/mapping_set_repository.hpp"
#include "masd.dogen.annotations/types/archetype_location_repository.hpp"

namespace masd::dogen::coding::transforms {

context::context(
    const boost::shared_ptr<masd::dogen::annotations::type_repository>& type_repository,
    const boost::shared_ptr<masd::dogen::annotations::archetype_location_repository>& archetype_location_repository,
    const boost::shared_ptr<masd::dogen::annotations::annotation_factory>& annotation_factory,
    const boost::shared_ptr<masd::dogen::annotations::annotation_expander>& annotation_expander,
    const boost::shared_ptr<masd::dogen::coding::helpers::mapping_set_repository>& mapping_repository,
    const boost::shared_ptr<masd::dogen::tracing::tracer>& tracer)
    : type_repository_(type_repository),
      archetype_location_repository_(archetype_location_repository),
      annotation_factory_(annotation_factory),
      annotation_expander_(annotation_expander),
      mapping_repository_(mapping_repository),
      tracer_(tracer) { }

const boost::shared_ptr<masd::dogen::annotations::type_repository>& context::type_repository() const {
    return type_repository_;
}

boost::shared_ptr<masd::dogen::annotations::type_repository>& context::type_repository() {
    return type_repository_;
}

void context::type_repository(const boost::shared_ptr<masd::dogen::annotations::type_repository>& v) {
    type_repository_ = v;
}

void context::type_repository(const boost::shared_ptr<masd::dogen::annotations::type_repository>&& v) {
    type_repository_ = std::move(v);
}

const boost::shared_ptr<masd::dogen::annotations::archetype_location_repository>& context::archetype_location_repository() const {
    return archetype_location_repository_;
}

boost::shared_ptr<masd::dogen::annotations::archetype_location_repository>& context::archetype_location_repository() {
    return archetype_location_repository_;
}

void context::archetype_location_repository(const boost::shared_ptr<masd::dogen::annotations::archetype_location_repository>& v) {
    archetype_location_repository_ = v;
}

void context::archetype_location_repository(const boost::shared_ptr<masd::dogen::annotations::archetype_location_repository>&& v) {
    archetype_location_repository_ = std::move(v);
}

const boost::shared_ptr<masd::dogen::annotations::annotation_factory>& context::annotation_factory() const {
    return annotation_factory_;
}

boost::shared_ptr<masd::dogen::annotations::annotation_factory>& context::annotation_factory() {
    return annotation_factory_;
}

void context::annotation_factory(const boost::shared_ptr<masd::dogen::annotations::annotation_factory>& v) {
    annotation_factory_ = v;
}

void context::annotation_factory(const boost::shared_ptr<masd::dogen::annotations::annotation_factory>&& v) {
    annotation_factory_ = std::move(v);
}

const boost::shared_ptr<masd::dogen::annotations::annotation_expander>& context::annotation_expander() const {
    return annotation_expander_;
}

boost::shared_ptr<masd::dogen::annotations::annotation_expander>& context::annotation_expander() {
    return annotation_expander_;
}

void context::annotation_expander(const boost::shared_ptr<masd::dogen::annotations::annotation_expander>& v) {
    annotation_expander_ = v;
}

void context::annotation_expander(const boost::shared_ptr<masd::dogen::annotations::annotation_expander>&& v) {
    annotation_expander_ = std::move(v);
}

const boost::shared_ptr<masd::dogen::coding::helpers::mapping_set_repository>& context::mapping_repository() const {
    return mapping_repository_;
}

boost::shared_ptr<masd::dogen::coding::helpers::mapping_set_repository>& context::mapping_repository() {
    return mapping_repository_;
}

void context::mapping_repository(const boost::shared_ptr<masd::dogen::coding::helpers::mapping_set_repository>& v) {
    mapping_repository_ = v;
}

void context::mapping_repository(const boost::shared_ptr<masd::dogen::coding::helpers::mapping_set_repository>&& v) {
    mapping_repository_ = std::move(v);
}

const boost::shared_ptr<masd::dogen::tracing::tracer>& context::tracer() const {
    return tracer_;
}

boost::shared_ptr<masd::dogen::tracing::tracer>& context::tracer() {
    return tracer_;
}

void context::tracer(const boost::shared_ptr<masd::dogen::tracing::tracer>& v) {
    tracer_ = v;
}

void context::tracer(const boost::shared_ptr<masd::dogen::tracing::tracer>&& v) {
    tracer_ = std::move(v);
}

}

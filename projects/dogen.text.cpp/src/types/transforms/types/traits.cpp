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
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"

namespace dogen::text::cpp::transforms::types {

std::string traits::facet_qn() {
    static std::string r(cpp::traits::backend_qn() + ".types");
    return r;
}

std::string traits::facet_sn() {
    static std::string r("types");
    return r;
}

std::string traits::canonical_archetype() {
    static std::string r(traits::facet_qn() + ".canonical_archetype");
    return r;
}

std::string traits::class_header_archetype_qn() {
    static std::string r(traits::facet_qn() + ".class_header");
    return r;
}

std::string traits::class_header_archetype_sn() {
    static std::string r("class_header");
    return r;
}

std::string traits::class_forward_declarations_archetype_qn() {
    static std::string r(traits::facet_qn() + ".class_forward_declarations");
    return r;
}

std::string traits::class_forward_declarations_archetype_sn() {
    static std::string r("class_forward_declarations");
    return r;
}

std::string traits::archetype_class_header_transform_archetype_qn(){
    static std::string r(traits::facet_qn() + ".archetype_class_header_transform");
    return r;
}

std::string traits::archetype_class_header_transform_archetype_sn(){
    static std::string r("archetype_class_header_transform");
    return r;
}

std::string traits::archetype_class_header_factory_archetype_qn(){
    static std::string r(traits::facet_qn() + ".archetype_class_header_factory");
    return r;
}

std::string traits::archetype_class_header_factory_archetype_sn(){
    static std::string r("archetype_class_header_factory");
    return r;
}

std::string traits::archetype_class_implementation_transform_archetype_qn(){
    static std::string r(traits::facet_qn() + ".archetype_class_implementation_transform");
    return r;
}

std::string traits::archetype_class_implementation_transform_archetype_sn(){
    static std::string r("archetype_class_implementation_transform");
    return r;
}

std::string traits::archetype_class_implementation_factory_archetype_qn(){
    static std::string r(traits::facet_qn() + ".archetype_class_implementation_factory");
    return r;
}

std::string traits::archetype_class_implementation_factory_archetype_sn(){
    static std::string r("archetype_class_implementation_factory");
    return r;
}

std::string traits::facet_class_header_transform_archetype_qn(){
    static std::string r(traits::facet_qn() + ".facet_class_header_transform");
    return r;
}

std::string traits::facet_class_header_transform_archetype_sn(){
    static std::string r("facet_class_header_transform");
    return r;
}

std::string traits::facet_class_header_factory_archetype_qn(){
    static std::string r(traits::facet_qn() + ".facet_class_header_factory");
    return r;
}

std::string traits::facet_class_header_factory_archetype_sn(){
    static std::string r("facet_class_header_factory");
    return r;
}

std::string traits::facet_class_implementation_transform_archetype_qn(){
    static std::string r(traits::facet_qn() + ".facet_class_implementation_transform");
    return r;
}

std::string traits::facet_class_implementation_transform_archetype_sn(){
    static std::string r("facet_class_implementation_transform");
    return r;
}

std::string traits::facet_class_implementation_factory_archetype_qn(){
    static std::string r(traits::facet_qn() + ".facet_class_implementation_factory");
    return r;
}

std::string traits::facet_class_implementation_factory_archetype_sn(){
    static std::string r("facet_class_implementation_factory");
    return r;
}

std::string traits::backend_class_header_transform_archetype_qn(){
    static std::string r(traits::facet_qn() +  ".backend_class_header_transform");
    return r;
}

std::string traits::backend_class_header_transform_archetype_sn(){
    static std::string r("backend_class_header_transform");
    return r;
}

std::string traits::backend_class_header_factory_archetype_qn(){
    static std::string r(traits::facet_qn() +  ".backend_class_header_factory");
    return r;
}

std::string traits::backend_class_header_factory_archetype_sn(){
    static std::string r("backend_class_header_factory");
    return r;
}

std::string traits::backend_class_implementation_transform_archetype_qn(){
    static std::string r(traits::facet_qn() + "backend_class_implementation_transform");
    return r;
}

std::string traits::backend_class_implementation_transform_archetype_sn(){
    static std::string r("backend_class_implementation_transform");
    return r;
}

std::string traits::backend_class_implementation_factory_archetype_qn(){
    static std::string r(traits::facet_qn() + "backend_class_implementation_factory");
    return r;
}

std::string traits::backend_class_implementation_factory_archetype_sn(){
    static std::string r("backend_class_implementation_factory");
    return r;
}

std::string traits::part_class_header_transform_archetype_qn(){
    static std::string r(traits::facet_qn() +  ".part_class_header_transform");
    return r;
}

std::string traits::part_class_header_transform_archetype_sn(){
    static std::string r("part_class_header_transform");
    return r;
}

std::string traits::part_class_implementation_transform_archetype_qn(){
    static std::string r(traits::facet_qn() + "part_class_implementation_transform");
    return r;
}

std::string traits::part_class_implementation_transform_archetype_sn(){
    static std::string r("part_class_implementation_transform");
    return r;
}

std::string traits::archetype_kind_class_header_transform_archetype_qn(){
    static std::string r(traits::facet_qn() +  ".archetype_kind_class_header_transform");
    return r;
}

std::string traits::archetype_kind_class_header_transform_archetype_sn(){
    static std::string r("archetype_kind_class_header_transform");
    return r;
}

std::string traits::archetype_kind_class_implementation_transform_archetype_qn(){
    static std::string r(traits::facet_qn() + "archetype_kind_class_implementation_transform");
    return r;
}

std::string traits::archetype_kind_class_implementation_transform_archetype_sn(){
    static std::string r("archetype_kind_class_implementation_transform");
    return r;
}

std::string traits::visitor_forward_declarations_archetype_qn() {
    static std::string r(traits::facet_qn() + ".visitor_forward_declarations");
    return r;
}

std::string traits::visitor_forward_declarations_archetype_sn() {
    static std::string r("visitor_forward_declarations");
    return r;
}

std::string traits::primitive_forward_declarations_archetype_qn() {
    static std::string r(traits::facet_qn() + ".primitive_forward_declarations");
    return r;
}

std::string traits::primitive_forward_declarations_archetype_sn() {
    static std::string r("primitive_forward_declarations");
    return r;
}

std::string traits::class_implementation_archetype_qn() {
    static std::string r(traits::facet_qn() + ".class_implementation");
    return r;
}

std::string traits::class_implementation_archetype_sn() {
    static std::string r("class_implementation");
    return r;
}

std::string traits::enum_header_archetype_qn() {
    static std::string r(traits::facet_qn() + ".enum_header");
    return r;
}

std::string traits::enum_header_archetype_sn() {
    static std::string r("enum_header");
    return r;
}

std::string traits::exception_header_archetype_qn() {
    static std::string r(traits::facet_qn() + ".exception_header");
    return r;
}

std::string traits::exception_header_archetype_sn() {
    static std::string r("exception_header");
    return r;
}

std::string traits::namespace_header_archetype_qn() {
    static std::string r(traits::facet_qn() + ".namespace_header");
    return r;
}

std::string traits::namespace_header_archetype_sn() {
    static std::string r("namespace_header");
    return r;
}

std::string traits::visitor_header_archetype_qn() {
    static std::string r(traits::facet_qn() + ".visitor_header");
    return r;
}

std::string traits::visitor_header_archetype_sn() {
    static std::string r("visitor_header");
    return r;
}

std::string traits::builtin_header_archetype_qn() {
    static std::string r(traits::facet_qn() + ".builtin_header");
    return r;
}

std::string traits::builtin_header_archetype_sn() {
    static std::string r("builtin_header");
    return r;
}

std::string traits::primitive_header_archetype_qn() {
    static std::string r(traits::facet_qn() + ".primitive_header");
    return r;
}

std::string traits::primitive_header_archetype_sn() {
    static std::string r("primitive_header");
    return r;
}

std::string traits::primitive_implementation_archetype_qn() {
    static std::string r(traits::facet_qn() + ".primitive_implementation");
    return r;
}

std::string traits::primitive_implementation_archetype_sn() {
    static std::string r("primitive_implementation");
    return r;
}

std::string traits::feature_template_bundle_header_archetype_qn() {
    static std::string r(traits::facet_qn() + ".feature_template_bundle_header");
    return r;
}

std::string traits::feature_template_bundle_header_archetype_sn() {
    static std::string r("feature_template_bundle_header");
    return r;
}

std::string traits::feature_template_bundle_implementation_archetype_qn() {
    static std::string r(traits::facet_qn() + ".feature_template_bundle_implementation");
    return r;
}

std::string traits::feature_template_bundle_implementation_archetype_sn() {
    static std::string r("feature_template_bundle_implementation");
    return r;
}

std::string traits::feature_bundle_header_archetype_qn() {
    static std::string r(traits::facet_qn() + ".feature_bundle_header");
    return r;
}

std::string traits::feature_bundle_header_archetype_sn() {
    static std::string r("feature_bundle_header");
    return r;
}

std::string traits::feature_bundle_implementation_archetype_qn() {
    static std::string r(traits::facet_qn() + ".feature_bundle_implementation");
    return r;
}

std::string traits::feature_bundle_implementation_archetype_sn() {
    static std::string r("feature_bundle_implementation");
    return r;
}

std::string traits::variability_initializer_header_archetype_qn() {
    static std::string r(traits::facet_qn() + ".variability_initializer_header");
    return r;
}

std::string traits::variability_initializer_header_archetype_sn() {
    static std::string r("variability_initializer_header");
    return r;
}

std::string traits::variability_initializer_implementation_archetype_qn() {
    static std::string r(traits::facet_qn() +
        ".variability_initializer_implementation");
    return r;
}

std::string traits::variability_initializer_implementation_archetype_sn() {
    static std::string r("variability_initializer_implementation");
    return r;
}

std::string traits::main_archetype_qn() {
    static std::string r(traits::facet_qn() + ".main");
    return r;
}

std::string traits::main_archetype_sn() {
    static std::string r("main");
    return r;
}

}

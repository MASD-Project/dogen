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
#include "dogen/test_models/northwind/types/products.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

products::products()
    : unit_price_(static_cast<double>(0)),
      units_in_stock_(static_cast<int>(0)),
      units_in_order_(static_cast<int>(0)),
      reorder_level_(static_cast<int>(0)),
      discontinued_(static_cast<bool>(0)) { }

products::products(
    const dogen::test_models::northwind::product_id& product_id,
    const std::string& product_name,
    const dogen::test_models::northwind::supplier_id& supplier_id,
    const dogen::test_models::northwind::category_id& category_id,
    const std::string& quantity_per_unit,
    const double unit_price,
    const int units_in_stock,
    const int units_in_order,
    const int reorder_level,
    const bool discontinued)
    : product_id_(product_id),
      product_name_(product_name),
      supplier_id_(supplier_id),
      category_id_(category_id),
      quantity_per_unit_(quantity_per_unit),
      unit_price_(unit_price),
      units_in_stock_(units_in_stock),
      units_in_order_(units_in_order),
      reorder_level_(reorder_level),
      discontinued_(discontinued) { }

void products::swap(products& other) noexcept {
    using std::swap;
    swap(product_id_, other.product_id_);
    swap(product_name_, other.product_name_);
    swap(supplier_id_, other.supplier_id_);
    swap(category_id_, other.category_id_);
    swap(quantity_per_unit_, other.quantity_per_unit_);
    swap(unit_price_, other.unit_price_);
    swap(units_in_stock_, other.units_in_stock_);
    swap(units_in_order_, other.units_in_order_);
    swap(reorder_level_, other.reorder_level_);
    swap(discontinued_, other.discontinued_);
}

bool products::operator==(const products& rhs) const {
    return product_id_ == rhs.product_id_ &&
        product_name_ == rhs.product_name_ &&
        supplier_id_ == rhs.supplier_id_ &&
        category_id_ == rhs.category_id_ &&
        quantity_per_unit_ == rhs.quantity_per_unit_ &&
        unit_price_ == rhs.unit_price_ &&
        units_in_stock_ == rhs.units_in_stock_ &&
        units_in_order_ == rhs.units_in_order_ &&
        reorder_level_ == rhs.reorder_level_ &&
        discontinued_ == rhs.discontinued_;
}

products& products::operator=(products other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::northwind::product_id& products::product_id() const {
    return product_id_;
}

dogen::test_models::northwind::product_id& products::product_id() {
    return product_id_;
}

void products::product_id(const dogen::test_models::northwind::product_id& v) {
    product_id_ = v;
}

void products::product_id(const dogen::test_models::northwind::product_id&& v) {
    product_id_ = std::move(v);
}

const std::string& products::product_name() const {
    return product_name_;
}

std::string& products::product_name() {
    return product_name_;
}

void products::product_name(const std::string& v) {
    product_name_ = v;
}

void products::product_name(const std::string&& v) {
    product_name_ = std::move(v);
}

const dogen::test_models::northwind::supplier_id& products::supplier_id() const {
    return supplier_id_;
}

dogen::test_models::northwind::supplier_id& products::supplier_id() {
    return supplier_id_;
}

void products::supplier_id(const dogen::test_models::northwind::supplier_id& v) {
    supplier_id_ = v;
}

void products::supplier_id(const dogen::test_models::northwind::supplier_id&& v) {
    supplier_id_ = std::move(v);
}

const dogen::test_models::northwind::category_id& products::category_id() const {
    return category_id_;
}

dogen::test_models::northwind::category_id& products::category_id() {
    return category_id_;
}

void products::category_id(const dogen::test_models::northwind::category_id& v) {
    category_id_ = v;
}

void products::category_id(const dogen::test_models::northwind::category_id&& v) {
    category_id_ = std::move(v);
}

const std::string& products::quantity_per_unit() const {
    return quantity_per_unit_;
}

std::string& products::quantity_per_unit() {
    return quantity_per_unit_;
}

void products::quantity_per_unit(const std::string& v) {
    quantity_per_unit_ = v;
}

void products::quantity_per_unit(const std::string&& v) {
    quantity_per_unit_ = std::move(v);
}

double products::unit_price() const {
    return unit_price_;
}

void products::unit_price(const double v) {
    unit_price_ = v;
}

int products::units_in_stock() const {
    return units_in_stock_;
}

void products::units_in_stock(const int v) {
    units_in_stock_ = v;
}

int products::units_in_order() const {
    return units_in_order_;
}

void products::units_in_order(const int v) {
    units_in_order_ = v;
}

int products::reorder_level() const {
    return reorder_level_;
}

void products::reorder_level(const int v) {
    reorder_level_ = v;
}

bool products::discontinued() const {
    return discontinued_;
}

void products::discontinued(const bool v) {
    discontinued_ = v;
}

} } }

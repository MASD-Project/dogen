/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/dia/domain/composite.hpp"
#include "dogen/dia/domain/attribute.hpp"

namespace boost {

template<typename T>
inline bool operator==(const boost::shared_ptr<T>& lhs,
    const boost::shared_ptr<T>& rhs) {
    return
        (!lhs.get() && !rhs.get()) ||
        ((lhs.get() && rhs.get()) && (*lhs == *rhs));
}

}

namespace dogen {
namespace dia {

composite::
composite(std::string type, std::vector<boost::shared_ptr<attribute> > value,
    boost::shared_ptr<composite> inner_composite)
    : type_(type), value_(value), inner_composite_(inner_composite) { }

std::vector<boost::shared_ptr<attribute> > composite::value() const {
    return value_;
}

void composite::value(std::vector<boost::shared_ptr<attribute> > value) {
    value_ = value;
}

boost::shared_ptr<composite> composite::inner_composite() const {
    return inner_composite_;
}

void composite::inner_composite(boost::shared_ptr<composite> value) {
    inner_composite_ = value;
}

bool composite::operator==(const dogen::dia::composite& value) const {
    return
        type_ == value.type() &&
        value_ == value.value() &&
        inner_composite_ == value.inner_composite();
}

} }

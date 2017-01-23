#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "Zeta/serialization/String_ser.hpp"
#include "Phi/serialization/TestType_ser.hpp"

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const Phi::TestType& v,
    const unsigned int /*version*/) {
    ar << make_nvp("Version", v.Version_);
    ar << make_nvp("AField", v.AField_);
}

template<typename Archive>
void load(Archive& ar,
    Phi::TestType& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("Version", v.Version_);
    ar >> make_nvp("AField", v.AField_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const Phi::TestType& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, Phi::TestType& v, unsigned int version);

template void save(archive::text_oarchive& ar, const Phi::TestType& v, unsigned int version);
template void load(archive::text_iarchive& ar, Phi::TestType& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const Phi::TestType& v, unsigned int version);
template void load(archive::binary_iarchive& ar, Phi::TestType& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const Phi::TestType& v, unsigned int version);
template void load(archive::xml_iarchive& ar, Phi::TestType& v, unsigned int version);

} }

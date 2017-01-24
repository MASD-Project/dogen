#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "Phi/serialization/Date_ser.hpp"
#include "Zeta/serialization/ExternalModelTest_ser.hpp"

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const Zeta::ExternalModelTest& v,
    const unsigned int /*version*/) {
    ar << make_nvp("DateTest", v.DateTest_);
    ar << make_nvp("BinariesTest", v.BinariesTest_);
    ar << make_nvp("CollectionOfCollectionTest", v.CollectionOfCollectionTest_);
    ar << make_nvp("CollectionOfCollectionOfCollectionTest", v.CollectionOfCollectionOfCollectionTest_);
}

template<typename Archive>
void load(Archive& ar,
    Zeta::ExternalModelTest& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("DateTest", v.DateTest_);
    ar >> make_nvp("BinariesTest", v.BinariesTest_);
    ar >> make_nvp("CollectionOfCollectionTest", v.CollectionOfCollectionTest_);
    ar >> make_nvp("CollectionOfCollectionOfCollectionTest", v.CollectionOfCollectionOfCollectionTest_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const Zeta::ExternalModelTest& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, Zeta::ExternalModelTest& v, unsigned int version);

template void save(archive::text_oarchive& ar, const Zeta::ExternalModelTest& v, unsigned int version);
template void load(archive::text_iarchive& ar, Zeta::ExternalModelTest& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const Zeta::ExternalModelTest& v, unsigned int version);
template void load(archive::binary_iarchive& ar, Zeta::ExternalModelTest& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const Zeta::ExternalModelTest& v, unsigned int version);
template void load(archive::xml_iarchive& ar, Zeta::ExternalModelTest& v, unsigned int version);

} }

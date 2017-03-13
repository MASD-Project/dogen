// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_TEST_MODELS_NORTHWIND_ODB_EMPLOYEES_ODB_ORACLE_HXX
#define DOGEN_TEST_MODELS_NORTHWIND_ODB_EMPLOYEES_ODB_ORACLE_HXX

// Begin prologue.
//
#include <odb/boost/version.hxx>
#if ODB_BOOST_VERSION != 2040000 // 2.4.0
#  error ODB and C++ compilers see different libodb-boost interface versions
#endif
#include <boost/shared_ptr.hpp>
#include <odb/boost/smart-ptr/pointer-traits.hxx>
#include <odb/boost/smart-ptr/wrapper-traits.hxx>
#include <odb/boost/optional/wrapper-traits.hxx>
#include <odb/boost/unordered/container-traits.hxx>
#include <odb/boost/date-time/oracle/gregorian-traits.hxx>
#include <odb/boost/date-time/oracle/posix-time-traits.hxx>
#include <odb/boost/multi-index/container-traits.hxx>
#include <odb/boost/uuid/oracle/uuid-traits.hxx>
//
// End prologue.

#include <odb/version.hxx>

#if (ODB_VERSION != 20400UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "dogen/test_models/northwind/types/employees.hpp"

#include "dogen/test_models/northwind/odb/employee_id-odb-oracle.hxx"

#include "dogen/test_models/northwind/odb/employees-odb.hxx"

#include <odb/details/buffer.hxx>

#include <odb/oracle/version.hxx>
#include <odb/oracle/forward.hxx>
#include <odb/oracle/binding.hxx>
#include <odb/oracle/oracle-types.hxx>
#include <odb/oracle/query.hxx>

namespace odb
{
  // employees
  //
  template <typename A>
  struct query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >
  {
    // employee_id
    //
    struct employee_id_class_
    {
      employee_id_class_ ()
      {
      }

      // value
      //
      typedef
      oracle::query_column<
        oracle::value_traits<
          int,
          oracle::id_int32 >::query_type,
        oracle::id_int32 >
      value_type_;

      static const value_type_ value;
    };

    static const employee_id_class_ employee_id;

    // last_name
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    last_name_type_;

    static const last_name_type_ last_name;

    // first_name
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    first_name_type_;

    static const first_name_type_ first_name;

    // title
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    title_type_;

    static const title_type_ title;

    // title_of_courtesy
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    title_of_courtesy_type_;

    static const title_of_courtesy_type_ title_of_courtesy;

    // birth_date
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::boost::gregorian::date,
        oracle::id_date >::query_type,
      oracle::id_date >
    birth_date_type_;

    static const birth_date_type_ birth_date;

    // hire_date
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::boost::gregorian::date,
        oracle::id_date >::query_type,
      oracle::id_date >
    hire_date_type_;

    static const hire_date_type_ hire_date;

    // address
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    address_type_;

    static const address_type_ address;

    // city
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    city_type_;

    static const city_type_ city;

    // region
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    region_type_;

    static const region_type_ region;

    // postal_code
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    postal_code_type_;

    static const postal_code_type_ postal_code;

    // country
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    country_type_;

    static const country_type_ country;

    // home_phone
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    home_phone_type_;

    static const home_phone_type_ home_phone;

    // extension
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    extension_type_;

    static const extension_type_ extension;

    // photo
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::vector< char >,
        oracle::id_blob >::query_type,
      oracle::id_blob >
    photo_type_;

    static const photo_type_ photo;

    // notes
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    notes_type_;

    static const notes_type_ notes;

    // reports_to
    //
    struct reports_to_class_
    {
      reports_to_class_ ()
      {
      }

      // value
      //
      typedef
      oracle::query_column<
        oracle::value_traits<
          int,
          oracle::id_int32 >::query_type,
        oracle::id_int32 >
      value_type_;

      static const value_type_ value;
    };

    static const reports_to_class_ reports_to;

    // photo_path
    //
    typedef
    oracle::query_column<
      oracle::value_traits<
        ::std::string,
        oracle::id_string >::query_type,
      oracle::id_string >
    photo_path_type_;

    static const photo_path_type_ photo_path;
  };

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::employee_id_class_::value_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::employee_id_class_::
  value (A::table_name, "\"EMPLOYEE_ID\"", 0, 10);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::employee_id_class_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::employee_id;

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::last_name_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::
  last_name (A::table_name, "\"LAST_NAME\"", 0, 512);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::first_name_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::
  first_name (A::table_name, "\"FIRST_NAME\"", 0, 512);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::title_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::
  title (A::table_name, "\"TITLE\"", 0, 512);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::title_of_courtesy_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::
  title_of_courtesy (A::table_name, "\"TITLE_OF_COURTESY\"", 0, 512);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::birth_date_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::
  birth_date (A::table_name, "\"BIRTH_DATE\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::hire_date_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::
  hire_date (A::table_name, "\"HIRE_DATE\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::address_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::
  address (A::table_name, "\"ADDRESS\"", 0, 512);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::city_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::
  city (A::table_name, "\"CITY\"", 0, 512);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::region_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::
  region (A::table_name, "\"REGION\"", 0, 512);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::postal_code_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::
  postal_code (A::table_name, "\"POSTAL_CODE\"", 0, 512);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::country_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::
  country (A::table_name, "\"COUNTRY\"", 0, 512);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::home_phone_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::
  home_phone (A::table_name, "\"HOME_PHONE\"", 0, 512);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::extension_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::
  extension (A::table_name, "\"EXTENSION\"", 0, 512);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::photo_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::
  photo (A::table_name, "\"PHOTO\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::notes_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::
  notes (A::table_name, "\"NOTES\"", 0, 512);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::reports_to_class_::value_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::reports_to_class_::
  value (A::table_name, "\"REPORTS_TO\"", 0, 10);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::reports_to_class_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::reports_to;

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::photo_path_type_
  query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >::
  photo_path (A::table_name, "\"PHOTO_PATH\"", 0, 512);

  template <typename A>
  struct pointer_query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >:
    query_columns< ::dogen::test_models::northwind::employees, id_oracle, A >
  {
  };

  template <>
  class access::object_traits_impl< ::dogen::test_models::northwind::employees, id_oracle >:
    public access::object_traits< ::dogen::test_models::northwind::employees >
  {
    public:
    static const std::size_t batch = 1UL;

    struct id_image_type
    {
      composite_value_traits< ::dogen::test_models::northwind::employee_id, id_oracle >::image_type id_value;

      std::size_t version;
    };

    struct image_type
    {
      // employee_id_
      //
      composite_value_traits< ::dogen::test_models::northwind::employee_id, id_oracle >::image_type employee_id_value;

      // last_name_
      //
      char last_name_value[512];
      ub2 last_name_size;
      sb2 last_name_indicator;

      // first_name_
      //
      char first_name_value[512];
      ub2 first_name_size;
      sb2 first_name_indicator;

      // title_
      //
      char title_value[512];
      ub2 title_size;
      sb2 title_indicator;

      // title_of_courtesy_
      //
      char title_of_courtesy_value[512];
      ub2 title_of_courtesy_size;
      sb2 title_of_courtesy_indicator;

      // birth_date_
      //
      char birth_date_value[7];
      sb2 birth_date_indicator;

      // hire_date_
      //
      char hire_date_value[7];
      sb2 hire_date_indicator;

      // address_
      //
      char address_value[512];
      ub2 address_size;
      sb2 address_indicator;

      // city_
      //
      char city_value[512];
      ub2 city_size;
      sb2 city_indicator;

      // region_
      //
      char region_value[512];
      ub2 region_size;
      sb2 region_indicator;

      // postal_code_
      //
      char postal_code_value[512];
      ub2 postal_code_size;
      sb2 postal_code_indicator;

      // country_
      //
      char country_value[512];
      ub2 country_size;
      sb2 country_indicator;

      // home_phone_
      //
      char home_phone_value[512];
      ub2 home_phone_size;
      sb2 home_phone_indicator;

      // extension_
      //
      char extension_value[512];
      ub2 extension_size;
      sb2 extension_indicator;

      // photo_
      //
      mutable oracle::lob_callback photo_callback;
      sb2 photo_indicator;
      oracle::lob photo_lob;

      // notes_
      //
      char notes_value[512];
      ub2 notes_size;
      sb2 notes_indicator;

      // reports_to_
      //
      composite_value_traits< ::dogen::test_models::northwind::employee_id, id_oracle >::image_type reports_to_value;

      // photo_path_
      //
      char photo_path_value[512];
      ub2 photo_path_size;
      sb2 photo_path_indicator;

      std::size_t version;

      oracle::change_callback change_callback_;

      oracle::change_callback*
      change_callback ()
      {
        return &change_callback_;
      }
    };

    struct extra_statement_cache_type;

    using object_traits<object_type>::id;

    static id_type
    id (const image_type&);

    static void
    bind (oracle::bind*,
          image_type&,
          oracle::statement_kind);

    static void
    bind (oracle::bind*, id_image_type&);

    static void
    init (image_type&,
          const object_type&,
          oracle::statement_kind);

    static void
    init (object_type&,
          const image_type&,
          database*);

    static void
    init (id_image_type&, const id_type&);

    typedef oracle::object_statements<object_type> statements_type;

    typedef oracle::query_base query_base_type;

    static const std::size_t column_count = 18UL;
    static const std::size_t id_column_count = 1UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char find_statement[];
    static const char update_statement[];
    static const char erase_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, const object_type&);

    static pointer_type
    find (database&, const id_type&);

    static bool
    find (database&, const id_type&, object_type&);

    static bool
    reload (database&, object_type&);

    static void
    update (database&, const object_type&);

    static void
    erase (database&, const id_type&);

    static void
    erase (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    public:
    static bool
    find_ (statements_type&,
           const id_type*);

    static void
    load_ (statements_type&,
           object_type&,
           bool reload);
  };

  // employees
  //
}

#include "dogen/test_models/northwind/odb/employees-odb-oracle.ixx"

#include <odb/post.hxx>

#endif // DOGEN_TEST_MODELS_NORTHWIND_ODB_EMPLOYEES_ODB_ORACLE_HXX

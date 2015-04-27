// vim: sw=3 ts=3 expandtab cindent
#ifndef NFIRSPP_BUSINESS_ADDRESS_H__
#define NFIRSPP_BUSINESS_ADDRESS_H__

#include "business/bits/value_component.h"
#include <utility>

namespace firepp {
namespace business {

namespace details_ {

struct street_name_tag final : length_validation_and_assignment {
   static inline const char * type_name() noexcept {
      return "street name";
   }
};


struct street_number_tag final : length_validation_and_assignment {
   static inline const char * type_name() noexcept {
      return "street number";
   }
};


struct street_city_tag final : length_validation_and_assignment {
   static inline const char * type_name() noexcept {
      return "city";
   }
};


struct apartment_tag final : length_validation_and_assignment {
   static inline const char * type_name() noexcept {
      return "apartment";
   }
};


struct zip_code_tag final : regex_validation_and_assignment<zip_code_tag, std::index_sequence<1, 3>> {
   static inline const std::regex & get_regex() {
      thread_local std::regex zip_code_regex{"^([0-9]{5})([-.]?([0-9]{4}))?$"};
      return zip_code_regex;
   }

   static inline const char * type_name() noexcept {
      return "zip code";
   }
};


struct census_track_tag final : regex_validation_and_assignment<census_track_tag, std::index_sequence<1, 2>> {
   static inline const std::regex & get_regex() {
      thread_local std::regex census_track_regex{"^([0-9]{4})[-.]?([0-9]{2})$"};
      return census_track_regex;
   }

   static inline const char * type_name() noexcept {
      return "zip code";
   }
};


struct email_address_tag final : regex_validation_and_assignment<email_address_tag, std::index_sequence<0>> {
   static inline const std::regex & get_regex() {
      thread_local std::regex email_address_regex{"^[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}$", std::regex_constants::icase};
      return email_address_regex;
   }

   static inline const char * type_name() noexcept {
      return "email address";
   }
};


struct social_security_number_tag final : regex_validation_and_assignment<social_security_number_tag, std::index_sequence<1, 2, 3>> {
   static inline const std::regex & get_regex() {
      thread_local std::regex social_security_number_regex{"^([0-9]{3})[-.]?([0-9]{2})[-.]?([0-9]{4})$"};
      return social_security_number_regex;
   }

   static inline const char * type_name() noexcept {
      return "social security number";
   }
};

}


using street_name = details_::value_component<details_::street_name_tag, 30>;
using street_number = details_::value_component<details_::street_number_tag, 8>;
using us_city = details_::value_component<details_::street_city_tag, 20>;
using apartment = details_::value_component<details_::apartment_tag, 15>;
using us_zip_code = details_::value_component<details_::zip_code_tag, 9>;
using census_track = details_::value_component<details_::census_track_tag, 6>;
using email_address = details_::value_component<details_::email_address_tag, 254>;
using social_security_number = details_::value_component<details_::social_security_number_tag, 9>;


class street_direction final : public details_::abbreviated_and_full<street_direction, 2> {
public:
   using details_::abbreviated_and_full<street_direction, 2>::abbreviated_and_full;

   static const street_direction east;
   static const street_direction north;
   static const street_direction west;
   static const street_direction south;
   static const street_direction northeast;
   static const street_direction northwest;
   static const street_direction southwest;
   static const street_direction southeast;

   static inline const char *type_name() noexcept {
      return "street direction";
   }
};


class street_type final : public details_::abbreviated_and_full<street_type, 4> {
public:
   using details_::abbreviated_and_full<street_type, 4>::abbreviated_and_full;

   static const street_type alley;
   static const street_type annex;
   static const street_type arcade;
   static const street_type avenue;
   static const street_type beach;
   static const street_type bend;
   static const street_type bluff;
   static const street_type bluffs;
   static const street_type bottom;
   static const street_type boulevard;
   static const street_type branch;
   static const street_type bridge;
   static const street_type brook;
   static const street_type brooks;
   static const street_type burg;
   static const street_type burgs;
   static const street_type bypass;
   static const street_type camp;
   static const street_type canyon;
   static const street_type cape;
   static const street_type causeway;
   static const street_type center;
   static const street_type centers;
   static const street_type circle;
   static const street_type circles;
   static const street_type cliff;
   static const street_type cliffs;
   static const street_type club;
   static const street_type common;
   static const street_type commons;
   static const street_type corner;
   static const street_type corners;
   static const street_type court;
   static const street_type courts;
   static const street_type cove;
   static const street_type creek;
   static const street_type crescent;
   static const street_type crossing;
   static const street_type crossroad;
   static const street_type crossroads;
   static const street_type curve;
   static const street_type dale;
   static const street_type dam;
   static const street_type divide;
   static const street_type drive;
   static const street_type drives;
   static const street_type estate;
   static const street_type estates;
   static const street_type expressway;
   static const street_type extension;
   static const street_type extensions;
   static const street_type fall;
   static const street_type falls;
   static const street_type ferry;
   static const street_type field;
   static const street_type fields;
   static const street_type flat;
   static const street_type flats;
   static const street_type ford;
   static const street_type fords;
   static const street_type forest;
   static const street_type forge;
   static const street_type forges;
   static const street_type fork;
   static const street_type forks;
   static const street_type fort;
   static const street_type freeway;
   static const street_type garden;
   static const street_type gardens;
   static const street_type gateway;
   static const street_type glen;
   static const street_type glens;
   static const street_type green;
   static const street_type greens;
   static const street_type grove;
   static const street_type groves;
   static const street_type harbor;
   static const street_type harbors;
   static const street_type haven;
   static const street_type heights;
   static const street_type highway;
   static const street_type hill;
   static const street_type hills;
   static const street_type hollow;
   static const street_type inlet;
   static const street_type island;
   static const street_type islands;
   static const street_type isle;
   static const street_type junction;
   static const street_type junctions;
   static const street_type key;
   static const street_type keys;
   static const street_type knoll;
   static const street_type knolls;
   static const street_type lake;
   static const street_type lakes;
   static const street_type landing;
   static const street_type lane;
   static const street_type light;
   static const street_type lights;
   static const street_type loaf;
   static const street_type lock;
   static const street_type locks;
   static const street_type lodge;
   static const street_type loop;
   static const street_type mall;
   static const street_type manor;
   static const street_type manors;
   static const street_type meadow;
   static const street_type meadows;
   static const street_type mews;
   static const street_type mill;
   static const street_type mills;
   static const street_type mission;
   static const street_type motorway;
   static const street_type mount;
   static const street_type mountain;
   static const street_type mountains;
   static const street_type neck;
   static const street_type orchard;
   static const street_type oval;
   static const street_type park;
   static const street_type parkway;
   static const street_type parkways;
   static const street_type pass;
   static const street_type passage;
   static const street_type path;
   static const street_type pike;
   static const street_type pine;
   static const street_type pines;
   static const street_type place;
   static const street_type plaza;
   static const street_type point;
   static const street_type points;
   static const street_type port;
   static const street_type ports;
   static const street_type prairie;
   static const street_type radial;
   static const street_type ramp;
   static const street_type ranch;
   static const street_type rapid;
   static const street_type rapids;
   static const street_type rest;
   static const street_type ridge;
   static const street_type ridges;
   static const street_type river;
   static const street_type road;
   static const street_type roads;
   static const street_type route;
   static const street_type row;
   static const street_type rue;
   static const street_type run;
   static const street_type shoal;
   static const street_type shoals;
   static const street_type shore;
   static const street_type shores;
   static const street_type skyway;
   static const street_type spring;
   static const street_type springs;
   static const street_type spur;
   static const street_type spurs;
   static const street_type square;
   static const street_type squares;
   static const street_type station;
   static const street_type stravenue;
   static const street_type stream;
   static const street_type street;
   static const street_type streets;
   static const street_type summit;
   static const street_type terrace;
   static const street_type throughway;
   static const street_type trace;
   static const street_type track;
   static const street_type trafficway;
   static const street_type trail;
   static const street_type trailer;
   static const street_type tunnel;
   static const street_type turnpike;
   static const street_type underpass;
   static const street_type union_;
   static const street_type unions;
   static const street_type valley;
   static const street_type valleys;
   static const street_type viaduct;
   static const street_type view;
   static const street_type views;
   static const street_type village;
   static const street_type villages;
   static const street_type vile;
   static const street_type vista;
   static const street_type walk;
   static const street_type wall;
   static const street_type way;
   static const street_type well;
   static const street_type wells;

   static inline const char *type_name() noexcept {
      return "street type";
   }
};


class us_state final : public details_::abbreviated_and_full<us_state, 2> {
public:
   using details_::abbreviated_and_full<us_state, 2>::abbreviated_and_full;

   static const us_state AL;
   static const us_state AK;
   static const us_state AZ;
   static const us_state CA;
   static const us_state CO;
   static const us_state CT;
   static const us_state DE;
   static const us_state DC;
   static const us_state FL;
   static const us_state GA;
   static const us_state HI;
   static const us_state ID;
   static const us_state IL;
   static const us_state IN;
   static const us_state IA;
   static const us_state KS;
   static const us_state KY;
   static const us_state LA;
   static const us_state ME;
   static const us_state MD;
   static const us_state MA;
   static const us_state MI;
   static const us_state MN;
   static const us_state MS;
   static const us_state MO;
   static const us_state MT;
   static const us_state NE;
   static const us_state NV;
   static const us_state NH;
   static const us_state NJ;
   static const us_state NY;
   static const us_state NC;
   static const us_state ND;
   static const us_state OH;
   static const us_state OK;
   static const us_state OR;
   static const us_state PA;
   static const us_state RI;
   static const us_state SC;
   static const us_state SD;
   static const us_state TN;
   static const us_state TX;
   static const us_state UT;
   static const us_state VT;
   static const us_state VA;
   static const us_state WA;
   static const us_state WV;
   static const us_state WI;
   static const us_state WY;
   static const us_state AS;
   static const us_state CZ;
   static const us_state DD;
   static const us_state FM;
   static const us_state GU;
   static const us_state MH;
   static const us_state MP;
   static const us_state PW;
   static const us_state PR;
   static const us_state UM;
   static const us_state VI;
   static const us_state OO;

   static inline const char *type_name() noexcept {
      return "US State/Territory";
   }
};


class us_street final {
public:
   inline us_street(const street_direction &p, const street_name &n, const street_type &t, const street_direction &s={}) :
      prefix_(p),
      name_(n),
      type_(t),
      suffix_(s)
   {
      if (!valid()) {
         throw std::invalid_argument{"Not a valid street."};
      }
   }

   inline us_street(const street_name &n, const street_type &t, const street_direction &s={}) :
      us_street{{}, n, t, s}
   {
   }

   inline us_street() = default;
   inline us_street(const us_street &) = default;
   inline us_street(us_street &&) = default;

   inline us_street &  operator =(const us_street &) = default;
   inline us_street & operator =(us_street &&) = default;

   inline bool valid() const noexcept {
      return name().valid() && type().valid();
   }

   inline const street_direction & prefix() const noexcept {
      return prefix_;
   }

   inline const street_name & name() const noexcept {
      return name_;
   }

   inline const street_type & type() const noexcept {
      return type_;
   }

   inline const street_direction & suffix() const noexcept {
      return suffix_;
   }

private:
   street_direction prefix_;
   street_name name_;
   street_type type_;
   street_direction suffix_;
};


class fips_county_code final {
public:
   explicit inline fips_county_code(uint16_t code) :
      value(code)
   {
      using std::to_string;

      if (!valid()) {
         throw std::invalid_argument{'\'' + to_string(code) + "' is not a valid FIPS county code."};
      }
   }

   inline fips_county_code() = default;
   inline fips_county_code(const fips_county_code &) = default;
   inline fips_county_code(fips_county_code &&) = default;

   inline fips_county_code &  operator =(const fips_county_code &) = default;
   inline fips_county_code & operator =(fips_county_code &&) = default;

   inline bool valid() const {
      return (0 < value) && (value < 1000);
   }

   inline uint16_t to_integer() const noexcept {
      return value;
   }

private:
   uint16_t value = 0;
};


class address final {
public:
   inline address(const street_number &n, const us_street &s, const apartment &a, const us_city &c, const us_state &st, const us_zip_code &z) :
      number_(n),
      street_(s),
      apt_(a),
      city_(c),
      state_(st),
      zip_code_(z)
   {
      if (!valid()) {
         throw std::invalid_argument{"Not a valid address."};
      }
   }

   inline address() = default;
   inline address(const address &) = default;
   inline address(address &&) = default;

   inline address &  operator =(const address &) = default;
   inline address & operator =(address &&) = default;

   inline bool valid() const noexcept {
      return number().valid() &&
             street().valid() &&
             city().valid() &&
             state().valid();
   }

   inline const street_number & number() const noexcept {
      return number_;
   }

   inline const us_street & street() const noexcept {
      return street_;
   }

   inline const apartment & apt() const noexcept {
      return apt_;
   }

   inline const us_city & city() const noexcept {
      return city_;
   }

   inline const us_state & state() const noexcept {
      return state_;
   }

   inline const us_zip_code & zip_code() const noexcept {
      return zip_code_;
   }

private:
   street_number number_;
   us_street street_;
   apartment apt_;
   us_city city_;
   us_state state_;
   us_zip_code zip_code_;
};

}
}

#endif

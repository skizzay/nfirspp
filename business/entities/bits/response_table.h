// vim: sw=3 ts=3 expandtab cindent
#pragma once

#include <boost/uuid/uuid.hpp>
#include <algorithm>
#include <vector>

namespace firepp {
namespace business {
namespace details_ {

template<class ResponseType, boost::uuids::uuid ResponseType::*id, class Alloc=std::allocator<ResponseType>>
class response_table final {
public:
   using id_type = boost::uuids::uuid;

   inline ResponseType &get_response(const id_type &responder_id) {
      using std::begin;
      using std::end;
      using std::find_if;

      auto e = end(responses);
      auto i = find_if(begin(responses), e, [responder_id](const ResponseType &response) -> bool {
            return responder_id == response.*id;
         });

      if (i == e) {
         ResponseType response;
         response.*id = responder_id;
         responses.emplace_back(response);
         return responses.back();
      }

      return *i;
   }

   inline std::vector<ResponseType, Alloc> known_ids() const {
      using std::begin;
      using std::end;
      using std::transform;

      std::vector<ResponseType, Alloc> result;
      result.reserve(responses.size());
      transform(begin(responses), end(responses), [](const ResponseType &response) -> const id_type & {
            return response.*id;
         });
      return result;
   }

private:
   std::vector<ResponseType, Alloc> responses;
};

}
}
}

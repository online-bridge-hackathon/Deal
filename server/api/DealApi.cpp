/**
* Deal
* # Introduction A web service that accepts request by APIs and returns 1+ bridge deals  # OpenAPI Specification This API is documented in **OpenAPI format**  # Cross-Origin Resource Sharing This API features Cross-Origin Resource Sharing (CORS) implemented in compliance with  [W3C spec](https://www.w3.org/TR/cors/). And that allows cross-domain communication from the browser. All responses have a wildcard same-origin which makes them completely public and accessible to everyone, including any code on any site.  # Authentication  Forms of authentication:   - API Key 
*
* The version of the OpenAPI document: 0.0.1
* Contact: support@example.com
*
* NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
* https://openapi-generator.tech
* Do not edit the class manually.
*/

#include "DealApi.h"
#include "Helpers.h"

namespace org {
namespace openapitools {
namespace server {
namespace api {

using namespace org::openapitools::server::helpers;
using namespace org::openapitools::server::model;

DealApi::DealApi(std::shared_ptr<Pistache::Rest::Router> rtr) { 
    router = rtr;
}

void DealApi::init() {
    setupRoutes();
}

void DealApi::setupRoutes() {
    using namespace Pistache::Rest;

    Routes::Get(*router, base + "/api/deal", Routes::bind(&DealApi::get_deal_handler, this));

    // Default handler, called when a route is not found
    router->addCustomHandler(Routes::bind(&DealApi::deal_api_default_handler, this));
}

void DealApi::get_deal_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {

    // Getting the query params
    auto seedQuery = request.query().get("seed");
    Pistache::Optional<std::string> seed;
    if(!seedQuery.isEmpty()){
        std::string valueQuery_instance;
        if(fromStringValue(seedQuery.get(), valueQuery_instance)){
            seed = Pistache::Some(valueQuery_instance);
        }
    }
    auto sessionQuery = request.query().get("session");
    Pistache::Optional<int32_t> session;
    if(!sessionQuery.isEmpty()){
        int32_t valueQuery_instance;
        if(fromStringValue(sessionQuery.get(), valueQuery_instance)){
            session = Pistache::Some(valueQuery_instance);
        }
    }
    auto eventQuery = request.query().get("event");
    Pistache::Optional<int32_t> event;
    if(!eventQuery.isEmpty()){
        int32_t valueQuery_instance;
        if(fromStringValue(eventQuery.get(), valueQuery_instance)){
            event = Pistache::Some(valueQuery_instance);
        }
    }
    auto firstBoardQuery = request.query().get("firstBoard");
    Pistache::Optional<int32_t> firstBoard;
    if(!firstBoardQuery.isEmpty()){
        int32_t valueQuery_instance;
        if(fromStringValue(firstBoardQuery.get(), valueQuery_instance)){
            firstBoard = Pistache::Some(valueQuery_instance);
        }
    }
    auto numberOfBoardsQuery = request.query().get("numberOfBoards");
    Pistache::Optional<int32_t> numberOfBoards;
    if(!numberOfBoardsQuery.isEmpty()){
        int32_t valueQuery_instance;
        if(fromStringValue(numberOfBoardsQuery.get(), valueQuery_instance)){
            numberOfBoards = Pistache::Some(valueQuery_instance);
        }
    }
    
    try {
      this->get_deal(seed, session, event, firstBoard, numberOfBoards, response);
    } catch (nlohmann::detail::exception &e) {
        //send a 400 error
        response.send(Pistache::Http::Code::Bad_Request, e.what());
        return;
    } catch (std::exception &e) {
        //send a 500 error
        response.send(Pistache::Http::Code::Internal_Server_Error, e.what());
        return;
    }

}

void DealApi::deal_api_default_handler(const Pistache::Rest::Request &, Pistache::Http::ResponseWriter response) {
    response.send(Pistache::Http::Code::Not_Found, "The requested method does not exist");
}

}
}
}
}

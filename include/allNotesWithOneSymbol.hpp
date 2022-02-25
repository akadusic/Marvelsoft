#include <stdlib.h>
#include <boost/any.hpp>
#include <jsoncpp/json/json.h>
#include <future>

void allNotesWithOneSymbol(std::promise<std::vector<boost::any>>&& fifthPromise,std::string symbol,Json::Value parsedDocument);

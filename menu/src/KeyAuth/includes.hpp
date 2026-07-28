#pragma once

#include <Windows.h>
#include <iostream>
#include <Security/Api/json.hpp>

#pragma comment (lib, "advapi32.lib")
#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "wldap32.lib" )
#pragma comment(lib, "crypt32.lib" )
#pragma comment(lib, "Ws2_32.lib")

#define CURL_STATICLIB
#include <Security/Api/curl/curl.h>

#include "utils.hpp"
#ifndef NTLM_NTLM_HPP
#define NTLM_NTLM_HPP

#include <string>

#include <ntlm.h>

std::string base64_encode(const std::string&);

std::string base64_decode(const std::string&);

#endif //NTLM_NTLM_HPP

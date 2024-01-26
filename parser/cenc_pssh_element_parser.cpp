/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "cenc_pssh_element_parser.h"
#include "cenc_pssh.h"
#include "utils.h"

namespace dash {
namespace mpd {

bool CencPsshElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {

  return true;
}

bool CencPsshElementParser::ParseTextData(ElementBase *elem_out,
    const std::string sub_element, const char *content, int length) {
  CencPssh *elem = static_cast<CencPssh*>(elem_out);      
  elem->pssh_= {content, length};
  return true;
}

bool CencPsshElementParser::ParseEnd(const std::string &element_name,
    ElementBase *elem_out, const GetExternalAttributes &get_attribs) {
  return true;
}

ElementBase* CencPsshElementParser::CreateElement(
    const std::string &element) const {
  return new CencPssh();
}

} // namespace mpd
} // namespace dash
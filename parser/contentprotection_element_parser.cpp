/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "contentprotection_element_parser.h"
#include "contentprotection.h"
#include "cenc_pssh_element_parser.h"
#include "cenc_pssh.h"


namespace dash {
namespace mpd {

bool ContentProtectionElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  ContentProtection *elem = static_cast<ContentProtection*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("robustness") {
      elem->robustness_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("refId") {
      elem->ref_id_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("ref") {
      elem->ref_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      DescriptorElementParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* ContentProtectionElementParser::CreateElement(
    const std::string &element) const {
  return new ContentProtection();
}

void ContentProtectionElementParser::AttachChildElementToParent(ElementBase *parent,
    ElementBase *child) {
  ContentProtection *cp_elem = static_cast<ContentProtection*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "CencPssh") {
    cp_elem->cenc_pssh_ = static_cast<CencPssh*>(child);
  } else {
    ElementBaseParser::AttachChildElementToParent(parent, child);
  }
}  

ElementBaseParser* ContentProtectionElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  // Create parsers for the supported children under this node
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "cenc:pssh") {
    parser = std::make_unique < CencPsshElementParser > (name, parent);
  } else {
    return ElementBaseParser::CreateChildParser(name, parent);
  }

  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
